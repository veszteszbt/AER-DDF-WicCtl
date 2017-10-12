#ifndef WIC_AUDIO_H
# define WIC_AUDIO_H
# include <alsa_host.h>
namespace wic
{
	template<typename TConfig>
	class audio
	{
		static const uint8_t device = TConfig::cfg_device;

		static const uint8_t channel = TConfig::cfg_channel;
	public:
		static void init()
		{
			if(!alsa_host::exists(device,channel))
				throw "bad channel";
		}

		static void uninit()
		{}

		static void play(const std::string &file)
		{ alsa_host::play(file,device,channel); }
	};
}
#endif
