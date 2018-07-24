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
	typedef uint32_t class_id_type;
	constexpr static const char *cfg_name = "DDF - pirate - cashier_laser_controller";
	static const uint32_t cfg_class_id = 0x100030;
};

struct wic_class_config : public property_config_base
{
	constexpr static const char *cfg_name = "DDF - pirate - cashier_laser_controller";
	static const uint32_t cfg_class_id = 0x100030;
	static const uint16_t cfg_multiplicity = 1;

	typedef rpc cfg_earpc;

	typedef uint8_t cfg_value_type;

	typedef property_data_type<cfg_object_id_type, cfg_value_type> cfg_property_data_type;

	static const uint32_t cfg_member_id = 3;

	static const uint32_t cfg_cooldown_time = 1000;

	typedef wicp::wic_class<
		TestConfig,
		cfg_object_id_type, 
		cfg_value_type, 
		net::ipv4_address,
		std::integral_constant<uint32_t, cfg_member_id>, Int<cfg_member_id>
	> cfg_wic_class;	
};

typedef wicp::local_property<wic_class_config> local_property;
static void l_change_handler(uint64_t object_id)
{
	std::cout << "local property value: `" << int(local_property::value(object_id)) << "'" << std::endl;
	if(object_id == 68)
		++object_id;
	else
		--object_id;

	local_property::value(object_id, local_property::value(object_id, local_property::value(object_id)+1));
}

typedef wicp::remote_property<wic_class_config> remote_property;
static void r_change_handler(uint64_t object_id)
{
	std::cout << "remote property value: `" << int(remote_property::value(object_id)) << "'" << std::endl;
	if(object_id == 68)
		++object_id;
	else
		--object_id;

	remote_property::value(object_id, remote_property::value(object_id, remote_property::value(object_id)+1));	
}

static int count = 0;

int main() 
{ 
	journal::min_level = 255;
	journal::init(fname);
	rpc::init();
	using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(5s);
	if(sport == 1234)
	{
		wic_class_config::cfg_wic_class::set_local(68);
		wic_class_config::cfg_wic_class::set_local(69);
		wic_class_config::cfg_wic_class::set_remote(70, {127,0,0,1});
		wic_class_config::cfg_wic_class::set_remote(71, {127,0,0,1});
		local_property::init();
		local_property::subscribe_to_change(69, l_change_handler);
		// local_property::subscribe_to_change(69, l_change_handler);
		local_property::remote_add(68, 70);
		local_property::remote_add(68, 71);
		local_property::remote_add(69, 70);
		local_property::remote_add(69, 71);
		local_property::value(69, 0);
	}
	else
	{
		wic_class_config::cfg_wic_class::set_local(70);
		wic_class_config::cfg_wic_class::set_local(71);
		wic_class_config::cfg_wic_class::set_remote(68, {127,0,0,1});
		wic_class_config::cfg_wic_class::set_remote(69, {127,0,0,1});
		remote_property::init(68); 
		remote_property::init(69); // TODO place this to set_remote
		// remote_property::subscribe_to_change(68, r_change_handler);		
		remote_property::subscribe_to_change(69, r_change_handler);		
		// while(1)
		// {
		// 	std::this_thread::sleep_for(500ms);
		// 	remote_property::value(69, count++);
		// }
	}
	// local_property::value(12, 8);
	// local_property::value(12, 4);

	// remote_property::value(34, 8);
	// remote_property::value(34, 4);
	//device_role::remote_add(device_role::instance(0));
	while(1)
	{
		std::string x ;
		std::cin >> x;
	}

}