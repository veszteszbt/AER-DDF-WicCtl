#ifndef EARPC_PROCESS_SEND_H
# define EARPC_PROCESS_SEND_H
# include <cstdint>
# include <list>
# include <forward_list>
# include <mutex>
# include <condition_variable>
# include <net/ipv4_address.h>
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

		typedef typename TEnv::call_id_type        call_id_type;

		typedef typename TEnv::command_id_type     command_id_type;

		typedef typename TEnv::earpc_header_type   earpc_header_type;

		typedef typename TEnv::clock clock;

		typedef typename clock::time_point time_point;

		struct queue_record
		{
			net::ipv4_address ip;

			uint16_t port;

			call_id_type call_id;

			command_id_type command_id;

			uint8_t *buffer;

			uint16_t size;

			time_point resend_time;

			uint8_t retries;

			queue_record(const queue_record &that)
				: ip(that.ip)
				, port(that.port)
				, call_id(that.call_id)
				, command_id(that.command_id)
				, buffer(new uint8_t[that.size])
				, size(that.size)
				, resend_time(that.resend_time)
				, retries(that.retries)
			{ memcpy(buffer,that.buffer,size); }

			queue_record()
				: buffer(0)
			{}

			queue_record(
				net::ipv4_address i,
				uint16_t p,
				call_id_type cid,
				command_id_type cmd,
				const void *b,
				uint16_t s
			)
				: ip(i)
				, port(p)
				, call_id(cid)
				, command_id(cmd)
				, buffer(new uint8_t[s])
				, size(s)
				, retries(8)
				, resend_time(time_point::min())
			{ memcpy(buffer,b,s); }

			~queue_record()
			{ delete buffer; }
			
		};

		typedef std::list<queue_record> queue_type;

		static std::mutex               queue_lock;

		static std::mutex               suspend_lock;

		static std::condition_variable  suspend_cv;

		static queue_type               queue;

		constexpr static ::earpc::udp    &conn = TEnv::conn;

		static int64_t tp2msec(time_point p)
		{ return std::chrono::time_point_cast<std::chrono::milliseconds>(p).time_since_epoch().count(); }

		struct packet
		{
			uint8_t *buf;
			const net::ipv4_address ip;
			const uint16_t port;
			const uint16_t size;
			packet(
				net::ipv4_address pip,
				uint16_t pport,
				uint8_t *pbuf,
				uint16_t psize
			)
				:buf(pbuf)
				,ip(pip)
				,port(pport)
				,size(psize)
			{}
		};

	public:
		static void start()
		{
			log(log::debug,"earpc.process.send") << "initializing" << log::end;

			while(1)
			{
				time_point ns = time_point::max();
				
				std::forward_list<packet> packets_to_send;

				queue_lock.lock();
				for(
					typename queue_type::iterator i = queue.begin();
					i != queue.end();
					++i
				) {
					if(i->resend_time > clock::now())
					{
						if(ns > i->resend_time)
							ns = i->resend_time;
						continue;
					}

					i->resend_time = clock::now() + std::chrono::milliseconds(400);
					if(ns > i->resend_time)
						ns = i->resend_time;

					const uint16_t size = sizeof(earpc_header_type) + i->size;
					uint8_t *buf = new uint8_t[size];

					earpc_header_type &h = *reinterpret_cast<earpc_header_type*>(buf);
					h.call_id = i->call_id;
					h.command_id = i->command_id;
					h.checksum_create();
					memcpy(buf+sizeof(earpc_header_type),i->buffer,i->size);

					log(log::debug,"earpc.process.send") << "doing send operation" << std::endl <<
						"command: " << std::hex << i->command_id  << std::endl <<
						" target: " << (std::string)i->ip << std::endl <<
						"call id: " << std::hex << i->call_id << std::endl <<
						log::end;

					const net::ipv4_address ip = i->ip;
					const uint16_t port = i->port;

					packets_to_send.push_front(packet(ip,port,buf,size));
				}

				queue_lock.unlock();

				for(
					auto i = packets_to_send.begin();
					i != packets_to_send.end();
					++i
				)
				{
					
					conn.send(i->ip,i->port,i->buf,i->size);
					delete i->buf;
				}

				if(ns == time_point::max())
				{
					log(log::trace,"earpc.process.send") <<
						"nothing to do; suspending until next notify" <<
						log::end;

					std::unique_lock<std::mutex> ul(suspend_lock);
					suspend_cv.wait(ul);
					log(log::trace,"earpc.process.send") << "resuming on notify" << log::end;
				}

				else
				{
					log(log::trace,"earpc.process.send") <<
						"nothing to do; suspending for " <<
						std::dec << tp2msec(time_point(ns-clock::now())) << " msec" <<
						log::end;

					std::unique_lock<std::mutex> ul(suspend_lock);
					suspend_cv.wait_until(ul,ns);
					log(log::trace,"earpc.process.send") << "resuming on timeout" << log::end;
				}
			}
		}

		static void notify(
			net::ipv4_address ip,
			uint16_t port,
			call_id_type call_id,
			command_id_type command_id,
			const void *buffer,
			uint16_t size
		)
		{
			queue_lock.lock();
			queue.push_back(queue_record(ip,port,call_id,command_id,buffer,size));
			queue_lock.unlock();

			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}

		static void remove(net::ipv4_address ip, call_id_type cid)
		{
			queue_lock.lock();
			for(
				typename queue_type::iterator i = queue.begin();
				i != queue.end();
				++i
			)
				if(i->call_id == cid && i->ip == ip)
				{
					log(log::debug,"earpc.process.send") <<	"removing call" <<  std::endl <<
						"command: " << std::hex << i->command_id << std::endl <<
						" target: " << (std::string)i->ip << std::endl <<
						"call id: " << std::hex << i->call_id << std::endl <<
						log::end;
					queue.erase(i);
					break;
				}
			queue_lock.unlock();
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
}}
#endif
