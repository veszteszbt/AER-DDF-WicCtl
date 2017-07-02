#ifndef EARPC_EARPC_H
# define EARPC_EARPC_H
# include <cstdint>
# include <fstream>
# include <thread>
# include <chrono>
# include <types/integer.h>
# include <net/ipv4_address.h>
# include <net/algorithm.h>
# include <earpc/process/feedback.h>
# include <earpc/process/send.h>
# include <earpc/process/recv.h>

namespace earpc
{
	template<typename TConfig>
	class earpc
	{
		struct env
		{
			typedef std::chrono::high_resolution_clock clock;

			typedef typename TConfig::command_id_type command_id_type;

			typedef typename TConfig::call_id_type call_id_type;

			class
			__attribute__((__packed__))
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

			constexpr static udp &conn = TConfig::connection;
		
		};

		typedef env env_feedback;

		typedef env env_send;

		struct env_recv : public env
		{
			typedef typename process::feedback<env_feedback> proc_feedback;

			typedef typename process::send<env_send>         proc_send;

			struct call_handle_base
			{
				const typename env::call_id_type call_id;

				const net::ipv4_address ip;

				const uint16_t          port;

				call_handle_base(
					net::ipv4_address i,
					uint16_t p,
					typename env::call_id_type cid
				)
					: ip(i)
					, port(p)
					, call_id(cid)
				{}
			};

			struct command_record
			{
				typename env::command_id_type command_id;

				uint16_t arg_size;

				uint16_t ret_size;

				void (*callback)(call_handle_base,const void*);

				command_record()
					: callback(0)
				{}

				command_record(
					typename env::command_id_type cmd,
					uint16_t as,
					uint16_t rs,
					void (*c)(call_handle_base,const void*)
				)
					: command_id(cmd)
					, arg_size(as)
					, ret_size(rs)
					, callback(c)
				{}
			};

			typedef std::list<command_record>                command_buffer_type;

			static const typename env::command_id_type       command_id_ack = TConfig::command_id_ack;

			static const typename env::command_id_type       command_id_nak = TConfig::command_id_nak;

			static const typename env::command_id_type       command_id_return = TConfig::command_id_return;

			static const typename env::command_id_type       command_id_exception = TConfig::command_id_exception;

			static command_buffer_type                       command_buffer;
		};
		typedef typename process::recv<env_recv>         proc_recv;

		typedef typename env_recv::proc_feedback         proc_feedback;

		typedef typename env_recv::proc_send             proc_send;

		typedef typename env::clock clock;

		typedef typename env::call_id_type call_id_type;
	public:
		typedef typename env::command_id_type command_id_type;
	private:

		static const uint32_t call_timeout = 1120;

                struct outgoing_call_record
                {
                        net::ipv4_address ip;

                        call_id_type call_id;

                        command_id_type command_id;

                        void (*callback)(void*);

                        const void *arg; 

                        uint16_t arg_size;
                                
                        uint16_t return_size;

                        uint64_t expiry;
                                
                        bool ack_recvd;
                                        
                        bool returned;  


                        outgoing_call_record() {}

                        template<typename Treturn>
                        outgoing_call_record(
                                net::ipv4_address i,
                                command_id_type cmd,
                                call_id_type cid,
                                const void *a,
                                uint16_t as,
                                uint16_t rs,
                                void (*cb)(Treturn*)
                        )       
                                : ip(i)
                                , call_id(cid)
                                , command_id(cmd)
                                , callback(reinterpret_cast<void(*)(void*)>(cb))
                                , arg(a)
                                , arg_size(as)
                                , return_size(rs)
                                , expiry(clock::now()+std::chrono::milliseconds(call_timeout))
                                , ack_recvd(false)
                                , returned(false)
                        {}
                };

		static std::list<outgoing_call_record> outgoing_call_buffer;

		static std::ifstream urandom;

		static void start()
		{
			std::thread feedback(proc_feedback::start);

			std::thread send(proc_send::start);

			std::thread recv(proc_recv::start);

			recv.join();

			send.join();

			feedback.join();
		}

		static call_id_type generate_call_id()
		{
			call_id_type r;
			urandom.read(reinterpret_cast<char*>(&r),sizeof(call_id_type));
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
			// TODO: LOCK!!!!
			env_recv::command_buffer.push_back(
				typename env_recv::command_record(
					id,sizeof(Targ),sizeof(Treturn),
					reinterpret_cast<void(*)(typename env_recv::call_handle_base,const void*)>(callback)
				)
			);
		}

		template<typename Treturn, typename Targ>
		static void call(net::ipv4_address ip, command_id_type cmd, const Targ &arg, void(*c)(Treturn*))
		{
			call_id_type cid = generate_call_id();
			outgoing_call_buffer.push(
				outgoing_call_record(ip,cmd,cid,&arg,sizeof(Targ),sizeof(Treturn),c)
			);
			std::cout << "\e[37;01m - \e[0mearpc: initiating send for call ", << std::hex << cid << std::endl;
			proc_send::notify(ip,1234,cid,cmd,&arg,sizeof(Targ));		
		}

		static std::thread init()
		{ return std::thread(start); }
	};

	template<typename c>
	typename earpc<c>::env_recv::command_buffer_type earpc<c>::env_recv::command_buffer;

	template<typename c>
	std::ifstream earpc<c>::urandom("/dev/urandom");
}
#endif
