#ifndef WICP_TYPES_PROPERTY_RECORD_H
# define WICP_TYPES_PROPERTY_RECORD_H
# include <chrono>
# include <mutex>
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

		static std::mutex history_lock;

		static bool cooldown_pending;
	};

	template <typename Tvalue>
	typename property_record<Tvalue>::history_type property_record<Tvalue>::history;
	
	template <typename Tvalue>
	typename property_record<Tvalue>::value_type property_record<Tvalue>::local_value;
	
	template <typename Tvalue>
	sched::listener property_record<Tvalue>::on_change;
	
	template <typename Tvalue>
	std::mutex property_record<Tvalue>::history_lock;
	
	template <typename Tvalue>
	bool property_record<Tvalue>::cooldown_pending;

}}
#endif