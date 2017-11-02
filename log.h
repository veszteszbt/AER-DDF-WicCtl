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

class log
{
	static std::ostream *out_stream;

	static std::map<std::string,uint8_t> domains;

	static std::mutex    item_lock;

	static std::mutex    suspend_lock;

	static std::queue<std::string*> item_list;

	static std::thread *process;

	static std::condition_variable suspend_cv;


	const std::string   &domain;

	const uint8_t        level;

	std::stringstream    buffer;




	static std::ostream &get_stream(const std::string&);

	static std::string get_timestamp();

	std::string level_to_string(const char *p, uint8_t limit);

	std::string get_level();

	bool needs_output();

	static volatile bool is_running;

	static void process_start();

	static void suspend();

	static void notify(const std::string &s);


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

	static void init();

	static void uninit();

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
