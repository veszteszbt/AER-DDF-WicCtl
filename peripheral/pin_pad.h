#ifndef PERIPHERAL_PIN_PAD_H
# define PERIPHERAL_PIN_PAD_H
# include <oosp/remote_property.h>
# include <oosp/forward_property.h>
# include <type_traits>
# include <entity.h>

struct keystroke_t
{
	uint8_t key;
	bool    state;

	constexpr keystroke_t()
		: key(0)
		, state(false)
	{}

	constexpr keystroke_t(uint8_t pkey, bool pstate)
		: key(pkey)
		, state(pstate)
	{}

	constexpr keystroke_t(const keystroke_t &that)
		: key(that.key)
		, state(that.state)
	{}

	explicit operator uint16_t()
	{ return (uint16_t)key+(state?0x100:0); }

	bool operator==(const keystroke_t &that)
	{ return that.key == key && that.state == state; }

	bool operator!=(const keystroke_t &that)
	{ return that.key != key || that.state != state; }
};

namespace peripheral
{
	template<typename TConfig>
	struct pin_pad : wic::entity
	{
		typedef TConfig config;
		typedef keystroke_t value_type;
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
			oosp::forward_property<property_config>,
			oosp::remote_property<property_config>
		> property;

		static void change_handler()
		{
			const value_type v = property::value();
			journal(journal::trace,"wic.peripheral.input") <<
				TConfig::name << ": key " << std::dec << (int)v.key <<
				' ' << (v.state?"down":"up") << journal::end;
		}

	public:
		static void init(oosp::role_type &role)
		{
			property::init(role);
			property::on_change += change_handler;
		}

		static void uninit()
		{ property::uninit(); }

		static void remote_add(oosp::role_type &role)
		{ property::remote_add(role); }

		static void remote_del(oosp::role_type &role)
		{ property::remote_del(role); }

		typedef expose_property<property,false> value;

	};
}
#endif
