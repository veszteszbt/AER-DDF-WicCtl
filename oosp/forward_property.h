#ifndef OOSP_FORWARD_PROPERTY_H
# define OOSP_FORWARD_PROPERTY_H
namespace oosp {

	template<typename TConfig>
	class forward_property
	{
		struct property_config : TConfig {};
		typedef remote_property<property_config> property;

		struct replica_config : TConfig {};
		typedef local_property<replica_config> replica;

		static journal jrn(uint8_t level)
		{
			return journal(level,"oosp.property.forward") << "property: " << std::hex <<
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
		typedef TConfig config;

		typedef typename property::value_type value_type;

		static void init(oosp::role_type &role, value_type v = value_type())
		{
			property::init(role,v);
			replica::init(v);
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

		static bool remote_add(oosp::role_type &role)
		{ replica::remote_add(role); }

		static bool remote_del(oosp::role_type &role)
		{ replica::remote_del(role); }

		static uint32_t failures()
		{ return property::failures(); }

		constexpr static sched::listener &on_change = property::on_change;
	};
}
#endif
