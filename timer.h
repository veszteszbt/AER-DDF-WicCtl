#ifndef WIC_TIMER_H
# define WIC_TIMER_H
# include <cstdint>
# include <mutex>
# include <thread>
# include <condition_variable>
# include <property_config_base.h>
namespace wic
{
	template<typename TConfig>
	class timer
	{
		typedef typename property_config_base::cfg_clock clock;

		struct property_config : public property_config_base
		{
			typedef uint64_t cfg_value_type;

			static const uint32_t cfg_class_id = TConfig::cfg_class_id;

			static const uint32_t cfg_member_id = TConfig::cfg_member_id;

			static const uint32_t cfg_cooldown_time = 0;

			static const bool cfg_commit_change_only = true;
		};
		typedef wicp::local_property<property_config> property;

		static const uint32_t interval = TConfig::cfg_interval;

		static std::thread *proc;

		static volatile bool running;

		static typename clock::time_point start_time;

		static std::mutex lock;

		static std::mutex               suspend_lock;

		static std::condition_variable  suspend_cv;

		static void thread_start()
		{
			while(1)
			{
				lock.lock();
				if(!running)
				{
					lock.unlock();
					std::unique_lock<std::mutex> ul(suspend_lock);
					suspend_cv.wait(ul);
					continue;
				}

				typename clock::time_point t =
					start_time + std::chrono::milliseconds(static_cast<uint32_t>(interval));
				lock.unlock();

				{
					std::unique_lock<std::mutex> ul(suspend_lock);
					suspend_cv.wait_until(ul,t);
				}

				lock.lock();
				if(!running)
				{
					lock.unlock();
					continue;
				}
				start_time = t;
				lock.unlock();
				std::cout << "<<< timer fire >>>" << std::endl;
				property::value(property::value()+1);

			}
		}
	public:
		static void init()
		{
			property::init();
			running = false;
			proc = new std::thread(thread_start);
		}

		static void uninit()
		{
			delete proc;
			property::uninit();
		}

		static void start()
		{
			lock.lock();
			if(running)
			{
				lock.unlock();
				return;
			}
			running = true;
			start_time = clock::now();
			lock.unlock();
			property::value(0);
			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}

		static void stop()
		{
			lock.lock();
			if(!running)
			{
				lock.unlock();
				return;
			}
			running = false;
			lock.unlock();
			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}

		static uint64_t value()
		{ return property::value(); }

		static void value(uint64_t v)
		{ property::value(v); }

		constexpr static listener_t  &on_change = property::on_change;
	};

	template<typename c>
	std::thread *timer<c>::proc;

	template<typename c>
	volatile bool timer<c>::running;

	template<typename c>
	typename timer<c>::clock::time_point timer<c>::start_time;

	template<typename c>
	std::mutex               timer<c>::lock;

	template<typename c>
	std::mutex               timer<c>::suspend_lock;

	template<typename c>
	std::condition_variable  timer<c>::suspend_cv;
}
#endif
