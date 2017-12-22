#ifndef TYPES_TIME_H
# define TYPES_TIME_H
# include <chrono>
namespace types {
namespace time {

	// time_point to nanoseconds
	template<typename Tclock, typename Trep>
	uint64_t nsec(std::chrono::time_point<Tclock,Trep> t)
	{ nsec(std::chrono::time_point_cast<std::chrono::nanoseconds>(t)); }

	template<typename Tclock>
	uint64_t nsec(std::chrono::time_point<Tclock,std::chrono::nanoseconds> t)
	{ return t.time_since_epoch(); }

	// duration to nanoseconds
	int64_t nsec(std::chrono::nanoseconds t)
	{ return t.count(); }

	template<typename Trep, typename Tratio>
	int64_t nsec(std::chrono::duration<Trep,Tratio> t)
	{ nsec(std::chrono::duration_cast<std::chrono::nanoseconds>(t)); }

	// time_point to milliseconds
	template<typename Tclock, typename Trep>
	uint64_t msec(std::chrono::time_point<Tclock,Trep> t)
	{ msec(std::chrono::time_point_cast<std::chrono::milliseconds>(t)); }

	template<typename Tclock>
	uint64_t msec(std::chrono::time_point<Tclock,std::chrono::milliseconds> t)
	{ return t.time_since_epoch(); }

	// duration to milliseconds
	int64_t msec(std::chrono::milliseconds t)
	{ return t.count(); }

	template<typename Trep, typename Tratio>
	int64_t msec(std::chrono::duration<Trep,Tratio> t)
	{ msec(std::chrono::duration_cast<std::chrono::milliseconds>(t)); }

}}
#endif
