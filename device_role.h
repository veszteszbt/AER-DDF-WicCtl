#ifndef DEVICE_ROLE_H
# define DEVICE_ROLE_H
namespace wic {

template<typename TConfig>
class device_role
{
	static_assert(TConfig::cfg_multiplicity > 0, "device multiplicity must be at least 1");

	static wicp::role_type *role[];

	static std::mutex lock;

	static volatile bool initialized;

	struct prop_health_config : public TConfig
	{
		typedef uint8_t cfg_value_type;
		static const uint32_t cfg_member_id = 0xeffffff;
		static const uint32_t cfg_cooldown_time = 1000;
	};
	typedef wicp::local_property<prop_health_config> prop_health;

	static void health_change_handler(wicp::role_type &r)
	{ prop_health::value(r.get_health()); }

public:

	static const uint16_t multiplicity = TConfig::cfg_multiplicity;

	static wicp::role_type &instance(uint16_t i = 0)
	{
		lock.lock();
		if(!initialized)
			init();
		lock.unlock();
		return *role[i];
	}

	static void init()
	{
		if(initialized)
			return;

		for(uint16_t i = 0; i < multiplicity; ++i)
			role[i] = new wicp::role_type(TConfig::cfg_name);

		if(multiplicity == 1)
		{
			prop_health::init(role[0]->get_health());
			role[0]->on_health_change += health_change_handler;
		}
		initialized = true;
	}

	static void uninit()
	{
		lock.lock();
		if(!initialized)
		{
			lock.unlock();
			return;
		}
		lock.unlock();
		if(multiplicity == 1)
			role[0]->on_health_change -= health_change_handler;
		prop_health::uninit();
		for(int i = 0; i < multiplicity; ++i)
			delete role[i];
	}

	static uint8_t health()
	{
		lock.lock();
		if(!initialized)
			init();
		lock.unlock();
		return prop_health::value();
	}

	static void remote_add(wicp::role_type &role)
	{
		if(multiplicity != 1)
			return;

		lock.lock();
		if(!initialized)
			init();

		lock.unlock();
		prop_health::remote_add(role);
	}

	static void remote_del(wicp::role_type &role)
	{
		if(multiplicity != 1)
			return;

		lock.lock();
		if(!initialized)
			init();

		lock.unlock();
		prop_health::remote_del(role);
	}

	constexpr static sched::listener &on_health_change = prop_health::on_change;
};

template<typename c>
wicp::role_type *device_role<c>::role[c::cfg_multiplicity];

template<typename c>
std::mutex device_role<c>::lock;

template<typename c>
volatile bool device_role<c>::initialized = false;

}
#endif
