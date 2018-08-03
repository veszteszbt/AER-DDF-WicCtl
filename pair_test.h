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
#include <wicp/types/property.h>
#include <wicp/types/property_record.h>
#include <wicp/types/property_data_type.h>
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


struct wic_class_config : public property_config_base
{
	constexpr static const char *cfg_name = "TestClass";

	static const uint32_t cfg_class_id = 0x100030;

	typedef rpc cfg_earpc;
};

typedef std::integral_constant<uint32_t, 3> member_id;

typedef wicp::wic_class<
	wic_class_config,
	wicp::types::Property<3, true, uint8_t, 1000, 16>
	// wicp::types::Property<1, true, uint8_t, 1, 16>,
	// wicp::types::Property<2, true, uint8_t, 1, 16>,
	// wicp::types::Property<5, true, uint8_t, 1, 16>	
> wic_class;	

// typedef wicp::local_property<wic_class_config> local_property;

// typedef wicp::remote_property<wic_class_config> remote_property;

static int count = 0;

// static void l_change_handler(uint64_t object_id)
// {
// 	const auto value = int(local_property::value(object_id));
// 	std::stringstream ss;
// 	ss << "change_handler; local object: " << std::hex << object_id << "; value: " << std::dec << value;
// 	std::cout << ss.str() << std::endl;
// 	journal(journal::trace, "test.local") << ss.str() << journal::end;

// 	local_property::value(0x68, local_property::value(0x68) + 1);
// }

// static void r_change_handler(uint64_t object_id)
// {
// 	const auto value = int(remote_property::value(object_id));
// 	std::stringstream ss;
// 	ss << "change_hangler; remote object: " << std::hex << object_id << "; value: " << std::dec << value;
// 	std::cout << ss.str() << std::endl;
// 	journal(journal::trace, "test.local") << ss.str() << journal::end;

// 	remote_property::value(0x69, remote_property::value(0x69) + 1);
// }

// static void l_change_handler_echo(uint64_t object_id)
// {
// 	auto value = int(local_property::value(object_id));
// 	std::stringstream ss;
// 	ss << "echo; local object: " << std::hex << object_id << "; value: " << std::dec << value;
// 	std::cout << ss.str() << std::endl;
// 	journal(journal::trace, "faszlo_echo") << ss.str() << journal::end;
// }

static void r_change_handler_echo(uint64_t object_id)
{
	typedef wic_class::template get_remote<member_id> property;

	auto value = int(property::value(object_id));
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

	// local_property::init();
	// remote_property::init();

	using namespace std::literals::chrono_literals;
	wic_class::init();
	wic_class::set_remote(0x68, {10,2,1,100});
	// wic_class::set_local(0x69);
	typedef wic_class::template get_remote<member_id> property;
	property::subscribe_to_change(0x68, r_change_handler_echo);
	
	// std::this_thread::sleep_for(2s);
	int cnt = 0;
	while(1)
	{
		std::this_thread::sleep_for(500ms);
		property::value(0x68,cnt++);
	}

	// // wic_class::set_remote(0x69, {127,0,0,1});
	// // 	remote_property::init(0x69);
	// // 	remote_property::subscribe_to_change(0x69, r_change_handler_echo);
	// while(1)
	// {
	// 	std::string x ;
	// 	std::cin >> x;
	// }

}
