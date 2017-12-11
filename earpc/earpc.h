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
# include <earpc/buffer/command.h>
# include <earpc/buffer/incoming_call.h>
# include <earpc/buffer/outgoing_call.h>
# include <earpc/buffer/parking_call.h>
# include <earpc/process/feedback.h>
# include <earpc/process/send.h>
# include <earpc/process/recv.h>
# include <earpc/process/expiry.h>
namespace earpc
{
	template<typename TConfig>
	class earpc
	{

		struct env_base
		{
			typedef std::chrono::high_resolution_clock    clock;

			typedef typename clock::time_point            time_point;

			typedef typename TConfig::command_id_type     command_id_type;

			typedef typename TConfig::call_id_type        call_id_type;
#pragma pack(push,1)
			class
			earpc_header_type
			{
			public:
				command_id_type command_id;

				call_id_type    call_id;

				uint16_t        checksum;

				bool checksum_create()
				{
					*const_cast<volatile uint16_t*>(&checksum) = 0;
					checksum = ::types::integer::htons(net::algorithm::checksum_finish(
						net::algorithm::checksum_add(this,sizeof(earpc_header_type))
					));
					return true;
				}

				bool checksum_verify() const
				{ return net::algorithm::checksum_verify(this,sizeof(earpc_header_type)); }
			};
#pragma pack(pop)
			struct call_handle_base
			{
				const call_id_type call_id;

				const net::ipv4_address ip;

				const uint16_t          port;

				call_handle_base(
					net::ipv4_address i,
					uint16_t p,
					call_id_type cid
				)
					: ip(i)
					, port(p)
					, call_id(cid)
				{}
			};

			constexpr static udp &conn = TConfig::connection;

			static const uint32_t call_timeout = 3200;
		};

		struct env_buffers : public env_base
		{
			typedef typename wic::earpc::buffer::template command<env_base>        buf_command;

			typedef typename wic::earpc::buffer::template incoming_call<env_base>  buf_incoming_call;

			typedef typename wic::earpc::buffer::template outgoing_call<env_base>  buf_outgoing_call;

			typedef typename wic::earpc::buffer::template parking_call<env_base>   buf_parking_call;

		};

		typedef env_buffers env_feedback;

		typedef env_buffers env_send;

		static void outgoing_call_finished(net::ipv4_address);

		struct env_expiry : public env_buffers
		{
			typedef typename process::feedback<env_feedback> proc_feedback;

			typedef typename process::send<env_send>         proc_send;

			constexpr static void(*call_finished)(net::ipv4_address) = &outgoing_call_finished;
		};

		struct env_recv : public env_expiry
		{
			typedef typename process::expiry<env_expiry>     proc_expiry;

			static const typename env_buffers::command_id_type       command_id_ack = TConfig::command_id_ack;

			static const typename env_buffers::command_id_type       command_id_nak = TConfig::command_id_nak;

			static const typename env_buffers::command_id_type       command_id_return = TConfig::command_id_return;

			static const typename env_buffers::command_id_type       command_id_exception = TConfig::command_id_exception;

		};
		typedef typename process::recv<env_recv>     proc_recv;

		typedef typename env_recv::proc_feedback     proc_feedback;

		typedef typename env_recv::proc_send         proc_send;

		typedef typename env_recv::proc_expiry       proc_expiry;

		typedef typename env_recv::clock             clock;

		typedef typename env_recv::call_id_type      call_id_type;

		typedef typename env_buffers::buf_incoming_call buf_incoming_call;

		typedef typename env_buffers::buf_outgoing_call buf_outgoing_call;

		typedef typename env_buffers::buf_parking_call  buf_parking_call;

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
			std::thread recv(proc_recv::start);
			std::thread expiry(proc_expiry::start);
			
#ifdef __linux__
			pthread_setname_np(feedback.native_handle(),"earpc feedback");
			pthread_setname_np(send.native_handle(),"earpc send");
			pthread_setname_np(recv.native_handle(),"earpc recv");
			pthread_setname_np(expiry.native_handle(),"earpc expiry");
#endif

			recv.join();

			send.join();

			feedback.join();

			expiry.join();
		}

		template<typename T>
		static T get_random()
		{
			static std::default_random_engine generator(
				std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::time_point_cast<std::chrono::nanoseconds>(clock::now()).time_since_epoch()).count()
			);
			static std::uniform_int_distribution<T> distribution(1,-1);
	
			return distribution(generator);
		}

		static call_id_type generate_call_id(net::ipv4_address ip)
		{
			while(true)
			{
				call_id_type r = get_random<call_id_type>();

				if(buf_incoming_call::find(ip,r) != buf_incoming_call::end())
					continue;
				if(buf_outgoing_call::find(ip,r) != buf_outgoing_call::end())
					continue;
				return r;
			}
		}

		static void do_call(
			net::ipv4_address ip,
			command_id_type cmd,
			const void *argp,
			uint16_t argl,
			uint16_t retl,
			void(*c)(net::ipv4_address,command_id_type,const void*)
		)
		{
			buf_outgoing_call::lock();

			if(buf_outgoing_call::has_call_to(ip))
			{
				buf_outgoing_call::unlock();
				journal(journal::debug,"earpc.api.call") <<  "call to remote is ongoing; parking call; command: " << std::hex << cmd <<
					"; target: " << (std::string)ip << journal::end;
				buf_parking_call::lock();
				buf_parking_call::push(ip,cmd,0,argp,argl,retl,c);
				buf_parking_call::unlock();
				return;
			}

			buf_incoming_call::lock();
			call_id_type cid = generate_call_id(ip);
			buf_outgoing_call::push(
				ip,cmd,cid,argp,argl,retl,c
			);
			buf_incoming_call::unlock();
			buf_outgoing_call::unlock();

			journal(journal::debug,"earpc.api.call") <<  "initiating send; command: " << std::hex << cmd <<
				"; target: " << (std::string)ip << "; call id: " << std::hex << cid << journal::end;

			proc_send::notify(ip,1234,cid,cmd,argp,argl);
			proc_expiry::notify();
		}

	public:
		template<typename Treturn>
		using call_handle = typename proc_recv::template call_handle<Treturn>;

		template<typename Treturn, typename Targ>
		static 
		std::enable_if_t<!std::is_same<Treturn,std::string>::value && !std::is_same<Targ,std::string>::value>
		set_command(
			command_id_type id,
			void(*callback)(call_handle<Treturn>,const Targ*)
		)
		{
			env_recv::buf_command::lock();
			env_recv::buf_command::push(
				id,sizeof(Targ),sizeof(Treturn),
				reinterpret_cast<typename env_recv::buf_command::callback_type>(callback)
			);
			env_recv::buf_command::unlock();
		}

		template<typename Treturn>//
		static
		std::enable_if_t<!std::is_same<Treturn,std::string>::value>
		set_command(
			command_id_type id,
			void(*callback)(call_handle<Treturn>,const std::string&)
		)
		{
			env_recv::buf_command::lock();
			env_recv::buf_command::push(
				id,0xffff,sizeof(Treturn),
				reinterpret_cast<typename env_recv::buf_command::callback_type>(callback)
			);
			env_recv::buf_command::unlock();
		}

		template<typename Targ>//
		static
		std::enable_if_t<!std::is_same<Targ,std::string>::value>
		set_command(
			command_id_type id,
			void(*callback)(call_handle<std::string>,const Targ*)
		)
		{
			env_recv::buf_command::lock();
			env_recv::buf_command::push(
				id,sizeof(Targ),0xffff,
				reinterpret_cast<typename env_recv::buf_command::callback_type>(callback)
			);
			env_recv::buf_command::unlock();
		}

		//
		static void set_command(
			command_id_type id,
			void(*callback)(call_handle<std::string>,const std::string&)
		)
		{
			env_recv::buf_command::lock();
			env_recv::buf_command::push(
				id,0xffff,0xffff,
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
		static void call(
			net::ipv4_address ip,
			command_id_type cmd,
			const Targ &arg,
			void(*c)(net::ipv4_address,command_id_type,const Treturn*)
		)
		{ do_call(ip,cmd,&arg,sizeof(Targ),sizeof(Treturn),reinterpret_cast<generic_callback_type>(c)); }

		template<typename Targ>
		static void call(
			net::ipv4_address ip,
			command_id_type cmd,
			const Targ &arg,
			void(*c)(net::ipv4_address,command_id_type,const std::string&)
		)
		{ do_call(ip,cmd,&arg,sizeof(Targ),(uint16_t)-1,reinterpret_cast<generic_callback_type>(c)); }

		template<typename Treturn>
		static void call(
			net::ipv4_address ip,
			command_id_type cmd,
			const std::string &arg,
			void(*c)(net::ipv4_address,command_id_type,const Treturn*)
		)
		{ do_call(ip,cmd,arg.c_str(),arg.size(),sizeof(Treturn),reinterpret_cast<generic_callback_type>(c)); }

		static void call(
			net::ipv4_address ip,
			command_id_type cmd,
			const std::string &arg,
			void(*c)(net::ipv4_address,command_id_type,const std::string&)
		)
		{ do_call(ip,cmd,arg.c_str(),arg.size(),(uint16_t)-1,reinterpret_cast<generic_callback_type>(c)); }

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
	void earpc<c>::outgoing_call_finished(net::ipv4_address ip)
	{
		buf_outgoing_call::lock();

		if(buf_outgoing_call::has_call_to(ip))
		{
			buf_outgoing_call::unlock();
			return;
		}

		typename buf_outgoing_call::record_type r;

		buf_parking_call::lock();
		if(buf_parking_call::pop(ip,r))
		{
			buf_parking_call::unlock();

			buf_incoming_call::lock();
			r.call_id = generate_call_id(ip);
			buf_incoming_call::unlock();

			buf_outgoing_call::push(r);
			buf_outgoing_call::unlock();

			journal(journal::debug,"earpc.api.call") <<  "resuming parked call; command: " << std::hex << r.command_id << 
				"; target: " << (std::string)ip <<
				"; call id: " << std::hex << r.call_id << journal::end;

			proc_send::notify(ip,1234,r.call_id,r.command_id,r.arg,r.arg_size);
			proc_expiry::notify();

		}

		else
		{
			buf_parking_call::unlock();
			buf_outgoing_call::unlock();
		}
	}

}
#endif
