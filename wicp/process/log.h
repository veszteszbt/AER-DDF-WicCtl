#ifndef WICP_PROCESS_LOG_H
# define WICP_PROCESS_LOG_H
# include <mutex>
# include <condition_variable>
# include <thread>
# include <string>
# include <list>
# include <iomanip>
# include <chrono>
# include <process/sql_executor.h>

namespace wicp {
namespace process
{
	template<typename TEnv>
	class log
	{
		typedef typename TEnv::clock           clock;

		typedef typename TEnv::history_type    history_type;

		typedef typename TEnv::history_record  history_record;

		typedef typename TEnv::value_type      value_type;

		
		static const uint32_t cooldown_time                         = TEnv::cooldown_time;

		constexpr static history_type         &history              = TEnv::history;

		constexpr static std::mutex           &history_lock         = TEnv::history_lock;

		static typename clock::time_point time;

	public:
		static void init()
		{
			time = clock::time_point::min();
		};

		static void uninit()
		{}

		static void notify()
		{
			history_lock.lock();
			const history_record r = history.front();

			if(r.time > time)
			{
				time = r.time;
				history_lock.unlock();

				std::stringstream s;
				s << "INSERT INTO `wic`.`log_wicp` VALUES (" << 
					std::chrono::time_point_cast<std::chrono::nanoseconds>(r.time).time_since_epoch().count() << ',' <<
					TEnv::class_id << ',' <<
					TEnv::member_id << ",X'" << std::hex;

				for(int i = 0; i < sizeof(value_type); ++i)
					s << std::setfill('0') << std::setw(2) <<
						static_cast<uint32_t>(reinterpret_cast<const uint8_t*>(&r.value)[i]);
					
				s << "');";
				::process::sql_executor::notify(s.str());

			}
			else
				history_lock.unlock();
		}
	};


	template<typename e>
	typename log<e>::clock::time_point log<e>::time;
}}
#endif
