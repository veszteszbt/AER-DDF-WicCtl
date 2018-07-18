#ifndef WICP_TYPES_PROPERTY_RECORD_H
# define WICP_TYPES_PROPERTY_RECORD_H
# include <chrono>
# include <mutex>
# include <list>
# include <sched/listener.h>
namespace wicp {
namespace types 
{
	template <typename TcallId, typename Tvalue>
	struct property_record_base
	{
		typedef TcallId call_id_type;

		typedef Tvalue value_type;

		typedef std::chrono::high_resolution_clock clock;
	
		struct remote_record
		{
			typename clock::time_point sync_timestamp;

			typename clock::time_point pending_timestamp;

			call_id_type call_id;

			typename clock::time_point sync_start;

			typename clock::duration latency;

			uint32_t failures;

			// remote_record(const remote_record &t)
			// 	: sync_timestamp(t.sync_timestamp)
			// 	, pending_timestamp(t.pending_timestamp)
			// 	, sync_start(t.sync_start)
			// 	, latency(t.latency)
			// 	, failures(t.failures)
			// 	, call_id(t.call_id)
			// {}

			remote_record()
				: sync_timestamp(clock::time_point::min())
				, pending_timestamp(clock::time_point::min())
				, failures(0)
				, call_id(0)
			{}
		};

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

		history_type history;

		remote_record remote;

		value_type local_value;

		sched::listener on_change;

		bool cooldown_pending;
	};
}}
#endif