#include <iostream>
#include "alsa_pcm.h"

int main()
{

	alsa::pcm::pcm_t pcm("hw:0",SND_PCM_STREAM_PLAYBACK,0);

	alsa::pcm::hw_params_t params(pcm);

	std::cout << "Setting access" << std::endl;
	params.access(SND_PCM_ACCESS_RW_INTERLEAVED);

	std::cout << "Setting format" << std::endl;
	params.format(SND_PCM_FORMAT_S16_LE);


	std::cout << "Channels: " << params.channels() << "; max: " << params.channels_max() << "; min: " << params.channels_min() << std::endl;

	int dir = 0;

	unsigned rate = 44100;

	std::cout << "Setting rate" << std::endl;
	params.set_rate_near(&rate,&dir);

	params.apply();

	snd_pcm_uframes_t period;

	dir = 0;

	params.get_period_size(&period,&dir);

	std::cout << "PCM name: " << pcm.name() << std::endl;

	std::cout << "PCM state: " << pcm.state_name() << " (" << pcm.state() << ")" << std::endl;

	std::cout << "Period size: " << period << std::endl;

	return 0;
}
