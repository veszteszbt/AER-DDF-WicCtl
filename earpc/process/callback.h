#ifndef EARPC_PROCESS_CALLBACK_H
# define EARPC_PROCESS_CALLBACK_H
# include <sched/process.h>
# include <sched/lockable.h>
# include <functional>
# include <list>
namespace earpc {
namespace process {

template<typename TEnv>
class callback
{
	static sched::lockable<std::list<std::function<void()> > > buffer;

	class callback_process : public sched::process
	{
		virtual const std::string &name()
		{
			static const std::string n("earpc callback");
			return n;
		}

		virtual void init()
		{
			journal(journal::debug,"earpc.process.callback") <<
				"initializing" <<
				journal::end;
		}

		virtual void uninit()
		{
			journal(journal::debug,"earpc.process.callback") <<
				"uninitializing" <<
				journal::end;
		}

		virtual void exec()
		{
			buffer.lock();
			if(buffer.empty())
			{
				buffer.unlock();
				journal(journal::trace,"earpc.process.callback") <<
					"nothing to do; suspending until next notify" <<
					journal::end;
				suspend();
			}

			else
			{
				std::function<void()> f = buffer.front();
				buffer.pop_front();
				buffer.unlock();
				journal(journal::trace,"earpc.process.callback") <<
					"serving callback" <<
					journal::end;
				f();
			}
		}
	public:
		virtual ~callback_process() {}
	};

	static sched::lockable<std::list<callback_process> > processes;

	static const uint16_t max_callback_threads = 512;

public:
	static void init()
	{
		journal(journal::trace,"earpc.process.callback") <<
			"initializing service with 4 workers" <<
			journal::end;
		processes.lock();
		for(int c = 0; c < 4; ++c)
		{
			processes.emplace_back();
			processes.back().start();
		}
		processes.unlock();

		journal(journal::debug,"earpc.process.callback") <<
			"service initialized" <<
			journal::end;
	}

	static void uninit()
	{
		journal(journal::trace,"earpc.process.callback") <<
			"uninitializing workers" <<
			journal::end;
		processes.lock();
		for(auto &p : processes)
			p.stop();
		processes.clear();
		processes.unlock();
		journal(journal::debug,"earpc.process.callback") <<
			"service uninitialized" <<
			journal::end;
	}

	template<typename T>
	static void notify(void(*fn)(T), T t)
	{
		journal(journal::trace,"earpc.process.callback") <<
			"adding new item to queue" <<
			journal::end;
		buffer.lock();
		buffer.push_back(std::bind(fn,t));
		buffer.unlock();

		processes.lock();
		for(auto &p : processes)
			if(p.suspended())
			{
				journal(journal::trace,"earpc.process.callback") <<
					"notifying worker process" <<
					journal::end;
				p.notify();
				processes.unlock();
				return;
			}

		if(processes.size() < max_callback_threads)
		{
			journal(journal::trace,"earpc.process.callback") <<
				"every worker is busy; starting worker #" << processes.size() <<
				journal::end;
			processes.emplace_back();
			processes.back().start();
			processes.unlock();
			return;
		}

		journal(journal::warning,"earpc.process.callback") <<
			"every worker is busy, but not starting new worker as thread number limit " <<
			max_callback_thread << " reached" <<
			journal::end;

		processes.unlock();
	}
};

template<typename e>
sched::lockable<std::list<std::function<void()> > > callback<e>::buffer;

template<typename e>
sched::lockable<std::list<typename callback<e>::callback_process> > callback<e>::processes;

}}
#endif
