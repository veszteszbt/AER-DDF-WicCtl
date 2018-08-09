#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <cstdint>
#include <earpc/udp.h>
#include <earpc/earpc.h>
#include <net/algorithm.h>
#include <net/ipv4_address.h>
#include <oosp/local_property.h>
#include <oosp/remote_property.h>
#include <oosp/forward_property.h>
#include <oosp/oosp_class.h>
#include <oosp/types/property_record.h>
#include <oosp/types/property.h>
#include <property_config_base.h>
#include <device_role.h>
#include <devman/devman.h>

#include <status.h>
#include <event.h>
#include <journal.h>

#include <property_room.h>
#include <property_external.h>
#include <peripheral/addressable_led_strip.h>
#include <peripheral/button.h>
#include <peripheral/buzzer.h>
#include <peripheral/dimmable_led_strip.h>
#include <peripheral/ir_sensor.h>
#include <peripheral/knock_sensor.h>
#include <peripheral/laser_sensor.h>
#include <peripheral/led_strip.h>
#include <peripheral/magnetic_lock.h>
#include <peripheral/magnetic_sensor.h>
#include <peripheral/pin_pad.h>
#include <peripheral/polarity_sensor.h>
#include <peripheral/potentiometer.h>
#include <peripheral/power_switch.h>
#include <peripheral/rfid.h>
#include <peripheral/text_display.h>

typedef earpc::earpc<earpc::config<uint64_t,uint32_t,sport,dport>> rpc;

template <typename TobjId, typename Tvalue>
struct property_data_type
{
	typedef TobjId object_id_type;
	typedef Tvalue value_type;

	object_id_type object_id;
	value_type value;

	property_data_type() = default;

	property_data_type(
		object_id_type pobject_id,
		const value_type &pvalue 
	) 
		: object_id(pobject_id)
		, value(pvalue)
	{}

	bool operator==(const property_data_type &that) const
	{ return std::tie(object_id, value) == std::tie(that.object_id, that.value); }
};

template <int N>
struct Int : public oosp::types::property_record<uint32_t, uint64_t, uint8_t>
{
	static const int result = N;
};

struct wic_class_config : public property_config_base
{
	constexpr static const char *cfg_name = "TestClass";

	static const uint32_t cfg_class_id = 0x100030;

	typedef rpc cfg_earpc;
};

template <uint32_t c>
struct ic
{
	typedef std::integral_constant<uint32_t, c> type;
};

template <uint32_t c>
using ic_t = typename::ic<c>::type;

typedef oosp::oosp_class<
	wic_class_config,
	oosp::types::Property<1, true, uint8_t, 1000, 16>
> oosp_class;	

typedef oosp_class::template get_local<ic_t<1>> local_property;

typedef oosp_class::template get_remote<ic_t<1>> remote_property;

static void l_change_handler(uint64_t object_id)
{
	const auto value = int(local_property::value(object_id));
	std::stringstream ss;
	ss << "change_handler; local object: " << std::hex << object_id << "; value: " << std::dec << value;
	std::cout << ss.str() << std::endl;
	journal(journal::trace, "test.local") << ss.str() << journal::end;

	local_property::value(0x68, local_property::value(0x68) + 1);
}

static void r_change_handler(uint64_t object_id)
{
	const auto value = int(remote_property::value(object_id));
	std::stringstream ss;
	ss << "change_hangler; remote object: " << std::hex << object_id << "; value: " << std::dec << value;
	std::cout << ss.str() << std::endl;
	journal(journal::trace, "test.local") << ss.str() << journal::end;

	remote_property::value(0x69, remote_property::value(0x69) + 1);
}

static void l_change_handler_echo(uint64_t object_id)
{
	auto value = int(local_property::value(object_id));
	std::stringstream ss;
	ss << "echo; local object: " << std::hex << object_id << "; value: " << std::dec << value;
	std::cout << ss.str() << std::endl;
	journal(journal::trace, "faszlo_echo") << ss.str() << journal::end;
}

static void r_change_handler_echo(uint64_t object_id)
{
	auto value = int(remote_property::value(object_id));
	std::stringstream ss;
	ss << "echo; remote object: " << std::hex << object_id << "; value: " << std::dec << value;
	std::cout << ss.str() << std::endl;
	journal(journal::trace, "faszlo_echo") << ss.str() << journal::end;
}

int main() 
{ 
	journal::min_level = 255;
	journal::init(fname);
	rpc::init();

	oosp_class::init();

	using namespace std::literals::chrono_literals;
	if(sport == 1234)
	{
		oosp_class::set_remote(0x70, {127,0,0,1});

		oosp_class::set_local(0x68);
			local_property::subscribe_to_change(0x68, l_change_handler_echo);
			oosp_class::remote_add(0x68, 0x70);

		oosp_class::set_local(0x69);
			local_property::subscribe_to_change(0x69, l_change_handler);
			oosp_class::remote_add(0x69, 0x70);
	}
	else
	{
		oosp_class::set_local(0x70);

		oosp_class::set_remote(0x68, {127,0,0,1});
			remote_property::subscribe_to_change(0x68, r_change_handler);

		oosp_class::set_remote(0x69, {127,0,0,1});
			remote_property::subscribe_to_change(0x69, r_change_handler_echo);
	}
	while(1)
	{
		std::string x ;
		std::cin >> x;
		if(x == "print")
		{
			if(sport == 1234)
			{
				std::cout << std::hex << "object: 68; value: " << std::dec << int(local_property::value(0x68)) << std::endl;	
				std::cout << std::hex << "object: 69; value: " << std::dec << int(local_property::value(0x69)) << std::endl;
			}
			else
			{
				std::cout << std::hex << "object: 68; value: " << std::dec << int(remote_property::value(0x68)) << std::endl;	
				std::cout << std::hex << "object: 69; value: " << std::dec << int(remote_property::value(0x69)) << std::endl;
			}
		}
		else if(sport == 11234)
			local_property::value(0x68, remote_property::value(0x68) + 1);	
		else 
			remote_property::value(0x68, remote_property::value(0x68) + 1);	
	}

}
