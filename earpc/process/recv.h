#ifndef EARPC_PROCESS_RECV_H
# define EARPC_PROCESS_RECV_H
#include <thread>
#include <functional>
namespace earpc {
namespace process
{
	template<typename TEnv>
	class recv
	{
		typedef typename TEnv::call_id_type        call_id_type;

		typedef typename TEnv::command_id_type     command_id_type;

		typedef typename TEnv::earpc_header_type   earpc_header_type;

		typedef typename TEnv::buf_command         buf_command;

		typedef typename TEnv::buf_incoming_call   buf_incoming_call;

		typedef typename TEnv::buf_outgoing_call   buf_outgoing_call;

		typedef typename TEnv::call_handle_base    call_handle_base;

		typedef typename TEnv::proc_feedback       proc_feedback;

		typedef typename TEnv::proc_send           proc_send;

		typedef typename TEnv::proc_expiry         proc_expiry;


		static const command_id_type command_id_ack          = TEnv::command_id_ack;

		static const command_id_type command_id_nak          = TEnv::command_id_nak;

		static const command_id_type command_id_return       = TEnv::command_id_return;

		static const command_id_type command_id_exception    = TEnv::command_id_exception;
		constexpr static ::earpc::udp &conn                  = TEnv::conn;

		static uint8_t *buffer;

		static void process_return(net::ipv4_address ip,uint16_t port, uint16_t size)
		{
			earpc_header_type &h = *reinterpret_cast<earpc_header_type*>(buffer);

			buf_outgoing_call::lock();
			for(
				typename buf_outgoing_call::iterator i = buf_outgoing_call::begin();
				i != buf_outgoing_call::end();
				++i
			)
				if(i->call_id == h.call_id && i->ip == ip)
				{
					const command_id_type cmd = i->command_id;
					const typename buf_outgoing_call::callback_type f = i->callback;
					if(i->return_size == 0xffff)
					{
						proc_feedback::notify(
							ip,
							port,
							h.call_id,
							command_id_ack
						);
						buf_outgoing_call::erase(i);
						buf_outgoing_call::unlock();

						std::string r(
							reinterpret_cast<char*>(buffer+sizeof(earpc_header_type)),
							size-sizeof(earpc_header_type)
						);
					
						f(ip,cmd,reinterpret_cast<void*>(&r));
						return;
					}

					else if((size - sizeof(earpc_header_type)) == i->return_size)
					{
						proc_feedback::notify(
							ip,
							port,
							h.call_id,
							command_id_ack
						);
						buf_outgoing_call::erase(i);
						buf_outgoing_call::unlock();

						f(
							ip,cmd,
							reinterpret_cast<void*>(buffer+sizeof(earpc_header_type))
						);
						return;
					} 

					else
					{
						buf_outgoing_call::erase(i);
						buf_outgoing_call::unlock();
						proc_feedback::notify(
							ip,
							port,
							h.call_id,
							command_id_nak
						);
						f(ip,cmd,0);
						return;

					}
				}

			buf_outgoing_call::unlock();
			proc_feedback::notify(
				ip,
				port,
				h.call_id,
				command_id_nak
			);
		}

		static void process_call(net::ipv4_address ip, uint16_t port, uint16_t size)
		{
			earpc_header_type &h = *reinterpret_cast<earpc_header_type*>(buffer);

			buf_command::lock();
			typename buf_command::iterator i = buf_command::find(h.command_id);
			if(i == buf_command::end())
			{
				buf_command::unlock();
/*				proc_feedback::notify(
					ip,
					port,
					h.call_id,
					command_id_nak
				);
*/
				journal(journal::error,"earpc.process.recv.call") << "unknown command" << std::endl <<
					"command: " << std::hex << h.command_id << std::endl <<
					" caller: " << (std::string)ip << std::endl <<
					"call id: " << std::hex << h.call_id << std::endl <<
					journal::end;
				return;
			}


			if(i->arg_size != size-sizeof(earpc_header_type) && i->arg_size!=0xffff)
			{ 
				buf_command::unlock();
				proc_feedback::notify(
					ip,
					port,
					h.call_id,
					command_id_nak
				);
				journal(journal::error,"earpc.process.recv.call") << "argument size mismatch" << std::endl <<
					"expected" << std::dec << i->arg_size <<
					"; received " << (size-sizeof(earpc_header_type)) << std::endl <<
					"command: " << std::hex << h.command_id << std::endl <<
					" caller: " << (std::string)ip << std::endl <<
					"call id: " << std::hex << h.call_id << std::endl <<
					journal::end;

				return;
			}

			buf_incoming_call::lock();
			typename buf_incoming_call::iterator icall = buf_incoming_call::find(ip,h.call_id);
			if(icall != buf_incoming_call::end())
			{
				buf_command::unlock();
				buf_incoming_call::unlock();
				if(icall->checksum == h.checksum)
				{
					proc_feedback::notify(
						ip,
						port,
						h.call_id,
						command_id_ack
					);
					journal(journal::warning,"earpc.process.recv.call") << "retransmitted call" << std::endl <<
						"command: " << std::hex << h.command_id << std::endl <<
						" caller: " << (std::string)ip << std::endl <<
						"call id: " << std::hex << h.call_id << std::endl <<
						journal::end;
				}

				else
				{
					proc_feedback::notify(
						ip,
						port,
						h.call_id,
						command_id_nak
					);
					journal(journal::warning,"earpc.process.recv.call") << "duplicate call id" << std::endl <<
						"command: " << std::hex << h.command_id << std::endl <<
						" caller: " << (std::string)ip << std::endl <<
						"call id: " << std::hex << h.call_id << std::endl <<
						journal::end;
				}
				return;
			}
			buf_incoming_call::unlock();

			buf_outgoing_call::lock();
			typename buf_outgoing_call::iterator ocall = buf_outgoing_call::find(ip,h.call_id);
			if(ocall != buf_outgoing_call::end())
			{
				buf_command::unlock();
				buf_outgoing_call::unlock();
				proc_feedback::notify(
					ip,
					port,
					h.call_id,
					command_id_nak
				);
				journal(journal::error,"earpc.process.recv.call") << "duplicate call id" << std::endl <<
					"command: " << std::hex << h.command_id << std::endl <<
					" caller: " << (std::string)ip << std::endl <<
					"call id: " << std::hex << h.call_id << std::endl <<
					journal::end;
				return;
			}
			buf_outgoing_call::unlock();

			proc_feedback::notify(
				ip,
				port,
				h.call_id,
				command_id_ack
			);

			buf_incoming_call::lock();
			buf_incoming_call::push(ip,port,h.command_id,h.call_id,h.checksum);
			buf_incoming_call::unlock();

			proc_expiry::notify();
			journal(journal::trace,"earpc.process.recv.call") << "serving" << std::endl <<
				"command: " << std::hex << h.command_id << std::endl <<
				" caller: " << (std::string)ip << std::endl <<
				"call id: " << std::hex << h.call_id << std::endl <<
				journal::end;

			const typename buf_command::callback_type f = i->callback;
			buf_command::unlock();

			if(i->arg_size!=0xffff)
				f(
					call_handle_base(ip,port,h.call_id),
					buffer+sizeof(earpc_header_type)
				);
			else
			{
				std::string *x = new std::string(
					reinterpret_cast<char*>(buffer+sizeof(earpc_header_type)),
					size-sizeof(earpc_header_type)
				);

				f(call_handle_base(ip,port,h.call_id),x);

				delete x;
			}
		}

		static void process_ack(net::ipv4_address ip, uint16_t port, uint16_t size)
		{
			earpc_header_type &h = *reinterpret_cast<earpc_header_type*>(buffer);

			proc_send::remove(ip,h.call_id);
			buf_incoming_call::lock();
			typename buf_incoming_call::iterator i = buf_incoming_call::find(ip,h.call_id);
			if(i != buf_incoming_call::end())
			{
				journal(journal::trace,"earpc.process.recv.ack") << "return value accepted; call finished" << std::endl <<
					"command: " << std::hex << i->command_id << std::endl <<
					" target: " << (std::string)i->ip << std::endl <<
					"call id: " << std::hex << i->call_id << std::endl <<
					journal::end;
				buf_incoming_call::erase(i);
				buf_incoming_call::unlock();
				return;
			}
			buf_incoming_call::unlock();

			buf_outgoing_call::lock();
			typename buf_outgoing_call::iterator j = buf_outgoing_call::find(ip,h.call_id);
			if(j == buf_outgoing_call::end())
				journal(journal::warning,"earpc.process.recv.ack") << "ACK on unknown call id" << std::endl <<
					" remote: " << (std::string)ip << std::endl <<
					"call id: " << std::hex << h.call_id << std::endl <<
					journal::end;
			else
				journal(journal::trace,"earpc.process.recv.ack") << "outgoing call accepted" << std::endl <<
					"command: " << std::hex << j->command_id << std::endl <<
					" target: " << (std::string)j->ip << std::endl <<
					"call id: " << std::hex << j->call_id << std::endl <<
					journal::end;

			buf_outgoing_call::unlock();
		}

		static void process_nak(net::ipv4_address ip, uint16_t port, uint16_t size)
		{
			earpc_header_type &h = *reinterpret_cast<earpc_header_type*>(buffer);

			proc_send::remove(ip,h.call_id);
			buf_incoming_call::lock();
			typename buf_incoming_call::iterator i = buf_incoming_call::find(ip,h.call_id);
			if(i != buf_incoming_call::end())
			{
				journal(journal::error,"earpc.process.recv.nak") << "return value rejected" << std::endl <<
					"command: " << std::hex << i->command_id << std::endl <<
					" caller: " << (std::string)i->ip << std::endl <<
					"call id: " << std::hex << i->call_id << std::endl <<
					journal::end;

				buf_incoming_call::erase(i);
				buf_incoming_call::unlock();
				return;
			}
			buf_incoming_call::unlock();
			buf_outgoing_call::lock();

			typename buf_outgoing_call::iterator j = buf_outgoing_call::find(ip,h.call_id);
			if(j != buf_outgoing_call::end())
			{
				journal(journal::error,"earpc.process.recv.nak") << "outgoing call rejected; returning failure to API" << std::endl <<
					"command: " << std::hex << j->command_id << std::endl <<
					" target: " << (std::string)j->ip << std::endl <<
					"call id: " << std::hex << j->call_id << std::endl <<
					journal::end;

				const typename buf_outgoing_call::callback_type f = j->callback;
				const command_id_type cmd = j->command_id;
				buf_outgoing_call::erase(j);
				buf_outgoing_call::unlock();
				f(ip,cmd,0);
				return;
			}
			else
			{
				journal(journal::warning,"earpc.process.recv.nak") << "unknown call id " << std::endl <<
					" source: " << (std::string)ip << std::endl <<
					"call id: " << std::hex << h.call_id << std::endl <<
					journal::end;
				buf_outgoing_call::unlock();
			}
		}

		static void process()
		{
			net::ipv4_address ip;
			uint16_t port;
			const int size = conn.recv(ip, port, buffer, 65535);
			if(size <= 0)
				return;

			if(size < sizeof(earpc_header_type))
			{
				journal(journal::warning,"earpc.process.recv") << "dropping due to size error" << std::endl <<
					"caller: " << (std::string)ip << std::endl <<
					journal::end;
					
				return;
			}

			earpc_header_type &h = *reinterpret_cast<earpc_header_type*>(buffer);

			if(!h.checksum_verify())
			{
				journal(journal::warning,"earpc.process.recv") << "dropping due to size error" << std::endl <<
					"caller: " << (std::string)ip << std::endl <<
					journal::end;
				return;
			}

			switch(h.command_id)
			{
				case command_id_ack:
					process_ack(ip,port,size);
					break;
					
				case command_id_nak:
					process_nak(ip,port,size);
					break;

				case command_id_return:
					process_return(ip,port,size);
					break;

				case command_id_exception:
					proc_feedback::notify(
						ip,
						port,
						h.call_id,
						command_id_ack
					);
					break;

				default:
					process_call(ip,port,size);
					break;
			}
		}

	public:
		template<typename Treturn,bool dummy = false>
		struct call_handle : public call_handle_base
		{
			void respond(const Treturn &ret)
			{
				journal(journal::trace,"earpc.api.respond") << "notifying send process" << journal::end;
				proc_send::notify(
					call_handle_base::ip,
					call_handle_base::port,
					call_handle_base::call_id,
					command_id_return,
					&ret,sizeof(Treturn)
				);
			}


			call_handle(
				net::ipv4_address i,
				uint16_t p,
				call_id_type cid
			)
				: call_handle_base(i,p,cid)
			{}
		};
		
		template<bool dummy>
		struct call_handle<std::string,dummy> : public call_handle_base
		{
			void respond(const std::string &ret)
			{
//				std::cout << "\e[37;01m - \e[0mearpc return: notifying send process" << std::endl;
				proc_send::notify(
					call_handle_base::ip,
					call_handle_base::port,
					call_handle_base::call_id,
					command_id_return,
					ret.c_str(),ret.size()
				);
			}


			call_handle(
				net::ipv4_address i,
				uint16_t p,
				call_id_type cid
			)
				: call_handle_base(i,p,cid)
			{}
		};

		static void start()
		{
			journal(journal::debug,"earpc.process.recv") << "initializing" << journal::end;
			buffer = new uint8_t[65536];
			while(1)
				process();
			delete buffer;
		}
	};

	template<typename e>
	uint8_t *recv<e>::buffer;
}}
#endif
