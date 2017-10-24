#ifndef WICP_FORWARD_PROPERTY_H
# define WICP_FORWARD_PROPERTY_H
namespace wicp {

	template<typename TConfig>
	class forward_property
	{
		typedef remote_property<TConfig> property;

		typedef local_property<TConfig> replica;

		static void property_change()
		{ replica::value(property::value()); }

		static void replica_change()
		{ property::value(replica::value()); }

	public:
		typedef typename property::value_type value_type;

		static void init(net::ipv4_address ip)
		{ 
			property::init(ip);
			replica::init(property::value());
			replica::on_change += replica_change;
			property::on_change += property_change;
		}

		static void uninit()
		{
			replica::on_change -= replica_change;
			property::on_change -= property_change;
			replica::uninit();
			property::uninit();
		}

		static value_type value()
		{ return property::value(); }

		static void value(value_type v)
		{ property::value(v); }

		static bool remote_add(net::ipv4_address ip)
		{ replica::remote_add(ip); }

		static bool remote_del(net::ipv4_address ip)
		{ replica::remote_del(ip); }

		static uint32_t failures()
		{ return property::failures(); }

		constexpr static sched::listener &on_change = property::on_change;
	};
}
#endif
