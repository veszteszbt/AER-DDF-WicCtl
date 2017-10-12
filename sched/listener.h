#ifndef SCHED_LISTENER_H
# define SCHED_LISTENER_H
# include <list>
# include <sched/lockable.h>
namespace sched {

struct listener
{
	typedef void(*handler_type)();

private:
	typedef std::list<handler_type> handlers_type;

	lockable<handlers_type> handlers;

public:
	listener &operator+=(handler_type h)
	{
		handlers.lock();
		handlers.push_back(h);
		handlers.unlock();
		return *this;
	}

	listener &operator-=(handler_type h)
	{
		handlers.lock();
		for(
			typename handlers_type::iterator i = handlers.begin();
			i != handlers.end();
			++i
		)
			if(*i == h)
			{
				handlers.erase(i);
				break;
			}
		handlers.unlock();
		return *this;
	}

	listener &operator()()
	{
		handlers.lock();
		handlers_type h(handlers);
		handlers.unlock();
		for(
			typename handlers_type::iterator i = h.begin();
			i != h.end();
			(*i++)()
		);
		return *this;
	}
};

}
#endif
