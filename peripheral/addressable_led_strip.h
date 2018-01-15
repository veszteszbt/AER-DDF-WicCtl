#ifndef PERIPHERAL_ADDRESSABLE_LED_STRIP
# include <wicp/remote_property.h>
# include <wicp/forward_property.h>
# include <type_traits>
# include <entity.h>
namespace peripheral
{
	template<typename TConfig>
	struct addressable_led_strip: wic::entity
	{
		typedef TConfig config;

		static const uint8_t led_count = TConfig::cfg_led_count;

		struct color_type
		{
			uint8_t red;
			uint8_t green;
			uint8_t blue;

			constexpr bool operator==(const color_type &t) const
			{ return red == t.red && green == t.green && blue == t.blue; }

			constexpr bool operator!=(const color_type &t) const
			{ return red != t.red || green != t.green || blue != t.blue; }
		};

		struct value_type
		{
			typedef addressable_led_strip<TConfig> parent;

			static const uint8_t size = led_count;

			color_type led[led_count];

			constexpr bool operator==(const value_type &t) const
			{
				for(int i = 0; i < led_count; ++i)
					if(t.led[i] != led[i])
						return false;
				return true;
			}

			constexpr bool operator!=(const value_type &t) const
			{
				for(int i = 0; i < led_count; ++i)
					if(t.led[i] != led[i])
						return true;
				return false;
			}
		};

	private:

		struct prop_value_config : public TConfig
		{
			typedef value_type cfg_value_type;

			static const bool cfg_commit_change_only = true;

			static const bool cfg_read = true;

			static const bool cfg_write = true;

			static const uint32_t cfg_cooldown_time = TConfig::cfg_cooldown_time;
		};
		typedef std::conditional_t<
			TConfig::cfg_replicate_locally,
			wicp::forward_property<prop_value_config>,
			wicp::remote_property<prop_value_config>
		> prop_value;

		struct prop_enabled_config : public TConfig
		{
			typedef bool cfg_value_type;

			static const uint32_t cfg_member_id = TConfig::cfg_member_id+1;

			static const bool cfg_commit_change_only = true;

			static const bool cfg_read = true;

			static const bool cfg_write = true;

			static const uint32_t cfg_cooldown_time = TConfig::cfg_cooldown_time;
		};
		typedef std::conditional_t<
			TConfig::cfg_replicate_locally,
			wicp::forward_property<prop_enabled_config>,
			wicp::remote_property<prop_enabled_config>
		> prop_enabled;


	public:
		static void init(wicp::role_type &role)
		{
			prop_value::init(role);
			prop_enabled::init(role);
		}

		static void uninit()
		{
			prop_value::uninit();
			prop_enabled::uninit();
		}

		static void remote_add(wicp::role_type &role)
		{
			prop_value::remote_add(role);
			prop_enabled::remote_add(role);
		}

		static void remote_del(wicp::role_type &role)
		{
			prop_value::remote_del(role);
			prop_enabled::remote_del(role);
		}

		typedef expose_property<prop_value> value;

		typedef expose_property<prop_enabled> enabled;
	};
}

template<typename Tv, typename Tctrt1 = decltype(Tv::parent::led_count)>
std::istream &operator>>(std::istream &is, Tv &out)
{
	Tv v;
	for(int i = 0; i < Tv::size; ++i)
	{
		char hash;
		is >> hash;
		if(hash != '#')
		{
			is.setstate(std::ios::failbit);
			return is;
		}
		uint32_t value;
		is >> std::hex >> value;
		if(is.fail())
			return is;

		if(value > 16777215)
		{
			is.setstate(std::ios::failbit);
			return is;
		}
		const int x = is.peek();
		if(x >= 0 && (isalnum(x) || (i != Tv::size -1 && (x==10 || x==13))))
		{
			is.setstate(std::ios::failbit);
			return is;
		}

		v.led[i].red = (value>>16)&0xff;
		v.led[i].green = (value>>8)&0xff;
		v.led[i].blue = value&0xff;
	}
	out = v;
	return is;
}

template<typename Tv, typename Tctrt1 = decltype(Tv::parent::led_count)>
std::ostream &operator<<(std::ostream &os, const Tv &v)
{
	for(int i = 0; i < Tv::size; ++i)
	{
		os << std::hex << '#' <<
		(int)v.led[i].red <<
		(int)v.led[i].green <<
		(int)v.led[i].blue << ' ';
	}
	return os;
}
#endif
