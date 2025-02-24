#ifndef LOG_H
# define LOG_H
# include <iostream>
# include <fstream>
# include <sstream>
# include <cstdint>
# include <mutex>
# include <map>
# include <queue>
# include <thread>
# include <condition_variable>

class journal
{
	static std::ostream *out_stream;

	static std::map<std::string,uint8_t> domains;

	static std::mutex    item_lock;

	static std::mutex    suspend_lock;

	static std::queue<std::string*> item_list;

	static std::thread *process;

	static std::condition_variable suspend_cv;


	const std::string    domain;

	const uint8_t        level;

	std::stringstream    buffer;




	static std::ostream &get_stream(const std::string&);

	static std::string get_timestamp();

	std::string level_to_string(const char *p, uint8_t limit);

	std::string get_level();

	bool output;

	static volatile bool is_running;

	static void process_start();

	static void suspend();

	static void notify(const std::string &s);


public:
	struct end_type {};
	
	static uint8_t min_level;

	static uint8_t default_level;

	constexpr static const end_type end = end_type();

	static const uint8_t fatal = 0;
	static const uint8_t critical = 16;
	static const uint8_t error = 32;
	static const uint8_t warning = 48;
	static const uint8_t info = 64;
	static const uint8_t debug = 80;
	static const uint8_t trace = 96;

	static void init();

	static void uninit();

	static uint8_t domain_level(const std::string &domain);

	static void domain_level(const std::string &domain,uint8_t level);

	static std::vector<std::string> get_domains();

	journal(uint8_t plevel, const std::string &pdomain);

	journal(const journal &t)
		: domain(t.domain)
		, level(t.level)
		, output(t.output)
	{ if(output) buffer << t.buffer.str(); }


	template<typename T>
	journal &operator<<(T v)
	{
		if(output)
			buffer << v;
		return *this;
	}

	journal &operator<<(std::ostream&(*f)(std::ostream&));

	journal &operator<<(end_type);

	~journal();
};
#endif
