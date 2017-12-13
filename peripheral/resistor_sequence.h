#ifndef PERIPHERAL_RESISTOR_SEQUENCE_H
# define PERIPHERAL_RESISTOR_SEQUENCE_H
# include <wicp/remote_property.h>
# include <wicp/forward_property.h>
# include <type_traits>
# include <entity.h>
namespace peripheral
{
	template<typename TConfig>
	class resistor_sequence : wic::entity
	{
		struct property_config : public TConfig
		{
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
		typedef TConfig config;

		typedef typename TConfig::cfg_value_type value_type;

		static void init(wicp::role_type &role)
		{ property::init(role); }

		static void uninit()
		{ property::uninit(); }

		static void remote_add(wicp::role_type &role)
		{ property::remote_add(role); }

		static void remote_del(wicp::role_type &role)
		{ property::remote_del(role); }

		typedef expose_property<property,false> value;

	};
}
#endif
