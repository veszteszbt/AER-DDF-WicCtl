#ifndef WIC_AUDIO_SPEECH_H
# define WIC_AUDIO_SPEECH_H
# include <alsa_host.h>
# include <exception>
# include <property_config_base.h>
# include <wicp/local_property.h>
namespace wic
{
	template<typename TConfig>
	class audio_speech
	{
		typedef typename TConfig::cfg_audio audio;

		struct property_config : public property_config_base
		{
			typedef bool cfg_value_type;

			static const uint32_t class_id = TConfig::cfg_class_id;

			static const uint32_t member_id = TConfig::cfg_member_id;
		};
		typedef wicp::local_property<property_config> property;

		static void change_handler
		{
			if(property::value())
				audio::play(TConfig::cfg_source,finish_handler);
		}

		static void finish_handler()
		{ property::value(false); }

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
