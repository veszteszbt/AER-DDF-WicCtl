#ifndef WIC_DEVICE_H
# define WIC_DEVICE_H
# include <cstdint>
# include <string>
# include <chrono>
# include <types/time.h>
# include <net/ipv4_address.h>
# include <arctl.h>
# include <journal.h>

namespace wic {

template<typename TConfig>
class device : public wicp::device_type
{	
	typedef typename TConfig::cfg_earpc   rpc;

	typedef arctl<TConfig>                wifictl;

	typedef std::chrono::high_resolution_clock     clock;


#pragma pack(push,1)
	struct
	heartbeat_payload_type
	{
		uint64_t serial;
		uint32_t counter;
	};
#pragma pack(pop)

	typedef typename rpc::template call_handle<bool> heartbeat_call_handle_type;


	typedef std::map<net::ipv4_address, device<TConfig>*> dev_by_ip_type;

	typedef std::map<uint64_t, device<TConfig>*>          dev_by_serial_type;

	typedef std::map<std::string, device<TConfig>*>       dev_by_app_name_type;

	typedef std::map<std::string, wicp::role_type*>            role_by_name_type;

	static dev_by_ip_type       dev_by_ip;

	static dev_by_serial_type   dev_by_serial;

	static dev_by_app_name_type dev_by_app_name;

	static std::mutex           lock;

	static role_by_name_type role_by_name;

	volatile uint32_t          heartbeat_count;

	std::mutex                 suspend_lock;

	clock::time_point          last_seen;

	net::ipv4_address          ip;

	std::string                app_name;

	std::thread               *process;

	std::atomic_bool           process_running;

	std::condition_variable    suspend_cv;

	bool                       initialized;

	bool                       app_running;

	static device<TConfig> *get(net::ipv4_address ip)
	{
		device<TConfig> *r = 0;
		typename dev_by_ip_type::iterator i = dev_by_ip.find(ip);
		if(i != dev_by_ip.end())
			r = i->second;

		return r;
	}

	static device<TConfig> *get(uint64_t serial)
	{
		device<TConfig> *r = 0;
		typename dev_by_serial_type::iterator i = dev_by_serial.find(serial);
		if(i != dev_by_serial.end())
			r = i->second;

		return r;
	}

	static device<TConfig> *get(const std::string &name)
	{
		device<TConfig> *r = 0;
		typename dev_by_app_name_type::iterator i = dev_by_app_name.find(name);
		if(i != dev_by_app_name.end())
			r = i->second;

		return r;
	}

	static device<TConfig> *set(device<TConfig> *r)
	{
		dev_by_serial[r->serial] = r;
		dev_by_ip[r->ip] = r;
		return r;
	}


	static void heartbeat_handler(
		typename rpc::template call_handle<bool> h,
		const heartbeat_payload_type *v
	)
	{
		if(!v)
		{
			h.respond(false);
			journal(journal::error,"wic.device") << (std::string)h.ip << ": empty heartbeat payload" <<
				journal::end;
			return;
		}
		h.respond(true);
		journal(journal::trace,"wic.device.heartbeat") << (std::string)h.ip <<
			" -> {"<<std::hex<<v->serial<<","<<std::dec<<v->counter<<"}" <<
			journal::end;

		lock.lock();
		device<TConfig>
			*r = get(v->serial),
			*o = get(h.ip)
		;

		if(r)
		{
			journal(journal::trace,"wic.device.heartbeat") << (std::string)h.ip <<
				" -> {"<<std::hex<<v->serial<<","<<std::dec<<v->counter<<"}; notifying instance" <<
				journal::end;
			lock.unlock();
			r->heartbeat(h.ip,v->counter);
		}

		else if(o)
		{
			journal(journal::critical,"wic.device.client") << "ip collision on device arrival: " << (std::string)h.ip <<
				" bound to two devices: " << std::hex << v->serial << " amd " << o->serial <<
				journal::end;
			lock.unlock();
		}
		else
		{
			journal(journal::trace,"wic.device.heartbeat") << (std::string)h.ip <<
				" -> {"<<std::hex<<v->serial<<","<<std::dec<<v->counter<<"}; creating instance" <<
				journal::end;
			set(new device(v->serial, h.ip, v->counter));
			lock.unlock();
		}
	}

	void process_start()
	{
		wifictl *ctl = new wifictl(ip);

		uint32_t hb_value = 0, hb_outages = 0;


		journal(journal::debug,"wic.device.client") << "process initialized for " << std::hex << serial << " (" <<
			(std::string)ip << ")" << journal::end;


		while(process_running)
		{
			lock.lock();
			if(ctl->ip != ip)
			{
				delete ctl;
				ctl = new wifictl(ip);
				journal(journal::debug,"wic.device.client")  << "recreated control for new ip " << (std::string)ip <<
					journal::end;
			}
			lock.unlock();

			if(!initialized)
			{
				std::string t_app_name;
				if(!ctl->app_name(t_app_name))
				{
					journal(journal::error,"wic.device.client") << "unable to get app name from " <<
						(std::string)ctl->ip << journal::end;
					continue;
				}

				while(t_app_name.size() && !t_app_name.back())
					t_app_name.resize(t_app_name.size()-1);

				bool t_app_running;
				if(!ctl->app_is_running(t_app_running))
				{
					journal(journal::error,"wic.device.client")  << "unable to get state of app " << t_app_name <<
						" from "  << (std::string)ip << journal::end;
					continue;
				}

				lock.lock();

				app_name    = t_app_name;
				app_running = t_app_running;
				initialized = true;
				hb_outages  = 0;

				std::cout << (std::string)ip << " --> " << app_name << " "  <<
					(app_running?"\e[32;01m(running)":"\e[31;01m(not running)") << "\e[0m" <<
					std::endl;

				journal(journal::info,"wic.device.client") << (std::string)ip << ": app " << app_name << " " <<
					(app_running?"(running)":"(not running)") << journal::end;

				wicp::role_type *role = _get_role(app_name);
				if(role)
				{
					lock.unlock();
					if(role->bind(*this))
						journal(journal::info,"wic.device.client") << (std::string)get_ip() << ": bound to role `" <<
							role->name << "'" << journal::end;
					else
					{
						journal(journal::warning,"wic.device.client") << (std::string)get_ip() << ": corresponding role `" <<
							role->name << "' already bound to " << (std::string)role->get_ip() << journal::end;
					
					}
				}
				else
				{
					lock.unlock();
					journal(journal::warning,"wic.device.client") << (std::string)get_ip() << ": role `" <<
						app_name << "' not found" << journal::end;
				}

			}

			lock.lock();
			const clock::time_point hb_expect = clock::now()+std::chrono::milliseconds(1200);
			lock.unlock();

			{
				std::unique_lock<std::mutex> ul(suspend_lock);
				suspend_cv.wait_until(ul,hb_expect);
			}

			const clock::time_point finish = clock::now();

			lock.lock();
			if(heartbeat_count == hb_value)
			{
				++hb_outages;
				if(hb_outages > 5)
				{
					initialized = false;
					wicp::role_type *role = _get_role(app_name);
					if(role)
					{
						if(role->is_bound_to(*this))
							role->unbind();
					}
					std::cout << (std::string)ip << " -x-> " << app_name << " \e[31;01m(gone)\e[0m" << std::endl;
					journal(journal::error,"wic.device.client") << (std::string)ip << ": too many heartbeat outages; " <<
						"resetting to uninitialized state" << journal::end;
				}
				else
					journal(journal::warning,"wic.device.client")  << (std::string)ip <<
						": heartbeat outage " << hb_outages << journal::end;
			}

			else
			{
				if(hb_outages)
				{
					journal(journal::warning,"wic.device.client") << (std::string)ip << ": back in place after " <<
						static_cast<double>(types::time::nsec(finish-last_seen))/1000000000-1  <<
						" sec" << journal::end;
				}
				hb_outages = 0;
				hb_value = heartbeat_count;
				last_seen = clock::now();
			}
			lock.unlock();
		}

		delete ctl;
		lock.lock();
		journal(journal::debug,"wic.device.client") << "process uninitialized for " << std::hex << serial << " (" <<
			(std::string)ip << ")" << journal::end;
		lock.unlock();

	}

	~device()
	{
		process_running = false;
		process->join();
		delete process;
	}

	device(uint64_t pserial, net::ipv4_address pip, uint32_t counter = 0)
		: serial(pserial)
		, heartbeat_count(counter)
		, ip(pip)
		, process_running(true)
		, initialized(false)
		, app_running(false)
		, last_seen(clock::now())
	{
		process = new std::thread(std::bind(&device<TConfig>::process_start,this));
#ifdef __linux__
		pthread_setname_np(process->native_handle(),"wic device");
#endif

	}

	void heartbeat(net::ipv4_address pip, uint32_t counter)
	{
		lock.lock();
		if(pip != ip)
		{
			typename dev_by_ip_type::iterator j = dev_by_ip.find(ip);
			if(j->second != this)
			{
				journal(journal::critical,"wic.device.client") << "ip collision on ip change from " << (std::string)ip <<
					" to " << (std::string)pip << ": " << std::hex << j->second->serial <<
					" and " << j->second->serial << journal::end;
			}
			else
			{
				dev_by_ip.erase(j);
				ip = pip;
				dev_by_ip[pip] = this;
				journal(journal::info,"wic.device.client") << "ip change on device " << std::hex << j->second->serial <<
					"; old ip: " << (std::string)ip << "; new ip: " << 
					(std::string)pip << journal::end;

			}
		}
		heartbeat_count = counter;
		lock.unlock();

		std::lock_guard<std::mutex> lg(suspend_lock);
		suspend_cv.notify_one();
	}

	static void _set_role(wicp::role_type &role)
	{
		auto i = role_by_name.find(role.name);
		if(i != role_by_name.end())
		{
			i->second->unbind();
			role_by_name.erase(i);
		}

		role_by_name[role.name] = &role;
		role.bind(*get(role.name));
	}

	static bool _unset_role(const std::string &role)
	{
		auto i = role_by_name.find(role);
		if(i == role_by_name.end())
			return false;
		i->second->unbind();
		role_by_name.erase(i);
		return true;
	
	}
	static wicp::role_type *_get_role(const std::string &role)
	{
		auto i = role_by_name.find(role);
		if(i == role_by_name.end())
			return 0;
		return i->second;
	}

public:
	const uint64_t serial;

	static const role_by_name_type &roles()
	{ return role_by_name; }

	static void set_role(wicp::role_type &role)
	{
		lock.lock();
		_set_role(role);
		lock.unlock();
	}

	static bool unset_role(const std::string &role)
	{
		lock.lock();
		const bool r = _unset_role();
		lock.unlock();
		return r;
	}

	static wicp::role_type *get_role(const std::string &role)
	{
		lock.lock();
		wicp::role_type *const r = _get_role(role);
		lock.unlock();
		return r;
	}

	static const dev_by_serial_type &devices()
	{ return dev_by_serial; }

	bool get_app_state()
	{
		lock.lock();
		const bool r = app_running;
		lock.unlock();
		return r;
	}

	std::string get_app_name()
	{
		lock.lock();
		const std::string r = app_name;
		lock.unlock();
		return r;
	}

	virtual std::string get_name()
	{ return get_app_name(); }

	virtual net::ipv4_address get_ip()
	{
		lock.lock();
		const net::ipv4_address r = ip;
		lock.unlock();
		return r;
	}

	uint8_t get_state()
	{
		lock.lock();
		if(!initialized)
		{
			lock.unlock();
			return 0;
		}

		const double v = (254.0*(types::time::nsec(clock::now()-last_seen)/1000000000-1)/5);
		lock.unlock();

		if(v < 0)
			return 255;

		if(v > 254)
			return 0;

		return static_cast<uint8_t>(255-v);
	}


	static void init()
	{
		rpc::set_command(
			0xffffffff0ffff000,
			heartbeat_handler
		);
		journal(journal::debug,"wic.device.host") << "initialized" << journal::end;
	}

};

template<typename c>
typename device<c>::dev_by_ip_type device<c>::dev_by_ip;

template<typename c>
typename device<c>::dev_by_serial_type device<c>::dev_by_serial;

template<typename c>
typename device<c>::dev_by_app_name_type device<c>::dev_by_app_name;

template<typename c>
std::mutex device<c>::lock;

template<typename c>
typename device<c>::role_by_name_type device<c>::role_by_name;

}
#endif
