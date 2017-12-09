#ifndef REMOTE_TIMER_H
# define REMOTE_TIMER_H
namespace wic {

template<typename TConfig>
class remote_timer
{
	typedef typename property_config_base::cfg_clock clock;

	struct prop_value_config : public property_config_base
	{
		typedef uint64_t cfg_value_type;

		static const uint32_t cfg_class_id = TConfig::cfg_class_id;

		static const uint32_t cfg_member_id = TConfig::cfg_member_id;

		static const uint32_t cfg_cooldown_time = 0;

		static const bool cfg_commit_change_only = true;
	};
	typedef wicp::remote_property<prop_value_config> prop_value;

	struct prop_running_config : public property_config_base
	{
		typedef bool cfg_value_type;

		static const uint32_t cfg_class_id = TConfig::cfg_class_id;

		static const uint32_t cfg_member_id = TConfig::cfg_member_id+1;

		static const uint32_t cfg_cooldown_time = 0;

		static const bool cfg_commit_change_only = true;
	};
	typedef wicp::remote_property<prop_running_config> prop_running;

public:
	static const uint32_t interval = TConfig::cfg_interval;

	static void init(net::ipv4_address ip)
	{
		prop_value::init(ip);
		prop_running::init(ip);
	}

	static void uninit()
	{
		prop_running::uninit();
		prop_value::uninit();
	}

	static uint64_t value()
	{ return prop_value::value(); }

	static void value(uint64_t v)
	{ prop_value::value(v); }

	static bool running()
	{ return prop_running::value(); }

	static void running(bool v)
	{ prop_running::value(v); }

	static void start()
	{ running(true); }

	static void stop()
	{ running(false); }
	
	constexpr static sched::listener  &on_value_change = prop_value::on_change;

	constexpr static sched::listener  &on_running_change = prop_running::on_change;
};

}
#endif
