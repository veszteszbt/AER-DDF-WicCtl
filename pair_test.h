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
#include <wicp/local_property.h>
#include <wicp/remote_property.h>
#include <wicp/forward_property.h>
#include <wicp/wic_class.h>
#include <wicp/types/property_record.h>
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
struct Int : public wicp::types::property_record_base<uint32_t, uint64_t, uint8_t>
{
	static const int result = N;
};

struct TestConfig
{
	constexpr static const char               *cfg_name = "TestClass";

	typedef std::chrono::high_resolution_clock cfg_clock;

	typedef uint32_t                           cfg_class_id_type;
                                              
	typedef uint32_t                           cfg_member_id_type;
                                              
	typedef uint64_t                           cfg_object_id_type;

	typedef net::ipv4_address                  cfg_address_type;

	typedef rpc                                cfg_earpc;

	static const cfg_class_id_type             cfg_class_id = 0x100030;
};

struct wic_class_config : public property_config_base
{
	constexpr static const char *cfg_name = "TestClass";

	static const uint32_t cfg_class_id = 0x100030;

	typedef rpc cfg_earpc;

	typedef uint8_t cfg_value_type;

	typedef property_data_type<cfg_object_id_type, cfg_value_type> cfg_property_data_type;

	static const uint32_t cfg_cooldown_time = 1000;

	static const uint32_t cfg_member_id = 3;

	typedef wicp::wic_class<
		TestConfig,
		std::pair<std::integral_constant<uint32_t, cfg_member_id>, Int<cfg_member_id>>
	> cfg_wic_class;	
};

typedef wicp::local_property<wic_class_config> local_property;

typedef wicp::remote_property<wic_class_config> remote_property;

static int count = 0;

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

	local_property::init();
	remote_property::init();

	using namespace std::literals::chrono_literals;
	if(sport == 11234)
	{
		wic_class_config::cfg_wic_class::set_remote(0x70, {127,0,0,1});

		wic_class_config::cfg_wic_class::set_local(0x68);
			local_property::init(0x68,0);
			local_property::subscribe_to_change(0x68, l_change_handler_echo);
			local_property::remote_add(0x68, 0x70);

		wic_class_config::cfg_wic_class::set_local(0x69);
			local_property::init(0x69,0);
			local_property::subscribe_to_change(0x69, l_change_handler);
			local_property::remote_add(0x69, 0x70);
	}
	else
	{
		wic_class_config::cfg_wic_class::set_remote(0x68, {127,0,0,1});
			remote_property::init(0x68);
			remote_property::subscribe_to_change(0x68, r_change_handler);

		wic_class_config::cfg_wic_class::set_remote(0x69, {127,0,0,1});
			remote_property::init(0x69);
			remote_property::subscribe_to_change(0x69, r_change_handler_echo);
	}
	while(1)
	{
		std::string x ;
		std::cin >> x;
		if(x == "print")
		{
			if(sport == 11234)
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
