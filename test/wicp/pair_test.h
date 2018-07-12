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
#include <wicp/local_property.h>
#include <wicp/remote_property.h>
#include <wicp/forward_property.h>
#include <property_config_base.h>
#include <device_role.h>
#include <process/sql_executor.h>
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

struct device_role_config : public property_config_base
{
	constexpr static const char *cfg_name = "DDF - pirate - cashier_laser_controller";
	static const uint32_t cfg_class_id = 0x100030;
	static const uint16_t cfg_multiplicity = 1;
};
typedef wic::device_role<device_role_config> device_role;

/// laser ///
struct laser_config : public property_config_base
{
	constexpr static const char *name = "ddf::pirate::cashier_laser_controller::laser";
	static const uint32_t cfg_class_id = 0x100030;
	static const uint32_t cfg_member_id = 0x10;
	static const uint32_t cfg_cooldown_time = 200;
};
typedef peripheral::led_strip<laser_config> laser;

int main()
{
	journal::init();
	journal::min_level = 255;
	rpc::init();
	wicp::role_type test_role("dummy");
	device_role::init();
	device_role::remote_add(test_role);
}