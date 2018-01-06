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
	};
	typedef wicp::local_property<prop_health_config> prop_health;

	static void health_change_handler(wicp::role_type&)
	{ prop_health::value(role->get_health()); }

public:

	static wicp::role_type &instance()
	{ return *role; }

	static void init()
	{
		role = new wicp::role_type(TConfig::cfg_name);
		prop_health::init(role->get_health());
		role->on_health_changed += health_change_handler;
	}

	static void uninit()
	{
		role->on_health_changed -= health_change_handler;
		prop_health::uninit();
		delete role;
		role = 0;
	}

	static uint8_t health()
	{ return prop_health::value(); }

	constexpr static sched::listener &on_health_change = prop_health::on_change;
};

template<typename c>
wicp::role_type *device_role<c>::role = 0;

}
#endif
