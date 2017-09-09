#ifndef DEVICE_STATE_H
# define DEVICE_STATE_H
# include <net/mac_address.h>
# include <net/ipv4_address.h>
# include <ctime>

template<typename TConfig>
class device_state
{

	static std::string timestamp()
	{
		time_t now;
    		time(&now);
		char buf[64];
		strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
	    	return std::string(buf);
	}

	typedef typename TConfig::cfg_earpc rpc;

	static std::mutex lock;

	struct stat_record
	{
		volatile uint32_t last_heartbeat_num;

		uint64_t serial;

		net::ipv4_address ip;

		stat_record()
			: last_heartbeat_num(0)
		{}

		stat_record(const stat_record &t)
			: last_heartbeat_num(t.last_heartbeat_num)
		{}

		void heartbeat(uint32_t heartbeat_num)
		{
			if(
				(last_heartbeat_num + 1 != heartbeat_num) && (
					(last_heartbeat_num != (uint32_t)-1) || 
					heartbeat_num != 0
				)
			)
				if(heartbeat_num == 0)
					std::cout  << " >>> heartbeat warning: possible reboot" << std::endl;
				else
					std::cout << "["<<timestamp()<<"] >>> heartbeat warning: outage; delta is " << std::dec <<
						heartbeat_num-last_heartbeat_num << std::endl;

			last_heartbeat_num = heartbeat_num;
		}

	};

	struct
	__attribute__((packed))
	heartbeat_payload_type
	{
		uint64_t serial;
		uint32_t counter;
	};

	typedef std::map<net::ipv4_address, stat_record*> stat_by_ip_type;

	typedef std::map<uint64_t, stat_record*> stat_by_serial_type;

	static stat_by_ip_type stat_by_ip;

	static stat_by_serial_type stat_by_serial;

	static void app_name_get(net::ipv4_address ip, typename rpc::command_id_type cmd, const std::string &r)
	{
		if(&r)
			std::cout << r << std::endl;
		else
			std::cout << "failed to get app name" << std::endl;
	}

	static void heartbeat_handler(
		typename rpc::template call_handle<bool> h,
		const heartbeat_payload_type *v
	)
	{
		if(!v)
			h.respond(false);
		else
		{
			h.respond(true);
			lock.lock();

			typename stat_by_serial_type::iterator i = stat_by_serial.find(v->serial);
			if(i == stat_by_serial.end())
			{
				stat_record *r = new stat_record();
				r->last_heartbeat_num = v->counter;
				r->serial             = v->serial;
				r->ip                 = h.ip;

				if(stat_by_ip.find(h.ip) != stat_by_ip.end())
				{
					std::cout << " >>> WARNING: ip collision: " << (std::string)h.ip << " bound to two devices: " << 
						std::hex << v->serial << std::endl;
				}

				else
				{
					stat_by_serial[r->serial] = r;
					stat_by_ip[r->ip] = r;
					std::cout << " >>> registered new device " << std::hex << v->serial <<
						" with ip " << (std::string)h.ip << std::endl;

					rpc::call(
						h.ip,
						0xffffffff00001004,//0xffffffff00004003,
						true,
						app_name_get
					);
				}
			}
			else
			{
				if(h.ip != i->second->ip)
				{
					std::cout << " >>> ip change on device " << std::hex << i->second->serial <<
						"; old ip: " << (std::string)i->second->ip << "; new ip: " << 
						(std::string)h.ip << std::endl;

					typename stat_by_ip_type::iterator j = stat_by_ip.find(i->second->ip);
					stat_by_ip.erase(j);
					i->second->ip = h.ip;
					stat_by_ip[h.ip] = i->second;
				}
				i->second->heartbeat(v->counter);
			}

			lock.unlock();
		}
	}
public:
	static void init()
	{
		rpc::set_command(
			0xffffffff0ffff000,
			heartbeat_handler
		);
	}


};

template<typename c>
typename device_state<c>::stat_by_ip_type device_state<c>::stat_by_ip;

template<typename c>
typename device_state<c>::stat_by_serial_type device_state<c>::stat_by_serial;

template<typename c>
std::mutex device_state<c>::lock;
#endif
