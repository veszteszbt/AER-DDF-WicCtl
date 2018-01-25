#ifndef PROPERTY_ROOM_H
# define PROPERTY_ROOM_H

template<typename TConfig>
class property_room
{
	typedef wicp::local_property<TConfig> property;

	static void property_change_handler()
	{
		journal(journal::trace,"wic.property.room") <<
			TConfig::name << ": value changed to " <<
			'"' << std::dec << property::value() << '"' << journal::end;
	}

public:
	typedef TConfig config;

	typedef typename property::value_type value_type;

	static void init(value_type v = value_type())
	{
		property::init(v);
		property::on_change += property_change_handler;
	}

	static void uninit()
	{ property::uninit(); }

	static value_type value()
	{ return property::value(); }

	static void value(value_type v)
	{ property::value(v); }

	static value_type default_value()
	{ return property::default_value(); }

	static void remote_add(wicp::role_type &role)
	{ property::remote_add(role); }

	static void remote_del(wicp::role_type &role)
	{ property::remote_del(role); }

	constexpr static sched::listener &on_change = property::on_change;
};
#endif
