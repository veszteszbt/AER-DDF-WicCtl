#ifndef SCHED_PROCESS_H
# define SCHED_PROCESS_H
# include <thread>
# include <mutex>
# include <condition_variable>
# include <chrono>
namespace sched {

class process
{
	typedef std::chrono::high_resolution_clock clock;

	std::thread *_thread;

	volatile bool _is_running;

	volatile bool _is_suspended;

	std::condition_variable suspend_cv;

	std::mutex              suspend_lock;

	inline void _run()
	{
		while(_is_running)
			exec();
	}

	virtual const std::string &name();

	virtual void init();
	
	virtual void exec();

	virtual void uninit();


protected:
	process();

	void suspend();

	template<typename Tdur>
	void suspend(Tdur duration)
	{
		std::unique_lock<std::mutex> ul(suspend_lock);
		suspend_cv.wait_until(ul,clock::now()+duration);
	}

public:

	virtual ~process();

	void start();

	void stop();

	void notify();

	inline bool suspended()
	{ return _is_suspended; }
};

}
#endif
