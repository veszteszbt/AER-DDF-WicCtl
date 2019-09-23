#ifndef EARPC_PROCESS_SEND_H
# define EARPC_PROCESS_SEND_H
# include <cstdint>
# include <list>
# include <forward_list>
# include <mutex>
# include <condition_variable>
# include <net/ipv4_address.h>
# include <types/time.h>
#ifdef _MSC_VER
	#undef max
	#undef min
#endif
namespace earpc {
namespace process
{
	template<typename TEnv>
	class send
	{
		typedef typename TEnv::call_id_type      call_id_type;

		typedef typename TEnv::command_id_type   command_id_type;

		typedef typename TEnv::header_type header_type;

		typedef typename TEnv::outgoing_call_record outgoing_call_record;

		typedef typename TEnv::clock             clock;

		typedef typename clock::time_point       time_point;


		static std::mutex               queue_lock;

		static std::mutex               suspend_lock;

		static std::condition_variable  suspend_cv;

		static ::earpc::udp &conn;

		struct packet
		{
			const net::ipv4_address ip;
			uint8_t *buf;
			const uint16_t size;
			packet(
				net::ipv4_address pip,
				uint8_t *pbuf,
				uint16_t psize
			)
				: buf(pbuf)
				, ip(pip)
				, size(psize)
			{}
		};

		struct queue_record
		{
			net::ipv4_address ip;

			call_id_type call_id;

			command_id_type command_id;

			uint8_t *buffer;

			uint16_t size;

			time_point resend_time;

			queue_record(const queue_record &that)
				: ip(that.ip)
				, call_id(that.call_id)
				, command_id(that.command_id)
				, buffer(new uint8_t[that.size])
				, size(that.size)
				, resend_time(that.resend_time)
			{ memcpy(buffer,that.buffer,size); }

			queue_record()
				: buffer(0)
			{}

			queue_record(
				net::ipv4_address i,
				call_id_type cid,
				command_id_type cmd,
				const void *b,
				uint16_t s
			)
				: ip(i)
				, call_id(cid)
				, command_id(cmd)
				, buffer(new uint8_t[s])
				, size(s)
				, resend_time(time_point::min())
			{ memcpy(buffer,b,s); }

			~queue_record()
			{ delete buffer; }

			void send()
			{
				const uint16_t buf_size = sizeof(header_type) + size;
				uint8_t *buf = new uint8_t[buf_size];

				header_type &h = *reinterpret_cast<header_type*>(buf);
				h.call_id = call_id;
				h.command_id = command_id;
				h.checksum_create();
				memcpy(buf+sizeof(header_type),buffer,size);
				conn.send(ip,TEnv::earpc_remote_port,buf,buf_size);
				delete[] buf;
			}
			
		};

		typedef std::list<queue_record> queue_type;

		static queue_type               queue;

		static volatile bool            notified;

	public:
		static void start()
		{
			journal(journal::debug,"earpc.process.send") << "initializing" << journal::end;
			notified = false;

			while(1)
			{
				time_point ns = time_point::max();
				
				queue_lock.lock();
				for(auto &i : queue)
				{
					if(i.resend_time > clock::now())
					{
						if(ns > i.resend_time)
							ns = i.resend_time;
						continue;
					}

					i.resend_time = clock::now() + std::chrono::milliseconds(400);
					if(ns > i.resend_time)
						ns = i.resend_time;

					journal(journal::trace,"earpc.call") <<
						"call id: " << std::hex << i.call_id <<
						"; command: " << std::hex << i.command_id <<
						"; target: " << (std::string)i.ip <<
						"; doing data send operation" <<
						journal::end;

					i.send();
				}
				queue_lock.unlock();

				if(ns == time_point::max())
				{
					journal(journal::trace,"earpc.process.send") <<
						"nothing to do; suspending until next notify" <<
						journal::end;

					std::unique_lock<std::mutex> ul(suspend_lock);
					if(!notified)
						suspend_cv.wait(ul);
					else
						notified = false;
				}

				else
				{
					journal(journal::trace,"earpc.process.send") <<
						"nothing to do; suspending for " << std::dec <<
						::types::time::msec(ns-clock::now()) <<
						" msec" << journal::end;

					std::unique_lock<std::mutex> ul(suspend_lock);
					if(!notified)
						suspend_cv.wait_until(ul,ns);
					else
						notified = false;
				}
				journal(journal::trace,"earpc.process.send") << "resuming" << journal::end;
			}

			journal(journal::debug,"earpc.process.send") << "uninitializing" << journal::end;
		}

		static void notify(
			net::ipv4_address ip,
			call_id_type call_id,
			command_id_type command_id,
			const void *buffer,
			uint16_t size
		)
		{
			queue_lock.lock();
			queue.emplace_back(ip,call_id,command_id,buffer,size);
			queue_lock.unlock();

			journal(journal::trace,"earpc.call") <<
				"call id: " << std::hex << call_id <<
				"; command: " << std::hex << command_id <<
				"; target: " << (std::string)ip <<
				"; " << std::dec << size <<
				" bytes of data queued for send" <<
				journal::end;

			std::lock_guard<std::mutex> lg(suspend_lock);
			notified = true;
			suspend_cv.notify_one();
		}

		static void notify(const outgoing_call_record &rec)
		{ notify(rec.ip,rec.call_id,rec.command_id,rec.arg.data(),rec.arg.size()); }

		static void reroute(call_id_type call_id, net::ipv4_address ip)
		{
			queue_lock.lock();
			for(auto &i : queue)
				if(i.call_id == call_id)
				{
					journal(journal::trace,"earpc.call") <<
						"call id: " << std::hex << i.call_id <<
						"; command: " << std::hex << i.command_id <<
						"; target: " << (std::string)i.ip <<
						"; rerouting queued data to " << (std::string)ip <<
						journal::end;
					i.ip = ip;
					queue_lock.unlock();
					return;
				}
			queue_lock.unlock();

			journal(journal::trace,"earpc.call") <<
				"call id: " << std::hex << call_id <<
				"; target: " << (std::string)ip <<
				"; no queued data found for rerouting" <<
				journal::end;
		}

		static void remove(call_id_type call_id)
		{
			queue_lock.lock();
			for(auto i = queue.begin(); i != queue.end(); ++i)
				if(i->call_id == call_id)
				{
					journal(journal::trace,"earpc.call") <<
						"call id: " << std::hex << call_id <<
						"; command: " << std::hex << i->command_id <<
						"; target: " << (std::string)i->ip <<
						"; removing queued data" <<
						journal::end;

					queue.erase(i);
					queue_lock.unlock();
					return;
				}
			queue_lock.unlock();
			
			journal(journal::trace,"earpc.call") <<
				"call id: " << std::hex << call_id <<
				"; no queued data found for removal" <<
				journal::end;
		}
	};

	template<typename e>
	std::mutex send<e>::queue_lock;

	template<typename e>
	std::mutex send<e>::suspend_lock;

	template<typename e>
	std::condition_variable send<e>::suspend_cv;

	template<typename e>
	typename send<e>::queue_type send<e>::queue;

	template<typename e>
	volatile bool send<e>::notified;

	template<typename e>
	::earpc::udp &send<e>::conn = e::conn;
}}
#endif
