#ifndef WIC_COLOR_SENSOR_H
#define WIC_COLOR_SENSOR_H
#include <chrono>
#include <video/color_checker.h>
#include <video/stream_reader.h>

namespace wic {

template<typename TConfig>
class color_sensor
{
	struct property_config : public property_config_base
	{
		typedef uint64_t cfg_value_type;

		static const uint32_t cfg_class_id = TConfig::cfg_class_id;

		static const uint32_t cfg_member_id = TConfig::cfg_member_id;

		static const uint32_t cfg_cooldown_time = 0;

		static const bool cfg_commit_change_only = true;
	};
	typedef wicp::local_property<property_config> property;

	static_assert(TConfig::cfg_areas.size() <= 64 ,"Maximum 64 areas are supported");

	constexpr static const std::initializer_list<video::color_checker::area> &areas = TConfig::cfg_areas;

	static video::color_checker* checker;

	static video::stream_reader* reader;

	static volatile bool disposed;

	static std::thread* proc;

	static void reconnect()
	{
		using namespace std::literals::chrono_literals;

		std::cout << "\e[31;01m - \e[0mcolor sensor: stream reader failure; recreating" << std::endl;

		delete reader;
		std::thread::this_thread::sleep(300ms);
		try
		{ reader = new video::stream_reader(TConfig::cfg_stream); }

		catch(...)
		{ reconnect(); }
	
	}

	static void thread_start()
	{
		checker = new video::color_checker(areas);
		try { reader = new video::stream_reader(TConfig::cfg_stream); }
		catch(...)
		{
			reader = 0;
			reconnect();
		}
		std::cout << "\e[32;01m - \e[0mcolor sensor: initialized" << std::endl;
		while(!disposed)
		{
			try
			{ reader.process_frame(std::bind(&color_checker::check_for_color,&checker,std::placeholders::_1)); }

			catch(...)
			{ reconnect(); }
			uint64_t v = 0;
			for (int i = areas.size()-1 ;i >=0 ; --i)
			{
				v <<= 1;
				if(c.get_result(i))
					v |= 1;
			}
			property::value(v);
		}

		delete checker;
		delete reader;
	}

public:
	static void init()
	{
		property::init();
		disposed = false;
		proc = new std::thread(thread_start);
	}

	static void uninit()
	{
		disposed = true;
		proc->join();
		delete proc;
		property::uninit();
	}

	static uint64_t value()
	{ return property::value(); }

	constexpr static listener_t &on_change = property::on_change;
};


template<typename c>
volatile bool color_sensor<c>::disposed;

template<typename c>
std::thread *color_sensor<c>::proc;

template<typename c>
video::color_checker *color_sensor<c>::checker;

template<typename c>
video::stream_reader *color_sensor<c>::reader;

}
#endif
