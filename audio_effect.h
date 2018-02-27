#ifndef WIC_AUDIO_EFFECT_H
# define WIC_AUDIO_EFFECT_H
# include <alsa_host.h>
# include <exception>
namespace wic
{
	template<typename TConfig>
	class audio_effect
	{
		typedef typename TConfig::cfg_audio audio;

	public:
		static void init()
		{}

		static void uninit()
		{}

		static void play()
		{ audio::play(TConfig::cfg_source,TConfig::cfg_gain); }
	};
}
#endif
