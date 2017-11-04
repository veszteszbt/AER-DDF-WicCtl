#include <journal.h>
#include <cctype>
std::ostream &journal::get_stream(const std::string&)
{
	if(!out_stream || !*out_stream)
	{
		std:: cout << "\e[31;01m - \e[0mjournal error: cannot write to output stream" << std::endl;
		delete out_stream;
		out_stream = 0;
		return std::cout;
	}

	return *out_stream;
}

std::string journal::get_timestamp()
{
	time_t now;
	time(&now);
	char buf[64];
	strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));	
	return buf;
}

std::string journal::level_to_string(const char *p, uint8_t limit)
{
	std::stringstream s;
	s << p;
	const uint8_t d = (limit-level);
	if(d)
		s << ' ' << d;

	return s.str();
}

std::string journal::get_level()
{
	if(level > debug)
		return level_to_string("TRACE",trace);
	else if(level > info)
		return level_to_string("DEBUG",debug);
	else if(level > warning)
		return level_to_string("INFO",info);
	else if(level > error)
		return level_to_string("WARNING",warning);
	else if(level > critical)
		return level_to_string("ERROR",error);
	else if(level > fatal)
		return level_to_string("CRITICAL",critical);
	else
		return level_to_string("FATAL",fatal);
}

bool journal::needs_output()
{
	if(level > min_level)
		return false;

	auto i = domains.find(domain);
	if(i == domains.end())
		return false;

	if(level > i->second)
		return false;

	return true;
}

journal &journal::operator<<(std::ostream&(*f)(std::ostream&))
{
	if(needs_output())
		buffer << f;
	return *this;
}

journal &journal::operator<<(end_type)
{
	if(needs_output())
	{
		const std::string prefix = get_timestamp() + " ["+get_level()+"] ("+domain+") ";
		std::string payload = buffer.str();
		int len = payload.size();
		for(
			auto i = payload.rbegin();
			i != payload.rend() && std::isspace(*i);
			++i
		)
			--len;

		payload.resize(len);

		for(
			auto p = payload.find('\n');
			p != std::string::npos;
			p = payload.find('\n',p+1)
		)
			payload.insert(p+1,std::string(prefix.size(),' '));

		notify(prefix + payload + "\n\n");
	}
	buffer.str(std::string());
	return *this;
}

journal::~journal()
{
	buffer.seekg(0,std::ios::end);
	if(buffer.tellg())
	{
		buffer.seekg(0,std::ios::beg);
		*this << end;
	}
}


void journal::suspend()
{
	std::unique_lock<std::mutex> ul(suspend_lock);
	suspend_cv.wait(ul);
}

void journal::notify(const std::string &s)
{
	item_lock.lock();
	item_list.push(new std::string(s));
	item_lock.unlock();
	std::lock_guard<std::mutex> lg(suspend_lock);
	suspend_cv.notify_one();

}

void journal::process_start()
{
	out_stream = new std::ofstream("/var/journal/wic_host.journal",std::ios_base::app);

	while(is_running)
	{
		item_lock.lock();
		if(item_list.empty())
		{
			item_lock.unlock();
			out_stream->flush();
			suspend();
			continue;
		}

		std::string *e = item_list.front();
		item_list.pop();
		item_lock.unlock();
		
		if(!((*out_stream) << *e))
			std::cout << *e;
		delete e;
	}

	delete out_stream;
}

void journal::init()
{
	if(process)
		return;

	is_running = true;
	process = new std::thread(process_start);
#ifdef __linux__
	pthread_setname_np(process->native_handle(),"journal file writer");
#endif
}

void journal::uninit()
{
	if(process)
	{
		is_running = false;
		process->join();
		delete process;
	}
}


std::ostream  *journal::out_stream;

std::mutex    journal::item_lock;

std::mutex    journal::suspend_lock;

std::condition_variable journal::suspend_cv;

std::queue<std::string*> journal::item_list;

uint8_t       journal::min_level = journal::info;

volatile bool          journal::is_running = true;

std::thread   *journal::process = 0;


std::map<std::string,uint8_t> journal::domains = {
{"earpc.api.call",255},
{"earpc.api.respond",255},
{"earpc.process.expiry",255},
{"earpc.process.feedback",255},
{"earpc.process.master",255},
{"earpc.process.recv",255},
{"earpc.process.recv.ack",255},
{"earpc.process.recv.call",255},
{"earpc.process.recv.nak",255},
{"earpc.process.send",255},
{"wic.device.client",255},
{"wic.device.host",255},
{"wicp.commit",255},
{"wicp.property.local",255},
{"wicp.property.remote",255},
{"wicp.sync.local",255},
{"wicp.sync.remote",255}
};
