#ifndef EARPC_EARPC_H
# define EARPC_EARPC_H
# include <journal.h>
# include <type_traits>
# include <cstdint>
# include <random>
# include <thread>
# include <pthread.h>
# include <chrono>
# include <types/integer.h>
# include <net/ipv4_address.h>
# include <net/algorithm.h>
# include <earpc/reason.h>
# include <earpc/types/header.h>
# include <earpc/types/call_handle.h>
# include <earpc/buffer/command.h>
# include <earpc/buffer/incoming_call.h>
# include <earpc/buffer/outgoing_call.h>
# include <earpc/serializer.h>
# include <earpc/process/feedback.h>
# include <earpc/process/send.h>
# include <earpc/process/callback.h>
# include <earpc/process/recv.h>
# include <earpc/process/expiry.h>
# include <earpc/config.h>
namespace earpc
{
	template<typename TConfig>
	class earpc
	{
		struct env_base
		{
			typedef std::chrono::high_resolution_clock    clock;

			typedef typename clock::time_point            time_point;

			typedef typename TConfig::cfg_command_id_type     command_id_type;

			typedef typename TConfig::cfg_call_id_type        call_id_type;

			static const uint16_t earpc_local_port      = TConfig::cfg_local_port;

			static const uint16_t earpc_remote_port     = TConfig::cfg_remote_port;

			static const uint32_t call_timeout          = TConfig::cfg_call_timeout;

			constexpr static udp &conn                  = TConfig::cfg_connection;
		};

		struct env_types : public env_base
		{
			typedef types::header<env_base>               header_type;

			typedef types::call_record<env_base>          call_record;

			typedef types::incoming_call_record<env_base> incoming_call_record;

			typedef types::outgoing_call_record<env_base> outgoing_call_record;


			typedef types::call_handle<env_base>          call_handle_base;

			typedef types::incoming_call_handle<env_base> incoming_call_handle_base;

			typedef types::outgoing_call_handle<env_base> outgoing_call_handle_base;

		};

		struct env_buffers : public env_types
		{
			typedef typename wic::earpc::buffer::template command<env_types>        buf_command;

			typedef typename wic::earpc::buffer::template incoming_call<env_types>  buf_incoming_call;

			typedef typename wic::earpc::buffer::template outgoing_call<env_types>  buf_outgoing_call;
		};


		typedef env_buffers env_feedback;

		typedef env_buffers env_send;

		typedef env_buffers env_callback;

		static void outgoing_call_finished(net::ipv4_address);

		static void outgoing_call_rerouted(net::ipv4_address,net::ipv4_address);

		struct env_expiry : public env_buffers
		{
			typedef typename process::feedback<env_feedback> proc_feedback;

			typedef typename process::send<env_send>         proc_send;

			typedef typename process::callback<env_callback> proc_callback;

			constexpr static void(*on_outgoing_call_finished)(net::ipv4_address) = &outgoing_call_finished;

			constexpr static void(*on_outgoing_call_rerouted)(net::ipv4_address,net::ipv4_address) = &outgoing_call_rerouted;
		};

		struct env_recv : public env_expiry
		{
			typedef typename process::expiry<env_expiry>       proc_expiry;

			static const typename env_base::command_id_type command_id_ack = TConfig::cfg_command_id_ack;

			static const typename env_base::command_id_type command_id_nak = TConfig::cfg_command_id_nak;

			static const typename env_base::command_id_type command_id_return = TConfig::cfg_command_id_return;

			static const typename env_base::command_id_type command_id_exception = TConfig::cfg_command_id_exception;

		};
		typedef typename process::recv<env_recv>     proc_recv;

		typedef typename env_recv::proc_callback     proc_callback;

		typedef typename env_recv::proc_feedback     proc_feedback;

		typedef typename env_recv::proc_send         proc_send;

		typedef typename env_recv::proc_expiry       proc_expiry;

		typedef typename env_recv::clock             clock;

		typedef typename env_recv::call_id_type      call_id_type;

		typedef typename env_buffers::buf_incoming_call buf_incoming_call;

		typedef typename env_buffers::buf_outgoing_call buf_outgoing_call;

		typedef typename env_types::outgoing_call_handle_base outgoing_call_handle_base;

		typedef void(*generic_callback_type)(net::ipv4_address,typename env_buffers::command_id_type,const void*);

	public:
		typedef typename env_recv::command_id_type command_id_type;
	private:

		static std::thread *master_process;

		static void start()
		{
			journal(journal::debug,"earpc.process.master") << "initializing" << journal::end;
			std::thread feedback(proc_feedback::start);
			std::thread send(proc_send::start);
			proc_callback::init();
			std::thread recv(proc_recv::start);
			std::thread expiry(proc_expiry::start);
			
#ifdef __linux__
			pthread_setname_np(feedback.native_handle(),"earpc feedback");
			pthread_setname_np(send.native_handle(),"earpc send");
			pthread_setname_np(recv.native_handle(),"earpc recv");
			pthread_setname_np(expiry.native_handle(),"earpc expiry");
#endif

			recv.join();

			expiry.join();

			proc_callback::uninit();

			send.join();

			feedback.join();

		}

		template<typename T>
		static T get_random()
		{
			static std::default_random_engine generator(::types::time::nsec(clock::now()));

			static std::uniform_int_distribution<T> distribution(1,-1);
	
			return distribution(generator);
		}

		static call_id_type generate_call_id()
		{
			while(true)
			{
				call_id_type r = get_random<call_id_type>();

				if(buf_incoming_call::find(r) != buf_incoming_call::end())
					continue;
				if(buf_outgoing_call::find(r) != buf_outgoing_call::end())
					continue;
				return r;
			}
		}

		static call_id_type do_call(
			net::ipv4_address ip,
			command_id_type cmd,
			const std::vector<uint8_t> &arg,
			uint16_t retl,
			typename buf_outgoing_call::callback_type c
		)
		{
			buf_outgoing_call::lock();
			buf_incoming_call::lock();
			call_id_type cid = generate_call_id();
			buf_incoming_call::unlock();

			bool parked = (buf_outgoing_call::find_first_active_to(ip) != buf_outgoing_call::end());
			buf_outgoing_call::push(c,parked,ip,cmd,cid,arg.data(),arg.size(),retl);
			buf_outgoing_call::unlock();

			if(parked)
				journal(journal::debug,"earpc.call.outgoing") <<
					"call id: " << std::hex << cid <<
					"; command: " << std::hex << cmd <<
					"; target: " << (std::string)ip << 
					"; call to target is ongoing; parking call" <<
					journal::end;

			else
			{
				journal(journal::trace,"earpc.call.outgoing") <<
					"call id: " << std::hex << cid <<
					"; command: " << std::hex << cmd <<
					"; target: " << (std::string)ip << 
					"; initiating send" <<
					journal::end;

				proc_send::notify(ip,cid,cmd,arg.data(),arg.size());
				proc_expiry::notify();
			}
			return cid;
		}

	public:
		template<typename Treturn, typename Targ>
		using incoming_call_handle = typename proc_recv::template incoming_call_handle<Treturn,Targ>;

		template<typename Treturn, typename Targ>
		using outgoing_call_handle = typename proc_recv::template outgoing_call_handle<Treturn,Targ>;

		template<typename Treturn, typename Targ>
		static void
		set_command(
			command_id_type id,
			void(*callback)(incoming_call_handle<Treturn,Targ>)
		)
		{
			env_recv::buf_command::lock();
			env_recv::buf_command::push(
				id,
				std::is_same<std::decay_t<Targ>,std::string>::value ? 0xffff : sizeof(Targ),
				std::is_same<std::decay_t<Treturn>,std::string>::value ? 0xffff : sizeof(Treturn),
				reinterpret_cast<typename env_recv::buf_command::callback_type>(callback)
			);
			env_recv::buf_command::unlock();
		}

		static void clear_command(command_id_type id)
		{
			typename env_recv::buf_command::iterator i = env_recv::buf_command::find(id);
			if(i != env_recv::buf_command::end())
				env_recv::buf_command::erase(i);
		}

		template<typename Treturn, typename Targ>
		static call_id_type call(
			net::ipv4_address ip,
			command_id_type cmd,
			const Targ &arg,
			void(*c)(outgoing_call_handle<Treturn,Targ>)
		)
		{
			std::vector<uint8_t> argv;
			if(!serializer<Targ>::serialize(arg,argv))
			{
				journal(journal::critical,"earpc.call.outgoing") <<
					"; command: " << std::hex << cmd <<
					"; target: " << (std::string)ip << 
					"; unable to serialize argument; returning failure" <<
					journal::end;
				return 0;
			}

			return do_call(
				ip,cmd,argv,
				serializer<Treturn>::size(),
				reinterpret_cast<typename buf_outgoing_call::callback_type>(c)
			);
		}

		static bool cancel(call_id_type cid)
		{
			buf_outgoing_call::lock();
			auto call = buf_outgoing_call::find(cid);
			if(call == buf_outgoing_call::end())
			{
				buf_outgoing_call::unlock();
				journal(journal::warning,"earpc.call.outgoing") <<
					"call id: " << std::hex << cid <<
					"; could not find call to cancel" <<
					journal::end;
				return false;
			}
			proc_send::remove(cid);

			journal(journal::debug,"earpc.call.outgoing") <<
				"call id: " << std::hex << call->call_id <<
				"; command: " << std::hex << call->command_id <<
				"; target: " << (std::string)call->ip <<
				"; cancelled" <<
				journal::end;

			outgoing_call_handle_base handle(*call,0,0,reason::cancelled);
			auto f = call->callback;
			buf_outgoing_call::erase(call);
			outgoing_call_finished(handle.ip);
			buf_outgoing_call::unlock();
			f(handle);
			return true;
		}

		static bool reroute(call_id_type cid, net::ipv4_address new_ip)
		{
			buf_outgoing_call::lock();
			auto call = buf_outgoing_call::find(cid);
			if(call == buf_outgoing_call::end())
			{
				buf_outgoing_call::unlock();
				journal(journal::warning,"earpc.call.outgoing") <<
					"call id: " << std::hex << cid <<
					"; could not find call to reroute" <<
					journal::end;
				return false;
			}

			if(call->ip == new_ip)
			{
				journal(journal::warning,"earpc.call.outgoing") <<
					"call id: " << std::hex << call->call_id <<
					"; command: " << std::hex << call->command_id <<
					"; target: " << (std::string)call->ip <<
					"; reroute requested to current address" <<
					journal::end;
				buf_outgoing_call::unlock();
				return false;
			}

			proc_send::reroute(cid,new_ip);
			proc_feedback::reroute(cid,new_ip);
			call->ip = new_ip;
			journal(journal::debug,"earpc.call.outgoing") <<
				"call id: " << std::hex << call->call_id <<
				"; command: " << std::hex << call->command_id <<
				"; target: " << (std::string)call->ip <<
				"; orig target: " << (std::string)call->orig_ip <<
				"; rerouted" <<
				journal::end;

			buf_outgoing_call::unlock();
			return true;
		}

		static void init()
		{
			master_process = new std::thread(start);

#ifdef __linux__			
			pthread_setname_np(master_process->native_handle(),"earpc master");
#endif
			
		}

		static void uninit()
		{
			master_process->join();
			delete master_process;
		}
	};

	template<typename c>
	std::thread *earpc<c>::master_process;

	template<typename c>
	void earpc<c>::outgoing_call_rerouted(net::ipv4_address old_ip, net::ipv4_address new_ip)
	{
		if(buf_outgoing_call::find_first_active_to(old_ip) != buf_outgoing_call::end())
			return;

		auto call = buf_outgoing_call::find_first_parked_to(old_ip);
		if(call != buf_outgoing_call::end())
		{
			journal(journal::trace,"earpc.call.outgoing") <<
				"; call id: " << std::hex << call->call_id <<
				"; command: " << std::hex << call->command_id <<
				"; target: " << (std::string)call->ip <<
				"resuming parked call" <<
				journal::end;

			call->parked = false;
			call->reset_expiry();
			proc_send::notify(*call);
			proc_expiry::notify();
		}
	}

	template<typename c>
	void earpc<c>::outgoing_call_finished(net::ipv4_address ip)
	{
		if(buf_outgoing_call::find_first_active_to(ip) != buf_outgoing_call::end())
			return;

		auto call = buf_outgoing_call::find_first_parked_to(ip);
		if(call != buf_outgoing_call::end())
		{
			journal(journal::trace,"earpc.call.outgoing") <<
				"; call id: " << std::hex << call->call_id <<
				"; command: " << std::hex << call->command_id <<
				"; target: " << (std::string)ip <<
				"resuming parked call" <<
				journal::end;

			call->parked = false;
			call->reset_expiry();
			proc_send::notify(*call);
			proc_expiry::notify();
		}
	}

	typedef earpc<default_config> default_earpc;

}
#endif
