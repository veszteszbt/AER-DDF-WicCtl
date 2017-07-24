#ifndef EARPC_PROCESS_FEEDBACK_H
# define EARPC_PROCESS_FEEDBACK_H
# include <iostream>
# include <cstdint>
# include <list>
# include <mutex>
# include <condition_variable>
# include <net/ipv4_address.h>
# include <earpc/udp.h>
namespace earpc {
namespace process
{
	template<typename TEnv>
	class feedback
	{
		typedef typename TEnv::call_id_type      call_id_type; 

		typedef typename TEnv::command_id_type   command_id_type; 

		typedef typename TEnv::earpc_header_type earpc_header_type;

		constexpr static earpc::udp &conn = TEnv::conn;

		struct queue_record
		{
			net::ipv4_address ip;

			uint16_t port;

			call_id_type call_id;

			command_id_type feedback;

			uint8_t retries;

			queue_record() {}

			queue_record(
				net::ipv4_address i,
				uint16_t p,
				call_id_type cid,
				command_id_type fb
			)
				: ip(i)
				, port(p)
				, call_id(cid)
				, feedback(fb)
				, retries(8)
			{}
		};

		typedef std::list<queue_record> queue_type;

		static std::mutex queue_lock;

		static std::mutex suspend_lock;

		static std::condition_variable suspend_cv;

		static queue_type queue;

		static earpc_header_type packet;
	public:

		static void notify(
			net::ipv4_address ip,
			uint16_t port,
			call_id_type call_id,
			command_id_type feedback
		)
		{
//			std::cout <<
//				"\e[37;01m - \e[0mearpc feedback process: notified\n";

			queue_lock.lock();
			queue.push_back(queue_record(ip,port,call_id,feedback));
			queue_lock.unlock();

			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}

		static void start()
		{
//			std::cout <<
//				"\e[37;01m - \e[0mearpc feedback process: initializing\n";
			std::cout.flush();
			while(1)
			{
				queue_lock.lock();
				if(!queue.size())
				{
//					std::cout <<
//						"\e[37;01m - \e[0mearpc feedback process: nothing to do; "
//						"suspending until next notify\n";
					queue_lock.unlock();
					std::unique_lock<std::mutex> ul(suspend_lock);
					suspend_cv.wait(ul);
//					std::cout <<
//						"\e[37;01m - \e[0mearpc feedback process: resuming\n";
//					continue;
				}
//				std::cout <<
//					"\e[37;01m - \e[0mearpc feedback process: doing send operation\n";

				for(
					typename queue_type::iterator i = queue.begin();
					i != queue.end();
				) {
					packet.call_id = i->call_id;
					packet.command_id = i->feedback;
					packet.checksum_create();
					conn.send(i->ip,i->port,&packet,sizeof(earpc_header_type));
					queue.erase(i++);
				}
				queue_lock.unlock();
			}
		}
	};

	template<typename e>
	std::mutex feedback<e>::queue_lock;

	template<typename e>
	std::mutex feedback<e>::suspend_lock;

	template<typename e>
	std::condition_variable feedback<e>::suspend_cv;

	template<typename e>
	typename feedback<e>::queue_type feedback<e>::queue;

	template<typename e>
	typename feedback<e>::earpc_header_type feedback<e>::packet;
}}
#endif
