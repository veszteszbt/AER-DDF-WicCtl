#ifndef WICP_TYPES_PROPERTY_RECORD_H
# define WICP_TYPES_PROPERTY_RECORD_H
# include <chrono>
# include <mutex>
# include <list>
# include <sched/listener.h>
namespace wicp {
namespace types 
{
	template <typename TcallId, typename TpropertyData>
	struct property_record_base
	{
		typedef TcallId call_id_type;

		typedef TpropertyData property_data_type;

		typedef std::chrono::high_resolution_clock clock;

		struct history_record
		{
			typename clock::time_point	time;

			property_data_type			value;

			history_record() = default;

			history_record(property_data_type v)
				: time(clock::now())
				, value(v)
			{}
		};

		typedef std::list<history_record> history_type;

		history_type history;
	
		typename clock::time_point sync_timestamp;

		typename clock::time_point pending_timestamp;

		typename clock::time_point local_timestamp;

		call_id_type call_id;

		typename clock::time_point sync_start;

		typename clock::duration latency;

		uint32_t failures;

		property_data_type local_value;

		sched::listener on_change;

		bool cooldown_pending;


		// TODO local_timestamp?
		property_record_base()
			: sync_timestamp(clock::time_point::min())
			, pending_timestamp(clock::time_point::min())
			, failures(0)
			, call_id(0)
			, local_timestamp(clock::time_point::min())
		{}

		void init(property_data_type p = property_data_type())
		{
			// TODO
		}

		// remote_record(const remote_record &t)
		// 	: sync_timestamp(t.sync_timestamp)
		// 	, pending_timestamp(t.pending_timestamp)
		// 	, sync_start(t.sync_start)
		// 	, latency(t.latency)
		// 	, failures(t.failures)
		// 	, call_id(t.call_id)
		// {}
	};
}}
#endif