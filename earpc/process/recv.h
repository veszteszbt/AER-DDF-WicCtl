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
		typedef typename TEnv::command_id_type           command_id_type;

		typedef typename TEnv::header_type               header_type;

		typedef typename TEnv::buf_command               buf_command;

		typedef typename TEnv::buf_incoming_call         buf_incoming_call;

		typedef typename TEnv::buf_outgoing_call         buf_outgoing_call;

		typedef typename TEnv::incoming_call_handle_base incoming_call_handle_base;

		typedef typename TEnv::outgoing_call_handle_base outgoing_call_handle_base;

		typedef typename TEnv::proc_feedback             proc_feedback;

		typedef typename TEnv::proc_send                 proc_send;

		typedef typename TEnv::proc_expiry               proc_expiry;


		static const command_id_type command_id_ack          = TEnv::command_id_ack;

		static const command_id_type command_id_nak          = TEnv::command_id_nak;

		static const command_id_type command_id_return       = TEnv::command_id_return;

		static const command_id_type command_id_exception    = TEnv::command_id_exception;

		constexpr static ::earpc::udp &conn                  = TEnv::conn;

		static uint8_t *buffer;

		// Handle return value
		static void process_return(net::ipv4_address ip, uint16_t size)
		{
			header_type &h = *reinterpret_cast<header_type*>(buffer);

			proc_send::remove(h.call_id);

			buf_outgoing_call::lock();
			auto call = buf_outgoing_call::find(h.call_id);
			if(call != buf_outgoing_call::end())
			{
				if(call->parked)
				{
					journal(journal::critical,"earpc.call.outgoing") <<
						"call id: " << std::hex << h.call_id <<
						"; target: " << (std::string)ip <<
						"; command: " << std::hex << h.command_id <<
						"; return value on parked call; setting state to active" <<
						journal::end;

					call->parked = false;
				}

				if(call->ip != ip)
				{
					journal(journal::warning,"earpc.call.outgoing") <<
						"call id: " << std::hex << h.call_id <<
						"; target: " << (std::string)ip <<
						"; command: " << std::hex << h.command_id <<
						"; return value from different address; orig ip: " <<
						(std::string)call->orig_ip <<
						journal::end;

					const net::ipv4_address old_ip = call->ip;
					call->ip = ip;
					proc_send::reroute(h.call_id, ip);
					proc_feedback::reroute(h.call_id, ip);
					TEnv::on_outgoing_call_rerouted(old_ip,ip);
				}

				auto f = call->callback;

				const uint16_t ret_size = size-sizeof(header_type);

				if(call->return_size == 0xffff || ret_size == call->return_size)
				{
					proc_feedback::notify(
						ip,
						h.call_id,
						command_id_ack
					);

					journal(journal::trace,"earpc.call.outgoing") <<
						"call id: " << std::hex << h.call_id <<
						"; target: " << (std::string)ip <<
						"; command: " << std::hex << call->command_id <<
						"; successfully finished" <<
						journal::end;

					outgoing_call_handle_base handle(*call,&(&h)[1],ret_size,0);
					buf_outgoing_call::erase(call);
					TEnv::on_outgoing_call_finished(ip);
					buf_outgoing_call::unlock();

					f(handle);
					return;
				}

				else
				{
					proc_feedback::notify(
						ip,
						h.call_id,
						command_id_nak
					);

					journal(journal::critical,"earpc.call.outgoing") <<
						"call id: " << std::hex << h.call_id <<
						"; target: " << (std::string)ip <<
						"; command: " << std::hex << call->command_id <<
						"; return value size mismatch" <<
						"; expected" << std::dec << call->return_size <<
						"; received " << ret_size <<
						journal::end;

					outgoing_call_handle_base handle(*call,0,0,1);
					buf_outgoing_call::erase(call);
					TEnv::on_outgoing_call_finished(ip);
					buf_outgoing_call::unlock();

					f(handle);
					return;
				}
			}
			buf_outgoing_call::unlock();

			proc_feedback::notify(
				ip,
				h.call_id,
				command_id_nak
			);

			journal(journal::error,"earpc.call.outgoing") <<
				"call id: " << std::hex << h.call_id <<
				"; target: " << (std::string)ip <<
				"; return value received for unknown call" <<
				journal::end;
		}

		// Handle incoming call
		static void process_call(net::ipv4_address ip, uint16_t size)
		{
			header_type &h = *reinterpret_cast<header_type*>(buffer);

			const uint16_t arg_size = size-sizeof(header_type);
			
			// Process existing incoming call
			buf_incoming_call::lock();
			auto icall = buf_incoming_call::find(h.call_id);
			if(icall != buf_incoming_call::end())
			{
				if(icall->arg_compare(&(&h)[1],arg_size))
				{
					proc_feedback::notify(
						ip,
						h.call_id,
						command_id_ack
					);
					if(ip != icall->ip)
					{
						journal(journal::warning,"earpc.call.incoming") <<
							"call id: " << std::hex << h.call_id <<
							"; caller: " << (std::string)ip <<
							"; command: " << std::hex << h.command_id <<
							"; retransmitted call from different address; orig ip: " <<
							(std::string)icall->orig_ip <<
							journal::end;
						icall->ip = ip;
						proc_send::reroute(h.call_id, ip);
						proc_feedback::reroute(h.call_id, ip);
					}
					else
						journal(journal::warning,"earpc.call.incoming") <<
							"call id: " << std::hex << h.call_id <<
							"; caller: " << (std::string)ip <<
							"; command: " << std::hex << h.command_id <<
							"; retransmitted call" <<
							journal::end;
				}

				else
				{
					proc_feedback::notify(
						ip,
						h.call_id,
						command_id_nak
					);
					journal(journal::error,"earpc.call.incoming") <<
						"call id: " << std::hex << h.call_id <<
						"; command: " << std::hex << h.command_id <<
						"; caller: " << (std::string)ip <<
						"; duplicate call id" <<
						journal::end;
				}
				return;
			}
			buf_incoming_call::unlock();

			// Process existing outgoing call
			buf_outgoing_call::lock();
			auto ocall = buf_outgoing_call::find(h.call_id);
			if(ocall != buf_outgoing_call::end())
			{
				buf_outgoing_call::unlock();
				proc_feedback::notify(
					ip,
					h.call_id,
					command_id_nak
				);
				journal(journal::error,"earpc.call.incoming") <<
					"call id: " << std::hex << h.call_id <<
					"; command: " << std::hex << h.command_id <<
					"; caller: " << (std::string)ip <<
					"; duplicate call id" <<
					journal::end;
				return;
			}
			buf_outgoing_call::unlock();


			buf_command::lock();
			typename buf_command::iterator command = buf_command::find(h.command_id);

			// Handle unknown command
			if(command == buf_command::end())
			{
				buf_command::unlock();
/*				proc_feedback::notify(
					ip,
					port,
					h.call_id,
					command_id_nak
				);
*/
				journal(journal::critical,"earpc.call.incoming") <<
					"call id: " << std::hex << h.call_id <<
					"; caller: " << (std::string)ip <<
					"; unknown command " << std::hex << h.command_id <<
					journal::end;
				return;
			}

			// Handle invalid argument size
			if(
				command->arg_size != arg_size &&
				command->arg_size != 0xffff
			)
			{ 
				buf_command::unlock();
				proc_feedback::notify(
					ip,
					h.call_id,
					command_id_nak
				);
				journal(journal::critical,"earpc.call.incoming") <<
					"call id: " << std::hex << h.call_id <<
					"; caller: " << (std::string)ip <<
					"; command: "<< std::hex << h.command_id <<
					"; argument size mismatch" <<
					"; expected " << std::dec << command->arg_size <<
					"; received " << arg_size <<
					journal::end;

				return;
			}

			// Serve new call
			auto f = command->callback;
			const uint16_t ret_size = command->ret_size;
			buf_command::unlock();

			proc_feedback::notify(
				ip,
				h.call_id,
				command_id_ack
			);

			buf_incoming_call::lock();
			auto call = buf_incoming_call::push(
				ip,
				h.command_id,
				h.call_id,
				&(&h)[1],
				arg_size,
				ret_size
			);
			incoming_call_handle_base handle(*call,0);
			buf_incoming_call::unlock();

			proc_expiry::notify();
			journal(journal::trace,"earpc.call.incoming") << 
				"call id: " << std::hex << h.call_id <<
				"; command: " << std::hex << h.command_id <<
				"; caller: " << (std::string)ip <<
				"; serving call" <<
				journal::end;

			f(handle);
		}

		static void process_ack(net::ipv4_address ip, uint16_t size)
		{
			header_type &h = *reinterpret_cast<header_type*>(buffer);

			proc_send::remove(h.call_id);

			// Process incoming calls
			buf_incoming_call::lock();
			auto icall = buf_incoming_call::find(h.call_id);
			if(icall != buf_incoming_call::end())
			{
				if(icall->ip != ip)
					journal(journal::warning,"earpc.call.incoming") <<
						"call id: " << std::hex << h.call_id <<
						"; caller: " << (std::string)ip <<
						"; command: " << std::hex << h.command_id <<
						"; return value accepted from different address; orig ip: " <<
						(std::string)icall->orig_ip <<
						"; call finished" <<
						journal::end;
				else
					journal(journal::trace,"earpc.call.incoming") <<
						"call id: " << std::hex << icall->call_id <<
						"; command: " << std::hex << icall->command_id <<
						"; target: " << (std::string)icall->ip <<
						"; return value accepted; call finished" <<
						journal::end;
				
				buf_incoming_call::erase(icall);
				buf_incoming_call::unlock();
				return;
			}
			buf_incoming_call::unlock();

			// Process outgoing calls
			buf_outgoing_call::lock();
			auto ocall = buf_outgoing_call::find(h.call_id);
			if(ocall != buf_outgoing_call::end())
				journal(journal::error,"earpc.call.outgoing") <<
					"call id: " << std::hex << h.call_id <<
					"; remote: " << (std::string)ip <<
					"; ACK on unknown call id" <<
					journal::end;
			else
			{
				if(ocall->ip != ip)
				{
					journal(journal::trace,"earpc.call.outgoing") <<
						"call id: " << std::hex << ocall->call_id <<
						"; command: " << std::hex << ocall->command_id <<
						"; target: " << (std::string)ip <<
						"; accepted from different address; orig ip: " <<
						(std::string)ocall->orig_ip <<
						journal::end;

					const net::ipv4_address old_ip = ocall->ip;
					ocall->ip = ip;
					proc_feedback::reroute(ocall->call_id,ip);
					TEnv::on_outgoing_call_rerouted(old_ip,ip);
				}
				else
					journal(journal::trace,"earpc.call.outgoing") <<
						"call id: " << std::hex << ocall->call_id <<
						"; command: " << std::hex << ocall->command_id <<
						"; target: " << (std::string)ip <<
						"; accepted" <<
						journal::end;
			}
			buf_outgoing_call::unlock();
		}

		static void process_nak(net::ipv4_address ip, uint16_t size)
		{
			header_type &h = *reinterpret_cast<header_type*>(buffer);

			proc_send::remove(h.call_id);

			// Process incoming calls
			buf_incoming_call::lock();
			auto icall = buf_incoming_call::find(h.call_id);
			if(icall != buf_incoming_call::end())
			{
				if(icall->ip != ip)
				{
					journal(journal::critical,"earpc.call.incoming") <<
						"call id: " << std::hex << icall->call_id << 
						"; command: " << std::hex << icall->command_id <<
						"; target: " << (std::string)ip <<
						"; return value rejected from different address; orig ip: " <<
						(std::string)icall->orig_ip <<
						journal::end;
					icall->ip = ip;
				}
				else
					journal(journal::critical,"earpc.call.incoming") <<
						"call id: " << std::hex << icall->call_id << 
						"; command: " << std::hex << icall->command_id <<
						"; target: " << (std::string)ip <<
						"; return value rejected" <<
						journal::end;

				buf_incoming_call::erase(icall);
				buf_incoming_call::unlock();
				return;
			}
			buf_incoming_call::unlock();
			buf_outgoing_call::lock();

			auto ocall = buf_outgoing_call::find(h.call_id);
			if(ocall != buf_outgoing_call::end())
			{
				if(ocall->ip != ip)
				{
					journal(journal::critical,"earpc.call.outgoing") <<
						"call id: " << std::hex << ocall->call_id << 
						"; command: " << std::hex << ocall->command_id <<
						"; target: " << (std::string)ip <<
						"; call rejected from different address; orig ip: " <<
						(std::string)ocall->orig_ip <<
						"; returning failure to API" <<
						journal::end;
					const net::ipv4_address old_ip = ocall->ip;
					ocall->ip = ip;
					TEnv::on_outgoing_call_rerouted(old_ip,ip);
				}
				else
					journal(journal::critical,"earpc.call.outgoing") <<
						"call id: " << std::hex << ocall->call_id << 
						"; command: " << std::hex << ocall->command_id <<
						"; target: " << (std::string)ip <<
						"; outgoing call rejected; returning failure to API" <<
						journal::end;

				outgoing_call_handle_base handle(*ocall,0,0,2);
				auto f = ocall->callback;
				buf_outgoing_call::erase(ocall);
				TEnv::on_outgoing_call_finished(ip);
				buf_outgoing_call::unlock();
				f(handle);
				return;
			}
			buf_outgoing_call::unlock();
			
			journal(journal::error,"earpc.call") <<
				"call id: " << std::hex << h.call_id <<
				"; source: " << (std::string)ip <<
				"; NAK on unknown call id" <<
				journal::end;
		}

		static void process()
		{
			net::ipv4_address ip;
			uint16_t port;
			const int size = conn.recv(ip, port, buffer, 65535);
			if(size <= 0)
				return;

			if(size < sizeof(header_type))
			{
				journal(journal::error,"earpc.call") <<
					"source: " << (std::string)ip <<
					"; dropping due to packet size error" <<
					journal::end;
					
				return;
			}

			header_type &h = *reinterpret_cast<header_type*>(buffer);

			if(!h.checksum_verify())
			{
				journal(journal::error,"earpc.call") <<
					"source: " << (std::string)ip <<
					"; dropping due to checksum error" <<
					journal::end;
				return;
			}

			switch(h.command_id)
			{
				case command_id_ack:
					process_ack(ip,size);
					break;
					
				case command_id_nak:
					process_nak(ip,size);
					break;

				case command_id_return:
					process_return(ip,size);
					break;

				case command_id_exception:
					proc_feedback::notify(
						ip,
						h.call_id,
						command_id_ack
					);
					break;

				default:
					process_call(ip,size);
					break;
			}
		}

	public:
		template<typename Treturn, typename Targ>
		struct incoming_call_handle : public incoming_call_handle_base
		{
			template<typename T = Treturn>
			std::enable_if_t<!std::is_same<std::decay_t<T>,std::string>::value>
			respond(const T&ret)
			{
				journal(journal::trace,"earpc.call.incoming") <<
					"call id: " << std::hex << incoming_call_handle_base::call_id <<
					"; command: " << std::hex << incoming_call_handle_base::command_id <<
					"; source: " << (std::string) incoming_call_handle_base::ip <<
					"; sending return value" << journal::end;

				proc_send::notify(
					incoming_call_handle_base::ip,
					incoming_call_handle_base::call_id,
					command_id_return,
					&ret,sizeof(Treturn)
				);
			}

			template<typename T = Treturn>
			std::enable_if_t<std::is_same<std::decay_t<T>,std::string>::value>
			respond(const std::string &ret)
			{
				journal(journal::trace,"earpc.call.incoming") <<
					"call id: " << std::hex << incoming_call_handle_base::call_id <<
					"; command: " << std::hex << incoming_call_handle_base::command_id <<
					"; source: " << (std::string) incoming_call_handle_base::ip <<
					"; sending return value" << journal::end;

				proc_send::notify(
					incoming_call_handle_base::ip,
					incoming_call_handle_base::call_id,
					command_id_return,
					ret.c_str(),ret.size()
				);
			}

			template<typename T = Targ>
			std::enable_if_t<!std::is_same<std::decay_t<T>,std::string>::value,Targ>
			value()
			{
				journal(journal::trace,"earpc.call.incoming") <<
					"call id: " << std::hex << incoming_call_handle_base::call_id <<
					"; command: " << std::hex << incoming_call_handle_base::command_id <<
					"; source: " << (std::string) incoming_call_handle_base::ip <<
					"; taking argument" << journal::end;

				Targ r;
				std::copy(
					incoming_call_handle_base::arg_bytes.begin(),
					incoming_call_handle_base::arg_bytes.end(),
					reinterpret_cast<uint8_t*>(&r)
				);
				return r; 

			}

			template<typename T = Targ>
			std::enable_if_t<std::is_same<std::decay_t<T>,std::string>::value,std::string>
			value()
			{
				journal(journal::trace,"earpc.call.incoming") <<
					"call id: " << std::hex << incoming_call_handle_base::call_id <<
					"; command: " << std::hex << incoming_call_handle_base::command_id <<
					"; source: " << (std::string) incoming_call_handle_base::ip <<
					"; taking argument" << journal::end;

				return std::string(
					incoming_call_handle_base::arg_bytes.begin(),
					incoming_call_handle_base::arg_bytes.end()
				);
			}

			template<typename T>
			incoming_call_handle(const T &call)
				: incoming_call_handle_base(call)
			{}
		};

		template<typename Treturn, typename Targ>
		struct outgoing_call_handle : public outgoing_call_handle_base
		{
			template<typename T = Treturn>
			std::enable_if_t<!std::is_same<std::decay_t<T>,std::string>::value,Treturn>
			value()
			{
				journal(journal::trace,"earpc.call.outgoing") <<
					"call id: " << std::hex << outgoing_call_handle_base::call_id <<
					"; command: " << std::hex << outgoing_call_handle_base::command_id <<
					"; source: " << (std::string) outgoing_call_handle_base::ip <<
					"; taking return value" << journal::end;

				Treturn r;
				std::copy(
					outgoing_call_handle_base::ret_bytes.begin(),
					outgoing_call_handle_base::ret_bytes.end(),
					reinterpret_cast<uint8_t*>(&r)
				);
				return r; 

			}

			template<typename T = Treturn>
			std::enable_if_t<std::is_same<std::decay_t<T>,std::string>::value,std::string>
			value()
			{
				journal(journal::trace,"earpc.call.outgoing") <<
					"call id: " << std::hex << outgoing_call_handle_base::call_id <<
					"; command: " << std::hex << outgoing_call_handle_base::command_id <<
					"; source: " << (std::string) outgoing_call_handle_base::ip <<
					"; taking return value" << journal::end;

				return std::string(
					outgoing_call_handle_base::ret_bytes.begin(),
					outgoing_call_handle_base::ret_bytes.end()
				);
			}

			template<typename T>
			outgoing_call_handle(const T &call)
				: outgoing_call_handle_base(call)
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
