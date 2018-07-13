#ifndef WICP_TYPES_PROPERTY_RECORD_H
# define WICP_TYPES_PROPERTY_RECORD_H
# include <chrono>
# include <list>
# include <sched/listener.h>
namespace wicp {
namespace types {

	template <typename Tvalue>
	struct property_record
	{
		typedef Tvalue value_type;

		typedef std::chrono::high_resolution_clock clock;
	
		struct history_record
		{
			typename clock::time_point time;

			value_type                value;

			history_record() {}

			history_record(value_type v)
				: time(clock::now())
				, value(v)
			{}
		};

		typedef std::list<history_record> history_type;

		static history_type history;

		static value_type local_value;

		static sched::listener on_change;
	};
}}
#endif