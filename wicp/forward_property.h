#ifndef WICP_FORWARD_PROPERTY_H
# define WICP_FORWARD_PROPERTY_H
namespace wicp {

	template<typename TConfig>
	class forward_property
	{
		struct property_config : TConfig {};
		typedef remote_property<property_config> property;

		struct replica_config : TConfig {};
		typedef local_property<replica_config> replica;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.property.forward") << "property: " << std::hex <<
				TConfig::cfg_class_id << "::" << TConfig::cfg_member_id << ' ';
		}


		static void property_change()
		{
			jrn(journal::trace) << "change on original property" << journal::end;
			replica::value(property::value());
		}

		static void replica_change()
		{
			jrn(journal::trace) << "change on replicated property" << journal::end;
			property::value(replica::value());
		}

	public:
		typedef typename property::value_type value_type;

		static void init(net::ipv4_address ip)
		{
			property::init(ip);
			replica::init(property::value());
			replica::on_change += replica_change;
			property::on_change += property_change;
			jrn(journal::debug) << "initialized" << journal::end;
		}

		static void uninit()
		{
			replica::on_change -= replica_change;
			property::on_change -= property_change;
			replica::uninit();
			property::uninit();
			jrn(journal::debug) << "uninitialized" << journal::end;
		}

		static value_type value()
		{ return property::value(); }

		static void value(value_type v)
		{
			jrn(journal::trace) << "set from API" << journal::end;
			property::value(v);
		}

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
