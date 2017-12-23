#ifndef TYPES_TIME_H
# define TYPES_TIME_H
# include <chrono>
namespace types {
namespace time {

	// time_point to nanoseconds
	template<typename Tclock>
	uint64_t nsec(std::chrono::time_point<Tclock,std::chrono::nanoseconds> t)
	{ return t.time_since_epoch(); }

	template<typename Tclock, typename Trep>
	uint64_t nsec(std::chrono::time_point<Tclock,Trep> t)
	{ nsec(std::chrono::time_point_cast<std::chrono::nanoseconds>(t)); }

	// duration to nanoseconds
	int64_t nsec(std::chrono::nanoseconds t)
	{ return t.count(); }

	template<typename Trep, typename Tratio>
	int64_t nsec(std::chrono::duration<Trep,Tratio> t)
	{ nsec(std::chrono::duration_cast<std::chrono::nanoseconds>(t)); }

	// time_point to microseconds
	template<typename Tclock>
	uint64_t usec(std::chrono::time_point<Tclock,std::chrono::microseconds> t)
	{ return t.time_since_epoch(); }

	template<typename Tclock, typename Trep>
	uint64_t usec(std::chrono::time_point<Tclock,Trep> t)
	{ usec(std::chrono::time_point_cast<std::chrono::microseconds>(t)); }

	// duration to microseconds
	int64_t usec(std::chrono::microseconds t)
	{ return t.count(); }

	template<typename Trep, typename Tratio>
	int64_t usec(std::chrono::duration<Trep,Tratio> t)
	{ usec(std::chrono::duration_cast<std::chrono::microseconds>(t)); }

	template<typename Trep, typename Tratio>
	double fusec(std::chrono::duration<Trep,Tratio> t)
	{ return static_cast<double>(nsec(t))/1000; }

	// time_point to milliseconds
	template<typename Tclock>
	uint64_t msec(std::chrono::time_point<Tclock,std::chrono::milliseconds> t)
	{ return t.time_since_epoch(); }

	template<typename Tclock, typename Trep>
	uint64_t msec(std::chrono::time_point<Tclock,Trep> t)
	{ msec(std::chrono::time_point_cast<std::chrono::milliseconds>(t)); }

	// duration to milliseconds
	int64_t msec(std::chrono::milliseconds t)
	{ return t.count(); }

	template<typename Trep, typename Tratio>
	int64_t msec(std::chrono::duration<Trep,Tratio> t)
	{ msec(std::chrono::duration_cast<std::chrono::milliseconds>(t)); }

	template<typename Trep, typename Tratio>
	double fmsec(std::chrono::duration<Trep,Tratio> t)
	{ return static_cast<double>(nsec(t))/1000000; }


}}
#endif
