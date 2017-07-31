#ifndef PERIPHERAL_TEXT_DISPLAY_H
# define PERIPHERAL_TEXT_DISPLAY_H
namespace peripheral
{
	template<typename TConfig>
	struct text_display
	{
		struct value_type
		{
			char data[32];

			value_type() {}

			value_type(const char *x)
			{
				for(int i = 0; i < 32; ++i)
					data[i] = x[i];
				
			}

			value_type &operator=(const char *x)
			{
				for(int i = 0; i < 32; ++i)
					data[i] = x[i];

				return *this;
			}

			value_type &operator=(const value_type &x)
			{
				for(int i = 0; i < 32; ++i)
					data[i] = x.data[i];

				return *this;
			}

			bool operator==(const value_type &x) const
			{
				for(int i = 0; i < 32; ++i)
					if(data[i] != x.data[i])
						return false;

				return true;
			}

			bool operator!=(const value_type &x) const
			{
				for(int i = 0; i < 32; ++i)
					if(data[i] != x.data[i])
						return true;

				return false;
			}
		};
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
		{
			property::init(ip);
		}

		static value_type value()
		{ return property::value(); }

		static void value(value_type v)
		{ property::value(); }

		static void uninit()
		{
		
		}

	};
}
#endif
