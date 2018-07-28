#ifndef WICP_TYPES_SYNC_RECORD_H
# define WICP_TYPES_SYNC_RECORD_H
# include <chrono>
namespace wicp {
namespace types 
{
	template<typename TCallId, typename TClock>
	struct sync_record
	{
		typedef TCallId            call_id_type;

		typedef TClock             clock;


		typename clock::time_point timestamp;

		typename clock::time_point pending_timestamp;

		call_id_type               call_id;

		typename clock::time_point start;

		typename clock::duration   latency;

		uint32_t                   failures;

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
