#ifndef PERIPHERAL_RESISTOR_SEQUENCE_H
# define PERIPHERAL_RESISTOR_SEQUENCE_H
namespace peripheral
{
	template<typename TConfig>
	class resistor_sequence
	{
		struct property_config : public TConfig
		{
			static const bool cfg_commit_change_only = true;

			static const bool cfg_read = true;

			static const bool cfg_write = false;
		
		};
		typedef wicp::remote_property<property_config> property;

	public:
		typedef typename TConfig::cfg_value_type value_type;

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
