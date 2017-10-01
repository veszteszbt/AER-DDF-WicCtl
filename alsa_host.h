#ifndef ALSA_HOST_H
# define ALSA_HOST_H
# include <iostream>
# include <string>
# include <sstream>
# include <map>
# include <alsa_pcm.h>
# include <alsa/asoundlib.h>
# include <alsa/control.h>

class alsa_host
{
	class player_t
	{
		alsa::pcm::pcm_t pcm;

		uint16_t *buffer;

		uint16_t *sbuffer;

		uint8_t device;

		unsigned channels;

		unsigned rate;

		snd_pcm_uframes_t period;

		volatile bool disposed;

		struct stream_type
		{
			uint8_t channel;
			std::istream &stream;

			stream_type(uint8_t pchannel, std::istream &pstream);
		};

		typedef std::list<stream_type> streams_type;

		streams_type             streams;

		std::mutex               streams_lock;

		std::mutex               suspend_lock;

		std::condition_variable  suspend_cv;

		std::string itos(uint8_t v);

		void sleep();

		void notify();

		void start();

		std::thread process;

	public:
		player_t(uint8_t pdevice, unsigned prate = 44100);

		void play(std::istream &stream, uint8_t channel);

		~player_t();
	};

	class alsa_card_t
	{
		static std::string ll_get_name(int id);

		static std::string ll_get_longname(int id);

		static std::string ll_get_hwid(int id);

		player_t *player;

	public:

		const std::string longname;

		const std::string name;

		const std::string hwid;

		const int id;

		alsa_card_t();

		alsa_card_t(int id);

		~alsa_card_t();
	};

	typedef std::map<int,alsa_card_t*> cards_by_id_t;

	static cards_by_id_t cards_by_id;
public:

	static void init();

	static void uninit();

	static void play(
		const std::string &file,
		uint8_t card_id,
		uint8_t channel_id
	);

	
};
#endif
