#include <ctgmath>
#include <alsa_host.h>
#include <soundstream.h>
#include <errno.h>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

alsa_host::player_t::stream_type::stream_type(
	alsa_host::stream_id_type pid,
	uint8_t pchannel,
	std::basic_istream<int16_t> &pstream,
	float pgain,
	std::function<void()> pcallback
)
	: id(pid)
	, channel(pchannel)
	, stream(pstream)
	, callback(pcallback)
	, gain(pgain)
	, paused(false)
{}

std::string alsa_host::player_t::hwname(uint8_t v)
{
	std::stringstream s;
	s << "hw:" << static_cast<unsigned>(v);
	return s.str();
}

void alsa_host::player_t::sleep()
{
	std::unique_lock<std::mutex> ul(suspend_lock);
	suspend_cv.wait(ul);
}

void alsa_host::player_t::notify()
{
	std::lock_guard<std::mutex> lg(suspend_lock);
	suspend_cv.notify_one();
}

void alsa_host::player_t::start()
{
	sleep();

	std::cout <<
		"\e[32;01m - \e[0malsa host: player initialized for device " << (int)device <<
		" with " << (int)channels << " channels at " << rate << "Hz" << std::endl;

	while(!disposed)
	{
		if(pcm->delay() > period*4)
			std::this_thread::sleep_for(std::chrono::microseconds(1000000l*period/rate));

		memset(buffer,0,period*channels*2);
		streams_lock.lock();
/*				while(streams.empty())
		{
			streams_lock.unlock();
			std::cout <<
				"\e[37;01m - \e[0malsa host player " << (int)device <<
				": nothing to do; suspending until next notify" << std::endl;
			sleep();
			streams_lock.lock();
		}
*/
		for(
			streams_type::iterator stream = streams.begin();
			stream != streams.end();
		)
		{
			if(stream->paused)
				continue;
			stream->stream.read(sbuffer,period);
			const size_t wbytes = stream->stream.gcount();
			for(size_t i = 0; i < wbytes; ++i)
			{
				const int index = i*channels+stream->channel;
				const int a = static_cast<int>(buffer[index]);
				const int b = static_cast<int>(stream->gain*sbuffer[i]);

				buffer[index] =
					static_cast<int16_t>(((a < 0 && b < 0)
						? (a + b) - ((a * b)/INT16_MIN)
						: ((a > 0 && b > 0)
							? (a + b) - ((a * b)/INT16_MAX)
							: (a + b)
						)));

			}

			if(!stream->stream.good())
			{
				// TODO: do on worker thread
				stream->callback();
				stream = streams.erase(stream);
			}
			else
				++stream;
		}
		streams_lock.unlock();

		int16_t *p = buffer;

		for(int size = period; size > 0;)
		{
			int result = pcm->writei(reinterpret_cast<void*>(p),size);
			if(result >= 0)
			{
				size -= result;
				p += result*channels;
			}

			else switch(result)
			{
				case -EAGAIN:
					std::cout << "\e[33;01m - \e[0malsa host: pcm buffer overrun for device " << (int)device << std::endl;
					continue;

				case -EPIPE:
					std::cout << "\e[33;01m - \e[0malsa host: pcm buffer underrun for device " << (int)device << std::endl;
					pcm->prepare();
					break;

				case -ESTRPIPE:
					std::cout << "\e[33;01m - \e[0malsa host: pcm instance for device " << (int)device << "is paused; resuming" << std::endl;
					pcm->resume();
					break;

				default:
					std::cout << "\e[33;01m - \e[0malsa host: pcm instance for device " << (int)device << " reported unknown error; reinitializing in 3 seconds" << result << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(3));
					try
					{ init_pcm(); }
					catch(alsa::error &e)
					{
						std::cout << "\e[31;01m - \e[0malsa host: pcm instance reinit for device " << (int)device << " failed; retrying in 3 seconds" << std::endl;
						std::this_thread::sleep_for(std::chrono::seconds(3));
					
					}
					break;
					
			}

		}
				
	}
	std::cout << "\e[37;01m - \e[0malsa host: player uninitialized for device " << (int)device << std::endl;
}


void alsa_host::player_t::init_pcm()
{

	delete pcm;
	pcm = new alsa::pcm::pcm_t(hwname(device).c_str(),SND_PCM_STREAM_PLAYBACK,0);
	pcm->params.access(SND_PCM_ACCESS_RW_INTERLEAVED);
	pcm->params.format(SND_PCM_FORMAT_S16_LE);
	channels = pcm->params.channels_max();
	pcm->params.channels(channels);

	int dir = 0;
	pcm->params.set_rate_near(&rate,&dir);
	pcm->params.get_period_size_min(&period,&dir);

	double period_msec = static_cast<double>(period)*1000/rate;
	if(period_msec < 2.0)
		period = static_cast<snd_pcm_uframes_t>(8*rate/1000);


	dir = 0;
	pcm->params.set_period_size(period,dir);

	pcm->params.apply();

	pcm->params.get_period_size(&period,&dir);
	period_msec = static_cast<double>(period)*1000/rate;

	std::cout << "\e[37;01m - \e[0malsa host: rate for card " << std::dec << (int)device << ": " << rate << " Hz" << std::endl;
	std::cout << "\e[37;01m - \e[0malsa host: period for card " << std::dec << (int)device << ": " << period_msec << " msec" << std::endl;


}

alsa_host::player_t::player_t(uint8_t pdevice, unsigned prate)
	: pcm(0)
	, device(pdevice)
	, rate(prate)
	, disposed(false)
	, process(0)
{
	init_pcm();
	process = new std::thread(&alsa_host::player_t::start,this);
	{
#ifdef __linux__
		std::stringstream s;
		s << "alsa host " << std::dec << (int)pdevice;
		sched_param p;
		int policy;
		pthread_setname_np(process->native_handle(),s.str().c_str());
#endif
		pthread_getschedparam(process->native_handle(),&policy,&p);
		p.sched_priority = sched_get_priority_max(SCHED_RR);
		pthread_setschedparam(process->native_handle(),SCHED_RR,&p);
	}
	const unsigned l = period*channels;
	buffer = new int16_t[l];
	sbuffer = new int16_t[period];
	notify();
}

uint8_t alsa_host::player_t::num_channels()
{ return channels; }


alsa_host::stream_id_type
alsa_host::player_t::play(std::basic_istream<int16_t> &stream, uint8_t channel, float gain, std::function<void()> callback)
{
	static alsa_host::stream_id_type last_sid = 0;

	streams_lock.lock();

	alsa_host::stream_id_type sid = last_sid + 1;

	bool u = true;
	while(u)
	{
		if(!++sid)
			continue;

		u = false;

		for(auto s : streams)
			if(s.id == sid)
			{
				u = true;
				break;
			}
	}

	streams.push_back(stream_type(sid,channel,stream,gain,callback));
	last_sid = sid;
	streams_lock.unlock();
	notify();
	return sid;
}

void
alsa_host::player_t::cancel(stream_id_type sid)
{
	streams_lock.lock();
	for(auto i = streams.begin(); i != streams.end(); ++i)
		if(i->id == sid)
		{
			std::function<void()> f = i->callback;
			streams.erase(i);
			streams_lock.unlock();
			f();
			return;
		}
	streams_lock.unlock();
}

void
alsa_host::player_t::pause(stream_id_type sid)
{
	streams_lock.lock();
	for(auto i = streams.begin(); i != streams.end(); ++i)
		if(i->id == sid)
		{
			i->paused = true;
			break;
		}
	streams_lock.unlock();
}

void
alsa_host::player_t::resume(stream_id_type sid)
{
	streams_lock.lock();
	for(auto i = streams.begin(); i != streams.end(); ++i)
		if(i->id == sid)
		{
			i->paused = false;
			break;
		}
	streams_lock.unlock();
}

alsa_host::player_t::~player_t()
{
	if(process)
	{
		disposed = true;
		notify();
		process->join();
	}
	delete process;
	delete buffer;
	delete sbuffer;
}

alsa_host::alsa_card_t::alsa_card_t()
	: id(-1)
	, _player(0)
{}

alsa_host::alsa_card_t::alsa_card_t(int pid)
	: id(pid)
	, name(ll_get_name(pid))
	, longname(ll_get_longname(pid))
	, hwid(ll_get_hwid(pid))
	
{
	std::cout << "\e[32;01m - \e[0malsa host: registered sound card #" << id << " - " << name << " ("<<longname<<")" << std::endl;
	_player = new player_t(id);
}

alsa_host::alsa_card_t::~alsa_card_t()
{ delete _player; }

std::string alsa_host::alsa_card_t::ll_get_name(int id)
{
	char *n;
	snd_card_get_name(id,&n);
	if(!n)
		return "";
	return std::string(n);
}

std::string alsa_host::alsa_card_t::ll_get_longname(int id)
{
	char *n = 0;
	snd_card_get_longname(id,&n);
	if(!n)
		return "";
	return std::string(n);
}

std::string alsa_host::alsa_card_t::ll_get_hwid(int id)
{
	std::stringstream s;
	s << "hw:" << std::dec << id;
	return s.str();
}

alsa_host::player_t &alsa_host::alsa_card_t::player()
{ return *_player; }

alsa_host::file_play_handle::file_play_handle(const std::string &file, std::function<void()> callback)
	: _stream(new isoundstream(file))
	, _callback(callback)
{}

alsa_host::file_play_handle::file_play_handle(const file_play_handle &that)
	: _stream(that._stream)
	, _callback(that._callback)
{}

void alsa_host::file_play_handle::operator()()
{
	delete _stream;
	_callback();
}

void alsa_host::init()
{
	int card = -1;
	
	// collect and allocate sound cards
	for(
		snd_card_next(&card);
		card >= 0;
		snd_card_next(&card)
	)
		if(cards_by_id.find(card) != cards_by_id.end())
			std::cout << "\e[33;01m - \e[0malsa host: warning: sound card " << card << " already exists; omitting" << std::endl;

		else
		{
			try
			{ cards_by_id[card] = new alsa_card_t(card); }
			catch(alsa::error &e)
			{
				std::cout << "\e[31;01m - \e[0malsa host: error: sound card " << card << " cannot be initialized: " << e.what() << std::endl;
			}
		}
}


void alsa_host::uninit()
{
	for(
		cards_by_id_t::iterator i = cards_by_id.begin();
		i != cards_by_id.end();
		++i
	)
		delete i->second;
}

bool alsa_host::exists(uint8_t card_id, uint8_t channel_id)
{
	cards_by_id_t::iterator card = cards_by_id.find(card_id);
	return (card != cards_by_id.end() && card->second->player().num_channels() > channel_id);
}

alsa_host::stream_id_type
alsa_host::play(const std::string &file, uint8_t card_id, uint8_t channel_id, float gain, std::function<void()> callback)
{
	cards_by_id_t::iterator card = cards_by_id.find(card_id);
	if(card == cards_by_id.end())
	{
		std::cout << "\e[31;01m - \e[0malsa host: play error: invalid card id `" << (int)card_id << "' specified" << std::endl;
		//TODO: do on worker thread
		callback();
		return 0;
	}
	
	file_play_handle f(file,callback);

	return card->second->player().play(f.stream(),channel_id,gain,f);
}

void
alsa_host::cancel(uint8_t card_id, stream_id_type sid)
{
	cards_by_id_t::iterator card = cards_by_id.find(card_id);
	if(card == cards_by_id.end())
	{
		std::cout << "\e[31;01m - \e[0malsa host: cancel error: invalid card id `" << (int)card_id << "' specified" << std::endl;
		return;
	}
	card->second->player().cancel(sid);
}
void
alsa_host::pause(uint8_t card_id, stream_id_type sid)
{
	cards_by_id_t::iterator card = cards_by_id.find(card_id);
	if(card == cards_by_id.end())
	{
		std::cout << "\e[31;01m - \e[0malsa host: cancel error: invalid card id `" << (int)card_id << "' specified" << std::endl;
		return;
	}
	card->second->player().pause(sid);
}
void
alsa_host::resume(uint8_t card_id, stream_id_type sid)
{
	cards_by_id_t::iterator card = cards_by_id.find(card_id);
	if(card == cards_by_id.end())
	{
		std::cout << "\e[31;01m - \e[0malsa host: cancel error: invalid card id `" << (int)card_id << "' specified" << std::endl;
		return;
	}
	card->second->player().resume(sid);
}
alsa_host::cards_by_id_t alsa_host::cards_by_id;
