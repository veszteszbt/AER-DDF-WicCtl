#ifndef DEVICE_ROLE_H
# define DEVICE_ROLE_H
namespace wic {

template<typename TConfig>
class device_role
{
	static wicp::role_type *role;

	struct prop_health_config : public TConfig
	{
		typedef uint8_t cfg_value_type;
		static const uint32_t cfg_member_id = 0xeffffff;
		static const uint32_t cfg_cooldown_time = 1000;
	};
	typedef wicp::local_property<prop_health_config> prop_health;

	static void health_change_handler(wicp::role_type&)
	{ prop_health::value(role->get_health()); }

public:

	static wicp::role_type &instance()
	{
		if(!role)
			init();
		return *role;
	}

	static void init()
	{
		if(role)
			return;
		role = new wicp::role_type(TConfig::cfg_name);
		prop_health::init(role->get_health());
		role->on_health_change += health_change_handler;
	}

	static void uninit()
	{
		if(!role)
			return;
		role->on_health_change -= health_change_handler;
		prop_health::uninit();
		delete role;
		role = 0;
	}

	static uint8_t health()
	{
		if(!role)
			init();
		return prop_health::value();
	}

	static void remote_add(wicp::role_type &role)
	{ prop_health::remote_add(role); }

	static void remote_del(wicp::role_type &role)
	{ prop_health::remote_del(role); }

	constexpr static sched::listener &on_health_change = prop_health::on_change;
};

template<typename c>
wicp::role_type *device_role<c>::role = 0;

}
#endif
