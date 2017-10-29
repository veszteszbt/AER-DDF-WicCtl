#ifndef WICP_PROCESS_COMMIT_H
# define WICP_PROCESS_COMMIT_H
# include <log.h>
# include <cstdint>
# include <mutex>
# include <thread>
# include <atomic>
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

		static std::atomic<bool>        is_running;


		static void cooldown_finish()
		{
			log(log::trace,"wicp.commit") << "cooldown finished" << std::endl <<
				"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
				log::end;
				
			if(change_only || value != history.front().value)
				notify();
		}

		static void start()
		{
			log(log::debug,"wicp.commit") << "initialized" << std::endl <<
				"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
				log::end;
			while(is_running)
			{
				std::unique_lock<std::mutex> ul(suspend_lock);
				history_lock.lock();
				if(change_only && !history.empty() && value == history.front().value)
				{
					log(log::trace,"wicp.commit") << "no change; suspending until next notify" << std::endl <<
						"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
						log::end;
					history_lock.unlock();
					suspend_cv.wait(ul);
					continue;
				}
				else
					cooldown_pending = true;
					log(log::trace,"wicp.commit") << "comitting new value to history" << std::endl <<
						"  length: " << history.size() << std::endl <<
						"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
						log::end;

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
			log(log::debug,"wicp.commit") << "uninitialized" << std::endl <<
				"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
				log::end;
		}
	public:

		static void init()
		{
			is_running = true;
			proc_thread = new std::thread(start);

#ifdef __linux__			
			pthread_setname_np(proc_thread->native_handle(),"wicp commit");
#endif
			
		}

		static void uninit()
		{
			is_running = false;
			proc_thread->join();
			delete proc_thread;
		}

		static void notify()
		{
			if(cooldown_pending)
			{
				log(log::trace,"wicp.commit") << "cooldown pending; ignoring notify" << std::endl <<
					"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
					log::end;

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

	template<typename c>
	std::atomic<bool>        commit<c>::is_running;
}}
#endif
