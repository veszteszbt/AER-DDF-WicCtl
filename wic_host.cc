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
#include <property_config_base.h>
#include <process/sql_executor.h>

#include <device.h>
#include <game_event.h>

#include <audio.h>
#include <audio_effect.h>
#include <audio_speech.h>
#include <timer.h>

#include <peripheral/gpio_input.h>
#include <peripheral/gpio_output.h>
#include <peripheral/pin_pad.h>
#include <peripheral/pwm_output.h>
#include <peripheral/rfid.h>
#include <peripheral/text_display.h>
#include <peripheral/voltage_level.h>


earpc::udp wicc_earpc_config::connection(1234, 1234);

struct devstat_config
{
	typedef wicc_earpc cfg_earpc;
};
typedef wic::device<devstat_config> devstat;

/// Site DDF
namespace ddf
{

	/// Room pirate
	namespace pirate
	{

			/// cashier_laser_controller
			namespace cashier_laser_controller
			{

				/// laser ///
				struct laser_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::cashier_laser_controller::laser";

					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<laser_config> laser;

				/// lcd ///
				struct lcd_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::cashier_laser_controller::lcd";

					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::text_display<lcd_config> lcd;

				/// pin_pad ///
				struct pin_pad_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::cashier_laser_controller::pin_pad";

					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 40;
				};
				typedef peripheral::pin_pad<pin_pad_config> pin_pad;

				/// cash_box ///
				struct cash_box_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::cashier_laser_controller::cash_box";

					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<cash_box_config> cash_box;

				/// switch_1 ///
				struct switch_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::cashier_laser_controller::switch_1";

					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<switch_1_config> switch_1;

				/// led_strip ///
				struct led_strip_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::cashier_laser_controller::led_strip";

					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<led_strip_config> led_strip;

				static void init(net::ipv4_address ip)
				{
					laser::init(ip);
					laser::remote_add(net::ipv4_address(10,1,0,40));

					lcd::init(ip);
					lcd::remote_add(net::ipv4_address(10,1,0,40));

					pin_pad::init(ip);
					pin_pad::remote_add(net::ipv4_address(10,1,0,40));

					cash_box::init(ip);
					cash_box::remote_add(net::ipv4_address(10,1,0,40));

					switch_1::init(ip);
					switch_1::remote_add(net::ipv4_address(10,1,0,40));

					led_strip::init(ip);
					led_strip::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					laser::uninit();
					lcd::uninit();
					pin_pad::uninit();
					cash_box::uninit();
					switch_1::uninit();
					led_strip::uninit();

				}
			}

			/// entrance_hanger_controller
			namespace entrance_hanger_controller
			{

				/// debouncer_1 ///
				struct debouncer_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::entrance_hanger_controller::debouncer_1";

					static const uint32_t cfg_class_id = 0x100060;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_1_config> debouncer_1;

				/// led ///
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::entrance_hanger_controller::led";

					static const uint32_t cfg_class_id = 0x100060;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<led_config> led;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::entrance_hanger_controller::magnetic_sensor";

					static const uint32_t cfg_class_id = 0x100060;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_config> magnetic_sensor;

				/// debouncer_2 ///
				struct debouncer_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::entrance_hanger_controller::debouncer_2";

					static const uint32_t cfg_class_id = 0x100060;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_2_config> debouncer_2;

				static void init(net::ipv4_address ip)
				{
					debouncer_1::init(ip);
					debouncer_1::remote_add(net::ipv4_address(10,1,0,40));

					led::init(ip);
					led::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor::init(ip);
					magnetic_sensor::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_2::init(ip);
					debouncer_2::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					debouncer_1::uninit();
					led::uninit();
					magnetic_sensor::uninit();
					debouncer_2::uninit();

				}
			}

			/// ghostbox_picture_laser_boat_wheel_controller
			namespace ghostbox_picture_laser_boat_wheel_controller
			{

				/// magnetic_lock_1 ///
				struct magnetic_lock_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1";

					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_1_config> magnetic_lock_1;

				/// magnetic_lock_2 ///
				struct magnetic_lock_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2";

					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_2_config> magnetic_lock_2;

				/// magnetic_lock_3 ///
				struct magnetic_lock_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3";

					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_3_config> magnetic_lock_3;

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer";

					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_config> debouncer;

				/// photosensor ///
				struct photosensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor";

					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<photosensor_config> photosensor;

				/// knock_sensor ///
				struct knock_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor";

					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<knock_sensor_config> knock_sensor;

				/// led_strip_1 ///
				struct led_strip_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1";

					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x70;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<led_strip_1_config> led_strip_1;

				/// led_strip_2 ///
				struct led_strip_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2";

					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x80;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<led_strip_2_config> led_strip_2;

				/// potentiometer ///
				struct potentiometer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer";

					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x90;

					static const uint32_t cfg_cooldown_time = 40;
				};
				typedef peripheral::voltage_level<potentiometer_config> potentiometer;

				static void init(net::ipv4_address ip)
				{
					magnetic_lock_1::init(ip);
					magnetic_lock_1::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_2::init(ip);
					magnetic_lock_2::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_3::init(ip);
					magnetic_lock_3::remote_add(net::ipv4_address(10,1,0,40));

					debouncer::init(ip);
					debouncer::remote_add(net::ipv4_address(10,1,0,40));

					photosensor::init(ip);
					photosensor::remote_add(net::ipv4_address(10,1,0,40));

					knock_sensor::init(ip);
					knock_sensor::remote_add(net::ipv4_address(10,1,0,40));

					led_strip_1::init(ip);
					led_strip_1::remote_add(net::ipv4_address(10,1,0,40));

					led_strip_2::init(ip);
					led_strip_2::remote_add(net::ipv4_address(10,1,0,40));

					potentiometer::init(ip);
					potentiometer::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					magnetic_lock_1::uninit();
					magnetic_lock_2::uninit();
					magnetic_lock_3::uninit();
					debouncer::uninit();
					photosensor::uninit();
					knock_sensor::uninit();
					led_strip_1::uninit();
					led_strip_2::uninit();
					potentiometer::uninit();

				}
			}

			/// map_controller
			namespace map_controller
			{

				/// magnetic_sensor_1 ///
				struct magnetic_sensor_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::map_controller::magnetic_sensor_1";

					static const uint32_t cfg_class_id = 0x100010;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::voltage_level<magnetic_sensor_1_config> magnetic_sensor_1;

				/// magnetic_sensor_2 ///
				struct magnetic_sensor_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::map_controller::magnetic_sensor_2";

					static const uint32_t cfg_class_id = 0x100010;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::voltage_level<magnetic_sensor_2_config> magnetic_sensor_2;

				/// led_strip ///
				struct led_strip_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::map_controller::led_strip";

					static const uint32_t cfg_class_id = 0x100010;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 40;
				};
				typedef peripheral::pwm_output<led_strip_config> led_strip;

				static void init(net::ipv4_address ip)
				{
					magnetic_sensor_1::init(ip);
					magnetic_sensor_1::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor_2::init(ip);
					magnetic_sensor_2::remote_add(net::ipv4_address(10,1,0,40));

					led_strip::init(ip);
					led_strip::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					magnetic_sensor_1::uninit();
					magnetic_sensor_2::uninit();
					led_strip::uninit();

				}
			}

			/// rex_flipper_controller
			namespace rex_flipper_controller
			{

				/// light_controller_1 ///
				struct light_controller_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_1";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<light_controller_1_config> light_controller_1;

				/// light_controller_2 ///
				struct light_controller_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_2";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<light_controller_2_config> light_controller_2;

				/// light_controller_3 ///
				struct light_controller_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_3";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<light_controller_3_config> light_controller_3;

				/// light_controller_4 ///
				struct light_controller_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_4";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<light_controller_4_config> light_controller_4;

				/// light_controller_5 ///
				struct light_controller_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_5";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<light_controller_5_config> light_controller_5;

				/// light_controller_6 ///
				struct light_controller_6_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_6";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<light_controller_6_config> light_controller_6;

				/// light_controller_7 ///
				struct light_controller_7_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_7";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x70;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<light_controller_7_config> light_controller_7;

				/// photosensor_1 ///
				struct photosensor_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_1";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x80;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<photosensor_1_config> photosensor_1;

				/// photosensor_2 ///
				struct photosensor_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_2";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x90;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<photosensor_2_config> photosensor_2;

				/// photosensor_3 ///
				struct photosensor_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_3";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xa0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<photosensor_3_config> photosensor_3;

				/// photosensor_4 ///
				struct photosensor_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_4";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xb0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<photosensor_4_config> photosensor_4;

				/// photosensor_5 ///
				struct photosensor_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_5";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xc0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<photosensor_5_config> photosensor_5;

				/// photosensor_6 ///
				struct photosensor_6_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_6";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xd0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<photosensor_6_config> photosensor_6;

				/// photosensor_7 ///
				struct photosensor_7_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_7";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xe0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<photosensor_7_config> photosensor_7;

				/// rfid_reader ///
				struct rfid_reader_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::rfid_reader";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xf0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::rfid<rfid_reader_config> rfid_reader;

				/// magnetic_lock ///
				struct magnetic_lock_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::magnetic_lock";

					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x100;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_config> magnetic_lock;

				static void init(net::ipv4_address ip)
				{
					light_controller_1::init(ip);
					light_controller_1::remote_add(net::ipv4_address(10,1,0,40));

					light_controller_2::init(ip);
					light_controller_2::remote_add(net::ipv4_address(10,1,0,40));

					light_controller_3::init(ip);
					light_controller_3::remote_add(net::ipv4_address(10,1,0,40));

					light_controller_4::init(ip);
					light_controller_4::remote_add(net::ipv4_address(10,1,0,40));

					light_controller_5::init(ip);
					light_controller_5::remote_add(net::ipv4_address(10,1,0,40));

					light_controller_6::init(ip);
					light_controller_6::remote_add(net::ipv4_address(10,1,0,40));

					light_controller_7::init(ip);
					light_controller_7::remote_add(net::ipv4_address(10,1,0,40));

					photosensor_1::init(ip);
					photosensor_1::remote_add(net::ipv4_address(10,1,0,40));

					photosensor_2::init(ip);
					photosensor_2::remote_add(net::ipv4_address(10,1,0,40));

					photosensor_3::init(ip);
					photosensor_3::remote_add(net::ipv4_address(10,1,0,40));

					photosensor_4::init(ip);
					photosensor_4::remote_add(net::ipv4_address(10,1,0,40));

					photosensor_5::init(ip);
					photosensor_5::remote_add(net::ipv4_address(10,1,0,40));

					photosensor_6::init(ip);
					photosensor_6::remote_add(net::ipv4_address(10,1,0,40));

					photosensor_7::init(ip);
					photosensor_7::remote_add(net::ipv4_address(10,1,0,40));

					rfid_reader::init(ip);
					rfid_reader::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock::init(ip);
					magnetic_lock::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					light_controller_1::uninit();
					light_controller_2::uninit();
					light_controller_3::uninit();
					light_controller_4::uninit();
					light_controller_5::uninit();
					light_controller_6::uninit();
					light_controller_7::uninit();
					photosensor_1::uninit();
					photosensor_2::uninit();
					photosensor_3::uninit();
					photosensor_4::uninit();
					photosensor_5::uninit();
					photosensor_6::uninit();
					photosensor_7::uninit();
					rfid_reader::uninit();
					magnetic_lock::uninit();

				}
			}

			/// stone_chest_controller
			namespace stone_chest_controller
			{

				/// magnetic_sensor_1 ///
				struct magnetic_sensor_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_1";

					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_1_config> magnetic_sensor_1;

				/// magnetic_sensor_2 ///
				struct magnetic_sensor_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_2";

					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_2_config> magnetic_sensor_2;

				/// magnetic_sensor_3 ///
				struct magnetic_sensor_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_3";

					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_3_config> magnetic_sensor_3;

				/// magnetic_sensor_4 ///
				struct magnetic_sensor_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_4";

					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_4_config> magnetic_sensor_4;

				/// magnetic_sensor_5 ///
				struct magnetic_sensor_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_5";

					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_5_config> magnetic_sensor_5;

				/// magnetic_lock_1 ///
				struct magnetic_lock_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_lock_1";

					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_1_config> magnetic_lock_1;

				/// magnetic_lock_2 ///
				struct magnetic_lock_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_lock_2";

					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x70;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_2_config> magnetic_lock_2;

				/// led_strip ///
				struct led_strip_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::led_strip";

					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x80;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<led_strip_config> led_strip;

				static void init(net::ipv4_address ip)
				{
					magnetic_sensor_1::init(ip);
					magnetic_sensor_1::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor_2::init(ip);
					magnetic_sensor_2::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor_3::init(ip);
					magnetic_sensor_3::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor_4::init(ip);
					magnetic_sensor_4::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor_5::init(ip);
					magnetic_sensor_5::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_1::init(ip);
					magnetic_lock_1::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_2::init(ip);
					magnetic_lock_2::remote_add(net::ipv4_address(10,1,0,40));

					led_strip::init(ip);
					led_strip::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					magnetic_sensor_1::uninit();
					magnetic_sensor_2::uninit();
					magnetic_sensor_3::uninit();
					magnetic_sensor_4::uninit();
					magnetic_sensor_5::uninit();
					magnetic_lock_1::uninit();
					magnetic_lock_2::uninit();
					led_strip::uninit();

				}
			}


			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0xa0;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed1_config> freezed1;

			/// Freezed5 ///
			struct freezed5_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0xb0;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed5_config> freezed5;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				typedef uint8_t cfg_value_type;

				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gamestate_config> gamestate;


			/// room_1
			struct room_1_config
			{
                		static const uint8_t cfg_device = 2;
				static const uint8_t cfg_channel = 7;
			};
			typedef wic::audio<room_1_config> room_1;

			namespace room_1_content
			{
				struct chord_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
				};
				typedef wic::audio_effect<chord_config> chord;

			}

			/// room_2
			struct room_2_config
			{
                		static const uint8_t cfg_device = 2;
				static const uint8_t cfg_channel = 6;
			};
			typedef wic::audio<room_2_config> room_2;

			namespace room_2_content
			{
				struct chord_config
				{
					typedef room_2 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
				};
				typedef wic::audio_effect<chord_config> chord;

			}

			/// FreezeTimer1
			struct freezetimer1_config
			{
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0xd0;
				static const uint32_t cfg_interval  = 3000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0xe0;
				static const uint32_t cfg_interval  = 15000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0xc0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;


			void freeze_1_start()
			{
				typedef typename pirate::freezed1 fr;
				typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,1,17).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_1_stop()
			{
				typedef typename pirate::freezed1 fr;
				typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,1,18).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_1_timeout()
			{
				typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::freezed1 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,1,19).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void freeze_5_start()
			{
				typedef typename pirate::freezed5 fr;
				typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,1,20).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_5_stop()
			{
				typedef typename pirate::freezed5 fr;
				typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,1,21).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_5_timeout()
			{
				typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::freezed5 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,1,22).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void game_state_changed()
			{
				typedef typename pirate::gametimer tmr;
				typedef typename pirate::gamestate gs;
				typedef typename pirate::freezed1 fr1;
				typedef typename pirate::freezed5 fr5;

				if(true)
				{
					game_event(1,1,16).propagate();
					(void)0; { 
      switch(gs::value())
      {
      	// Not started
      	case 0:
      		tmr::stop();
      		tmr::reset();
      		break;

      	// Started
      	case 1:
      		tmr::start();
      		fr1::value(false);
      		fr5::value(false);
      		break;

      	// Paused
      	case 2:
      		tmr::stop();
      		break;

      	// Finished
      	case 3:
      		tmr::stop();
      		tmr::reset();
      		break;
      }
     }
				}
			}
			void game_timer_expired()
			{
				typedef typename pirate::gametimer tmr;
				typedef typename pirate::gamestate gs;

				if(true && ( tmr::value() >= 3600 ))
				{
					game_event(1,1,15).propagate();
					(void)0; { gs::value(3); }
				}
			}
			void rotation_update()
			{
				typedef typename pirate::map_controller::led_strip starlight;
				typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer potentiometer;

				if(true)
				{
					game_event(1,1,23).propagate();
					(void)0; { 
        const uint16_t v = (potentiometer::value()>>5)+1;
        starlight::value(v*v);
       }
				}
			}


		static void init()
		{
			cashier_laser_controller::init(net::ipv4_address(10,1,1,53));
			entrance_hanger_controller::init(net::ipv4_address(10,1,1,57));
			ghostbox_picture_laser_boat_wheel_controller::init(net::ipv4_address(10,1,1,55));
			map_controller::init(net::ipv4_address(10,1,1,51));
			rex_flipper_controller::init(net::ipv4_address(10,1,1,54));
			stone_chest_controller::init(net::ipv4_address(10,1,1,52));

			freezed1::on_change += freeze_1_start;
			freezed1::on_change += freeze_1_stop;
			freezetimer1::on_change += freeze_1_timeout;
			freezed5::on_change += freeze_5_start;
			freezed5::on_change += freeze_5_stop;
			freezetimer5::on_change += freeze_5_timeout;
			gamestate::on_change += game_state_changed;
			gametimer::on_change += game_timer_expired;
			ghostbox_picture_laser_boat_wheel_controller::potentiometer::value::on_change += rotation_update;

			freezed1::init();
			freezed1::remote_add(net::ipv4_address(10,1,0,40));

			freezed5::init();
			freezed5::remote_add(net::ipv4_address(10,1,0,40));

			gamestate::init();
			gamestate::remote_add(net::ipv4_address(10,1,0,40));


			ddf::pirate::room_1::init();
			room_1_content::chord::init();

			ddf::pirate::room_2::init();
			room_2_content::chord::init();


			freezetimer1::init();
			freezetimer1::remote_add(net::ipv4_address(10,1,0,40));

			freezetimer5::init();
			freezetimer5::remote_add(net::ipv4_address(10,1,0,40));

			gametimer::init();
			gametimer::remote_add(net::ipv4_address(10,1,0,40));


		}

		static void uninit()
		{
			freezed1::on_change -= freeze_1_start;
			freezed1::on_change -= freeze_1_stop;
			freezetimer1::on_change -= freeze_1_timeout;
			freezed5::on_change -= freeze_5_start;
			freezed5::on_change -= freeze_5_stop;
			freezetimer5::on_change -= freeze_5_timeout;
			gamestate::on_change -= game_state_changed;
			gametimer::on_change -= game_timer_expired;
			ghostbox_picture_laser_boat_wheel_controller::potentiometer::value::on_change -= rotation_update;

			cashier_laser_controller::uninit();
			entrance_hanger_controller::uninit();
			ghostbox_picture_laser_boat_wheel_controller::uninit();
			map_controller::uninit();
			rex_flipper_controller::uninit();
			stone_chest_controller::uninit();

			freezed1::uninit();
			freezed5::uninit();
			gamestate::uninit();

			room_1_content::chord::uninit();

			ddf::pirate::room_1::uninit();
			room_2_content::chord::uninit();

			ddf::pirate::room_2::uninit();

			freezetimer1::init();
			freezetimer5::init();
			gametimer::init();

		}
	}

	/// Room magician
	namespace magician
	{

			/// cupboard_controller
			namespace cupboard_controller
			{

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::cupboard_controller::debouncer";

					static const uint32_t cfg_class_id = 0x200010;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_config> debouncer;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::cupboard_controller::magnetic_sensor";

					static const uint32_t cfg_class_id = 0x200010;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_config> magnetic_sensor;

				/// magnetic_lock ///
				struct magnetic_lock_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::cupboard_controller::magnetic_lock";

					static const uint32_t cfg_class_id = 0x200010;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_config> magnetic_lock;

				/// led_strip ///
				struct led_strip_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::cupboard_controller::led_strip";

					static const uint32_t cfg_class_id = 0x200010;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<led_strip_config> led_strip;

				static void init(net::ipv4_address ip)
				{
					debouncer::init(ip);
					debouncer::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor::init(ip);
					magnetic_sensor::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock::init(ip);
					magnetic_lock::remote_add(net::ipv4_address(10,1,0,40));

					led_strip::init(ip);
					led_strip::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					debouncer::uninit();
					magnetic_sensor::uninit();
					magnetic_lock::uninit();
					led_strip::uninit();

				}
			}

			/// design_board_controller
			namespace design_board_controller
			{

				/// linear_magnetic_sensor_1 ///
				struct linear_magnetic_sensor_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::design_board_controller::linear_magnetic_sensor_1";

					static const uint32_t cfg_class_id = 0x200020;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<linear_magnetic_sensor_1_config> linear_magnetic_sensor_1;

				/// linear_magnetic_sensor_2 ///
				struct linear_magnetic_sensor_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::design_board_controller::linear_magnetic_sensor_2";

					static const uint32_t cfg_class_id = 0x200020;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<linear_magnetic_sensor_2_config> linear_magnetic_sensor_2;

				/// linear_magnetic_sensor_3 ///
				struct linear_magnetic_sensor_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::design_board_controller::linear_magnetic_sensor_3";

					static const uint32_t cfg_class_id = 0x200020;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<linear_magnetic_sensor_3_config> linear_magnetic_sensor_3;

				/// magnetic_lock ///
				struct magnetic_lock_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::design_board_controller::magnetic_lock";

					static const uint32_t cfg_class_id = 0x200020;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_config> magnetic_lock;

				static void init(net::ipv4_address ip)
				{
					linear_magnetic_sensor_1::init(ip);
					linear_magnetic_sensor_1::remote_add(net::ipv4_address(10,1,0,40));

					linear_magnetic_sensor_2::init(ip);
					linear_magnetic_sensor_2::remote_add(net::ipv4_address(10,1,0,40));

					linear_magnetic_sensor_3::init(ip);
					linear_magnetic_sensor_3::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock::init(ip);
					magnetic_lock::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					linear_magnetic_sensor_1::uninit();
					linear_magnetic_sensor_2::uninit();
					linear_magnetic_sensor_3::uninit();
					magnetic_lock::uninit();

				}
			}

			/// entrance_controller
			namespace entrance_controller
			{

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::entrance_controller::debouncer";

					static const uint32_t cfg_class_id = 0x200040;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_config> debouncer;

				/// led ///
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::entrance_controller::led";

					static const uint32_t cfg_class_id = 0x200040;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<led_config> led;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::entrance_controller::magnetic_sensor";

					static const uint32_t cfg_class_id = 0x200040;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_config> magnetic_sensor;

				static void init(net::ipv4_address ip)
				{
					debouncer::init(ip);
					debouncer::remote_add(net::ipv4_address(10,1,0,40));

					led::init(ip);
					led::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor::init(ip);
					magnetic_sensor::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					debouncer::uninit();
					led::uninit();
					magnetic_sensor::uninit();

				}
			}

			/// futuristic_safe_controller
			namespace futuristic_safe_controller
			{

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::futuristic_safe_controller::debouncer";

					static const uint32_t cfg_class_id = 0x200030;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_config> debouncer;

				/// rfid_reader ///
				struct rfid_reader_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::futuristic_safe_controller::rfid_reader";

					static const uint32_t cfg_class_id = 0x200030;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::rfid<rfid_reader_config> rfid_reader;

				/// pin_pad ///
				struct pin_pad_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::futuristic_safe_controller::pin_pad";

					static const uint32_t cfg_class_id = 0x200030;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 40;
				};
				typedef peripheral::pin_pad<pin_pad_config> pin_pad;

				/// magnetic_lock ///
				struct magnetic_lock_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::futuristic_safe_controller::magnetic_lock";

					static const uint32_t cfg_class_id = 0x200030;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_config> magnetic_lock;

				static void init(net::ipv4_address ip)
				{
					debouncer::init(ip);
					debouncer::remote_add(net::ipv4_address(10,1,0,40));

					rfid_reader::init(ip);
					rfid_reader::remote_add(net::ipv4_address(10,1,0,40));

					pin_pad::init(ip);
					pin_pad::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock::init(ip);
					magnetic_lock::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					debouncer::uninit();
					rfid_reader::uninit();
					pin_pad::uninit();
					magnetic_lock::uninit();

				}
			}


			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x80;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed1_config> freezed1;

			/// Freezed5 ///
			struct freezed5_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed5_config> freezed5;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				typedef uint8_t cfg_value_type;

				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x70;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gamestate_config> gamestate;


			/// room_1
			struct room_1_config
			{
                		static const uint8_t cfg_device = 2;
				static const uint8_t cfg_channel = 1;
			};
			typedef wic::audio<room_1_config> room_1;

			namespace room_1_content
			{
				struct chord_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
				};
				typedef wic::audio_effect<chord_config> chord;
				struct event_1_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/magician/event_1.wav";

					static const uint32_t cfg_class_id = 0x200060;

					static const uint32_t cfg_member_id = 0x20;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/magician/event_2.wav";

					static const uint32_t cfg_class_id = 0x200060;

					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<event_2_config> event_2;

			}

			/// room_2
			struct room_2_config
			{
                		static const uint8_t cfg_device = 2;
				static const uint8_t cfg_channel = 0;
			};
			typedef wic::audio<room_2_config> room_2;

			namespace room_2_content
			{
				struct chord_config
				{
					typedef room_2 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
				};
				typedef wic::audio_effect<chord_config> chord;

			}

			/// FreezeTimer1
			struct freezetimer1_config
			{
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0xb0;
				static const uint32_t cfg_interval  = 3000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0xc0;
				static const uint32_t cfg_interval  = 15000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0xa0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;


			void freeze_1_start()
			{
				typedef typename magician::freezed1 fr;
				typedef typename magician::freezetimer1 tmr;
				typedef typename magician::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,2,15).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_1_stop()
			{
				typedef typename magician::freezed1 fr;
				typedef typename magician::freezetimer1 tmr;
				typedef typename magician::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,2,16).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_1_timeout()
			{
				typedef typename magician::freezetimer1 tmr;
				typedef typename magician::freezed1 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,2,17).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void freeze_5_start()
			{
				typedef typename magician::freezed5 fr;
				typedef typename magician::freezetimer5 tmr;
				typedef typename magician::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,2,18).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_5_stop()
			{
				typedef typename magician::freezed5 fr;
				typedef typename magician::freezetimer5 tmr;
				typedef typename magician::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,2,19).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_5_timeout()
			{
				typedef typename magician::freezetimer5 tmr;
				typedef typename magician::freezed5 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,2,20).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void game_state_changed()
			{
				typedef typename magician::gametimer tmr;
				typedef typename magician::gamestate gs;
				typedef typename magician::freezed1 fr1;
				typedef typename magician::freezed5 fr5;

				if(true)
				{
					game_event(1,2,14).propagate();
					(void)0; { 
      switch(gs::value())
      {
      	// Not started
      	case 0:
      		tmr::stop();
      		tmr::reset();
      		break;

      	// Started
      	case 1:
      		tmr::start();
      		fr1::value(false);
      		fr5::value(false);
      		break;

      	// Paused
      	case 2:
      		tmr::stop();
      		break;

      	// Finished
      	case 3:
      		tmr::stop();
      		tmr::reset();
      		break;
      }
     }
				}
			}
			void game_timer_expired()
			{
				typedef typename magician::gametimer tmr;
				typedef typename magician::gamestate gs;

				if(true && ( tmr::value() >= 3600 ))
				{
					game_event(1,2,13).propagate();
					(void)0; { gs::value(3); }
				}
			}
			void cupboard_controller_event_for_labyrinth_task()
			{
				typedef typename magician::cupboard_controller::debouncer debouncer;
				typedef typename magician::cupboard_controller::magnetic_lock magnetic_lock;

				if(true && (  debouncer::value()  ))
				{
					game_event(1,2,21).propagate();
					(void)0; {  magnetic_lock::value(0);  }
				}
			}


		static void init()
		{
			cupboard_controller::init(net::ipv4_address(10,1,1,58));
			design_board_controller::init(net::ipv4_address(10,1,1,59));
			entrance_controller::init(net::ipv4_address(10,1,1,61));
			futuristic_safe_controller::init(net::ipv4_address(10,1,1,60));

			freezed1::on_change += freeze_1_start;
			freezed1::on_change += freeze_1_stop;
			freezetimer1::on_change += freeze_1_timeout;
			freezed5::on_change += freeze_5_start;
			freezed5::on_change += freeze_5_stop;
			freezetimer5::on_change += freeze_5_timeout;
			gamestate::on_change += game_state_changed;
			gametimer::on_change += game_timer_expired;
			cupboard_controller::debouncer::value::on_change += cupboard_controller_event_for_labyrinth_task;

			freezed1::init();
			freezed1::remote_add(net::ipv4_address(10,1,0,40));

			freezed5::init();
			freezed5::remote_add(net::ipv4_address(10,1,0,40));

			gamestate::init();
			gamestate::remote_add(net::ipv4_address(10,1,0,40));


			ddf::magician::room_1::init();
			room_1_content::chord::init();
			room_1_content::event_1::init();

			room_1_content::event_2::init();


			ddf::magician::room_2::init();
			room_2_content::chord::init();


			freezetimer1::init();
			freezetimer1::remote_add(net::ipv4_address(10,1,0,40));

			freezetimer5::init();
			freezetimer5::remote_add(net::ipv4_address(10,1,0,40));

			gametimer::init();
			gametimer::remote_add(net::ipv4_address(10,1,0,40));


		}

		static void uninit()
		{
			freezed1::on_change -= freeze_1_start;
			freezed1::on_change -= freeze_1_stop;
			freezetimer1::on_change -= freeze_1_timeout;
			freezed5::on_change -= freeze_5_start;
			freezed5::on_change -= freeze_5_stop;
			freezetimer5::on_change -= freeze_5_timeout;
			gamestate::on_change -= game_state_changed;
			gametimer::on_change -= game_timer_expired;
			cupboard_controller::debouncer::value::on_change -= cupboard_controller_event_for_labyrinth_task;

			cupboard_controller::uninit();
			design_board_controller::uninit();
			entrance_controller::uninit();
			futuristic_safe_controller::uninit();

			freezed1::uninit();
			freezed5::uninit();
			gamestate::uninit();

			room_1_content::chord::uninit();
			room_1_content::event_1::uninit();
			room_1_content::event_2::uninit();

			ddf::magician::room_1::uninit();
			room_2_content::chord::uninit();

			ddf::magician::room_2::uninit();

			freezetimer1::init();
			freezetimer5::init();
			gametimer::init();

		}
	}

	/// Room villa
	namespace villa
	{

			/// control_room_controller
			namespace control_room_controller
			{

				/// switch_1 ///
				struct switch_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::switch_1";

					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<switch_1_config> switch_1;

				/// rfid ///
				struct rfid_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::rfid";

					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::rfid<rfid_config> rfid;

				/// magnetic_lock ///
				struct magnetic_lock_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::magnetic_lock";

					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_config> magnetic_lock;

				/// debouncer_1 ///
				struct debouncer_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::debouncer_1";

					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_1_config> debouncer_1;

				/// video_eject ///
				struct video_eject_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::video_eject";

					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<video_eject_config> video_eject;

				static void init(net::ipv4_address ip)
				{
					switch_1::init(ip);
					switch_1::remote_add(net::ipv4_address(10,1,0,40));

					rfid::init(ip);
					rfid::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock::init(ip);
					magnetic_lock::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_1::init(ip);
					debouncer_1::remote_add(net::ipv4_address(10,1,0,40));

					video_eject::init(ip);
					video_eject::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					switch_1::uninit();
					rfid::uninit();
					magnetic_lock::uninit();
					debouncer_1::uninit();
					video_eject::uninit();

				}
			}

			/// desk_controller
			namespace desk_controller
			{

				/// debouncer_3 ///
				struct debouncer_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desk_controller::debouncer_3";

					static const uint32_t cfg_class_id = 0x300020;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_3_config> debouncer_3;

				/// debouncer_4 ///
				struct debouncer_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desk_controller::debouncer_4";

					static const uint32_t cfg_class_id = 0x300020;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_4_config> debouncer_4;

				static void init(net::ipv4_address ip)
				{
					debouncer_3::init(ip);
					debouncer_3::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_4::init(ip);
					debouncer_4::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					debouncer_3::uninit();
					debouncer_4::uninit();

				}
			}

			/// desktop_pc
			namespace desktop_pc
			{

				/// Started ///
				struct started_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x10;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<started_config> started;

				/// Shutdown ///
				struct shutdown_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x20;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<shutdown_config> shutdown;

				/// Logged In ///
				struct logged_in_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x30;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<logged_in_config> logged_in;

				/// Recycled Restore ///
				struct recycled_restore_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x40;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<recycled_restore_config> recycled_restore;

				/// Audioplay started ///
				struct audioplay_started_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x50;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audioplay_started_config> audioplay_started;

				/// Audioplay finished ///
				struct audioplay_finished_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x60;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audioplay_finished_config> audioplay_finished;

				/// Audioplay paused ///
				struct audioplay_paused_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x70;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audioplay_paused_config> audioplay_paused;

				/// Restart Game ///
				struct restart_game_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x80;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<restart_game_config> restart_game;

				/// Audioplay startevent ///
				struct audioplay_startevent_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x90;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audioplay_startevent_config> audioplay_startevent;

				/// Audiopause pauseevent ///
				struct audiopause_pauseevent_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0xa0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audiopause_pauseevent_config> audiopause_pauseevent;

				static void init(net::ipv4_address ip)
				{
					desktop_pc::started::init(ip);
			desktop_pc::started::remote_add(net::ipv4_address(10,1,0,40));

					desktop_pc::shutdown::init(ip);
			desktop_pc::shutdown::remote_add(net::ipv4_address(10,1,0,40));

					desktop_pc::logged_in::init(ip);
			desktop_pc::logged_in::remote_add(net::ipv4_address(10,1,0,40));

					desktop_pc::recycled_restore::init(ip);
			desktop_pc::recycled_restore::remote_add(net::ipv4_address(10,1,0,40));

					desktop_pc::audioplay_started::init(ip);
			desktop_pc::audioplay_started::remote_add(net::ipv4_address(10,1,0,40));

					desktop_pc::audioplay_finished::init(ip);
			desktop_pc::audioplay_finished::remote_add(net::ipv4_address(10,1,0,40));

					desktop_pc::audioplay_paused::init(ip);
			desktop_pc::audioplay_paused::remote_add(net::ipv4_address(10,1,0,40));

					desktop_pc::restart_game::init(ip);
			desktop_pc::restart_game::remote_add(net::ipv4_address(10,1,0,40));

					desktop_pc::audioplay_startevent::init(ip);
			desktop_pc::audioplay_startevent::remote_add(net::ipv4_address(10,1,0,40));

					desktop_pc::audiopause_pauseevent::init(ip);
			desktop_pc::audiopause_pauseevent::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					desktop_pc::started::uninit();
					desktop_pc::shutdown::uninit();
					desktop_pc::logged_in::uninit();
					desktop_pc::recycled_restore::uninit();
					desktop_pc::audioplay_started::uninit();
					desktop_pc::audioplay_finished::uninit();
					desktop_pc::audioplay_paused::uninit();
					desktop_pc::restart_game::uninit();
					desktop_pc::audioplay_startevent::uninit();
					desktop_pc::audiopause_pauseevent::uninit();

				}
			}

			/// entrance_controller
			namespace entrance_controller
			{

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::entrance_controller::debouncer";

					static const uint32_t cfg_class_id = 0x300040;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_config> debouncer;

				/// led ///
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::entrance_controller::led";

					static const uint32_t cfg_class_id = 0x300040;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<led_config> led;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::entrance_controller::magnetic_sensor";

					static const uint32_t cfg_class_id = 0x300040;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_config> magnetic_sensor;

				static void init(net::ipv4_address ip)
				{
					debouncer::init(ip);
					debouncer::remote_add(net::ipv4_address(10,1,0,40));

					led::init(ip);
					led::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor::init(ip);
					magnetic_sensor::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					debouncer::uninit();
					led::uninit();
					magnetic_sensor::uninit();

				}
			}

			/// safe_controller
			namespace safe_controller
			{

				/// pin_pad ///
				struct pin_pad_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::safe_controller::pin_pad";

					static const uint32_t cfg_class_id = 0x300010;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 40;
				};
				typedef peripheral::pin_pad<pin_pad_config> pin_pad;

				/// magnetic_lock ///
				struct magnetic_lock_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::safe_controller::magnetic_lock";

					static const uint32_t cfg_class_id = 0x300010;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_config> magnetic_lock;

				/// debouncer_1 ///
				struct debouncer_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::safe_controller::debouncer_1";

					static const uint32_t cfg_class_id = 0x300010;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_1_config> debouncer_1;

				/// debouncer_2 ///
				struct debouncer_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::safe_controller::debouncer_2";

					static const uint32_t cfg_class_id = 0x300010;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_2_config> debouncer_2;

				static void init(net::ipv4_address ip)
				{
					pin_pad::init(ip);
					pin_pad::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock::init(ip);
					magnetic_lock::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_1::init(ip);
					debouncer_1::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_2::init(ip);
					debouncer_2::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					pin_pad::uninit();
					magnetic_lock::uninit();
					debouncer_1::uninit();
					debouncer_2::uninit();

				}
			}

			/// video_device
			namespace video_device
			{

				/// Started ///
				struct started_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x10;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<started_config> started;

				/// Shutdown ///
				struct shutdown_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x20;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<shutdown_config> shutdown;

				/// LiveCam started ///
				struct livecam_started_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x30;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<livecam_started_config> livecam_started;

				/// LiveCamSlides started ///
				struct livecamslides_started_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x40;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<livecamslides_started_config> livecamslides_started;

				/// Restart Game ///
				struct restart_game_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x50;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<restart_game_config> restart_game;

				/// Start LiveCams ///
				struct start_livecams_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x60;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<start_livecams_config> start_livecams;

				/// Start Tape ///
				struct start_tape_config : public property_config_base
				{
					typedef int32_t cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x70;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<start_tape_config> start_tape;

				/// Stop Tape ///
				struct stop_tape_config : public property_config_base
				{
					typedef int32_t cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x80;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<stop_tape_config> stop_tape;

				/// enabled ///
				struct enabled_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x90;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<enabled_config> enabled;

				/// casette_id ///
				struct casette_id_config : public property_config_base
				{
					typedef uint64_t cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xa0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<casette_id_config> casette_id;

				/// play_ongoing ///
				struct play_ongoing_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xb0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<play_ongoing_config> play_ongoing;

				static void init(net::ipv4_address ip)
				{
					video_device::started::init(ip);
			video_device::started::remote_add(net::ipv4_address(10,1,0,40));

					video_device::shutdown::init(ip);
			video_device::shutdown::remote_add(net::ipv4_address(10,1,0,40));

					video_device::livecam_started::init(ip);
			video_device::livecam_started::remote_add(net::ipv4_address(10,1,0,40));

					video_device::livecamslides_started::init(ip);
			video_device::livecamslides_started::remote_add(net::ipv4_address(10,1,0,40));

					video_device::restart_game::init(ip);
			video_device::restart_game::remote_add(net::ipv4_address(10,1,0,40));

					video_device::start_livecams::init(ip);
			video_device::start_livecams::remote_add(net::ipv4_address(10,1,0,40));

					video_device::start_tape::init(ip);
			video_device::start_tape::remote_add(net::ipv4_address(10,1,0,40));

					video_device::stop_tape::init(ip);
			video_device::stop_tape::remote_add(net::ipv4_address(10,1,0,40));

					video_device::enabled::init(ip);
			video_device::enabled::remote_add(net::ipv4_address(10,1,0,40));

					video_device::casette_id::init(ip);
			video_device::casette_id::remote_add(net::ipv4_address(10,1,0,40));

					video_device::play_ongoing::init(ip);
			video_device::play_ongoing::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					video_device::started::uninit();
					video_device::shutdown::uninit();
					video_device::livecam_started::uninit();
					video_device::livecamslides_started::uninit();
					video_device::restart_game::uninit();
					video_device::start_livecams::uninit();
					video_device::start_tape::uninit();
					video_device::stop_tape::uninit();
					video_device::enabled::uninit();
					video_device::casette_id::uninit();
					video_device::play_ongoing::uninit();

				}
			}


			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0xa0;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed1_config> freezed1;

			/// Freezed5 ///
			struct freezed5_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0xb0;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed5_config> freezed5;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				typedef uint8_t cfg_value_type;

				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gamestate_config> gamestate;


			/// room_1
			struct room_1_config
			{
                		static const uint8_t cfg_device = 2;
				static const uint8_t cfg_channel = 3;
			};
			typedef wic::audio<room_1_config> room_1;

			namespace room_1_content
			{
				struct chord_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
				};
				typedef wic::audio_effect<chord_config> chord;
				struct event_1_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/villa/event_1.wav";

					static const uint32_t cfg_class_id = 0x300080;

					static const uint32_t cfg_member_id = 0x20;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/villa/event_2.wav";

					static const uint32_t cfg_class_id = 0x300080;

					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<event_2_config> event_2;
				struct event_3_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/villa/event_3.wav";

					static const uint32_t cfg_class_id = 0x300080;

					static const uint32_t cfg_member_id = 0x40;
				};
				typedef wic::audio_speech<event_3_config> event_3;

			}

			/// room_2
			struct room_2_config
			{
                		static const uint8_t cfg_device = 2;
				static const uint8_t cfg_channel = 2;
			};
			typedef wic::audio<room_2_config> room_2;

			namespace room_2_content
			{
				struct chord_config
				{
					typedef room_2 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
				};
				typedef wic::audio_effect<chord_config> chord;

			}

			/// FreezeTimer1
			struct freezetimer1_config
			{
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0xd0;
				static const uint32_t cfg_interval  = 3000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0xe0;
				static const uint32_t cfg_interval  = 15000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0xc0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;


			void freeze_1_start()
			{
				typedef typename villa::freezed1 fr;
				typedef typename villa::freezetimer1 tmr;
				typedef typename villa::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,3,17).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_1_stop()
			{
				typedef typename villa::freezed1 fr;
				typedef typename villa::freezetimer1 tmr;
				typedef typename villa::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,3,18).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_1_timeout()
			{
				typedef typename villa::freezetimer1 tmr;
				typedef typename villa::freezed1 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,3,19).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void freeze_5_start()
			{
				typedef typename villa::freezed5 fr;
				typedef typename villa::freezetimer5 tmr;
				typedef typename villa::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,3,20).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_5_stop()
			{
				typedef typename villa::freezed5 fr;
				typedef typename villa::freezetimer5 tmr;
				typedef typename villa::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,3,21).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_5_timeout()
			{
				typedef typename villa::freezetimer5 tmr;
				typedef typename villa::freezed5 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,3,22).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void game_state_changed()
			{
				typedef typename villa::gametimer tmr;
				typedef typename villa::gamestate gs;
				typedef typename villa::freezed1 fr1;
				typedef typename villa::freezed5 fr5;

				if(true)
				{
					game_event(1,3,16).propagate();
					(void)0; { 
      switch(gs::value())
      {
      	// Not started
      	case 0:
      		tmr::stop();
      		tmr::reset();
      		break;

      	// Started
      	case 1:
      		tmr::start();
      		fr1::value(false);
      		fr5::value(false);
      		break;

      	// Paused
      	case 2:
      		tmr::stop();
      		break;

      	// Finished
      	case 3:
      		tmr::stop();
      		tmr::reset();
      		break;
      }
     }
				}
			}
			void game_timer_expired()
			{
				typedef typename villa::gametimer tmr;
				typedef typename villa::gamestate gs;

				if(true && ( tmr::value() >= 3600 ))
				{
					game_event(1,3,15).propagate();
					(void)0; { gs::value(3); }
				}
			}


		static void init()
		{
			control_room_controller::init(net::ipv4_address(10,1,0,74));
			desk_controller::init(net::ipv4_address(10,1,0,75));
			desktop_pc::init(net::ipv4_address(10,1,0,20));
			entrance_controller::init(net::ipv4_address(10,1,0,67));
			safe_controller::init(net::ipv4_address(10,1,0,62));
			video_device::init(net::ipv4_address(10,1,0,21));

			freezed1::on_change += freeze_1_start;
			freezed1::on_change += freeze_1_stop;
			freezetimer1::on_change += freeze_1_timeout;
			freezed5::on_change += freeze_5_start;
			freezed5::on_change += freeze_5_stop;
			freezetimer5::on_change += freeze_5_timeout;
			gamestate::on_change += game_state_changed;
			gametimer::on_change += game_timer_expired;

			freezed1::init();
			freezed1::remote_add(net::ipv4_address(10,1,0,40));

			freezed5::init();
			freezed5::remote_add(net::ipv4_address(10,1,0,40));

			gamestate::init();
			gamestate::remote_add(net::ipv4_address(10,1,0,40));


			ddf::villa::room_1::init();
			room_1_content::chord::init();
			room_1_content::event_1::init();

			room_1_content::event_2::init();

			room_1_content::event_3::init();


			ddf::villa::room_2::init();
			room_2_content::chord::init();


			freezetimer1::init();
			freezetimer1::remote_add(net::ipv4_address(10,1,0,40));

			freezetimer5::init();
			freezetimer5::remote_add(net::ipv4_address(10,1,0,40));

			gametimer::init();
			gametimer::remote_add(net::ipv4_address(10,1,0,40));


		}

		static void uninit()
		{
			freezed1::on_change -= freeze_1_start;
			freezed1::on_change -= freeze_1_stop;
			freezetimer1::on_change -= freeze_1_timeout;
			freezed5::on_change -= freeze_5_start;
			freezed5::on_change -= freeze_5_stop;
			freezetimer5::on_change -= freeze_5_timeout;
			gamestate::on_change -= game_state_changed;
			gametimer::on_change -= game_timer_expired;

			control_room_controller::uninit();
			desk_controller::uninit();
			desktop_pc::uninit();
			entrance_controller::uninit();
			safe_controller::uninit();
			video_device::uninit();

			freezed1::uninit();
			freezed5::uninit();
			gamestate::uninit();

			room_1_content::chord::uninit();
			room_1_content::event_1::uninit();
			room_1_content::event_2::uninit();
			room_1_content::event_3::uninit();

			ddf::villa::room_1::uninit();
			room_2_content::chord::uninit();

			ddf::villa::room_2::uninit();

			freezetimer1::init();
			freezetimer5::init();
			gametimer::init();

		}
	}

	/// Room junkyard
	namespace junkyard
	{

			/// entrance_controller
			namespace entrance_controller
			{

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::entrance_controller::debouncer";

					static const uint32_t cfg_class_id = 0x400030;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_config> debouncer;

				/// led ///
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::entrance_controller::led";

					static const uint32_t cfg_class_id = 0x400030;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<led_config> led;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::entrance_controller::magnetic_sensor";

					static const uint32_t cfg_class_id = 0x400030;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<magnetic_sensor_config> magnetic_sensor;

				static void init(net::ipv4_address ip)
				{
					debouncer::init(ip);
					debouncer::remote_add(net::ipv4_address(10,1,0,40));

					led::init(ip);
					led::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_sensor::init(ip);
					magnetic_sensor::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					debouncer::uninit();
					led::uninit();
					magnetic_sensor::uninit();

				}
			}

			/// secret_box_controller_1
			namespace secret_box_controller_1
			{

				/// button_grid ///
				struct button_grid_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::button_grid";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::pin_pad<button_grid_config> button_grid;

				/// debouncer_1 ///
				struct debouncer_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_1";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_1_config> debouncer_1;

				/// debouncer_2 ///
				struct debouncer_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_2";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_2_config> debouncer_2;

				/// debouncer_3 ///
				struct debouncer_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_3";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_3_config> debouncer_3;

				/// debouncer_4 ///
				struct debouncer_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_4";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_4_config> debouncer_4;

				/// debouncer_5 ///
				struct debouncer_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_5";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_5_config> debouncer_5;

				/// debouncer_6 ///
				struct debouncer_6_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_6";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0x70;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_6_config> debouncer_6;

				/// debouncer_7 ///
				struct debouncer_7_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_7";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0x80;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_7_config> debouncer_7;

				/// magnetic_lock_1 ///
				struct magnetic_lock_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::magnetic_lock_1";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0x90;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_1_config> magnetic_lock_1;

				/// magnetic_lock_2 ///
				struct magnetic_lock_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::magnetic_lock_2";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0xa0;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_2_config> magnetic_lock_2;

				/// magnetic_lock_3 ///
				struct magnetic_lock_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::magnetic_lock_3";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0xb0;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_3_config> magnetic_lock_3;

				/// magnetic_lock_4 ///
				struct magnetic_lock_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::magnetic_lock_4";

					static const uint32_t cfg_class_id = 0x400010;

					static const uint32_t cfg_member_id = 0xc0;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_4_config> magnetic_lock_4;

				static void init(net::ipv4_address ip)
				{
					button_grid::init(ip);
					button_grid::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_1::init(ip);
					debouncer_1::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_2::init(ip);
					debouncer_2::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_3::init(ip);
					debouncer_3::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_4::init(ip);
					debouncer_4::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_5::init(ip);
					debouncer_5::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_6::init(ip);
					debouncer_6::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_7::init(ip);
					debouncer_7::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_1::init(ip);
					magnetic_lock_1::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_2::init(ip);
					magnetic_lock_2::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_3::init(ip);
					magnetic_lock_3::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_4::init(ip);
					magnetic_lock_4::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					button_grid::uninit();
					debouncer_1::uninit();
					debouncer_2::uninit();
					debouncer_3::uninit();
					debouncer_4::uninit();
					debouncer_5::uninit();
					debouncer_6::uninit();
					debouncer_7::uninit();
					magnetic_lock_1::uninit();
					magnetic_lock_2::uninit();
					magnetic_lock_3::uninit();
					magnetic_lock_4::uninit();

				}
			}

			/// secret_box_controller_2
			namespace secret_box_controller_2
			{

				/// debouncer_1 ///
				struct debouncer_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_1";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_1_config> debouncer_1;

				/// debouncer_2 ///
				struct debouncer_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_2";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_2_config> debouncer_2;

				/// debouncer_3 ///
				struct debouncer_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_3";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_3_config> debouncer_3;

				/// debouncer_4 ///
				struct debouncer_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_4";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_4_config> debouncer_4;

				/// debouncer_5 ///
				struct debouncer_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_5";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_5_config> debouncer_5;

				/// debouncer_6 ///
				struct debouncer_6_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_6";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_6_config> debouncer_6;

				/// debouncer_7 ///
				struct debouncer_7_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_7";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x70;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_7_config> debouncer_7;

				/// debouncer_8 ///
				struct debouncer_8_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_8";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x80;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_8_config> debouncer_8;

				/// debouncer_9 ///
				struct debouncer_9_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_9";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x90;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_9_config> debouncer_9;

				/// debouncer_10 ///
				struct debouncer_10_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_10";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0xa0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_10_config> debouncer_10;

				/// light_controller ///
				struct light_controller_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::light_controller";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0xb0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<light_controller_config> light_controller;

				/// debouncer_12 ///
				struct debouncer_12_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_12";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0xc0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<debouncer_12_config> debouncer_12;

				/// magnetic_lock_1 ///
				struct magnetic_lock_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::magnetic_lock_1";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0xd0;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_1_config> magnetic_lock_1;

				/// magnetic_lock_2 ///
				struct magnetic_lock_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::magnetic_lock_2";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0xe0;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_2_config> magnetic_lock_2;

				/// magnetic_lock_3 ///
				struct magnetic_lock_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::magnetic_lock_3";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0xf0;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_3_config> magnetic_lock_3;

				/// magnetic_lock_4 ///
				struct magnetic_lock_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::magnetic_lock_4";

					static const uint32_t cfg_class_id = 0x400020;

					static const uint32_t cfg_member_id = 0x100;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_4_config> magnetic_lock_4;

				static void init(net::ipv4_address ip)
				{
					debouncer_1::init(ip);
					debouncer_1::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_2::init(ip);
					debouncer_2::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_3::init(ip);
					debouncer_3::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_4::init(ip);
					debouncer_4::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_5::init(ip);
					debouncer_5::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_6::init(ip);
					debouncer_6::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_7::init(ip);
					debouncer_7::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_8::init(ip);
					debouncer_8::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_9::init(ip);
					debouncer_9::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_10::init(ip);
					debouncer_10::remote_add(net::ipv4_address(10,1,0,40));

					light_controller::init(ip);
					light_controller::remote_add(net::ipv4_address(10,1,0,40));

					debouncer_12::init(ip);
					debouncer_12::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_1::init(ip);
					magnetic_lock_1::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_2::init(ip);
					magnetic_lock_2::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_3::init(ip);
					magnetic_lock_3::remote_add(net::ipv4_address(10,1,0,40));

					magnetic_lock_4::init(ip);
					magnetic_lock_4::remote_add(net::ipv4_address(10,1,0,40));


				}

				static void uninit()
				{
					debouncer_1::uninit();
					debouncer_2::uninit();
					debouncer_3::uninit();
					debouncer_4::uninit();
					debouncer_5::uninit();
					debouncer_6::uninit();
					debouncer_7::uninit();
					debouncer_8::uninit();
					debouncer_9::uninit();
					debouncer_10::uninit();
					light_controller::uninit();
					debouncer_12::uninit();
					magnetic_lock_1::uninit();
					magnetic_lock_2::uninit();
					magnetic_lock_3::uninit();
					magnetic_lock_4::uninit();

				}
			}


			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x70;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed1_config> freezed1;

			/// Freezed5 ///
			struct freezed5_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x80;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed5_config> freezed5;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				typedef uint8_t cfg_value_type;

				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x60;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gamestate_config> gamestate;


			/// room_1
			struct room_1_config
			{
                		static const uint8_t cfg_device = 2;
				static const uint8_t cfg_channel = 5;
			};
			typedef wic::audio<room_1_config> room_1;

			namespace room_1_content
			{
				struct chord_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
				};
				typedef wic::audio_effect<chord_config> chord;
				struct event_1_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/junkyard/event_1.wav";

					static const uint32_t cfg_class_id = 0x400050;

					static const uint32_t cfg_member_id = 0x20;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/junkyard/event_2.wav";

					static const uint32_t cfg_class_id = 0x400050;

					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<event_2_config> event_2;

			}

			/// room_2
			struct room_2_config
			{
                		static const uint8_t cfg_device = 2;
				static const uint8_t cfg_channel = 4;
			};
			typedef wic::audio<room_2_config> room_2;

			namespace room_2_content
			{
				struct chord_config
				{
					typedef room_2 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
				};
				typedef wic::audio_effect<chord_config> chord;

			}

			/// FreezeTimer1
			struct freezetimer1_config
			{
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0xa0;
				static const uint32_t cfg_interval  = 3000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0xb0;
				static const uint32_t cfg_interval  = 15000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x90;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;


			void freeze_1_start()
			{
				typedef typename junkyard::freezed1 fr;
				typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,4,14).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_1_stop()
			{
				typedef typename junkyard::freezed1 fr;
				typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,4,15).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_1_timeout()
			{
				typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::freezed1 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,4,16).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void freeze_5_start()
			{
				typedef typename junkyard::freezed5 fr;
				typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,4,17).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_5_stop()
			{
				typedef typename junkyard::freezed5 fr;
				typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,4,18).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_5_timeout()
			{
				typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::freezed5 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,4,19).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void game_state_changed()
			{
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::freezed1 fr1;
				typedef typename junkyard::freezed5 fr5;

				if(true)
				{
					game_event(1,4,13).propagate();
					(void)0; { 
      switch(gs::value())
      {
      	// Not started
      	case 0:
      		tmr::stop();
      		tmr::reset();
      		break;

      	// Started
      	case 1:
      		tmr::start();
      		fr1::value(false);
      		fr5::value(false);
      		break;

      	// Paused
      	case 2:
      		tmr::stop();
      		break;

      	// Finished
      	case 3:
      		tmr::stop();
      		tmr::reset();
      		break;
      }
     }
				}
			}
			void game_timer_expired()
			{
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::gamestate gs;

				if(true && ( tmr::value() >= 3600 ))
				{
					game_event(1,4,12).propagate();
					(void)0; { gs::value(3); }
				}
			}
			void labirynth_1()
			{
				typedef typename junkyard::secret_box_controller_1::debouncer_5 button;
				typedef typename junkyard::secret_box_controller_1::magnetic_lock_4 lock;

				if(true && (  button::value()  ))
				{
					game_event(1,4,20).propagate();
					(void)0; {  lock::value(0);  }
				}
			}
			void labirynth_2()
			{
				typedef typename junkyard::secret_box_controller_1::debouncer_6 button;
				typedef typename junkyard::secret_box_controller_2::magnetic_lock_1 lock;

				if(true && (  button::value()  ))
				{
					game_event(1,4,21).propagate();
					(void)0; {  lock::value(0);  }
				}
			}
			void labirynth_3()
			{
				typedef typename junkyard::secret_box_controller_1::debouncer_7 button;
				typedef typename junkyard::secret_box_controller_2::magnetic_lock_2 lock;

				if(true && (  button::value()  ))
				{
					game_event(1,4,22).propagate();
					(void)0; {  lock::value(0);  }
				}
			}


		static void init()
		{
			entrance_controller::init(net::ipv4_address(10,1,0,71));
			secret_box_controller_1::init(net::ipv4_address(10,1,0,69));
			secret_box_controller_2::init(net::ipv4_address(10,1,0,70));

			freezed1::on_change += freeze_1_start;
			freezed1::on_change += freeze_1_stop;
			freezetimer1::on_change += freeze_1_timeout;
			freezed5::on_change += freeze_5_start;
			freezed5::on_change += freeze_5_stop;
			freezetimer5::on_change += freeze_5_timeout;
			gamestate::on_change += game_state_changed;
			gametimer::on_change += game_timer_expired;
			secret_box_controller_1::debouncer_5::value::on_change += labirynth_1;
			secret_box_controller_1::debouncer_6::value::on_change += labirynth_2;
			secret_box_controller_1::debouncer_7::value::on_change += labirynth_3;

			freezed1::init();
			freezed1::remote_add(net::ipv4_address(10,1,0,40));

			freezed5::init();
			freezed5::remote_add(net::ipv4_address(10,1,0,40));

			gamestate::init();
			gamestate::remote_add(net::ipv4_address(10,1,0,40));


			ddf::junkyard::room_1::init();
			room_1_content::chord::init();
			room_1_content::event_1::init();

			room_1_content::event_2::init();


			ddf::junkyard::room_2::init();
			room_2_content::chord::init();


			freezetimer1::init();
			freezetimer1::remote_add(net::ipv4_address(10,1,0,40));

			freezetimer5::init();
			freezetimer5::remote_add(net::ipv4_address(10,1,0,40));

			gametimer::init();
			gametimer::remote_add(net::ipv4_address(10,1,0,40));


		}

		static void uninit()
		{
			freezed1::on_change -= freeze_1_start;
			freezed1::on_change -= freeze_1_stop;
			freezetimer1::on_change -= freeze_1_timeout;
			freezed5::on_change -= freeze_5_start;
			freezed5::on_change -= freeze_5_stop;
			freezetimer5::on_change -= freeze_5_timeout;
			gamestate::on_change -= game_state_changed;
			gametimer::on_change -= game_timer_expired;
			secret_box_controller_1::debouncer_5::value::on_change -= labirynth_1;
			secret_box_controller_1::debouncer_6::value::on_change -= labirynth_2;
			secret_box_controller_1::debouncer_7::value::on_change -= labirynth_3;

			entrance_controller::uninit();
			secret_box_controller_1::uninit();
			secret_box_controller_2::uninit();

			freezed1::uninit();
			freezed5::uninit();
			gamestate::uninit();

			room_1_content::chord::uninit();
			room_1_content::event_1::uninit();
			room_1_content::event_2::uninit();

			ddf::junkyard::room_1::uninit();
			room_2_content::chord::uninit();

			ddf::junkyard::room_2::uninit();

			freezetimer1::init();
			freezetimer5::init();
			gametimer::init();

		}
	}

	/// Room service
	namespace service
	{

			/// GMClient
			namespace gmclient
			{

				static void init(net::ipv4_address ip)
				{

				}

				static void uninit()
				{

				}
			}






		static void init()
		{
			gmclient::init(net::ipv4_address(10,1,0,40));





		}

		static void uninit()
		{

			gmclient::uninit();




		}
	}

}

template<typename T>
bool set_peripheral(const std::string &x)
{
	if(T::config::name == x)
	{
		typename T::value_type v;
		std::cin >> v;
		if(!std::cin.good())
		{
			std::string y;
			std::cin >> y;
			std::cout << "\e[31;01m[NOK]\e[0m Invalid value `"<<y<<"'" << std::endl;
		}
		else
			std::cout << "\e[32;01m[OK]\e[0m " << (typename T::value(v)) << std::endl;

		return true;
	}

	else
		return false;
}

template<typename T>
bool get_peripheral(const std::string &x)
{
	if(T::config::name == x)
	{
		typename T::value_type v = typename T::value();
		std::cout << "\e[32;01m[OK]\e[0m " << v << std::endl;
		return true;
	}

	else
		return false;
}
int main()
{
	journal::init();

	alsa_host::init();

	process::sql_executor::init();

	wicc_earpc::init();

	devstat::init();
std::cout << "initializing pirate" << std::endl;
	ddf::pirate::init();
std::cout << "initializing magician" << std::endl;
	ddf::magician::init();
std::cout << "initializing villa" << std::endl;
	ddf::villa::init();
std::cout << "initializing junkyard" << std::endl;
	ddf::junkyard::init();
std::cout << "initializing " << std::endl;
	ddf::service::init();


	std::string x;
	while(true)
	{
		std::cin >> x;
		if(x == "exit")
			break;

		else if(x == "1")
			ddf::pirate::room_1_content::chord::play();
		else if(x == "2")
			ddf::pirate::room_2_content::chord::play();
		else if(x == "3")
			ddf::magician::room_1_content::chord::play();
		else if(x == "4")
			ddf::magician::room_2_content::chord::play();
		else if(x == "5")
			ddf::villa::room_1_content::chord::play();
		else if(x == "6")
			ddf::villa::room_2_content::chord::play();
		else if(x == "7")
			ddf::junkyard::room_1_content::chord::play();
		else if(x == "8")
			ddf::junkyard::room_2_content::chord::play();
		else if(x == "delay")
		{
			int delay;
			std::cin >> delay;

			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}

		else if(x == "get")
		{
			std::cin >> x;

			if(get_peripheral<ddf::pirate::map_controller::magnetic_sensor_1>(x)) continue;
			if(get_peripheral<ddf::pirate::map_controller::magnetic_sensor_2>(x)) continue;
			if(get_peripheral<ddf::pirate::stone_chest_controller::magnetic_sensor_1>(x)) continue;
			if(get_peripheral<ddf::pirate::stone_chest_controller::magnetic_sensor_2>(x)) continue;
			if(get_peripheral<ddf::pirate::stone_chest_controller::magnetic_sensor_3>(x)) continue;
			if(get_peripheral<ddf::pirate::stone_chest_controller::magnetic_sensor_4>(x)) continue;
			if(get_peripheral<ddf::pirate::stone_chest_controller::magnetic_sensor_5>(x)) continue;
//			if(get_peripheral<ddf::pirate::cashier_laser_controller::pin_pad>(x)) continue;
			if(get_peripheral<ddf::pirate::cashier_laser_controller::switch_1>(x)) continue;
			if(get_peripheral<ddf::pirate::rex_flipper_controller::photosensor_1>(x)) continue;
			if(get_peripheral<ddf::pirate::rex_flipper_controller::photosensor_2>(x)) continue;
			if(get_peripheral<ddf::pirate::rex_flipper_controller::photosensor_3>(x)) continue;
			if(get_peripheral<ddf::pirate::rex_flipper_controller::photosensor_4>(x)) continue;
			if(get_peripheral<ddf::pirate::rex_flipper_controller::photosensor_5>(x)) continue;
			if(get_peripheral<ddf::pirate::rex_flipper_controller::photosensor_6>(x)) continue;
			if(get_peripheral<ddf::pirate::rex_flipper_controller::photosensor_7>(x)) continue;
			if(get_peripheral<ddf::pirate::rex_flipper_controller::rfid_reader>(x)) continue;
			if(get_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer>(x)) continue;
			if(get_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor>(x)) continue;
			if(get_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor>(x)) continue;
			if(get_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer>(x)) continue;
			if(get_peripheral<ddf::pirate::entrance_hanger_controller::debouncer_1>(x)) continue;
			if(get_peripheral<ddf::pirate::entrance_hanger_controller::magnetic_sensor>(x)) continue;
			if(get_peripheral<ddf::pirate::entrance_hanger_controller::debouncer_2>(x)) continue;
			if(get_peripheral<ddf::magician::cupboard_controller::debouncer>(x)) continue;
			if(get_peripheral<ddf::magician::cupboard_controller::magnetic_sensor>(x)) continue;
			if(get_peripheral<ddf::magician::design_board_controller::linear_magnetic_sensor_1>(x)) continue;
			if(get_peripheral<ddf::magician::design_board_controller::linear_magnetic_sensor_2>(x)) continue;
			if(get_peripheral<ddf::magician::design_board_controller::linear_magnetic_sensor_3>(x)) continue;
			if(get_peripheral<ddf::magician::futuristic_safe_controller::debouncer>(x)) continue;
			if(get_peripheral<ddf::magician::futuristic_safe_controller::rfid_reader>(x)) continue;
//			if(get_peripheral<ddf::magician::futuristic_safe_controller::pin_pad>(x)) continue;
			if(get_peripheral<ddf::magician::entrance_controller::debouncer>(x)) continue;
			if(get_peripheral<ddf::magician::entrance_controller::magnetic_sensor>(x)) continue;
//			if(get_peripheral<ddf::villa::safe_controller::pin_pad>(x)) continue;
			if(get_peripheral<ddf::villa::safe_controller::debouncer_1>(x)) continue;
			if(get_peripheral<ddf::villa::safe_controller::debouncer_2>(x)) continue;
			if(get_peripheral<ddf::villa::desk_controller::debouncer_3>(x)) continue;
			if(get_peripheral<ddf::villa::desk_controller::debouncer_4>(x)) continue;
			if(get_peripheral<ddf::villa::control_room_controller::switch_1>(x)) continue;
			if(get_peripheral<ddf::villa::control_room_controller::rfid>(x)) continue;
			if(get_peripheral<ddf::villa::control_room_controller::debouncer_1>(x)) continue;
			if(get_peripheral<ddf::villa::entrance_controller::debouncer>(x)) continue;
			if(get_peripheral<ddf::villa::entrance_controller::magnetic_sensor>(x)) continue;
//			if(get_peripheral<ddf::junkyard::secret_box_controller_1::button_grid>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_1::debouncer_1>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_1::debouncer_2>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_1::debouncer_3>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_1::debouncer_4>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_1::debouncer_5>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_1::debouncer_6>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_1::debouncer_7>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_1>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_2>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_3>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_4>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_5>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_6>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_7>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_8>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_9>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_10>(x)) continue;
			if(get_peripheral<ddf::junkyard::secret_box_controller_2::debouncer_12>(x)) continue;
//			if(get_peripheral<ddf::junkyard::secret_box_controller_2::spare_in1>(x)) continue;
//			if(get_peripheral<ddf::junkyard::secret_box_controller_2::spare_in2>(x)) continue;
			if(get_peripheral<ddf::junkyard::entrance_controller::debouncer>(x)) continue;
			if(get_peripheral<ddf::junkyard::entrance_controller::magnetic_sensor>(x)) continue;
			std::cout << "\e[31;01m[NOK]\e[0m No such peripheral" << std::endl;
		}

		else if(x == "set")
		{
			std::cin >> x;

			if(set_peripheral<ddf::pirate::map_controller::led_strip>(x)) continue;
			if(set_peripheral<ddf::pirate::stone_chest_controller::magnetic_lock_1>(x)) continue;
			if(set_peripheral<ddf::pirate::stone_chest_controller::magnetic_lock_2>(x)) continue;
			if(set_peripheral<ddf::pirate::stone_chest_controller::led_strip>(x)) continue;
			if(set_peripheral<ddf::pirate::cashier_laser_controller::laser>(x)) continue;
//			if(set_peripheral<ddf::pirate::cashier_laser_controller::lcd>(x)) continue;
			if(set_peripheral<ddf::pirate::cashier_laser_controller::cash_box>(x)) continue;
			if(set_peripheral<ddf::pirate::cashier_laser_controller::led_strip>(x)) continue;
			if(set_peripheral<ddf::pirate::rex_flipper_controller::light_controller_1>(x)) continue;
			if(set_peripheral<ddf::pirate::rex_flipper_controller::light_controller_2>(x)) continue;
			if(set_peripheral<ddf::pirate::rex_flipper_controller::light_controller_3>(x)) continue;
			if(set_peripheral<ddf::pirate::rex_flipper_controller::light_controller_4>(x)) continue;
			if(set_peripheral<ddf::pirate::rex_flipper_controller::light_controller_5>(x)) continue;
			if(set_peripheral<ddf::pirate::rex_flipper_controller::light_controller_6>(x)) continue;
			if(set_peripheral<ddf::pirate::rex_flipper_controller::light_controller_7>(x)) continue;
			if(set_peripheral<ddf::pirate::rex_flipper_controller::magnetic_lock>(x)) continue;
//			if(set_peripheral<ddf::pirate::rex_flipper_controller::led>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2>(x)) continue;
			if(set_peripheral<ddf::pirate::entrance_hanger_controller::led>(x)) continue;
			if(set_peripheral<ddf::magician::cupboard_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::magician::cupboard_controller::led_strip>(x)) continue;
			if(set_peripheral<ddf::magician::design_board_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::magician::futuristic_safe_controller::magnetic_lock>(x)) continue;
//			if(get_peripheral<ddf::magician::futuristic_safe_controller::addressable_led_strip>(x)) continue;
			if(set_peripheral<ddf::magician::entrance_controller::led>(x)) continue;
			if(set_peripheral<ddf::villa::safe_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::villa::control_room_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::villa::control_room_controller::video_eject>(x)) continue;
			if(set_peripheral<ddf::villa::entrance_controller::led>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_1::magnetic_lock_1>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_1::magnetic_lock_2>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_1::magnetic_lock_3>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_1::magnetic_lock_4>(x)) continue;
//			if(get_peripheral<ddf::junkyard::secret_box_controller_1::addressable_led>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::light_controller>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::magnetic_lock_1>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::magnetic_lock_2>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::magnetic_lock_3>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::magnetic_lock_4>(x)) continue;
//			if(set_peripheral<ddf::junkyard::secret_box_controller_2::spare_out1>(x)) continue;
//			if(set_peripheral<ddf::junkyard::secret_box_controller_2::spare_out2>(x)) continue;
			if(set_peripheral<ddf::junkyard::entrance_controller::led>(x)) continue;


			std::cout << "\e[31;01m[NOK]\e[0m No such peripheral" << std::endl;
		}
		else if(x == "play")
		{
			std::cin >> x;
			if(x == "magician")
			{
				std::cin >> x;
				if(x == "1")
					ddf::magician::room_1_content::event_1::playing(true);
				else if(x == "2")
					ddf::magician::room_1_content::event_2::playing(true);
				else
				{
					std::cout << "\e[31;01m[NOK]\e[0m No such sound in magician" << std::endl;
					continue;
				}
				std::cout << "\e[32;01m[OK]\e[0m" << std::endl;
			}
			else if(x == "villa")
			{
				std::cin >> x;
				if(x == "1")
					ddf::villa::room_1_content::event_1::playing(true);
				else if(x == "2")
					ddf::villa::room_1_content::event_2::playing(true);
				else if(x == "3")
					ddf::villa::room_1_content::event_3::playing(true);
				else
				{
					std::cout << "\e[31;01m[NOK]\e[0m No such sound in villa" << std::endl;
					continue;
				}
				std::cout << "\e[32;01m[OK]\e[0m" << std::endl;
			}
			else if(x == "junkyard")
			{
				std::cin >> x;
				if(x == "1")
					ddf::junkyard::room_1_content::event_1::playing(true);
				else if(x == "2")
					ddf::junkyard::room_1_content::event_2::playing(true);
				else
				{
					std::cout << "\e[31;01m[NOK]\e[0m No such sound in magician" << std::endl;
					continue;
				}
				std::cout << "\e[32;01m[OK]\e[0m" << std::endl;
			}
			else
				std::cout << "\e[31;01m[NOK]\e[0m No such room" << std::endl;
		
		}
		else if(x == "show")
		{
			std::cin >> x;
			if(x == "devices")
			{
				for(auto i : devstat::devices())
				{
					std::string sstate;
					const uint8_t state = i.second->get_state();

					if(state == 0)
						sstate = "\e[30;01m(gone)\e[0m";
					else if(state < 96)
						sstate  = "\e[31;01m(poor)\e[0m";
					else if(state < 192)
						sstate = "\e[33;01m(moderate)\e[0m";
					else
						sstate = "\e[32;01m(good)\e[0m";

					
					std::cout << std::hex << i.second->serial << " " << (std::string)i.second->get_ip() << " " << sstate;
					if(state !=  0)
					{
						std::cout << " " << i.second->get_app_name() << " " <<
							(i.second->get_app_state()?"(\e[32mrunning\e[0m)":"(\e[31mnot running\e[0m)");

					}

					std::cout << std::endl;
				}
				std::cout << "\e[32;01m[OK]\e[0m" << std::endl;
			}
			else
				std::cout << "\e[31;01m[NOK]\e[0m No such thing to show" << std::endl;
		}
	}

	ddf::pirate::uninit();
	ddf::magician::uninit();
	ddf::villa::uninit();
	ddf::junkyard::uninit();
	ddf::service::uninit();


	journal::uninit();
	return 0;
}

