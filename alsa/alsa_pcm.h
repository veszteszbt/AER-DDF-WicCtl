#ifndef ALSA_PCM_H
# define ALSA_PCM_H
# include <exception>
# include <string>
# include <cstring>
# include <list>
# include <functional>
# include <thread>
# include <mutex>
# include <condition_variable>
# include <alsa/asoundlib.h>

namespace alsa {

	class error : public std::exception
	{
		const char * const _what;
	public:
		error(unsigned v)
			: _what(snd_strerror(v))
		{}

		virtual const char *what() const noexcept
		{ return _what; }
	};

namespace pcm {

	class hw_params_t
	{
		snd_pcm_hw_params_t *_params;

		snd_pcm_t           *_pcm;

		template<typename T,typename Tparam>
		T get(int (*fn)(Tparam*,T*))
		{
			T rv;
			int r = fn(_params,&rv);
			if(r < 0)
				throw alsa::error(r);

			return rv;
		}

		template<typename... T, typename Tparam>
		void get(int (*fn)(Tparam*,T...), T... v)
		{
			int r = fn(_params,v...);
			if(r < 0)
				throw alsa::error(r);
		}

		template<typename... T>
		void set(int (*fn)(snd_pcm_t*,snd_pcm_hw_params_t*,T...), T... v)
		{
			int r = fn(_pcm,_params,v...);
			if(r < 0)
				throw alsa::error(r);
		}

		hw_params_t(snd_pcm_t *pcm)
			: _pcm(pcm)
		{
			snd_pcm_hw_params_malloc(&_params);
			snd_pcm_hw_params_any(_pcm,_params);
		}

	public:

		~hw_params_t()
		{ snd_pcm_hw_params_free(_params); }

		snd_pcm_access_t access()
		{ return get(snd_pcm_hw_params_get_access); }

		void access(snd_pcm_access_t v)
		{ set(snd_pcm_hw_params_set_access,v); }

		snd_pcm_format_t format()
		{ return get(snd_pcm_hw_params_get_format); }

		void format(snd_pcm_format_t v)
		{ set(snd_pcm_hw_params_set_format,v); }

		unsigned channels_max()
		{ return get(snd_pcm_hw_params_get_channels_max); }

		unsigned channels_min()
		{ return get(snd_pcm_hw_params_get_channels_min); }

		unsigned channels()
		{ return get(snd_pcm_hw_params_get_channels); }

		void channels(unsigned v)
		{ set(snd_pcm_hw_params_set_channels,v); }

		
		void get_rate(unsigned *v, int *dir)
		{ get(snd_pcm_hw_params_get_rate,v,dir); }

		void set_rate_near(unsigned *v, int *dir)
		{ set(snd_pcm_hw_params_set_rate_near,v,dir); }


		void get_period_size(snd_pcm_uframes_t *v, int *dir)
		{ get(snd_pcm_hw_params_get_period_size,v,dir); }

		void apply()
		{ set(snd_pcm_hw_params); }

		friend class pcm_t;
	};

	class pcm_t
	{
		snd_pcm_t *_pcm;

		snd_pcm_t *init(const std::string &device, snd_pcm_stream_t stream, int mode = 0)
		{
			int r = snd_pcm_open(&_pcm,device.c_str(),stream,mode);
			if(r < 0)
				throw alsa::error(r);
			return _pcm;	
		}

	public:
		hw_params_t params;

		pcm_t(const std::string &device, snd_pcm_stream_t stream, int mode = 0)
			: params(init(device,stream,mode))
		{}

		~pcm_t()
		{ snd_pcm_close(_pcm); }

		std::string name()
		{ return std::string(snd_pcm_name(_pcm)); }

		snd_pcm_state_t state()
		{ return snd_pcm_state(_pcm); }

		std::string state_name()
		{ return std::string(snd_pcm_state_name(state())); }


		void prepare()
		{ snd_pcm_prepare(_pcm); }

		snd_pcm_sframes_t writei(const void *buffer, snd_pcm_uframes_t frames)
		{ return snd_pcm_writei(_pcm,buffer,frames); }

		snd_pcm_sframes_t writen(void **buffer, snd_pcm_uframes_t frames)
		{ return snd_pcm_writen(_pcm,buffer,frames); }

		friend class hw_params_t;
	};

}

	class player
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

			stream_type(uint8_t pchannel, std::istream &pstream)
				: channel(pchannel)
				, stream(pstream)
			{}
		};

		typedef std::list<stream_type> streams_type;

		streams_type             streams;

		std::mutex               streams_lock;

		std::mutex               suspend_lock;

		std::condition_variable  suspend_cv;

		std::string itos(uint8_t v)
		{
			std::stringstream s;
			s << "hw:" << static_cast<unsigned>(v);
			return s.str();
		}

		void sleep()
		{
			std::unique_lock<std::mutex> ul(suspend_lock);
			suspend_cv.wait(ul);
		}

		void notify()
		{
			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}

		void start()
		{
			sleep();

			std::cout << "\e[37;01m - \e[0malsa player: process initialized for device " << (int)device << std::endl;

			while(!disposed)
			{
				const size_t rbytes = period*2;
				memset(buffer,0,rbytes*channels);
				streams_lock.lock();
/*				while(streams.empty())
				{
					streams_lock.unlock();
					std::cout << "\e[37;01m - \e[0malsa player: nothing to do; suspending until next notify" << std::endl;
					sleep();
					streams_lock.lock();
				}
*/
				for(
					streams_type::iterator stream = streams.begin();
					stream != streams.end();
				)
				{
					stream->stream.read(reinterpret_cast<char*>(sbuffer),rbytes);
					const size_t wbytes = stream->stream.gcount();
					for(size_t i = 0; i < wbytes/2; ++i)
						buffer[i*channels+stream->channel] += sbuffer[i];

					if(!stream->stream.good())
						stream = streams.erase(stream);
					else
						++stream;
				}
				streams_lock.unlock();

				pcm.writei(reinterpret_cast<void*>(buffer),period);
			}
			std::cout << "\e[37;01m - \e[0malsa player: process uninitialized for device " << (int)device << std::endl;
		}


		std::thread process;

	public:
		player(uint8_t pdevice, unsigned prate = 44100)
			: pcm(itos(pdevice).c_str(),SND_PCM_STREAM_PLAYBACK,0)
			, device(pdevice)
			, rate(prate)
			, disposed(false)
			, process(&alsa::player::start,this)
		{
			pcm.params.access(SND_PCM_ACCESS_RW_INTERLEAVED);
			pcm.params.format(SND_PCM_FORMAT_S16_LE);
			channels = pcm.params.channels_max();
			pcm.params.channels(channels);

			int dir = 0;
			pcm.params.set_rate_near(&rate,&dir);
			pcm.params.apply();
			dir = 0;
			pcm.params.get_period_size(&period,&dir);

			std::cout << "PCM name: " << pcm.name() << std::endl;

			std::cout << "PCM state: " << pcm.state_name() << " (" << pcm.state() << ")" << std::endl;

			std::cout << "Period size: " << period << std::endl;

			const unsigned l = period*channels;
			buffer = new uint16_t[l];
			sbuffer = new uint16_t[period];
			notify();
		}

		void play(std::istream &stream, uint8_t channel)
		{
			streams_lock.lock();
			streams.push_back(stream_type(channel,stream));
			streams_lock.unlock();
			notify();
		}

		~player()
		{
			disposed = true;
			notify();
			process.join();
			delete buffer;
			delete sbuffer;
		}
	};
}

#endif
