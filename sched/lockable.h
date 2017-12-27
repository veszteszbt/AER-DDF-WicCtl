#ifndef SCHED_LOCKABLE_H
# define SCHED_LOCKABLE_H
# include <mutex>
namespace sched {

template<typename T>
struct lockable : T, std::mutex
{
	template<typename... Targs>
	lockable(Targs... args)
		: T(args...)
	{}
};

}
#endif
