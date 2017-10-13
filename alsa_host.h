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
public:
	class player_t
	{
		alsa::pcm::pcm_t pcm;

		int16_t *buffer;

		int16_t *sbuffer;

		uint8_t device;

		unsigned channels;

		unsigned rate;

		snd_pcm_uframes_t period;

		volatile bool disposed;

		struct stream_type
		{
			uint8_t channel;
			std::basic_istream<int16_t> &stream;
			void (*callback)(std::basic_istream<int16_t>&);

			stream_type(uint8_t pchannel, std::basic_istream<int16_t> &pstream, void(*pcallback)(std::basic_istream<int16_t>&));
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

		uint8_t num_channels();

		void play(std::basic_istream<int16_t> &stream, uint8_t channel, void(*callback)(std::basic_istream<int16_t>&));

		~player_t();
	};

	class alsa_card_t
	{
		static std::string ll_get_name(int id);

		static std::string ll_get_longname(int id);

		static std::string ll_get_hwid(int id);

		player_t *_player;

	public:

		const std::string longname;

		const std::string name;

		const std::string hwid;

		const int id;

		alsa_card_t();

		alsa_card_t(int id);

		~alsa_card_t();

		player_t &player();
	};

private:
	typedef std::map<int,alsa_card_t*> cards_by_id_t;

	static cards_by_id_t cards_by_id;

	static void file_play_finish(std::basic_istream<int16_t> &stream);
public:

	static void init();

	static void uninit();

	static bool exists(uint8_t card, uint8_t channel);

	static void play(
		const std::string &file,
		uint8_t card_id,
		uint8_t channel_id
	);

	
};
#endif
