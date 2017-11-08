#ifndef PERIPHERAL_GPIO_INPUT_H
# define PERIPHERAL_GPIO_INPUT_H
# include <wicp/remote_property.h>
# include <wicp/forward_property.h>
# include <type_traits>
# include <entity.h>
namespace peripheral {

template<typename TConfig>
struct gpio_input : wic::entity
{
	typedef TConfig config;

	typedef bool value_type;

private:
	struct property_config : public TConfig
	{
		typedef value_type cfg_value_type;

		static const bool cfg_commit_change_only = true;

		static const bool cfg_read = true;

		static const bool cfg_write = false;
	
	};
	typedef std::conditional_t<
		TConfig::cfg_replicate_locally,
		wicp::forward_property<property_config>,
		wicp::remote_property<property_config>
	> property;


public:
	static void init(net::ipv4_address ip)
	{ property::init(ip); }

	static void uninit()
	{ property::uninit(); }

	static void remote_add(net::ipv4_address ip)
	{ property::remote_add(ip); }

	static void remote_del(net::ipv4_address ip)
	{ property::remote_del(ip); }

	typedef expose_property<property,false> value;
};

}
#endif
