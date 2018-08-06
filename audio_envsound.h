#ifndef WIC_AUDIO_ENVSOUND_H
# define WIC_AUDIO_ENVSOUND_H
# include <alsa_host.h>
# include <exception>
# include <property_config_base.h>
# include <oosp/local_property.h>
namespace wic
{
	template<typename TConfig>
	class audio_envsound
	{
		typedef typename TConfig::cfg_audio audio;

		struct property_config : public property_config_base
		{
			static const uint32_t class_id = TConfig::cfg_class_id;

			static const uint32_t member_id = TConfig::cfg_member_id;


		};
		typedef oosp::local_property<property_config> property;

		static void start()
		{
			audio::play(TConfig::cfg_source,)
		}

		static void change_handler
		{
				
		}

	public:
		static void init()
		{
			property::init();
			property::on_change += change_handler;
		}

		static void uninit()
		{
			property::uninit();
		}

		static bool playing()
		{ return property::value(); }

		static void playing(bool v)
		{ property::value(v); }
	};
}
#endif
