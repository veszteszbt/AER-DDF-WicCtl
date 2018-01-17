#ifndef DEVMAN_DEVMAN_H
# define DEVMAN_DEVMAN_H
# include <devman/types.h>
# include <devman/device.h>
# include <devman/process/binder.h>
# include <devman/process/expiry.h>
# include <devman/process/report.h>
namespace devman {

template<typename TConfig>
class devman
{

	struct env_device
	{
		typedef typename TConfig::cfg_earpc rpc;

		typedef std::chrono::high_resolution_clock clock;

		typedef typename clock::time_point time_point;

		static std::mutex devices_lock;

		static std::mutex roles_lock;

		static const uint32_t expiry_timeout = TConfig::cfg_expiry_timeout;

		static void report_call(uint64_t,wicp::call_report_type);
	};

	struct env_base : public env_device
	{
		typedef device<env_device>      device_type;

		typedef wicp::role_type         role_type;

		typedef std::list<device_type*> devices_type;

		typedef std::list<role_type*>   roles_type;

		static devices_type devices;

		static roles_type   roles;
	};


	struct env_expiry : public env_base
	{
		typedef typename process::binder<env_base> proc_binder;
	};

	typedef typename process::expiry<env_expiry> proc_expiry;

	typedef typename process::report<env_expiry> proc_report;

	typedef typename env_expiry::proc_binder     proc_binder;

	typedef typename env_base::devices_type      devices_type;

	typedef typename env_base::roles_type        roles_type;

	typedef typename env_base::device_type       device_type;

	typedef typename env_base::role_type         role_type;

	typedef typename env_base::clock             clock;

	typedef typename env_base::rpc               rpc;

	typedef typename rpc::call_id_type           call_id_type;


	typedef typename rpc::template incoming_call_handle<bool,types::heartbeat_payload_type> heartbeat_call_handle_type;

	constexpr static devices_type &devices = env_base::devices;

	constexpr static roles_type &roles = env_base::roles;

	constexpr static std::mutex &devices_lock = env_device::devices_lock;

	constexpr static std::mutex &roles_lock = env_device::roles_lock;

	static const uint32_t expiry_timeout = env_base::expiry_timeout;

	static device_type *dev_by_serial(uint64_t serial)
	{
		for(auto dev : devices)
			if(dev->serial == serial)
				return dev;
		return 0;
	}

	static device_type *dev_by_ip(net::ipv4_address ip)
	{
		for(auto dev : devices)
			if(dev->ip == ip)
				return dev;
		return 0;
	}

	static device_type *dev_by_cid(call_id_type cid)
	{
		for(auto dev : devices)
			if(dev->call_id == cid)
				return dev;
		return 0;
	}

	static void app_name_handler(typename device_type::arctl_type::template get_handle<std::string> h)
	{
		devices_lock.lock();
		device_type *dev = dev_by_cid(h.call_id);
		if(dev)
		{
			if(dev->state == types::state::identify)
			{
				dev->call_id = 0;
				if(h.reason == earpc::reason::success)
				{

					std::string name = h.value();
					while(name.size() && !name.back())
						name.resize(name.size()-1);

					dev->lock.lock();
					dev->ip = h.ip;
					dev->name = name;
					dev->lock.unlock();

					journal(journal::debug,"devman.device") <<
						"device: " << std::hex << dev->serial <<
						"; address: " << (std::string)dev->ip <<
						"; app: " << dev->name << 
						"; activating device" << 
						journal::end;

					dev->state = types::state::active;
					proc_binder::notify();
				}

				else if(h.reason != earpc::reason::cancelled)
				{
					journal(journal::error,"devman.device") <<
						"device: " << std::hex << dev->serial <<
						"; address: " << (std::string)dev->ip <<
						"; failed to obtain app name; resetting to unseen state" <<
						journal::end;

					dev->set_unseen();
				}
			}
		}
		else
			journal(journal::critical,"devman.device") <<
				"address: " << (std::string)h.ip <<
				"; could not find device for finished app_name call" <<
				journal::end;
				
		devices_lock.unlock();
	}

	static void heartbeat_process_state(device_type *dev)
	{
		switch(dev->state)
		{
			case types::state::unseen:
				journal(journal::trace,"devman.device") <<
					"device: " << std::hex << dev->serial <<
					"; address: " << (std::string)dev->ip <<
					"; setting device to identify state" <<
					journal::end;

				dev->set_identify();
				dev->call_id = dev->ctl->app_name(app_name_handler);
				break;
		}
	}

	static void heartbeat_handler(heartbeat_call_handle_type h)
	{
		if(h.reason != ::earpc::reason::process)
			return;

		h.respond(true);

		const types::heartbeat_payload_type v = h.value();

		roles_lock.lock();
		devices_lock.lock();
		device_type *r = dev_by_serial(v.serial);
		device_type *o = dev_by_ip(h.ip);

		if(o)
		{
			if(o != r)
			{
				journal(journal::critical,"devman.heartbeat") << "ip collision: " << (std::string)h.ip <<
					" bound to two devices: " << std::hex << v.serial << " and " << o->serial <<
					"; resetting both to unseen state" <<
					journal::end;
				r->set_unseen();
				o->set_unseen();
				if(r->call_id)
					rpc::cancel(r->call_id);
				if(o->call_id)
					rpc::cancel(r->call_id);
				devices_lock.unlock();
				roles_lock.unlock();
				proc_binder::notify();
				return;
			}

			else
			{
				const auto d = clock::now()-r->last_heartbeat-std::chrono::seconds(1);
				r->heartbeat_deviance = ::types::time::msec(d);
				journal(journal::trace,"devman.heartbeat") << (std::string)h.ip <<
					" -> " << (std::string)v <<
					"; deviance is " << ::types::time::fmsec(d) << " msec" <<
					journal::end;
				r->calculate_health();
				heartbeat_process_state(r);
			}
		}	

		else if(r)
		{
			journal(journal::trace,"devman.heartbeat") << "ip change on device " << r->serial <<
				"; old address: " << (std::string)r->ip <<
				"; new address: " << (std::string)h.ip <<
				"; rebinding" << 
				journal::end;
			r->lock.lock();
			r->ip = h.ip;
			r->lock.unlock();
			if(r->is_bound())
			{
				role_type *role = r->role;
				r->unbind();
				r->bind(role);
			}
		}

		else
		{
			journal(journal::trace,"devman.heartbeat") << (std::string)h.ip <<
				" -> " << (std::string)v << "; creating instance" <<
				journal::end;

			devices.push_back(new device_type(v.serial,h.ip));
			
			r = devices.back();
			heartbeat_process_state(r);
			proc_expiry::notify();
		}

		r->last_heartbeat = clock::now();
		r->expiry = clock::now()+std::chrono::milliseconds(static_cast<uint32_t>(expiry_timeout));

		devices_lock.unlock();
		roles_lock.unlock();
	}

public:

	static void init()
	{
		proc_binder::init();
		proc_expiry::init();
		proc_report::init();
		rpc::set_command(
			0xffffffff0ffff000,
			heartbeat_handler
		);

	}

	static void uninit()
	{
		rpc::clear_command(0xffffffff0ffff000);
		proc_report::uninit();
		proc_expiry::uninit();
		proc_binder::uninit();
	}

	static bool add_role(wicp::role_type &r)
	{
		roles_lock.lock();
		for(auto i : roles)
			if(i == &r)
			{
				roles_lock.unlock();
				return false;
			}

		roles.push_back(&r);
		roles_lock.unlock();
		proc_binder::notify();
		return true;
	}

	template<typename TRole>
	static void add_role()
	{
		for(uint16_t i = 0; i < TRole::multiplicity; ++i)
			add_role(TRole::instance(i));

	}
};


template<typename e>
void devman<e>::env_device::report_call(uint64_t serial, wicp::call_report_type r)
{ proc_report::notify(serial,r); }

template<typename e>
std::mutex devman<e>::env_device::devices_lock;

template<typename e>
std::mutex devman<e>::env_device::roles_lock;

template<typename e>
typename devman<e>::env_base::devices_type devman<e>::env_base::devices;

template<typename e>
typename devman<e>::env_base::roles_type devman<e>::env_base::roles;

}
#endif
