#ifndef PERIPHERAL_PWM_ADJUSTER_H
# define PERIPHERAL_PWM_ADJUSTER_H
namespace peripheral
{
	template<typename TConfig>
	struct pwm_adjuster
	{
		typedef uint16_t value_type;
	private:
		struct property_config : public TConfig
		{
			typedef value_type cfg_value_type;

			static const bool cfg_commit_change_only = true;

			static const bool cfg_read = true;

			static const bool cfg_write = false;
		
		};
		typedef wicp::remote_property<property_config> property;


	public:
		static void init(net::ipv4_address ip)
		{ property::init(ip); }

		static void uninit()
		{ property::uninit(); }

		static value_type value()
		{ return property::value(); }

		constexpr static listener_t &on_change = property::on_change;
	};
}
#endif
