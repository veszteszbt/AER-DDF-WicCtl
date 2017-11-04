#include <sched/process.h>
namespace sched {

void process::init() {}	

void process::exec() {}

void process::uninit() {}

const std::string &process::name()
{ 
	static const std::string n = "sched::process";
	return n;
}

void process::suspend()
{
	std::unique_lock<std::mutex> ul(suspend_lock);
	suspend_cv.wait(ul);
}

process::process()
	: _thread(0)
	, _is_running(false)
{}


process::~process()
{ delete _thread; }

void process::start()
{
	if(_is_running)
		return;
	_is_running = true;
	init();
	delete _thread;
	_thread = new std::thread(std::bind(&sched::process::_run,this));
#ifdef __linux__
	pthread_setname_np(_thread->native_handle(),name().c_str());
#endif
}

void process::stop()
{
	if(_thread)
	{
		_is_running = false;
		_thread->join();
		uninit();
		delete _thread;
		_thread = 0;
	}	
}

void process::notify()
{
	std::lock_guard<std::mutex> lg(suspend_lock);
	suspend_cv.notify_one();
}

}
