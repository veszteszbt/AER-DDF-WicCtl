#ifndef WIC_VIDEO_COLORSENSOR_H
# define WIC_VIDEO_COLORSENSOR_H
# include <alsa_host.h>
# include <exception>
# include <wicp/local_property.h>
# include <entity.h>
# include <video/color_checker.h>
# include <iomanip>
namespace wic
{
	template<typename TConfig>
	class video_colorsensor : public entity
	{
		typedef typename TConfig::cfg_video video;

		struct property_config : public property_config_base
		{
			typedef uint64_t cfg_value_type;

			static const uint32_t cfg_class_id = TConfig::cfg_class_id;

			static const uint32_t cfg_member_id = TConfig::cfg_member_id;

			static const uint32_t cfg_cooldown_time = 0;
		};
		typedef wicp::local_property<property_config> property;

		static ::video::color_checker checker;

		static void process_frame(::video::frame f)
		{
			uint64_t v = 0;
			checker.check_for_color(f);
			for(int i = 0; i < checker.size(); ++i)
				v |= (checker.get_result(i)?1:0) << i;
			property::value(v);
		}

		static void change_handler()
		{ journal(journal::trace,"wic.video.colorsensor") << TConfig::name << ": " << "value changed to " << std::setbase(2) << property::value() << journal::end; }


	public:
		static void init()
		{
			property::init(0);
			video::add_processor(process_frame);
			property::on_change += change_handler;
		}

		static void uninit()
		{
			video::del_processor(process_frame);
			property::on_change -= change_handler;
			property::uninit();
		}

		static void remote_add(wicp::role_type &role)
		{ property::remote_add(role); }

		static uint64_t value()
		{ return property::value(); }

		constexpr static sched::listener &on_value_change = property::on_change;

	};

	template<typename c>
	::video::color_checker video_colorsensor<c>::checker(c::cfg_areas);
}
#endif
