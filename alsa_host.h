#ifndef ALSA_HOST_H
# define ALSA_HOST_H
# include <iostream>
# include <functional>
# include <string>
# include <sstream>
# include <map>
# include <alsa_pcm.h>
# include <alsa/asoundlib.h>
# include <alsa/control.h>

class isoundstream;

class alsa_host
{
public:
	typedef uint32_t stream_id_type;

	class player_t
	{
		alsa::pcm::pcm_t *pcm;

		int16_t *buffer;

		int16_t *sbuffer;

		uint8_t  device;

		unsigned channels;

		unsigned rate;

		snd_pcm_uframes_t period;

		volatile bool disposed;

		struct stream_type
		{
			stream_id_type               id;

			const uint8_t                channel;

			const float                  gain;

			std::basic_istream<int16_t> &stream;

			std::function<void()>        callback;

			bool                         paused;

			stream_type(
				stream_id_type id,
				uint8_t pchannel,
				std::basic_istream<int16_t> &pstream,
				float pgain,
				std::function<void()> pcallback
			);
		};

		typedef std::list<stream_type> streams_type;

		streams_type             streams;

		std::mutex               streams_lock;

		std::mutex               suspend_lock;

		std::condition_variable  suspend_cv;

		std::string hwname(uint8_t v);

		void sleep();

		void notify();

		void start();

		std::thread *process;

		void init_pcm();

	public:
		player_t(uint8_t pdevice, unsigned prate = 44100);

		uint8_t num_channels();

		stream_id_type play(
			std::basic_istream<int16_t> &stream,
			uint8_t channel,
			float gain,
			std::function<void()> callback
		);

		void cancel(stream_id_type sid);

		void pause(stream_id_type sid);

		void resume(stream_id_type sid);

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

	static void nop() {}

	class file_play_handle
	{
		isoundstream *_stream;

		std::function<void()> _callback;
	public:
		void operator()();

		isoundstream &stream()
		{ return *_stream; }

		file_play_handle(const file_play_handle &that);

		file_play_handle(const std::string &file, std::function<void()> callback);
	};

public:
	static void init();

	static void uninit();

	static bool exists(uint8_t card, uint8_t channel);

	static stream_id_type play(
		const std::string &file,
		uint8_t card_id,
		uint8_t channel_id,
		float gain,
		std::function<void()> callback = nop
	);

	static void cancel(uint8_t card_id, stream_id_type sid);

	static void pause(uint8_t card_id, stream_id_type sid);

	static void resume(uint8_t card_id, stream_id_type sid);
};
#endif
