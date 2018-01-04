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

	time_point        expiry;

	call_id_type      call_id;

	arctl_type       *ctl;


	device(uint64_t pserial,net::ipv4_address pip)
		: serial(pserial)
		, role(0)
		, state(types::state::unseen)
		, expiry(clock::now()+std::chrono::milliseconds(static_cast<uint32_t>(TEnv::expiry_timeout)))
		, call_id(0)
		, ctl(0)
		, ip(pip)
	{}

	bool is_active()
	{ return state >= types::state::active; }

	bool is_bound()
	{ return role; }

	void bind(wicp::role_type *prole)
	{
		role = prole;
		role->bind(*this);
	}

	void unbind()
	{
		if(role)
		{
			role = 0;
			role->unbind();
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
};

}
#endif
