#ifndef DEVMAN_PROCESS_REPORT_H
# define DEVMAN_PROCESS_REPORT_H
namespace devman {
namespace process {

template<typename TEnv>
class report
{
	typedef typename TEnv::clock   clock;

	typedef typename TEnv::time_point time_point;

	struct record_type
	{
		uint64_t               serial;
		time_point             timestamp;
		wicp::call_report_type report;

		constexpr record_type(uint64_t s, wicp::call_report_type r)
			: serial(s)
			, timestamp(clock::now())
			, report(r)
		{}
	};

	typedef sched::lockable<std::list<record_type>> queue_type;

	typedef typename TEnv::device_type device_type;

	typedef typename TEnv::devices_type devices_type;

	constexpr static std::mutex &devices_lock = TEnv::devices_lock;

	constexpr static std::mutex &roles_lock = TEnv::roles_lock;

	constexpr static devices_type &devices = TEnv::devices;

	static queue_type queue;
	
	static std::mutex suspend_lock;

	static std::condition_variable suspend_cv;

	static volatile bool _running;

	static volatile bool _suspended;

	static std::thread  *_proc;

	static journal jrn(uint8_t s)
	{ return journal(s,"devman.process.report"); }

	static void process_record(const record_type &r)
	{
		roles_lock.lock();
		devices_lock.lock();

		device_type *dev = 0;
		for(auto i : devices)
			if(i->serial == r.serial)
			{
				dev = i;
				break;
			}

		if(!dev)
		{
			jrn(journal::critical) << "no known device for queued serial " << std::hex << r.serial << journal::end;
			devices_lock.unlock();
			roles_lock.unlock();
			return;
		}

		if(!r.report.success)
		{
			jrn(journal::error) <<
				"serial: " << std::hex << r.serial <<
				"; call failure; setting device to unseen state" <<
				journal::end;

			dev->set_unseen();
		}

		else if(r.report.latency >= 0)
		{
			if(dev->last_latency_info != time_point::min())
			{
				uint64_t d = ::types::time::msec(r.timestamp-dev->last_latency_info);
				if(d >= 800)
					dev->latency = r.report.latency;

				dev->latency = (dev->latency*300+r.report.latency*d)/(300+d);

				jrn(journal::trace) <<
					"serial: " << std::hex << r.serial <<
					"; latency info updated: " << std::dec << dev->latency << " msec" <<
					journal::end;


			}
			else
				dev->latency = r.report.latency;

			dev->last_latency_info = r.timestamp;
			dev->calculate_health();
		}

		devices_lock.unlock();
		roles_lock.unlock();
	}

	static void start()
	{
		jrn(journal::debug) << "initializing" << journal::end;
		while(_running)
		{
			queue.lock();
			if(queue.empty())
			{
				_suspended = true;
				queue.unlock();
			}
			else
			{
				const record_type r(queue.front());
				queue.pop_front();
				queue.unlock();
				process_record(r);
				continue;

			}


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
		pthread_setname_np(_proc->native_handle(),"devman report");
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

	static void notify(uint64_t serial, wicp::call_report_type report)
	{
		queue.lock();
		queue.emplace_back(serial,report);
		queue.unlock();
		journal j = jrn(journal::trace);
		j <<
			"device: " << std::hex << serial <<
			"; queued report of " << (report.success?"successful":"unsuccessful") << " call";

		if(report.latency >= 0)
			j << "; latency is " << std::dec << report.latency << " msec";

		j << journal::end;
		std::lock_guard<std::mutex> lg(suspend_lock);
		_suspended = false;
		suspend_cv.notify_one();
	}
};

template<typename e>
typename report<e>::queue_type report<e>::queue;

template<typename e>
std::mutex report<e>::suspend_lock;

template<typename e>
std::condition_variable report<e>::suspend_cv;

template<typename e>
volatile bool report<e>::_running;

template<typename e>
volatile bool report<e>::_suspended;

template<typename e>
std::thread  *report<e>::_proc;
}}
#endif
