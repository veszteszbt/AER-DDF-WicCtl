#ifndef PERIPHERAL_GPIO_OUTPUT_H
# define PERIPHERAL_GPIO_OUTPUT_H
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
		typedef wicp::remote_property<property_config> property;


	public:
		static void init(net::ipv4_address ip)
		{ property::init(ip); }

		static void uninit()
		{ property::uninit(); }

		static value_type value()
		{ return property::value(); }

		static void value(value_type v)
		{ property::value(v); }
	};
}
#endif
