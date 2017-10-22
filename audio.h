#ifndef WIC_AUDIO_H
# define WIC_AUDIO_H
# include <alsa_host.h>
# include <exception>
# include <functional>
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
			{
				std::cout << "\e[31;01m - \e[0mFATAL: cannot initialize audio on channel " << std::dec << 
					(int)device << '.' << (int)channel << std::endl;
				throw std::exception();

			}
		}

		static void uninit()
		{}

		static void play(const std::string &file)
		{ alsa_host::play(file,device,channel); }

		static void play(const std::string &file, std::function<void()> callback)
		{ alsa_host::play(file,device,channel,callback); }
	};
}
#endif
