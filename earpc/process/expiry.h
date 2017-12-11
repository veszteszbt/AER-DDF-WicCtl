#ifndef EARPC_PROCESS_EXPIRY_H
# define EARPC_PROCESS_EXPIRY_H
# include <journal.h>
# include <iostream>
# include <cstdint>
# include <list>
# include <mutex>
# include <condition_variable>
# include <net/ipv4_address.h>
# include <earpc/udp.h>
#ifdef _MSC_VER
	#undef max
	#undef min
#endif
namespace earpc {
namespace process
{
	template<typename TEnv>
	class expiry 
	{
		typedef typename TEnv::clock             clock;

		typedef typename clock::time_point       time_point;

		typedef typename TEnv::call_id_type      call_id_type; 

		typedef typename TEnv::command_id_type   command_id_type; 

		typedef typename TEnv::earpc_header_type earpc_header_type;

		typedef typename TEnv::buf_outgoing_call buf_outgoing_call;

		typedef typename TEnv::buf_incoming_call buf_incoming_call;

		typedef typename TEnv::proc_send         proc_send;


		static std::mutex               suspend_lock;

		static std::condition_variable  suspend_cv;


		static int64_t tp2msec(time_point p)
		{ return std::chrono::time_point_cast<std::chrono::milliseconds>(p).time_since_epoch().count(); }

	public:
		static void start()
		{
			journal(journal::debug,"earpc.process.expiry") << "initializing" << journal::end;

			while(1)
			{
				buf_outgoing_call::lock();

				time_point ns = time_point::max();
				for(
					typename buf_outgoing_call::iterator i = buf_outgoing_call::begin();
					i != buf_outgoing_call::end();
				) {
					const time_point t = clock::now();
					if(i->expiry > t)
					{
						if(ns > i->expiry)
							ns = i->expiry;
						++i;
					}
					else
					{
						const net::ipv4_address ip = i->ip;
						const command_id_type cmd = i->command_id;
						const call_id_type cid = i->call_id;
						const typename buf_outgoing_call::callback_type f = i->callback;
						proc_send::remove(ip,cid);
						buf_outgoing_call::erase(i);
						buf_outgoing_call::unlock();
						TEnv::call_finished(ip);
						f(ip,cmd,0);
						buf_outgoing_call::lock();
						i = buf_outgoing_call::begin();

						journal(journal::error,"earpc.process.expiry") << "outgoing call expired" << std::endl << 
							"command: " << std::hex << cmd << std::endl <<
							" target: " << (std::string)ip << std::endl <<
							"call id: " << std::hex << cid << std::endl <<
							journal::end;
					}
				}
				buf_outgoing_call::unlock();

				buf_incoming_call::lock();
				for(
					typename buf_incoming_call::iterator i = buf_incoming_call::begin();
					i != buf_incoming_call::end();
				) {
					const time_point t = clock::now();
					if(i->expiry > t)
					{
						if(ns > i->expiry)
							ns = i->expiry;
						++i;
					}
					else
					{
						const net::ipv4_address ip = i->ip;
						const command_id_type cmd = i->command_id;
						const call_id_type cid = i->call_id;
						proc_send::remove(ip,cid);
						buf_incoming_call::erase(i);
						buf_incoming_call::unlock();
						buf_incoming_call::lock();
						i = buf_incoming_call::begin();

						journal(journal::error,"earpc.process.expiry") << "incoming call expired" << std::endl << 
							"command: " << std::hex << cmd << std::endl <<
							" caller: " << (std::string)ip << std::endl <<
							"call id: " << std::hex << cid << std::endl <<
							journal::end;
					}
				}
				buf_incoming_call::unlock();

				if(ns == time_point::max())
				{
					journal(journal::trace,"earpc.process.expiry") << 
						"nothing to do; suspending until next notify" <<
						journal::end;

					std::unique_lock<std::mutex> ul(suspend_lock);
					suspend_cv.wait(ul);
					journal(journal::trace,"earpc.process.expiry") << "resuming on notify" << journal::end;
				}

				else
				{
					journal(journal::trace,"earpc.process.expiry") << 
						"nothing to do; suspending for " <<
						std::dec << tp2msec(time_point(ns-clock::now())) << " msec" <<
						journal::end;

					std::unique_lock<std::mutex> ul(suspend_lock);
					suspend_cv.wait_until(ul,ns);
					journal(journal::trace,"earpc.process.expiry") << "resuming on timeout" << journal::end;
				}
			}
		}

		static void notify()
		{
			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}

	};

	template<typename e>
	std::mutex expiry<e>::suspend_lock;

	template<typename e>
	std::condition_variable expiry<e>::suspend_cv;
}}
#endif
