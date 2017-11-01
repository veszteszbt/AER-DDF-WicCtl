#ifndef LOG_H
# define LOG_H
# include <iostream>
# include <fstream>
# include <sstream>
# include <cstdint>
# include <mutex>
# include <map>

class log
{
	static std::ostream *out_stream;

	static std::map<std::string,uint8_t> domains;

	const std::string   &domain;

	const uint8_t        level;

	std::stringstream    buffer;

	static std::mutex    file_lock;


	static std::ostream &get_stream(const std::string&);

	static std::string get_timestamp();

	std::string level_to_string(const char *p, uint8_t limit);

	std::string get_level();

	bool needs_output();

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
		if(needs_output())
			buffer << v;
		return *this;
	}

	log &operator<<(std::ostream&(*f)(std::ostream&));

	log &operator<<(end_type);

	~log();
};
#endif
