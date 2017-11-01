#ifndef WIC_DEVICE_H
# define WIC_DEVICE_H
# include <cstdint>
# include <string>
# include <chrono>
# include <types/time.h>
# include <net/ipv4_address.h>
# include <arctl.h>
# include <log.h>

namespace wic {

template<typename TConfig>
class device 
{	
	typedef typename TConfig::cfg_earpc   rpc;

	typedef arctl<TConfig>                wifictl;

	typedef std::chrono::high_resolution_clock     clock;


	struct
	__attribute__((packed))
	heartbeat_payload_type
	{
		uint64_t serial;
		uint32_t counter;
	};

	typedef typename rpc::template call_handle<bool> heartbeat_call_handle_type;


	typedef std::map<net::ipv4_address, device<TConfig>*> dev_by_ip_type;

	typedef std::map<uint64_t, device<TConfig>*>          dev_by_serial_type;

	static dev_by_ip_type     dev_by_ip;

	static dev_by_serial_type dev_by_serial;

	static std::mutex         cont_lock;


	volatile uint32_t          heartbeat_count;

	std::mutex                 inst_lock;

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
		cont_lock.lock();
		typename dev_by_ip_type::iterator i = dev_by_ip.find(ip);
		if(i != dev_by_ip.end())
			r = i->second;

		cont_lock.unlock();
		return r;
	}

	static device<TConfig> *get(uint64_t serial)
	{
		device<TConfig> *r = 0;
		cont_lock.lock();
		typename dev_by_serial_type::iterator i = dev_by_serial.find(serial);
		if(i != dev_by_serial.end())
			r = i->second;

		cont_lock.unlock();
		return r;
	}

	static device<TConfig> *set(device<TConfig> *r)
	{
		cont_lock.lock();
		dev_by_serial[r->serial] = r;
		dev_by_ip[r->ip] = r;
		cont_lock.unlock();
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
			return;
		}

		h.respond(true);

		device<TConfig>
			*r = get(v->serial),
			*o = get(h.ip)
		;

		if(r)
			r->heartbeat(h.ip,v->counter);

		else if(o)
		{
			log(log::critical,"wic.device.client") << "ip collision on device arrival: " << (std::string)h.ip <<
				" bound to two devices: " << std::hex << v->serial << " amd " << o->serial <<
				log::end;
		}
		else
			set(new device(v->serial, h.ip, v->counter));
	}

	void process_start()
	{
		wifictl *ctl = new wifictl(ip);

		uint32_t hb_value = 0, hb_outages = 0;


		log(log::debug,"wic.device.client") << "process initialized for " << std::hex << serial << " (" <<
			(std::string)ip << ")" << log::end;


		while(process_running)
		{
			inst_lock.lock();
			if(ctl->ip != ip)
			{
				delete ctl;
				ctl = new wifictl(ip);
				log(log::debug,"wic.device.client")  << "recreated control for new ip " << (std::string)ip <<
					log::end;
			}
			inst_lock.unlock();

			if(!initialized)
			{
				std::string t_app_name;
				if(!ctl->app_name(t_app_name))
				{
					log(log::error,"wic.device.client") << "unable to get app name from " <<
						(std::string)ctl->ip << log::end;
					continue;
				}

				bool t_app_running;
				if(!ctl->app_is_running(t_app_running))
				{
					log(log::error,"wic.device.client")  << "unable to get state of app " << t_app_name <<
						" from "  << (std::string)ip << log::end;
					continue;
				}

				inst_lock.lock();

				app_name    = t_app_name;
				app_running = t_app_running;
				initialized = true;
				hb_outages  = 0;

				std::cout << (std::string)ip << " --> " << app_name << " "  <<
					(app_running?"\e[32;01m(running)":"\e[31;01m(not running)") << "\e[0m" <<
					std::endl;
				log(log::info,"wic.device.client") << (std::string)ip << ": app " << app_name << " " <<
					(app_running?"(running)":"(not running)") << log::end;

				inst_lock.unlock();
			}

			inst_lock.lock();
			const clock::time_point hb_expect = clock::now()+std::chrono::milliseconds(1200);
			inst_lock.unlock();

			{
				std::unique_lock<std::mutex> ul(suspend_lock);
				suspend_cv.wait_until(ul,hb_expect);
			}

			const clock::time_point finish = clock::now();



			inst_lock.lock();
			if(heartbeat_count == hb_value)
			{
				++hb_outages;
				if(hb_outages > 20)
				{
					initialized = false;
					std::cout << (std::string)ip << " -x-> " << app_name << "\e[31;01m(gone)\e[0m" << std::endl;
					log(log::error,"wic.device.client") << (std::string)ip << ": too many heartbeat outages; " <<
						"resetting to uninitialized state" << log::end;
				}
				else
					log(log::warning,"wic.device.client")  << (std::string)ip <<
						": heartbeat outage " << hb_outages << log::end;
			}

			else
			{
				if(hb_outages)
				{
					log(log::warning,"wic.device.client") << (std::string)ip << ": back in place after " <<
						static_cast<double>(types::time::nsec(finish-last_seen))/1000000000-1  <<
						" sec" << log::end;
				}
				hb_outages = 0;
				hb_value = heartbeat_count;
				last_seen = clock::now();
			}
			inst_lock.unlock();
		}

		delete ctl;
		inst_lock.lock();
		log(log::debug,"wic.device.client") << "process uninitialized for " << std::hex << serial << " (" <<
			(std::string)ip << ")" << log::end;
		inst_lock.unlock();

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
		inst_lock.lock();
		if(pip != ip)
		{
			cont_lock.lock();
			typename dev_by_ip_type::iterator j = dev_by_ip.find(ip);
			if(j->second != this)
			{
				log(log::critical,"wic.device.client") << "ip collision on ip change from " << (std::string)ip <<
					" to " << (std::string)pip << ": " << std::hex << j->second->serial <<
					" and " << j->second->serial << log::end;
			}
			else
			{
				dev_by_ip.erase(j);
				ip = pip;
				dev_by_ip[pip] = this;
				log(log::info,"wic.device.client") << "ip change on device " << std::hex << j->second->serial <<
					"; old ip: " << (std::string)ip << "; new ip: " << 
					(std::string)pip << log::end;

			}
			cont_lock.unlock();
		}
		heartbeat_count = counter;
		inst_lock.unlock();

		std::lock_guard<std::mutex> lg(suspend_lock);
		suspend_cv.notify_one();
	}

public:
	const uint64_t        serial;

	static void init()
	{
		rpc::set_command(
			0xffffffff0ffff000,
			heartbeat_handler
		);
		log(log::debug,"wic.device.host") << "initialized" << log::end;
	}
};

template<typename c>
typename device<c>::dev_by_ip_type device<c>::dev_by_ip;

template<typename c>
typename device<c>::dev_by_serial_type device<c>::dev_by_serial;

template<typename c>
std::mutex device<c>::cont_lock;

}
#endif
