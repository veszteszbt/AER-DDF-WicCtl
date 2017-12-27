#ifndef TYPES_TIME_H
# define TYPES_TIME_H
# include <chrono>
# include <sstream>
# include <iomanip>
namespace types {
namespace time {

	// duration to nanoseconds
	inline int64_t nsec(std::chrono::nanoseconds t)
	{ return t.count(); }

	template<typename Trep, typename Tratio>
	int64_t nsec(std::chrono::duration<Trep,Tratio> t)
	{ return nsec(std::chrono::duration_cast<std::chrono::nanoseconds>(t)); }

	// time_point to nanoseconds
	template<typename Tclock>
	uint64_t nsec(std::chrono::time_point<Tclock,std::chrono::nanoseconds> t)
	{ return nsec(t.time_since_epoch()); }

	template<typename Tclock, typename Trep>
	uint64_t nsec(std::chrono::time_point<Tclock,Trep> t)
	{ return nsec(std::chrono::time_point_cast<std::chrono::nanoseconds>(t)); }

	// duration to microseconds
	inline int64_t usec(std::chrono::microseconds t)
	{ return t.count(); }

	template<typename Trep, typename Tratio>
	int64_t usec(std::chrono::duration<Trep,Tratio> t)
	{ return usec(std::chrono::duration_cast<std::chrono::microseconds>(t)); }

	template<typename Trep, typename Tratio>
	double fusec(std::chrono::duration<Trep,Tratio> t)
	{ return static_cast<double>(nsec(t))/1000; }

	// time_point to microseconds
	template<typename Tclock>
	uint64_t usec(std::chrono::time_point<Tclock,std::chrono::microseconds> t)
	{ return usec(t.time_since_epoch()); }

	template<typename Tclock, typename Trep>
	uint64_t usec(std::chrono::time_point<Tclock,Trep> t)
	{ return usec(std::chrono::time_point_cast<std::chrono::microseconds>(t)); }

	// duration to milliseconds
	inline int64_t msec(std::chrono::milliseconds t)
	{ return t.count(); }

	template<typename Trep, typename Tratio>
	int64_t msec(std::chrono::duration<Trep,Tratio> t)
	{ return msec(std::chrono::duration_cast<std::chrono::milliseconds>(t)); }

	template<typename Trep, typename Tratio>
	double fmsec(std::chrono::duration<Trep,Tratio> t)
	{ return static_cast<double>(nsec(t))/1000000; }

	// time_point to milliseconds
	template<typename Tclock>
	uint64_t msec(std::chrono::time_point<Tclock,std::chrono::milliseconds> t)
	{ return msec(t.time_since_epoch()); }

	template<typename Tclock, typename Trep>
	uint64_t msec(std::chrono::time_point<Tclock,Trep> t)
	{ return msec(std::chrono::time_point_cast<std::chrono::milliseconds>(t)); }

	template<typename Tclock, typename Trep>
	std::string timestamp(std::chrono::time_point<Tclock,Trep> t)
	{
		static const uint64_t epoc = 62168515200000000;
		const uint64_t U  = usec(t)+epoc;
		const uint64_t s  = U/1000000;
		const uint32_t d  = s/86400;
		const uint32_t q  = d/1461;
		const uint16_t qd = d%1461;
		uint16_t Y  = q*4;
		uint16_t m,D,yd;
		if(qd < 366)
		{
			yd = qd;
			if(yd < 31) //jan
			{ m = 1; D = yd; }
			else if(yd < 60) //feb
			{ m = 2; D = yd-31+1; }
			else if(yd < 91) // mar
			{ m = 3; D = yd-60+1; }
			else if(yd < 121) // apr
			{ m = 4; D = yd-91+1; }
			else if(yd < 152) // may
			{ m = 5; D = yd-121+1; }
			else if(yd < 183) // jun
			{ m = 6; D = yd-152+1; }
			else if(yd < 213) // jul
			{ m = 7; D = yd-182+1; }
			else if(yd < 244) // aug
			{ m = 8; D = yd-213+1; }
			else if(yd < 274) // sep
			{ m = 9; D = yd-244+1; }
			else if(yd < 305) // oct
			{ m = 10; D = yd-274+1; }
			else if(yd < 335) // nov
			{ m = 11; D = yd-305+1; }
			else if(yd < 366) // dec
			{ m = 12; D = yd-335+1; }
		}
		else
		{
			Y += 1+(qd-366)/365;
			yd = (qd-366)%365;
			if(yd < 31) //jan
			{ m = 1; D = yd+1; }
			else if(yd < 59) //feb
			{ m = 2; D = yd-31+1; }
			else if(yd < 90) // mar
			{ m = 3; D = yd-59+1; }
			else if(yd < 120) // apr
			{ m = 4; D = yd-90+1; }
			else if(yd < 151) // may
			{ m = 5; D = yd-120+1; }
			else if(yd < 182) // jun
			{ m = 6; D = yd-151+1; }
			else if(yd < 212) // jul
			{ m = 7; D = yd-181+1; }
			else if(yd < 243) // aug
			{ m = 8; D = yd-212+1; }
			else if(yd < 273) // sep
			{ m = 9; D = yd-243+1; }
			else if(yd < 304) // oct
			{ m = 10; D = yd-273+1; }
			else if(yd < 334) // nov
			{ m = 11; D = yd-304+1; }
			else if(yd < 365) // dec
			{ m = 12; D = yd-334+1; }
		}
		const uint32_t F = U%1000000;
		const uint16_t S = s%60;
		const uint16_t M = (s/60)%60;
		const uint16_t H = (s/3600)%24;

		std::stringstream r;
		r << std::dec <<
			Y <<
			'.' <<
			std::setfill('0') << std::setw(2) << m <<
			'.' <<
			std::setfill('0') << std::setw(2) << D <<
			' ' <<
			std::setfill('0') << std::setw(2) << H <<
			':' <<
			std::setfill('0') << std::setw(2) << M <<
			':' <<
			std::setfill('0') << std::setw(2) << S <<
			'.' <<
			std::setfill('0') << std::setw(6) << F;
		return r.str();
	}
}}
#endif
