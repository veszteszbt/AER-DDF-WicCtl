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
	public:
		static const uint32_t interval = TConfig::cfg_interval;
	private:
		static std::thread *proc;

		static volatile bool running;

		static volatile bool silent;

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
				if(silent)
				{
					silent = false;
					lock.unlock();
					continue;
				}
				start_time = t;
				lock.unlock();
				property::value(property::value()+1);

			}
		}

		static void notify()
		{
			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}
	public:
		static void init()
		{
			property::init();
			running = false;
			silent = false;
			proc = new std::thread(thread_start);
		}

		static void uninit()
		{
			delete proc;
			property::uninit();
		}

		static uint64_t value()
		{ return property::value(); }

		static void value(uint64_t v)
		{
			property::value(v);
			lock.lock();
			silent = true;
			start_time = clock::now();
			lock.unlock();
			notify();
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
			notify();
		}

		static void reset()
		{ value(0); }

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

		static void remote_add(net::ipv4_address ip)
		{ property::remote_add(ip); }


		constexpr static sched::listener  &on_change = property::on_change;
	};

	template<typename c>
	std::thread *timer<c>::proc;

	template<typename c>
	volatile bool timer<c>::running;

	template<typename c>
	volatile bool timer<c>::silent;

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
