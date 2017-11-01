#ifndef LOG_H
# define LOG_H
# include <iostream>
# include <fstream>
# include <sstream>
# include <cstdint>
# include <mutex>
# include <set>

class log
{
	static std::ostream *out_stream;

	static std::set<std::string> domains;

	const std::string   &domain;

	const uint8_t        level;

	std::stringstream    buffer;

	static std::mutex    file_lock;


	static std::ostream &get_stream(const std::string&)
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

	static std::string get_timestamp()
	{
		time_t now;
		time(&now);
		char buf[64];
		strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));	
		return buf;
	}

	std::string level_to_string(const char *p, uint8_t limit)
	{
		std::stringstream s;
		s << p;
		const uint8_t d = (limit-level);
		if(d)
			s << ' ' << d;

		return s.str();
	}


	std::string get_level()
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

public:
	struct end_type {};
	
	static uint8_t min_level;

	constexpr static const end_type end = end_type();

	static const uint8_t fatal = 0;
	static const uint8_t critical = 16;
	static const uint8_t error = 32;
	static const uint8_t warning = 48;
	static const uint8_t info = 64;
	static const uint8_t debug = 80;
	static const uint8_t trace = 255;

	log(uint8_t plevel, const std::string &pdomain)
		: domain(pdomain)
		, level(plevel)
	{}


	template<typename T>
	log &operator<<(T v)
	{
		if(level <= min_level && domains.find(domain) != domains.end())
			buffer << v;
		return *this;
	}

	log &operator<<(std::ostream&(*f)(std::ostream&))
	{
		if(level <= min_level && domains.find(domain) != domains.end())
			buffer << f;
		return *this;
	}

	log &operator<<(end_type)
	{
		if(level <= min_level && domains.find(domain) != domains.end())
		{
			const std::string prefix = get_timestamp() + " ["+get_level()+"] ("+domain+") ";
			std::string payload = buffer.str();
			for(
				auto p = payload.find('\n');
				p != std::string::npos;
				p = payload.find('\n',p+1)
			)
				payload.insert(p+1,std::string(prefix.size(),' '));

			file_lock.lock();
			get_stream(domain) << prefix + payload << std::endl;
			file_lock.unlock();
		}
		buffer.str(std::string());
		return *this;
	}

	~log()
	{
		buffer.seekg(0,std::ios::end);
		if(buffer.tellg())
		{
			buffer.seekg(0,std::ios::beg);
			*this << end;
		}
	}
};
#endif
