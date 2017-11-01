#include <log.h>
#include <cctype>
std::ostream &log::get_stream(const std::string&)
{
	if(!out_stream)	
	{
		out_stream = new std::ofstream("/var/log/wic_host.log",std::ios_base::app);
	}

	if(!out_stream || !*out_stream)
	{
		std:: cout << "\e[31;01m - \e[0mlog error: cannot write to output stream" << std::endl;
		delete out_stream;
		out_stream = 0;
		return std::cout;
	}

	return *out_stream;
}

std::string log::get_timestamp()
{
	time_t now;
	time(&now);
	char buf[64];
	strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));	
	return buf;
}

std::string log::level_to_string(const char *p, uint8_t limit)
{
	std::stringstream s;
	s << p;
	const uint8_t d = (limit-level);
	if(d)
		s << ' ' << d;

	return s.str();
}

std::string log::get_level()
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

bool log::needs_output()
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

log &log::operator<<(std::ostream&(*f)(std::ostream&))
{
	if(needs_output())
		buffer << f;
	return *this;
}

log &log::operator<<(end_type)
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

		file_lock.lock();
		std::ostream &o = get_stream(domain);
		o << prefix + payload + "\n\n";
		o.flush();
		file_lock.unlock();
	}
	buffer.str(std::string());
	return *this;
}

log::~log()
{
	buffer.seekg(0,std::ios::end);
	if(buffer.tellg())
	{
		buffer.seekg(0,std::ios::beg);
		*this << end;
	}
}


std::ostream *log::out_stream = 0;

std::mutex    log::file_lock;

uint8_t       log::min_level = log::info;

std::map<std::string,uint8_t> log::domains = {
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
