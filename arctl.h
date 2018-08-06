#ifndef ARCTL_H
# define ARCTL_H
# include <map>
# include <forward_list>
# include <sched/lockable.h>
# include <oosp/role.h>

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
	static void get_response(typename rpc::template outgoing_call_handle<Treturn,bool> h)
	{
		call_map.lock();
		typename call_map_type::iterator i = call_map.find(std::make_pair(h.orig_ip,h.command_id));
		if(i == call_map.end())
		{
			call_map.unlock();
			std::cout << "ERROR: unexpected response from " << (std::string)h.ip << std::endl;
			return;
		}

		while(!i->second.empty())
		{
			auto j = i->second.begin();
			*j->rv = (h.reason == earpc::reason::success)
				? new Treturn(h.value())
				: 0
			;
			std::lock_guard<std::mutex> lg(*j->lk);
			j->cv->notify_one();
			i->second.erase_after(i->second.before_begin());
		}
		call_map.erase(i);
		call_map.unlock();
	}
		

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
public:
	typedef TConfig config;

	typedef typename rpc::call_id_type call_id_type;

	template<typename T>
	using get_handle = typename rpc::template outgoing_call_handle<T,bool>;

	template<typename T>
	using set_handle = typename rpc::template outgoing_call_handle<bool,T>;

	template<typename T>
	using get_handler = void(*)(get_handle<T>);

	template<typename T>
	using set_handler = void(*)(set_handle<T>);

	const net::ipv4_address ip;

	arctl(net::ipv4_address pip)
		: ip(pip)
	{}

	bool system_version(uint32_t &out)
	{ return get(0xffffffff00001000,out); }

	call_id_type system_version(get_handler<uint32_t> handler)
	{ return rpc::call(ip,0xffffffff00001000,true,handler); }


	bool system_serial(uint64_t &out)
	{ return get(0xffffffff00001001,out); }

	call_id_type system_serial(get_handler<uint64_t> handler)
	{ return rpc::call(ip,0xffffffff00001001,true,handler); }


	bool system_monothonic_clock(uint64_t &out)
	{ return get(0xffffffff00001002,out); }

	call_id_type system_monothonic_clock(get_handler<uint64_t> handler)
	{ return rpc::call(ip,0xffffffff00001002,true,handler); }


	bool system_wall_clock(uint64_t &out)
	{ return get(0xffffffff00001003,out); }

	call_id_type system_wall_clock(get_handler<uint64_t> handler)
	{ return rpc::call(ip,0xffffffff00001003,true,handler); }


	bool system_commit_id(std::string &out)
	{ return get(0xffffffff00001004,out); }

	call_id_type system_commit_id(get_handler<std::string> handler)
	{ return rpc::call(ip,0xffffffff00001004,true,handler); }


	bool system_build_number(uint32_t &out)
	{ return get(0xffffffff00001005,out); }
	
	call_id_type system_build_number(get_handler<uint32_t> handler)
	{ return rpc::call(ip,0xffffffff00001005,true,handler); }


	bool system_cpu_usage(uint16_t &out)
	{ return get(0xffffffff00001006,out); }

	call_id_type system_cpu_usage(get_handler<uint16_t> handler)
	{ return rpc::call(ip,0xffffffff00001006,true,handler); }


	bool network_server_ip(net::ipv4_address &out)
	{ return get(0xffffffff00003008,out); }

	call_id_type network_server_ip(get_handler<net::ipv4_address> handler)
	{ return rpc::call(ip,0xffffffff00003008,true,handler); }


	bool app_status(uint8_t &out)
	{ return get(0xffffffff00004000,out); }

	call_id_type app_status(get_handler<uint8_t> handler)
	{ return rpc::call(ip,0xffffffff00004000,true,handler); }


	bool app_is_running(bool &out)
	{ return get(0xffffffff00004001,out); }

	call_id_type app_is_running(get_handler<bool> handler)
	{ return rpc::call(ip,0xffffffff00004001,true,handler); }


	bool app_name(std::string &out)
	{ return get(0xffffffff00004003,out); }

	call_id_type app_name(get_handler<std::string> handler)
	{ return rpc::call(ip,0xffffffff00004003,true,handler); }

};
template<typename c>
sched::lockable<typename arctl<c>::call_map_type> arctl<c>::call_map;
#endif
