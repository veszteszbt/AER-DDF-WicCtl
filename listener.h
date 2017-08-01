#ifndef LISTENER_H
# define LISTENER_H
# include <list>
struct listener_t
{
	typedef void(*handler_type)();

private:
	typedef std::list<handler_type> handlers_type;

	handlers_type handlers;

public:
	listener_t &operator+=(handler_type h)
	{
		handlers.push_back(h);
		return *this;
	}

	listener_t &operator-=(handler_type h)
	{
		for(
			handlers_type::iterator i = handlers.begin();
			i != handlers.end();
			++i
		)
			if(*i == h)
			{
				handlers.erase(i);
				break;
			}

		return *this;
	}

	listener_t &operator()()
	{
		for(
			handlers_type::iterator i = handlers.begin();
			i != handlers.end();
			(*i++)()
		);
		return *this;
	}
};
#endif
