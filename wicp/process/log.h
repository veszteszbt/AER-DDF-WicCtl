#ifndef WICP_PROCESS_LOG_H
# define WICP_PROCESS_LOG_H
# include <mutex>
# include <condition_variable>
# include <thread>
# include <string>
# include <list>
# include <iomanip>
# include <chrono>
#ifdef LOG_SQL
# include <process/sql_executor.h>
#endif
#ifdef _MSC_VER
	#undef max
	#undef min
#endif
namespace wicp {
namespace process
{
	template<typename TEnv>
	class log
	{
		typedef typename TEnv::clock				clock;

		typedef typename TEnv::value_type			value_type;

		typedef typename TEnv::history_type			history_type;

		typedef typename TEnv::history_record		history_record;


		typedef typename TEnv::object_id_type		object_id_type;

		typedef typename TEnv::member_id			member_id;

		typedef typename TEnv::wic_class			wic_class;

		typedef typename TEnv::encap_object_type	encap_object_type;


		static typename clock::time_point 			time;

		static const uint32_t cooldown_time			= TEnv::cooldown_time;

		constexpr static history_type &history		= TEnv::history;

		constexpr static std::mutex &history_lock	= TEnv::history_lock;

	public:
		static void init()
		{
			time = clock::time_point::min();
		};

		static void uninit()
		{}

		static journal jrn(uint8_t level)
		{
			int* x, *y;
			return journal(level,"wicp.commit") << "property: " << std::hex <<
				TEnv::class_id << "::" << TEnv::member_id::value << ' ';
		}

		static void notify(object_id_type object_id)
		{
			wic_class::template lock<encap_object_type>();
			auto it = wic_class::template find<encap_object_type>(object_id);
			if(it == wic_class::end())
			{
				wic_class::template unlock<encap_object_type>();
				jrn(journal::error) << "Invalid `" << wic_class::name << "' object reference `" << std::hex << object_id << journal::end;
				return;
			}
			it->second.property_lock.lock();
			const auto &property = it->second.properties.template get<member_id>();
			const history_record r = property.history.front();

			it->second.property_lock.unlock();
			wic_class::template unlock<encap_object_type>();

			if(r.time > time)
			{
				time = r.time;

#ifdef LOG_SQL

				std::stringstream s;
				s << "INSERT INTO `wic`.`log_wicp` VALUES (" <<
					std::chrono::time_point_cast<std::chrono::nanoseconds>(r.time).time_since_epoch().count() << ',' <<
					TEnv::class_id << ',' <<
					TEnv::member_id::value << ",X'" << std::hex;

				for(int i = 0; i < sizeof(value_type); ++i)
					s << std::setfill('0') << std::setw(2) <<
						static_cast<uint32_t>(reinterpret_cast<const uint8_t*>(&r.value)[i]);

				s << "');";
				::process::sql_executor::notify(s.str());
#endif

			}
		}
	};


	template<typename e>
	typename log<e>::clock::time_point log<e>::time;
}}
#endif
