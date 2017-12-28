#ifndef SCHED_LISTENER_H
# define SCHED_LISTENER_H
# include <list>
# include <sched/lockable.h>
namespace sched {

template<typename... Targs>
struct event
{
	typedef void(*handler_type)(Targs...);

private:
	typedef std::list<handler_type> handlers_type;

	lockable<handlers_type> handlers;

public:
	event<Targs...> &operator+=(handler_type h)
	{
		handlers.lock();
		handlers.push_back(h);
		handlers.unlock();
		return *this;
	}

	event<Targs...> &operator-=(handler_type h)
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

	event<Targs...> &operator()(Targs... args)
	{
		handlers.lock();
		handlers_type h(handlers);
		handlers.unlock();
		for(
			typename handlers_type::iterator i = h.begin();
			i != h.end();
			(*i++)(args...)
		);
		return *this;
	}
};

typedef event<> listener;

}
#endif
