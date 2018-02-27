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
		typedef alsa_host::stream_id_type stream_id_type;

		static void init()
		{
			if(!alsa_host::exists(device,channel))
			{
				std::cout << "\e[31;01m - \e[0mFATAL: cannot initialize audio on channel " << std::dec << 
					(int)device << '.' << (int)channel << std::endl;
//				throw std::exception();

			}
		}

		static void uninit()
		{}

		static stream_id_type play(const std::string &file, float gain)
		{ return alsa_host::play(file,device,channel,gain); }

		static stream_id_type play(const std::string &file, float gain, std::function<void()> callback)
		{ return alsa_host::play(file,device,channel,gain, callback); }

		static void cancel(stream_id_type sid)
		{ alsa_host::cancel(device,sid); }

		static void pause(stream_id_type sid)
		{ alsa_host::pause(device,sid); }

		static void resume(stream_id_type sid)
		{ alsa_host::resume(device,sid); }
	};
}
#endif
