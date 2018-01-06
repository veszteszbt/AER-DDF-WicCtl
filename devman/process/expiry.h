#ifndef DEVMAN_PROCESS_EXPIRY_H
# define DEVMAN_PROCESS_EXPIRY_H
namespace devman {
namespace process {

template<typename TEnv>
class expiry
{
	typedef typename TEnv::device_type device_type;

	typedef typename TEnv::devices_type devices_type;

	typedef typename TEnv::clock clock;

	typedef typename TEnv::time_point time_point;

	constexpr static std::mutex &devices_lock = TEnv::devices_lock;

	constexpr static std::mutex &roles_lock = TEnv::roles_lock;

	constexpr static devices_type &devices = TEnv::devices;

	static std::mutex suspend_lock;

	static std::condition_variable suspend_cv;

	static volatile bool _running;

	static volatile bool _suspended;

	static std::thread  *_proc;

	static journal jrn(uint8_t s)
	{ return journal(s,"devman.process.expiry"); }

	static void start()
	{
		jrn(journal::debug) << "initializing" << journal::end;
		while(_running)
		{
			roles_lock.lock();
			devices_lock.lock();

			time_point ns = time_point::max();
	
			for(auto dev : devices)
			{
				if(dev->state == types::state::unseen)
					continue;

				if((dev->expiry) < clock::now())
				{
					jrn(journal::error) <<
						"serial: " << std::hex << dev->serial <<
						"; silence timeout expired; setting device to unseen state" <<
						journal::end;

					dev->set_unseen();
				}
				else if((dev->expiry) < ns)
					ns = (dev->expiry);
			}

			devices_lock.unlock();
			roles_lock.unlock();
			{
				std::unique_lock<std::mutex> ul(suspend_lock);
				if(_suspended)
				{
					if(ns == time_point::max())
					{
						jrn(journal::trace) << "nothing to do; suspending until next notify" << journal::end;
						suspend_cv.wait(ul);
					}
					else
					{
						jrn(journal::trace) <<
							"nothing to do; suspending for " <<
							std::dec << ::types::time::msec(ns-clock::now()) << " msec" <<
							journal::end;

						suspend_cv.wait_until(ul,ns);
					}
					jrn(journal::trace) << "resuming" << journal::end;
				}
				_suspended = true;
			}
		}
		jrn(journal::debug) << "uninitializing" << journal::end;
	}

public:
	static void init()
	{
		_running = true;
		_suspended = false;
		_proc = new std::thread(start);
#ifdef __linux__
		pthread_setname_np(_proc->native_handle(),"devman expiry");
#endif
	}

	static void uninit()
	{
		_running = false;
		std::lock_guard<std::mutex> lg(suspend_lock);
		_suspended = false;
		suspend_cv.notify_one();
		_proc->join();
		delete _proc;
	}


	static void notify()
	{
		std::lock_guard<std::mutex> lg(suspend_lock);
		_suspended = false;
		suspend_cv.notify_one();
	}
};

template<typename e>
std::mutex expiry<e>::suspend_lock;

template<typename e>
std::condition_variable expiry<e>::suspend_cv;

template<typename e>
volatile bool expiry<e>::_running;

template<typename e>
volatile bool expiry<e>::_suspended;

template<typename e>
std::thread  *expiry<e>::_proc;

}}
#endif
