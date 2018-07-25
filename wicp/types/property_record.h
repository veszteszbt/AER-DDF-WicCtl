#ifndef WICP_TYPES_PROPERTY_RECORD_H
# define WICP_TYPES_PROPERTY_RECORD_H
# include <chrono>
# include <mutex>
# include <list>
# include <sched/listener.h>
namespace wicp {
namespace types 
{
	template <typename TcallId, typename TobjectId, typename Tvalue>
	struct property_record_base
	{
		typedef TcallId call_id_type;

		typedef Tvalue value_type;

		typedef std::chrono::high_resolution_clock clock;

		struct history_record
		{
			typename clock::time_point	time;

			value_type					value;

			history_record() = default;

			history_record(value_type v)
				: time(clock::now())
				, value(v)
			{}
		};

		struct sync_record
		{
			typename clock::time_point timestamp;

			typename clock::time_point pending_timestamp;

			call_id_type 				call_id;

			typename clock::time_point	start;

			typename clock::duration	latency;

			uint32_t 					failures;

			sync_record()
				: timestamp(clock::time_point::min())
				, pending_timestamp(clock::time_point::min())
				, start(clock::time_point::min())
				, failures(0)
				, call_id(0)
			{}
		};

		typedef TobjectId object_id_type;

		typedef std::list<history_record> history_type;

		history_type history;

		sync_record sync;

		typename clock::time_point local_timestamp;

		call_id_type initial_sync_cid;

		bool initial_sync_pending;

		value_type local_value;

		// TODO init default_value
		value_type default_value;

		sched::event<object_id_type> on_change;

		bool cooldown_pending;

		property_record_base()
			: local_timestamp(clock::time_point::min())
			, initial_sync_cid(0)
		{}

		void init(value_type p = value_type())
		{
			// TODO
		}

		// remote_record(const remote_record &t)
		// 	: timestamp(t.timestamp)
		// 	, pending_timestamp(t.pending_timestamp)
		// 	, start(t.start)
		// 	, latency(t.latency)
		// 	, failures(t.failures)
		// 	, call_id(t.call_id)
		// {}
	};
}}
#endif