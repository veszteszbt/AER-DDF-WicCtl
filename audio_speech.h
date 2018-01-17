#ifndef WIC_AUDIO_SPEECH_H
# define WIC_AUDIO_SPEECH_H
# include <alsa_host.h>
# include <exception>
# include <wicp/local_property.h>
# include <entity.h>
namespace wic
{
	template<typename TConfig>
	class audio_speech : public entity
	{
		typedef typename TConfig::cfg_audio audio;

		struct property_config : public property_config_base
		{
			typedef bool cfg_value_type;

			static const uint32_t cfg_class_id = TConfig::cfg_class_id;

			static const uint32_t cfg_member_id = TConfig::cfg_member_id;

			static const uint32_t cfg_cooldown_time = 0;
		};
		typedef wicp::local_property<property_config> property;

		static volatile bool is_playing;

		static std::mutex lock;

		static void change_handler()
		{
			lock.lock();
			if(property::value())
			{
				if(!is_playing)
				{
					is_playing = true;
					lock.unlock();
					audio::play(TConfig::cfg_source,finish_handler);
					return;
				}
			}
			else if(is_playing)
				property::value(true);

			lock.unlock();
		}

		static void finish_handler()
		{
			lock.lock();
			is_playing = false;
			property::value(false);
			lock.unlock();
		}

	public:
		static void init()
		{
			is_playing = false;
			property::init(false);
			property::on_change += change_handler;
		}

		static void uninit()
		{
			property::on_change -= change_handler;
			property::uninit();
		}

		static void remote_add(net::ipv4_address ip)
		{ property::remote_add(ip); }

		static void play()
		{ property::value(true); }

		typedef expose_property<property> playing;
	};

	template<typename c>
	volatile bool audio_speech<c>::is_playing;

	template<typename c>
	std::mutex audio_speech<c>::lock;
}
#endif
