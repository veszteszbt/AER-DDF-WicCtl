#ifndef WIC_EVENT_H
# define WIC_EVENT_H
# include <chrono>
# include <sched/listener.h>
# include <oosp/local_property.h>
namespace wic {

template<typename TConfig>
class event
{
		struct property_config : public property_config_base
		{
			typedef uint64_t cfg_value_type;

			static const uint32_t cfg_class_id = TConfig::cfg_class_id;

			static const uint32_t cfg_member_id = TConfig::cfg_member_id;

			static const uint32_t cfg_cooldown_time = 0;

			static const bool cfg_commit_change_only = true;
		};
		typedef oosp::local_property<property_config> property;
public:
	static void init()
	{ property::init(); }

	static void uninit()
	{ property::uninit(); }

	static void monitor()
	{
		if(TConfig::cfg_condition())
		{
			journal(journal::trace,"wic.event") << TConfig::name << " triggered" << journal::end;
			property::value(std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count());
			TConfig::cfg_action();
		}
	}
	static void remote_add(oosp::role_type &role)
	{ property::remote_add(role); }

	constexpr static sched::listener &on_raised = property::on_change;
};

}
#endif
