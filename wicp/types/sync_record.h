#ifndef WICP_TYPES_SYNC_RECORD_H
# define WICP_TYPES_SYNC_RECORD_H
# include <chrono>
namespace wicp {
namespace types
{
	template<typename TcallId, typename Tvalue, typename Tclock>
	struct sync_record
	{
		typedef TcallId				call_id_type;

		typedef Tvalue				value_type;

		typedef Tclock				clock;

		typename clock::time_point	timestamp;

		typename clock::time_point	pending_timestamp;

		call_id_type				call_id;

		value_type					local_value;

		value_type					default_value;

		typename clock::time_point	start;

		typename clock::duration	latency;

		uint32_t					failures;

		sync_record()
			: timestamp(clock::time_point::min())
			, pending_timestamp(clock::time_point::min())
			, start(clock::time_point::min())
			, failures(0)
			, call_id(0)
		{}
	};
}}
#endif
