#ifndef REMOTE_DEVICE_ROLE_H
# define REMOTE_DEVICE_ROLE_H
namespace wic {

template<typename TConfig>
class remote_device_role
{
	struct prop_health_config : public TConfig
	{
		typedef uint8_t cfg_value_type;
		static const uint32_t cfg_member_id = 0xeffffff;
	};
	typedef wicp::remote_property<prop_health_config> prop_health;
public:
	static void init(wicp::role_type &prole)
	{ prop_health::init(prole,0); }

	static void uninit()
	{ prop_health::uninit(); }

	static uint8_t health()
	{ return prop_health::value(); }

	constexpr static sched::listener &on_health_change = prop_health::on_change;
};

}
#endif
