#ifndef ARCTL_H
# define ARCTL_H
# include <map>
# include <forward_list>
# include <sched/lockable.h>

template<typename TConfig>
class arctl
{
	typedef typename TConfig::cfg_earpc rpc;

	typedef std::pair<net::ipv4_address,typename rpc::command_id_type> call_map_key_type;

	struct call_entry
	{
		std::condition_variable* cv;
		void ** rv;
		std::mutex *lk;

		constexpr call_entry(std::condition_variable *pcv, void **prv, std::mutex *plk)
			: cv(pcv)
			, rv(prv)
			, lk(plk)
		{}
			
	};

	typedef std::map<
		call_map_key_type,
		std::forward_list<call_entry>
	> call_map_type;

	static sched::lockable<call_map_type> call_map;


	template<typename Treturn>
	static void get_response(net::ipv4_address ip, typename rpc::command_id_type cmd, const Treturn *r)
	{
		call_map.lock();
		typename call_map_type::iterator i = call_map.find(std::make_pair(ip,cmd));
		if(i == call_map.end())
		{
			call_map.unlock();
			std::cout << "ERROR: unexpected response from " << (std::string)ip << std::endl;
			return;
		}

		while(!i->second.empty())
		{
			auto j = i->second.begin();
			*j->rv = r?new Treturn(*r):0;
			std::lock_guard<std::mutex> lg(*j->lk);
			j->cv->notify_one();
			i->second.erase_after(i->second.before_begin());
		}
		call_map.erase(i);
		call_map.unlock();
	}
		

	static void get_response_s(net::ipv4_address ip, typename rpc::command_id_type cmd, const std::string &r)
	{ get_response(ip,cmd,&r); }

	template<typename Treturn>
	bool get(typename rpc::command_id_type cmd,Treturn &r)
	{
		Treturn *rv;
		std::condition_variable cv;
		std::mutex lk;

		const call_map_key_type key = std::make_pair(ip,cmd);

		call_map.lock();

		bool call_ongoing = call_map.find(std::make_pair(ip,cmd)) != call_map.end();
		call_map[key].emplace_front(
			&cv,
			reinterpret_cast<void**>(&rv),
			&lk
		);

		if(!call_ongoing)
		{
			call_map.unlock();
			rpc::call(ip,cmd,true,get_response<Treturn>);
		}
		else
			call_map.unlock();

		std::unique_lock<std::mutex> ul(lk);
		cv.wait(ul);

		if(!rv)
			return false;

		r = *rv;
		delete rv;
		return true;
	}

	bool get(typename rpc::command_id_type cmd,std::string &r)
	{
		std::string *rv;
		std::condition_variable cv;
		std::mutex lk;

		const call_map_key_type key = std::make_pair(ip,cmd);

		call_map.lock();

		bool call_ongoing = call_map.find(std::make_pair(ip,cmd)) != call_map.end();
		call_map[key].emplace_front(
			&cv,
			reinterpret_cast<void**>(&rv),
			&lk
		);

		call_map.unlock();
		if(!call_ongoing)
			rpc::call(ip,cmd,true,get_response_s);
		std::unique_lock<std::mutex> ul(lk);
		cv.wait(ul);

		if(!rv)
			return false;

		r = *rv;
		delete rv;
		return true;
	}

public:
	typedef TConfig config;

	const net::ipv4_address ip;

	arctl(net::ipv4_address pip)
		: ip(pip)
	{}

	bool system_version(uint32_t &out)
	{ return get(0xffffffff00001000,out); }

	bool system_serial(uint64_t &out)
	{ return get(0xffffffff00001001,out); }

	bool system_monothonic_clock(uint64_t &out)
	{ return get(0xffffffff00001002,out); }

	bool system_wall_clock(uint64_t &out)
	{ return get(0xffffffff00001003,out); }

	bool system_commit_id(std::string &out)
	{ return get(0xffffffff00001004,out); }

	bool system_build_number(uint32_t &out)
	{ return get(0xffffffff00001005,out); }

	bool system_cpu_usage(uint16_t &out)
	{ return get(0xffffffff00001006,out); }

	bool app_status(uint8_t &out)
	{ return get(0xffffffff00004000,out); }

	bool app_is_running(bool &out)
	{ return get(0xffffffff00004001,out); }

	bool app_name(std::string &out)
	{ return get(0xffffffff00004003,out); }
};
template<typename c>
sched::lockable<typename arctl<c>::call_map_type> arctl<c>::call_map;
#endif
