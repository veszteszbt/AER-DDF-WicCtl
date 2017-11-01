#ifndef TYPES_TIME_H
# define TYPES_TIME_H
# include <chrono>
namespace types {
namespace time {
	template<typename Tclock, typename Trep>
	uint64_t nsec(std::chrono::time_point<Tclock,Trep> t)
	{ nsec(std::chrono::time_point_cast<std::chrono::nanoseconds>(t)); }

	template<typename Tclock>
	uint64_t nsec(std::chrono::time_point<Tclock,std::chrono::nanoseconds> t)
	{ return t.time_since_epoch(); }

	template<typename Trep, typename Tratio>
	int64_t nsec(std::chrono::duration<Trep,Tratio> t)
	{ nsec(std::chrono::duration_cast<std::chrono::nanoseconds>(t)); }

	int64_t nsec(std::chrono::nanoseconds t)
	{ return t.count(); }
}}
#endif
