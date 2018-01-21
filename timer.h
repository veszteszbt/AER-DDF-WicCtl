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

		struct prop_value_config : public property_config_base
		{
			typedef uint64_t cfg_value_type;

			static const uint32_t cfg_class_id = TConfig::cfg_class_id;

			static const uint32_t cfg_member_id = TConfig::cfg_member_id;

			static const uint32_t cfg_cooldown_time = 0;

			static const bool cfg_commit_change_only = true;
		};
		typedef wicp::local_property<prop_value_config> prop_value;

		struct prop_running_config : public property_config_base
		{
			typedef bool cfg_value_type;

			static const uint32_t cfg_class_id = TConfig::cfg_class_id;

			static const uint32_t cfg_member_id = TConfig::cfg_member_id+1;

			static const uint32_t cfg_cooldown_time = 0;

			static const bool cfg_commit_change_only = true;
		};
		typedef wicp::local_property<prop_running_config> prop_running;
	public:
		static const uint32_t interval = TConfig::cfg_interval;
	private:
		static std::thread *proc;

		static volatile bool _running;

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
				if(!_running)
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
				if(!_running)
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
				prop_value::value(prop_value::value()+1);

			}
		}

		
		static void notify()
		{
			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}

		static void value_change_handler()
		{ journal(journal::trace,"wic.timer") << TConfig::name << ": value changed to " << std::dec << prop_value::value() << journal::end; }


		static void running_change_handler()
		{
			const bool v = prop_running::value();
			lock.lock();
			if(_running == v)
			{
				lock.unlock();
				return;
			}
			_running = v;
			if(v)
				start_time = clock::now();
			lock.unlock();
			notify();
			journal(journal::trace,"wic.timer") << TConfig::name << ": " << (v?"started":"stopped") << journal::end;
		}
	public:
		static void init()
		{
			prop_value::init(0);
			prop_running::init(0);
			_running = false;
			silent = false;
			prop_running::on_change += running_change_handler;
			prop_value::on_change += value_change_handler;
			proc = new std::thread(thread_start);
		}

		static void uninit()
		{
			delete proc;
			prop_running::uninit();
			prop_value::uninit();
		}

		static uint64_t value()
		{ return prop_value::value(); }

		static void value(uint64_t v)
		{
			prop_value::value(v);
			lock.lock();
			silent = true;
			start_time = clock::now();
			lock.unlock();
			notify();
		}

		static bool running()
		{ return prop_running::value(); }

		static void running(bool v)
		{ prop_running::value(v); }

		static void start()
		{ running(true); }

		static void reset()
		{ value(0); }

		static void stop()
		{ running(false); }


		static void remote_add(wicp::role_type &role)
		{
			prop_value::remote_add(role);
			prop_running::remote_add(role);
		}


		constexpr static sched::listener  &on_value_change = prop_value::on_change;

		constexpr static sched::listener  &on_running_change = prop_running::on_change;
	};

	template<typename c>
	std::thread *timer<c>::proc;

	template<typename c>
	volatile bool timer<c>::_running;

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
