#ifndef PERIPHERAL_GPIO_OUTPUT_H
# define PERIPHERAL_GPIO_OUTPUT_H
# include <wicp/remote_property.h>
# include <wicp/forward_property.h>
# include <type_traits>
# include <entity.h>
namespace peripheral {

template<typename TConfig>
struct gpio_output : wic::entity
{
	typedef TConfig config;

	typedef bool value_type;
private:

	struct property_config : public TConfig
	{
		typedef value_type cfg_value_type;

		static const bool cfg_commit_change_only = true;

		static const bool cfg_read = true;

		static const bool cfg_write = true;
	
	};
	typedef std::conditional_t<
		TConfig::cfg_replicate_locally,
		wicp::forward_property<property_config>,
		wicp::remote_property<property_config>
	> property;

	static void property_change_handler()
	{
		journal(journal::trace,"wic.peripheral.output") <<
			TConfig::name << ": value changed to " <<
			property::value() << journal::end;
	}

public:
	static void init(wicp::role_type &role)
	{
		property::init(role);
		property::on_change += property_change_handler;
	}

	static void uninit()
	{ property::uninit(); }

	static void remote_add(wicp::role_type &role)
	{ property::remote_add(role); }

	static void remote_del(wicp::role_type &role)
	{ property::remote_del(role); }

	typedef expose_property<property> value;
};

}
#endif
