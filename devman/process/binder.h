#ifndef DEVMAN_PROCESS_BINDER_H
# define DEVMAN_PROCESS_BINDER_H
namespace devman {
namespace process {

template<typename TEnv>
class binder
{
	typedef typename TEnv::roles_type roles_type;

	typedef typename TEnv::devices_type devices_type;

	constexpr static devices_type &devices = TEnv::devices;

	constexpr static roles_type  &roles    = TEnv::roles;

	constexpr static std::mutex &devices_lock = TEnv::devices_lock;

	constexpr static std::mutex &roles_lock = TEnv::roles_lock;

	
	static std::mutex suspend_lock;

	static std::condition_variable suspend_cv;

	static volatile bool _running;

	static volatile bool _suspended;

	static std::thread *_proc;

	static journal jrn(uint8_t level)
	{ return journal(level,"devman.process.binder"); }

	static void start()
	{
		jrn(journal::debug) << "initializing" << journal::end;
		while(_running)
		{
			roles_lock.lock();
			devices_lock.lock();

			for(auto dev : devices)
				if(dev->is_active())
				{
					if(!dev->is_bound())
						for(auto role : roles)
							if(
								!role->is_bound() &&
								dev->name == role->name
							)
							{
								jrn(journal::trace) << "binding unbound active device " << std::hex << dev->serial <<
									" to corresponding unbound role `" << role->name << "'" <<
									journal::end;

								dev->bind(role);
								break;
							}
				}

				else if(dev->is_bound())
				{
					jrn(journal::trace) << "unbinding inactive device " << std::hex << dev->serial << journal::end;
					dev->unbind();
				}

			_suspended = true;
			devices_lock.unlock();
			roles_lock.unlock();
			{
				std::unique_lock<std::mutex> ul(suspend_lock);
				if(_suspended)
				{
					jrn(journal::trace) << "nothing to do; suspending until next notify" << journal::end;
					suspend_cv.wait(ul);
					_suspended = false;
					jrn(journal::trace) << "resuming" << journal::end;
				}
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
		pthread_setname_np(_proc->native_handle(),"devman binder");
#endif
	}

	static void uninit()
	{
		if(_proc)
		{
			_running = false;
			notify();
			_proc->join();
		}
	}

	static void notify()
	{
		std::lock_guard<std::mutex> lg(suspend_lock);
		_suspended = false;
		suspend_cv.notify_one();
	}
};

template<typename e>
std::mutex binder<e>::suspend_lock;

template<typename e>
std::condition_variable binder<e>::suspend_cv;

template<typename e>
volatile bool binder<e>::_running;

template<typename e>
volatile bool binder<e>::_suspended;

template<typename e>
std::thread *binder<e>::_proc;

}}
#endif
