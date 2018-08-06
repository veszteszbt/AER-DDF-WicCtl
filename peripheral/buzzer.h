#ifndef PERIPHERAL_BUZZER_H
# define PERIPHERAL_BUZZER_H
# include <oosp/remote_property.h>
# include <oosp/forward_property.h>
# include <type_traits>
# include <entity.h>

struct tone_t
{
	uint16_t freq;
	uint16_t length;

	constexpr tone_t()
		: freq(0)
		, length(0)
	{}

	constexpr tone_t(uint16_t f, uint16_t l)
		: freq(f)
		, length(l)
	{}

	operator uint32_t()
	{ return (static_cast<uint32_t>(freq)<<16)+length; }

	constexpr bool operator==(const tone_t &t)
	{ return t.freq == freq && t.length == length; }

	constexpr bool operator!=(const tone_t &t)
	{ return t.freq != freq || t.length != length; }
};

namespace peripheral
{
	template<typename TConfig>
	struct buzzer : wic::entity
	{
		typedef TConfig config;
		typedef tone_t value_type;
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
			if(v.length || v.freq)
				journal(journal::trace,"wic.peripheral.output") <<
					TConfig::name << ": " << std::dec << (int)v.freq << " Hz for " <<
					(int)v.length << " msec" << journal::end;
			else
				journal(journal::trace,"wic.peripheral.output") <<
					TConfig::name << ": activity finished" << journal::end;
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

		static void beep(uint16_t freq, uint16_t length)
		{ property::value(value_type(freq,length)); }

		typedef expose_property<property> value;

	};
}
#endif
