#ifndef PERIPHERAL_PIN_PAD_H
# define PERIPHERAL_PIN_PAD_H
# include <wicp/remote_property.h>
# include <wicp/forward_property.h>
# include <type_traits>
# include <entity.h>
namespace peripheral
{
	template<typename TConfig>
	struct pin_pad : wic::entity
	{
		typedef TConfig config;

		struct value_type
		{
			uint8_t key;
			bool    state;

			constexpr value_type()
				: key(0)
				, state(false)
			{}

			constexpr value_type(uint8_t pkey, bool pstate)
				: key(pkey)
				, state(pstate)
			{}

			constexpr value_type(const value_type &that)
				: key(that.key)
				, state(that.state)
			{}

			bool operator==(const value_type &that)
			{ return that.key == key && that.state == state; }

			bool operator!=(const value_type &that)
			{ return that.key != key || that.state != state; }
		};
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

		static void change_handler()
		{
			const value_type v = property::value();
			std::cout << TConfig::name << ": key " << std::dec << (int)v.key << ' ' << (v.state?"down":"up") << std::endl;
		}

	public:
		static void init(net::ipv4_address ip)
		{
			property::init(ip);
			property::on_change += change_handler;
		}

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
