#ifndef WIC_EARPC_H
# define WIC_EARPC_H
# include <cstdio>
# include <net/ipv4_address.h>
# include <types/vsizeof.h>
# include <pic/emulated/random.h>
# include <wic/earpc/process/feedback.h>
# include <wic/earpc/process/send.h>

namespace wic {
namespace earpc
{
	template<typename TConfig>
	class earpc
	{
		static_assert(
			std::is_integral<typename TConfig::command_id_type>::value,
			"Command id type must be an integral type"
		);
		static_assert(
			std::is_integral<typename TConfig::call_id_type>::value,
			"Call id type must be an integral type"
		);
		static_assert(
			TConfig::command_id_return != TConfig::command_id_exception &&
			TConfig::command_id_ack != TConfig::command_id_exception &&
			TConfig::command_id_ack != TConfig::command_id_return,
			"Return and exception must be distinct command ids"
		);

		struct env
		{

			typedef typename TConfig::logger log;

			typedef typename TConfig::command_id_type command_id_type;

			typedef typename TConfig::call_id_type call_id_type;

			typedef typename TConfig::clock_module clock;

			typedef typename TConfig::iface iface;

			struct
			__attribute__((__packed__))
			earpc_header_type
			{
				command_id_type command_id;
				call_id_type    call_id;
				uint16_t        checksum;
				bool checksum_create()
				{
					*const_cast<volatile uint16_t*>(&checksum) = 0;
					checksum = net::algorithm::checksum_finish(
						net::algorithm::checksum_add(this,sizeof(earpc_header_type))
					);
					return true;
				}

				bool checksum_verify() const
				{ return net::algorithm::checksum_verify(this,sizeof(earpc_header_type)); }
			};

			static const command_id_type command_id_ack = TConfig::command_id_ack;

			static const command_id_type command_id_nak = TConfig::command_id_nak;

			static const command_id_type command_id_return = TConfig::command_id_return;

			static const command_id_type command_id_exception = TConfig::command_id_exception;

			static const uint16_t resend_timeout = 70;

			static const uint16_t udp_port = TConfig::udp_port;
		};

		typedef typename TConfig::logger log;

		typedef typename TConfig::iface iface;

		typedef typename process::feedback<env> proc_feedback;

		typedef typename process::send<env>     proc_send;

		typedef typename env::command_id_type   command_id_type;

		typedef typename env::call_id_type      call_id_type;

		typedef typename env::earpc_header_type earpc_header_type;

		static const command_id_type command_id_ack = TConfig::command_id_ack;

		static const command_id_type command_id_nak = TConfig::command_id_nak;

		static const command_id_type command_id_return = TConfig::command_id_return;

		static const command_id_type command_id_exception = TConfig::command_id_exception;
		
		static const uint16_t udp_port = TConfig::udp_port;

	public:
		struct call_handle_base
		{
			const net::ipv4_address remote_ip;

			const uint16_t          remote_port;

			const command_id_type   command_id;

			const call_id_type      call_id;

			operator bool()
			{ return remote_ip == 0 && remote_port == 0 && command_id == 0 && call_id == 0; }

			call_handle_base()
				: remote_ip(0,0,0,0)
				, remote_port(0)
				, command_id(0)
				, call_id(0)
			{}

			call_handle_base(
				net::ipv4_address ip,
				uint16_t port,
				command_id_type cmd,
				call_id_type cid
			)
				: remote_ip(ip)
				, remote_port(port)
				, command_id(cmd)
				, call_id(cid)
			{}
		
		};


		template<typename Treturn>
		struct call_handle : public call_handle_base
		{
			call_handle(
				net::ipv4_address ip,
				uint16_t port,
				command_id_type cmd,
				call_id_type cid
			) : call_handle_base(ip,port,cmd,cid) {}

			typename std::enable_if_t<!std::is_same<Treturn,void>::value>
			respond(const Treturn &rv)
			{
				proc_send::add(
					call_handle_base::remote_ip,
					call_handle_base::remote_port,
					command_id_return,
					call_handle_base::call_id,
					&rv, sizeof(Treturn)
				);
			}
		};
	private:
		struct command_record
		{
			typedef void (*callback_type)(call_handle_base, const void*);
			command_id_type command_id;
			uint16_t arg_size;
			uint16_t ret_size;
			callback_type callback;

			command_record() {}

			command_record(command_id_type cid, uint16_t as, uint16_t rs, callback_type c)
				: command_id(cid)
				, arg_size(as)
				, ret_size(rs)
				, callback(c)
			{}
		};

		typedef ::container::circbuf<
			command_record,
			64,
			false,false
		> command_buffer_type;

		static command_buffer_type command_buffer;
	public:

		template<typename Treturn,typename Targ>
		using command_handler_type = void (*)(call_handle<Treturn>,const Targ*);

		template<typename Treturn, typename Targ>
		static bool set_command(command_id_type cmd, command_handler_type<Treturn,Targ> handler)
		{
			if(
				cmd == command_id_ack ||
				cmd == command_id_nak ||
				cmd == command_id_return ||
				cmd == command_id_exception
			) {
				log::println("\e[31;01m - \e[0mwic earpc: error: tried to add command with reserved id");
				return false;
			}

			for(
				typename command_buffer_type::iterator i = command_buffer.begin();
				i != command_buffer.end();
				++i
			)
				if(i->command_id == cmd)
				{
					if(handler)
					{
						log::println("\e[32;01m - \e[0mwic earpc: handler changed for command id ",cmd);
						i->arg_size = ::types::vsizeof<Targ>::value;
						i->ret_size = ::types::vsizeof<Treturn>::value;
						i->callback = reinterpret_cast<typename command_record::callback_type>(handler);
					}
					else
					{
						log::println("\e[32;01m - \e[0mwic earpc: command id ",cmd," removed");
						command_buffer.remove(i);	
					}
					return true;
				}

			command_buffer.push(command_record(
				cmd,
				::types::vsizeof<Targ>::value,
				::types::vsizeof<Treturn>::value,
				reinterpret_cast<typename command_record::callback_type>(handler)
			));
		}
	private:

		struct incoming_call_record : public earpc_header_type
		{
			net::ipv4_address ip;

			uint16_t          sport;

			bool              ack_sent;

			incoming_call_record() {}

			incoming_call_record(net::ipv4_address i, uint16_t sp, const earpc_header_type &h)
				: earpc_header_type(h)
				, ip(i)
				, sport(sp)
				, ack_sent(false)
			{}
		};

		typedef ::container::circbuf<
			incoming_call_record,
			32,
			true,true
		> incoming_call_buffer_type;

		static incoming_call_buffer_type incoming_call_buffer;


		struct outgoing_call_record
		{
			net::ipv4_address ip;

			call_id_type call_id;

			command_id_type command_id;

			void (*callback)(void*);

			const void *arg;

			uint16_t arg_size;

			uint16_t return_size;

			bool ack_recvd;

			bool returned;


			outgoing_call_record() {}

			template<typename Treturn>
			outgoing_call_record(
				net::ipv4_address i,
				call_id_type cid,
				command_id_type cmd,
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
				, ack_recvd(false)
				, returned(false)
			{}

		};

		typedef ::container::circbuf<
			outgoing_call_record,
			32,
			false,false
		> outgoing_call_buffer_type;

		static outgoing_call_buffer_type outgoing_call_buffer;

		static call_id_type generate_call_id()
		{ return pic::emulated::random::get<call_id_type>(); }
	


	public:
		static void init()
		{
			command_buffer.clear();
			proc_feedback::init();
			proc_send::init();

			incoming_call_buffer.clear();
			outgoing_call_buffer.clear();

			iface::udp_set_service(udp_port,process);
		}

		static uint8_t call_buffer[];

		
		template<typename Treturn, typename Targ>
		static call_handle_base call(net::ipv4_address ip, command_id_type cmd, const Targ &arg, void (*c)(Treturn*))
		{ 
			if(outgoing_call_buffer.full())
				return call_handle_base();

			const call_id_type cid = generate_call_id();

			const void *argp = const_cast<typename std::remove_cv_t<Targ>*>(&arg);

			if(!outgoing_call_buffer.push(outgoing_call_record(
				ip,cmd,cid,
				argp,
				sizeof(Targ),sizeof(Treturn),c
			)))
			{
				log::println("\e[31;01 - \e[0mwic earpc call: queue is full");
				return call_handle_base();
			}


			log::println("\e[37;01 - \e[0mwic earpc call: enqueued for send");
			proc_send::add(
				ip,
				udp_port,
				cmd,
				cid,
				argp, sizeof(Targ)
			);
		}


		static void process(
			net::ipv4_address src,
			net::ipv4_address dst,
			uint16_t sport,
			const void *buffer,
			uint16_t size
		) {
			earpc_header_type h = *reinterpret_cast<const earpc_header_type*>(buffer);
			if(!h.checksum_verify())
			{
				log::println("\e[33;01m - \e[0mwic earpc recv: dropping due to checksum failure");
			}

			else switch(h.command_id)
			{
				case command_id_ack:
					log::template println<16>("\e[32;01m - \e[0mwic earpc recv: ack on ",h.call_id);
					proc_send::remove(h.call_id);
					break;

				case command_id_nak:
					proc_send::remove(h.call_id);
					if(h.command_id == command_id_return)
					{
						log::template println<16>(
							"\e[31;01m - \e[0mwic earpc recv: error: nak packet on return of call ",
							h.call_id
						);
					}

					else
					{
						log::template println<16>(
							"\e[37;01m - \e[0mwic earpc recv: nak packet; call id is ",
							h.call_id
						);
					}
					break;

				case command_id_return:
					log::template println<16>(
						"\e[37;01m - \e[0mwic earpc recv: return packet; call id is ",
						h.call_id
					);
					for(
						typename outgoing_call_buffer_type::iterator i = outgoing_call_buffer.begin();
						i != outgoing_call_buffer.end();
						++i
					)
						if(i->call_id == h.call_id)
						{
							proc_feedback::notify(src,sport,i->call_id,command_id_ack);
//							const uint16_t ret_size =  size - sizeof(earpc_header_type);
							i->callback(
								reinterpret_cast<uint8_t*>(const_cast<void*>(buffer)) +
								sizeof(earpc_header_type)
							);
							outgoing_call_buffer.remove(i);
							return;
						}

					proc_feedback::notify(src,sport,h.call_id,command_id_nak);
					break;

				case command_id_exception:
					log::template println<16>(
						"\e[37;01m - \e[0mwic earpc recv: exception packet; call id is ",
						h.call_id
					);
					proc_feedback::notify(src,sport,h.call_id,command_id_ack);
					break;

				default:
					for(
						typename incoming_call_buffer_type::iterator i = incoming_call_buffer.begin();
						i != incoming_call_buffer.end();
						++i
					)
						if(i->call_id == h.call_id)
						{
							if(i->command_id == h.command_id && i->checksum == h.checksum)
								proc_feedback::notify(src,sport,i->call_id,command_id_ack);

							else
							{
								log::template println(
									"\e[33;01m - \e[0mwic earpc recv: duplicate call id ",
									i->call_id
								);
								proc_feedback::notify(src,sport,i->call_id,command_id_nak);
							}
							return;
						}

					for(
						typename outgoing_call_buffer_type::iterator i = outgoing_call_buffer.begin();
						i != outgoing_call_buffer.end();
						++i
					)
						if(i->call_id == h.call_id)
						{
							log::template println<16>(
								"\e[33;01m - \e[0mwic earpc recv: duplicate call id ",
								i->call_id
							);
							proc_feedback::notify(src,sport,i->call_id,command_id_nak);
							return;
						}
					
					for(
						typename command_buffer_type::iterator i = command_buffer.begin();
						i != command_buffer.end();
						++i
					)
						if(i->command_id == h.command_id)
						{

							log::template println<16>(
								"\e[37;01m - \e[0mwic earpc recv: call packet; call id is ",
								h.call_id,"; command id is ",h.command_id
							);

							const uint16_t arg_size = size-sizeof(earpc_header_type);

							if(i->arg_size != arg_size)
							{
								log::println(
									"\e[33;01m - \e[0mwic earpc recv: argument size mismatch; "
									"expected ",i->arg_size,"; got ",arg_size
								);
								proc_feedback::notify(src,sport,h.call_id,command_id_nak);
								return;
							}

							proc_feedback::notify(src,sport,h.call_id,command_id_ack);

							i->callback(
								call_handle_base(src,sport,h.command_id,h.call_id),
								reinterpret_cast<const uint8_t*>(buffer)+sizeof(earpc_header_type)
							);
							return;
						}

					log::println("\e[33;01m - \e[0mwic earpc recv: unknown command id ",h.command_id);
					proc_feedback::notify(src,sport,h.call_id,command_id_nak);
					break;
			}
		}
	};

	template<typename c>
	typename earpc<c>::command_buffer_type earpc<c>::command_buffer;

	template<typename c>
	typename earpc<c>::incoming_call_buffer_type earpc<c>::incoming_call_buffer;

	template<typename c>
	typename earpc<c>::outgoing_call_buffer_type earpc<c>::outgoing_call_buffer;

	template<typename c>
	uint8_t earpc<c>::call_buffer[768];
}}
#endif
