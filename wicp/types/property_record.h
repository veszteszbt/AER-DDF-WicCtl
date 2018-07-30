#ifndef WICP_TYPES_PROPERTY_RECORD_H
# define WICP_TYPES_PROPERTY_RECORD_H
# include <chrono>
# include <mutex>
# include <list>
# include <sched/listener.h>
# include <wicp/types/sync_record.h>
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

		typedef TobjectId object_id_type;

		typedef std::list<history_record> history_type;

		typedef ::wicp::types::sync_record<call_id_type, clock> sync_record_type;

		history_type history;

		sync_record_type sync;

		typename clock::time_point local_timestamp;

		call_id_type initial_sync_cid;

		bool initial_sync_pending;

		value_type local_value;

		value_type default_value;

		sched::event<object_id_type> on_change;

		bool cooldown_pending;

		property_record_base()
			: local_timestamp(clock::time_point::min())
			, initial_sync_cid(0)
		{}

		static void init(value_type p = value_type())
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
