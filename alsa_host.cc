#include <alsa_host.h>

alsa_host::player_t::stream_type::stream_type(uint8_t pchannel, std::istream &pstream)
	: channel(pchannel)
	, stream(pstream)
{}
std::string alsa_host::player_t::itos(uint8_t v)
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
		const size_t rbytes = period*2;
		memset(buffer,0,rbytes*channels);
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
	std::cout << "\e[37;01m - \e[0malsa host: player uninitialized for device " << (int)device << std::endl;
}


alsa_host::player_t::player_t(uint8_t pdevice, unsigned prate)
	: pcm(itos(pdevice).c_str(),SND_PCM_STREAM_PLAYBACK,0)
	, device(pdevice)
	, rate(prate)
	, disposed(false)
	, process(&alsa_host::player_t::start,this)
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

	const unsigned l = period*channels;
	buffer = new uint16_t[l];
	sbuffer = new uint16_t[period];
	notify();
}

void alsa_host::player_t::play(std::istream &stream, uint8_t channel)
{
	streams_lock.lock();
	streams.push_back(stream_type(channel,stream));
	streams_lock.unlock();
	notify();
}

alsa_host::player_t::~player_t()
{
	disposed = true;
	notify();
	process.join();
	delete buffer;
	delete sbuffer;
}

alsa_host::alsa_card_t::alsa_card_t()
	: id(-1)
	, player(0)
{}

alsa_host::alsa_card_t::alsa_card_t(int pid)
	: id(pid)
	, name(ll_get_name(pid))
	, longname(ll_get_longname(pid))
	, hwid(ll_get_hwid(pid))
	
{
	// collect information about sound card
	snd_ctl_t *ctl;

	if(snd_ctl_open(&ctl,hwid.c_str(),0))
	{
		std::cout << "\e[31;01m - \e[0malsa host: error obtaining ctl for sound card #" << id << std::endl;
		return;
	}

	snd_ctl_card_info_t *info;
	snd_ctl_card_info_malloc(&info);

	snd_ctl_card_info(ctl,info);

	//std::cout << "Components: " << snd_ctl_card_info_get_components(info) << std::endl;

	snd_ctl_card_info_free(info);

	std::cout << "\e[32;01m - \e[0malsa host: registered sound card #" << id << " - " << name << " ("<<longname<<")" << std::endl;
	player = new player_t(id);
}

alsa_host::alsa_card_t::~alsa_card_t()
{ delete player; }

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

void alsa_host::play(const std::string &file, uint8_t card_id, uint8_t channel_id)
{
	cards_by_id_t::iterator card = cards_by_id.begin();
	if(card == cards_by_id.end())
	{
		std::cout << "\e[31;01m - \e[0malsa host: play error: invalid card id `" << (int)card_id << "' specified" << std::endl;
	}

	//if(files)
	//card->player().play(stream,channel);
}
alsa_host::cards_by_id_t alsa_host::cards_by_id;
