#ifndef DEVMAN_DEVICE_H
# define DEVMAN_DEVICE_H
# include <arctl.h>
namespace devman {

template<typename TEnv>
struct device : public wicp::device_type
{
	struct arctl_config
	{
		typedef typename TEnv::rpc cfg_earpc;
	};
	typedef arctl<arctl_config> arctl_type;

	typedef typename TEnv::rpc         rpc;

	typedef typename TEnv::clock       clock;

	typedef typename TEnv::time_point  time_point;

	typedef typename rpc::call_id_type call_id_type;

	wicp::role_type *volatile role;

	std::mutex        lock;

	const uint64_t    serial;

	std::string       name;

	net::ipv4_address ip;


	volatile uint8_t  state;

	volatile uint8_t  health;

	time_point        expiry;

	time_point        last_heartbeat;

	int32_t           heartbeat_deviance;

	time_point        last_latency_info;

	uint32_t          latency;


	call_id_type      call_id;

	arctl_type       *ctl;



	device(uint64_t pserial,net::ipv4_address pip)
		: serial(pserial)
		, role(0)
		, state(types::state::unseen)
		, expiry(clock::now()+std::chrono::milliseconds(static_cast<uint32_t>(TEnv::expiry_timeout)))
		, last_heartbeat(clock::now())
		, last_latency_info(time_point::min())
		, call_id(0)
		, ctl(0)
		, health(0)
		, ip(pip)
	{}

	bool is_active()
	{ return state >= types::state::active; }

	bool is_unseen()
	{ return state == types::state::unseen; }

	bool is_bound()
	{ return role; }

	void bind(wicp::role_type *prole)
	{
		role = prole;
		role->bind(*this);
		std::cout << "\e[32;01m * \e[0m" << std::hex << serial << " (" << (std::string)ip << ") --> " << prole->name << std::endl;
	}

	void unbind()
	{
		if(role)
		{
			auto *const r = role;
			role = 0;
			r->unbind();
			std::cout << "\e[31;01m * \e[0m (" << std::hex << serial << ")" << (std::string)ip << " -x-> " << r->name << std::endl;
		}
	}


	void set_unseen()
	{
		if(state == types::state::unseen)
			return;

		state = types::state::unseen;
		if(ctl)
		{
			delete ctl;
			ctl = 0;
		}
		if(call_id)
		{
			rpc::cancel(call_id);
			call_id = 0;
		}
		calculate_health();
		unbind();
	}

	void set_identify()
	{
		if(state == types::state::identify)
			return;
		state = types::state::identify;
		if(ctl)
		{
			delete ctl;
			ctl = 0;
		}
		ctl = new arctl_type(ip);
	}

	void calculate_health()
	{
		if(!is_active())
		{
			lock.lock();
			if(health)
			{
				journal(journal::trace,"devman.device") << 
					"serial: " << std::hex << serial << 
					"; health changed to 0" <<
					journal::end;
				health = 0;
				if(is_bound())
				{
					lock.unlock();
					role->on_health_change(*role);
					return;
				}
			}
			lock.unlock();
			return;
		}

		double lat = (7.8-log(latency))/6;
		if(lat > 1)
			lat = 1;
		else if(lat < 0)
			lat = 0;

		double dev = (7.8-log(abs(heartbeat_deviance)))/6;
		if(dev > 1)
			dev = 1;
		else if(dev < 0)
			dev = 0;

		const uint8_t nh = 1+static_cast<uint8_t>(lat*dev*254);
	
		lock.lock();
		if(nh != health)
		{
			journal(journal::trace,"devman.device") << 
				"serial: " << std::hex << serial << 
				"; health changed to " << std::dec << (int)nh <<
				journal::end;

			health = nh;
			if(is_bound())
			{
				lock.unlock();
				role->on_health_change(*role);
				return;
			}
		}
		lock.unlock();
	}

	virtual ~device() {}

	virtual std::string get_name() 
	{
		lock.lock();
		const std::string r(name);
		lock.unlock();
		return r;
	}

	virtual net::ipv4_address get_ip()
	{
		lock.lock();
		const net::ipv4_address r(ip);
		lock.unlock();
		return r;
	}

	virtual void report_call(wicp::call_report_type r)
	{ TEnv::report_call(serial,r); }

	virtual uint8_t get_health()
	{
		lock.lock();
		const uint8_t r(health);
		lock.unlock();
		return r;
	}
};

}
#endif
