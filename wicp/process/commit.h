#ifndef WICP_PROCESS_COMMIT_H
# define WICP_PROCESS_COMMIT_H
# include <cstdint>
# include <mutex>
# include <thread>
# include <condition_variable>
# include <net/ipv4_address.h>
# include <pthread.h>
namespace wicp {
namespace process
{
	template<typename TEnv>
	class commit
	{
		typedef typename TEnv::clock           clock;

		typedef typename TEnv::proc_sync       proc_sync;

		typedef typename TEnv::proc_log        proc_log;

		typedef typename TEnv::history_type    history_type;

		typedef typename TEnv::history_record  history_record;

		typedef typename TEnv::value_type      value_type;

		
		static const uint32_t cooldown_time                         = TEnv::cooldown_time;

		constexpr static history_type         &history              = TEnv::history;

		constexpr static std::mutex           &history_lock         = TEnv::history_lock;


		constexpr static value_type           &value                = TEnv::value;

		constexpr static const bool            change_only          = TEnv::commit_change_only;

                static std::mutex               suspend_lock;

                static std::condition_variable  suspend_cv;

		static bool                     cooldown_pending;

		static std::thread             *proc_thread;


		static void cooldown_finish()
		{
//			std::cout << "\e[37;01m - \e[0mwicp commit process: cooldown finished" << std::endl;
			if(change_only || value != history.front().value)
				notify();
		}

		static void start()
		{
//			std::cout << "\e[32;01m - \e[0mwicp commit process: initialized" << std::endl;
			while(1)
			{
				std::unique_lock<std::mutex> ul(suspend_lock);
				history_lock.lock();
				if(change_only && !history.empty() && value == history.front().value)
				{
//					std::cout << "\e[37;01m - \e[0mwicp commit process: no change" << std::endl;
					history_lock.unlock();
					suspend_cv.wait(ul);
					continue;
				}
				else
					cooldown_pending = true;
//				std::cout <<
//					"\e[37;01m - \e[0mwicp commit process: comitting new value to history; length is " <<
//					history.size() <<
//				std::endl;


				const history_record hr(value);
				history.push_front(hr);
				if(history.size() > 16)
					history.pop_back();
				history_lock.unlock();

				TEnv::sync_local();

				proc_sync::notify();
				proc_log::notify();

				suspend_cv.wait_until(ul,hr.time + std::chrono::milliseconds(static_cast<uint32_t>(cooldown_time)));
				cooldown_pending = false;
			}
		}
	public:

		static void init()
		{
			proc_thread = new std::thread(start);

#ifdef __linux__			
			pthread_setname_np(proc_thread->native_handle(),"wicp commit");
#endif
			
		}

		static void uninit()
		{
			delete proc_thread;
		}

		static void notify()
		{
			if(cooldown_pending)
			{
//				std::cout << "\e[33;01m - \e[0mwicp commit process: cooldown pending; omitting new value" << std::endl;
				return;
			}
			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();

		}
	};

	template<typename c>
	bool commit<c>::cooldown_pending;

	template<typename c>
	std::mutex commit<c>::suspend_lock;

	template<typename c>
	std::thread *commit<c>::proc_thread;

	template<typename c>
	std::condition_variable commit<c>::suspend_cv;
}}
#endif
