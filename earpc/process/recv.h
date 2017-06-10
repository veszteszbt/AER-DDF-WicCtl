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

		typedef typename TEnv::command_buffer_type command_buffer_type;

		typedef typename TEnv::call_handle_base    call_handle_base;

		typedef typename TEnv::proc_feedback       proc_feedback;

		typedef typename TEnv::proc_send           proc_send;


		static const command_id_type command_id_ack          = TEnv::command_id_ack;

		static const command_id_type command_id_nak          = TEnv::command_id_nak;

		static const command_id_type command_id_return       = TEnv::command_id_return;

		static const command_id_type command_id_exception    = TEnv::command_id_exception;

		constexpr static earpc::udp &conn                    = TEnv::conn;

		constexpr static command_buffer_type &command_buffer = TEnv::command_buffer;

		static uint8_t *buffer;

		static void process()
		{
			net::ipv4_address ip;
			uint16_t port;
			const int size = conn.recv(ip, port, buffer, 65535);
			if(size <= 0)
				return;

			if(size < sizeof(earpc_header_type))
			{
				std::cout <<
					"\e[33;01m - \e[0mearpc recv process: dropping due to size error" <<
				std::endl;
				return;
			}

			earpc_header_type &h = *reinterpret_cast<earpc_header_type*>(buffer);

			if(!h.checksum_verify())
			{
				std::cout <<
					"\e[33;01m - \e[0mearpc recv process: dropping due to checksum error" <<
				std::endl;
				return;
			}

			switch(h.command_id)
			{
				case command_id_ack:
					std::cout <<
					"\e[37;01m - \e[0mearpc recv process: ACK on "<< std::hex << h.call_id << std::endl;
					proc_send::remove(h.call_id);
					break;
					
				case command_id_nak:
					proc_send::remove(h.call_id);
					break;

				case command_id_return:
					proc_feedback::notify(
						ip,
						port,
						h.call_id,
						command_id_ack
					);
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
					std::cout <<
						"\e[37;01m - \e[0mearpc recv process: ip is "<<
							std::dec << (int)ip.octet[0] << '.'
							<< (int)ip.octet[1] << '.'
							<< (int)ip.octet[2] << '.'
							<< (int)ip.octet[3] <<
						"; port is " << port <<
						"; command id is " << std::hex <<
						h.command_id << "; call id is " << h.call_id << "; checksum is " <<
						h.checksum <<
					std::endl;

					for(
						typename command_buffer_type::iterator i = command_buffer.begin();
						i != command_buffer.end();
						++i
					)
						if(i->command_id == h.command_id)
						{

							if(i->arg_size == size-sizeof(earpc_header_type))
							{
								proc_feedback::notify(
									ip,
									port,
									h.call_id,
									command_id_ack
								);
								std::cout << "\e[37;01m - \e[0mearpc recv process: serving call "
									<< std::hex << h.call_id
								<<std::endl;

								i->callback(
									call_handle_base(ip,port,h.call_id),
									buffer+sizeof(earpc_header_type)
								);
							}

							else
							{
								proc_feedback::notify(
									ip,
									port,
									h.call_id,
									command_id_nak
								);
								std::cout << "\e[37;01m - \e[0mearpc recv process: dropping due to argument size mismatch "
									<< std::hex << h.call_id
								<<std::endl;
							}
							return;
						}
					proc_feedback::notify(
						ip,
						port,
						h.call_id,
						command_id_nak
					);
					std::cout << "\e[37;01m - \e[0mearpc recv process: call "
						<< std::hex << h.call_id << ": dropping due to unknown command "<<h.command_id
					<<std::endl;

					break;
			}
		}

	public:
		template<typename Treturn>
		struct call_handle : public call_handle_base
		{
			void respond(const Treturn &ret)
			{
				std::cout << "\e[37;01m - \e[0mearpc return: notifying send process" << std::endl;
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

		static void start()
		{
			std::cout << "\e[37;01m - \e[0mearpc recv process: initializing" << std::endl;
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
