#ifndef EARPC_EARPC_H
# define EARPC_EARPC_H

# include <cstdint>
# include <fstream>
# include <thread>
# include <pthread.h>
# include <chrono>
# include <types/integer.h>
# include <net/ipv4_address.h>
# include <net/algorithm.h>
# include <earpc/buffer/command.h>
# include <earpc/buffer/incoming_call.h>
# include <earpc/buffer/outgoing_call.h>
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
		};

		typedef env_buffers env_feedback;

		typedef env_buffers env_send;

		struct env_expiry : public env_buffers
		{
			typedef typename process::feedback<env_feedback> proc_feedback;

			typedef typename process::send<env_send>         proc_send;
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

		typedef typename env_recv::buf_incoming_call buf_incoming_call;

		typedef typename env_recv::buf_outgoing_call buf_outgoing_call;

	public:
		typedef typename env_recv::command_id_type command_id_type;
	private:

		static std::thread *main_process;

		static std::ifstream urandom;

		static void start()
		{
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

		static call_id_type generate_call_id(net::ipv4_address ip)
		{
			call_id_type r;
			do
			{
				urandom.read(reinterpret_cast<char*>(&r),sizeof(call_id_type));
			} while(
				buf_incoming_call::find(ip,r) != buf_incoming_call::end() ||
				buf_outgoing_call::find(ip,r) != buf_outgoing_call::end()
			);
			return r;
		}


	public:
		template<typename Treturn>
		using call_handle = typename proc_recv::template call_handle<Treturn>;

		template<typename Treturn, typename Targ>
		static void set_command(
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
		{
			buf_outgoing_call::lock();
			buf_incoming_call::lock();
			call_id_type cid = generate_call_id(ip);
			buf_outgoing_call::push(
				ip,cmd,cid,&arg,sizeof(Targ),c
			);
			buf_incoming_call::unlock();
			buf_outgoing_call::unlock();
//			std::cout << "\e[37;01m - \e[0mearpc: initiating send for call " << std::hex << cid << std::endl;
			proc_send::notify(ip,1234,cid,cmd,&arg,sizeof(Targ));
			proc_expiry::notify();
		}

		template<typename Targ>
		static void call(
			net::ipv4_address ip,
			command_id_type cmd,
			const Targ &arg,
			void(*c)(net::ipv4_address,command_id_type,const std::string&)
		)
		{
			buf_outgoing_call::lock();
			buf_incoming_call::lock();
			call_id_type cid = generate_call_id(ip);
			buf_outgoing_call::push(
				ip,cmd,cid,&arg,sizeof(Targ),c
			);
			buf_incoming_call::unlock();
			buf_outgoing_call::unlock();
//			std::cout << "\e[37;01m - \e[0mearpc: initiating send for call " << std::hex << cid << std::endl;
			proc_send::notify(ip,1234,cid,cmd,&arg,sizeof(Targ));
			proc_expiry::notify();
		}

		static void init()
		{
			main_process = new std::thread(start);

#ifdef __linux__			
			pthread_setname_np(main_process->native_handle(),"earpc master");
#endif
		}

		static void uninit()
		{
			main_process->join();
			delete main_process;
		}
	};

	template<typename c>
	std::ifstream earpc<c>::urandom("/dev/urandom");

	template<typename c>
	std::thread *earpc<c>::main_process;
}
#endif
