#ifndef PERIPHERAL_GPIO_OUTPUT_H
# define PERIPHERAL_GPIO_OUTPUT_H
# include <wicp/remote_property.h>
# include <wicp/forward_property.h>
# include <type_traits>
namespace peripheral
{
	template<typename TConfig>
	struct gpio_output
	{
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


	public:
		static void init(net::ipv4_address ip)
		{ property::init(ip); }

		static void uninit()
		{ property::uninit(); }

		static value_type value()
		{ return property::value(); }

		static void value(value_type v)
		{ property::value(v); }

		static void remote_add(net::ipv4_address ip)
		{ property::remote_add(ip); }

		static void remote_del(net::ipv4_address ip)
		{ property::remote_del(ip); }
	};
}
#endif
