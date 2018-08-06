#ifndef PROPERTY_EXTERNAL_H
# define PROPERTY_EXTERNAL_H

template<typename TConfig>
class property_external 
{
	typedef std::conditional_t<
		TConfig::cfg_replicate_locally,
		oosp::forward_property<TConfig>,
		oosp::remote_property<TConfig>
	> property;

	static void property_change_handler()
	{
		journal(journal::trace,"wic.property.external") <<
			TConfig::name << ": value changed to " <<
			'"' << std::dec << property::value() << '"' << journal::end;
	}

public:

	typedef TConfig config;

	typedef typename property::value_type value_type;

	static void init(oosp::role_type &role, value_type v = value_type())
	{
		property::init(role,v);
		property::on_change += property_change_handler;
	}

	static void uninit()
	{ property::uninit(); }

	static value_type value()
	{ return property::value(); }

	static void value(value_type v)
	{ property::value(v); }

	static void remote_add(oosp::role_type &role)
	{ property::remote_add(role); }

	static void remote_del(oosp::role_type &role)
	{ property::remote_del(role); }

	constexpr static sched::listener &on_change = property::on_change;
};
#endif
