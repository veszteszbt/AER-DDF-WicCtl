#ifndef EARPC_EARPC_H
# define EARPC_EARPC_H
# include <cstdint>
# include <thread>
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

		static void start()
		{
			std::thread feedback(proc_feedback::start);

			std::thread send(proc_send::start);

			std::thread recv(proc_recv::start);

			recv.join();

			send.join();

			feedback.join();
		}


	public:
		template<typename Treturn>
		using call_handle = typename proc_recv::template call_handle<Treturn>;

		typedef typename env::command_id_type command_id_type;

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

		static std::thread init()
		{ return std::thread(start); }
	};

	template<typename c>
	typename earpc<c>::env_recv::command_buffer_type earpc<c>::env_recv::command_buffer;
}
#endif
