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
#include <oosp/local_property.h>
#include <oosp/remote_property.h>
#include <oosp/forward_property.h>
#include <property_config_base.h>
#include <device_role.h>
#include <process/sql_executor.h>
#include <devman/devman.h>

#include <status.h>
#include <event.h>

#include <audio.h>
#include <audio_effect.h>
#include <audio_speech.h>
#include <video.h>
#include <video_colorsensor.h>
#include <timer.h>

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


struct dm_config
{
	typedef wicc_earpc cfg_earpc;

	static const uint32_t cfg_expiry_timeout = 3200;
};
typedef devman::devman<dm_config> dm;

/// Site DDF
namespace ddf
{

	/// Room pirate
	namespace pirate
	{

			/// cashier_laser_controller
			namespace cashier_laser_controller
			{
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
				typedef peripheral::power_switch<cash_box_config> cash_box;

				/// switch_1 ///
				struct switch_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::cashier_laser_controller::switch_1";
					static const uint32_t cfg_class_id = 0x100030;
					static const uint32_t cfg_member_id = 0x50;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<switch_1_config> switch_1;

				/// led_strip ///
				struct led_strip_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::cashier_laser_controller::led_strip";
					static const uint32_t cfg_class_id = 0x100030;
					static const uint32_t cfg_member_id = 0x60;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<led_strip_config> led_strip;

				/// buzzer ///
				struct buzzer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::cashier_laser_controller::buzzer";
					static const uint32_t cfg_class_id = 0x100030;
					static const uint32_t cfg_member_id = 0x70;
					static const uint32_t cfg_cooldown_time = 20;
				};
				typedef peripheral::buzzer<buzzer_config> buzzer;

			}

			/// entrance_hanger_controller
			namespace entrance_hanger_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - pirate - entrance_hanger_controller";
					static const uint32_t cfg_class_id = 0x100060;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::entrance_hanger_controller::debouncer";
					static const uint32_t cfg_class_id = 0x100060;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_config> debouncer;

				/// led ///
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::entrance_hanger_controller::led";
					static const uint32_t cfg_class_id = 0x100060;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::led_strip<led_config> led;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::entrance_hanger_controller::magnetic_sensor";
					static const uint32_t cfg_class_id = 0x100060;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_config> magnetic_sensor;

				/// debouncer_2 ///
				struct debouncer_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::entrance_hanger_controller::debouncer_2";
					static const uint32_t cfg_class_id = 0x100060;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_2_config> debouncer_2;

			}

			/// ghostbox_picture_laser_boat_wheel_controller
			namespace ghostbox_picture_laser_boat_wheel_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - pirate - ghostbox_picture_laser_boat_wheel_controller";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// magnetic_lock_1 ///
				struct magnetic_lock_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_1_config> magnetic_lock_1;

				/// magnetic_lock_2 ///
				struct magnetic_lock_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_2_config> magnetic_lock_2;

				/// magnetic_lock_3 ///
				struct magnetic_lock_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_3_config> magnetic_lock_3;

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_config> debouncer;

				/// photosensor ///
				struct photosensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint32_t cfg_member_id = 0x50;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::laser_sensor<photosensor_config> photosensor;

				/// knock_sensor ///
				struct knock_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint32_t cfg_member_id = 0x60;
					static const uint32_t cfg_cooldown_time = 100;
				};
				typedef peripheral::knock_sensor<knock_sensor_config> knock_sensor;

				/// led_strip_1 ///
				struct led_strip_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint32_t cfg_member_id = 0x70;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::led_strip<led_strip_1_config> led_strip_1;

				/// led_strip_2 ///
				struct led_strip_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint32_t cfg_member_id = 0x80;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::led_strip<led_strip_2_config> led_strip_2;

				/// potentiometer ///
				struct potentiometer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer";
					static const uint32_t cfg_class_id = 0x100050;
					static const uint32_t cfg_member_id = 0x90;
					static const uint32_t cfg_cooldown_time = 40;
				};
				typedef peripheral::potentiometer<potentiometer_config> potentiometer;

			}

			/// map_controller
			namespace map_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - pirate - map_controller";
					static const uint32_t cfg_class_id = 0x100010;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// magnetic_sensor_1 ///
				struct magnetic_sensor_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::map_controller::magnetic_sensor_1";
					static const uint32_t cfg_class_id = 0x100010;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::polarity_sensor<magnetic_sensor_1_config> magnetic_sensor_1;

				/// magnetic_sensor_2 ///
				struct magnetic_sensor_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::map_controller::magnetic_sensor_2";
					static const uint32_t cfg_class_id = 0x100010;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::polarity_sensor<magnetic_sensor_2_config> magnetic_sensor_2;

				/// led_strip ///
				struct led_strip_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::map_controller::led_strip";
					static const uint32_t cfg_class_id = 0x100010;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 40;
				};
				typedef peripheral::dimmable_led_strip<led_strip_config> led_strip;

			}

			/// rex_flipper_controller
			namespace rex_flipper_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - pirate - rex_flipper_controller";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// light_controller_1 ///
				struct light_controller_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_1";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<light_controller_1_config> light_controller_1;

				/// light_controller_2 ///
				struct light_controller_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_2";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<light_controller_2_config> light_controller_2;

				/// light_controller_3 ///
				struct light_controller_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_3";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<light_controller_3_config> light_controller_3;

				/// light_controller_4 ///
				struct light_controller_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_4";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<light_controller_4_config> light_controller_4;

				/// light_controller_5 ///
				struct light_controller_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_5";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x50;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<light_controller_5_config> light_controller_5;

				/// light_controller_6 ///
				struct light_controller_6_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_6";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x60;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<light_controller_6_config> light_controller_6;

				/// light_controller_7 ///
				struct light_controller_7_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::light_controller_7";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x70;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<light_controller_7_config> light_controller_7;

				/// photosensor_1 ///
				struct photosensor_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_1";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x80;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::ir_sensor<photosensor_1_config> photosensor_1;

				/// photosensor_2 ///
				struct photosensor_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_2";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x90;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::ir_sensor<photosensor_2_config> photosensor_2;

				/// photosensor_3 ///
				struct photosensor_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_3";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0xa0;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::ir_sensor<photosensor_3_config> photosensor_3;

				/// photosensor_4 ///
				struct photosensor_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_4";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0xb0;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::ir_sensor<photosensor_4_config> photosensor_4;

				/// photosensor_5 ///
				struct photosensor_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_5";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0xc0;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::ir_sensor<photosensor_5_config> photosensor_5;

				/// photosensor_6 ///
				struct photosensor_6_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_6";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0xd0;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::ir_sensor<photosensor_6_config> photosensor_6;

				/// photosensor_7 ///
				struct photosensor_7_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::photosensor_7";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0xe0;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::ir_sensor<photosensor_7_config> photosensor_7;

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
				typedef peripheral::magnetic_lock<magnetic_lock_config> magnetic_lock;
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::led";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x110;
					static const uint32_t cfg_cooldown_time = 50;
					static const uint32_t cfg_led_count = 3;
				};
				typedef peripheral::addressable_led_strip<led_config> led;

			}

			/// stone_chest_controller
			namespace stone_chest_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - pirate - stone_chest_controller";
					static const uint32_t cfg_class_id = 0x100020;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// magnetic_sensor_1 ///
				struct magnetic_sensor_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_1";
					static const uint32_t cfg_class_id = 0x100020;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_1_config> magnetic_sensor_1;

				/// magnetic_sensor_2 ///
				struct magnetic_sensor_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_2";
					static const uint32_t cfg_class_id = 0x100020;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_2_config> magnetic_sensor_2;

				/// magnetic_sensor_3 ///
				struct magnetic_sensor_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_3";
					static const uint32_t cfg_class_id = 0x100020;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_3_config> magnetic_sensor_3;

				/// magnetic_sensor_4 ///
				struct magnetic_sensor_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_4";
					static const uint32_t cfg_class_id = 0x100020;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_4_config> magnetic_sensor_4;

				/// magnetic_sensor_5 ///
				struct magnetic_sensor_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_sensor_5";
					static const uint32_t cfg_class_id = 0x100020;
					static const uint32_t cfg_member_id = 0x50;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_5_config> magnetic_sensor_5;

				/// magnetic_lock_1 ///
				struct magnetic_lock_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_lock_1";
					static const uint32_t cfg_class_id = 0x100020;
					static const uint32_t cfg_member_id = 0x60;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_1_config> magnetic_lock_1;

				/// magnetic_lock_2 ///
				struct magnetic_lock_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::magnetic_lock_2";
					static const uint32_t cfg_class_id = 0x100020;
					static const uint32_t cfg_member_id = 0x70;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_2_config> magnetic_lock_2;

				/// led_strip ///
				struct led_strip_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::stone_chest_controller::led_strip";
					static const uint32_t cfg_class_id = 0x100020;
					static const uint32_t cfg_member_id = 0x80;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::led_strip<led_strip_config> led_strip;

			}


			/// Audio Message URL ///
			struct audio_message_url_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::audio_message_url";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x110;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<audio_message_url_config> audio_message_url;

			/// ComDev Reset ///
			struct comdev_reset_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::comdev_reset";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0xf0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<comdev_reset_config> comdev_reset;

			/// ComDev Silence ///
			struct comdev_silence_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::comdev_silence";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x100;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<comdev_silence_config> comdev_silence;

			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::freezed1";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x160;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<freezed1_config> freezed1;

			/// Freezed5 ///
			struct freezed5_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::freezed5";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x170;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<freezed5_config> freezed5;

			/// GM Help Status ///
			struct gm_help_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::gm_help_status";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0xa0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gm_help_status_config> gm_help_status;

			/// GameEnd ///
			struct gameend_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::gameend";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x140;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gameend_config> gameend;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::gamestate";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x130;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gamestate_config> gamestate;

			/// Incoming Call ///
			struct incoming_call_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::incoming_call";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0xb0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<incoming_call_config> incoming_call;

			/// Incoming Call Status ///
			struct incoming_call_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::incoming_call_status";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0xc0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<incoming_call_status_config> incoming_call_status;

			/// Paused ///
			struct paused_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::paused";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x150;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<paused_config> paused;

			/// Restart Game ///
			struct restart_game_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::restart_game";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<restart_game_config> restart_game;

			/// Text Message ///
			struct text_message_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::text_message";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0xd0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<text_message_config> text_message;

			/// Text Message Sender ///
			struct text_message_sender_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::text_message_sender";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0xe0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<text_message_sender_config> text_message_sender;

			/// knock_count ///
			struct knock_count_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::knock_count";
				typedef uint32_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x560;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<knock_count_config> knock_count;

			/// map_sensor1_triggered ///
			struct map_sensor1_triggered_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::map_sensor1_triggered";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x5c0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<map_sensor1_triggered_config> map_sensor1_triggered;

			/// map_sensor2_triggered ///
			struct map_sensor2_triggered_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::map_sensor2_triggered";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x5d0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<map_sensor2_triggered_config> map_sensor2_triggered;

			/// pin_code ///
			struct pin_code_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::pin_code";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x4f0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<pin_code_config> pin_code;

			/// rex_enabled ///
			struct rex_enabled_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_enabled";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x320;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_enabled_config> rex_enabled;

			/// rex_left_column_failure ///
			struct rex_left_column_failure_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_left_column_failure";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x380;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_left_column_failure_config> rex_left_column_failure;

			/// rex_middle_column_failure ///
			struct rex_middle_column_failure_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_middle_column_failure";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x390;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_middle_column_failure_config> rex_middle_column_failure;

			/// rex_photosensor_4_value ///
			struct rex_photosensor_4_value_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_photosensor_4_value";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x340;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_photosensor_4_value_config> rex_photosensor_4_value;

			/// rex_photosensor_5_value ///
			struct rex_photosensor_5_value_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_photosensor_5_value";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x350;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_photosensor_5_value_config> rex_photosensor_5_value;

			/// rex_photosensor_6_value ///
			struct rex_photosensor_6_value_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_photosensor_6_value";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x360;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_photosensor_6_value_config> rex_photosensor_6_value;

			/// rex_photosensor_7_value ///
			struct rex_photosensor_7_value_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_photosensor_7_value";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x370;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_photosensor_7_value_config> rex_photosensor_7_value;

			/// rex_right_column_failure ///
			struct rex_right_column_failure_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_right_column_failure";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x3a0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_right_column_failure_config> rex_right_column_failure;

			/// rex_score ///
			struct rex_score_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_score";
				typedef uint32_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x310;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_score_config> rex_score;

			/// rex_trials_left ///
			struct rex_trials_left_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::rex_trials_left";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x330;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rex_trials_left_config> rex_trials_left;

			/// star_value ///
			struct star_value_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::star_value";
				typedef uint16_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x640;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<star_value_config> star_value;

			/// timedevent_an_1 ///
			struct timedevent_an_1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_1";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x720;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_an_1_config> timedevent_an_1;

			/// timedevent_an_2 ///
			struct timedevent_an_2_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_2";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x7a0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_an_2_config> timedevent_an_2;

			/// timedevent_an_3 ///
			struct timedevent_an_3_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_3";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x820;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_an_3_config> timedevent_an_3;

			/// timedevent_ghost_voice ///
			struct timedevent_ghost_voice_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::timedevent_ghost_voice";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x6d0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_ghost_voice_config> timedevent_ghost_voice;

			/// timedevent_pc_1 ///
			struct timedevent_pc_1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::timedevent_pc_1";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x760;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_pc_1_config> timedevent_pc_1;

			/// timedevent_pc_2 ///
			struct timedevent_pc_2_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::timedevent_pc_2";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x7e0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_pc_2_config> timedevent_pc_2;

			/// wheel_last_pos ///
			struct wheel_last_pos_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::wheel_last_pos";
				typedef uint16_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x630;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<wheel_last_pos_config> wheel_last_pos;


			/// room_1
			struct room_1_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 1;
			};
			typedef wic::audio<room_1_config> room_1;

			namespace room_1_content
			{
				struct chord_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::chord";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<chord_config> chord;
				struct progress_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::progress";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/progress.wav";
					constexpr static const float cfg_gain = 1.3;
				};
				typedef wic::audio_effect<progress_config> progress;
				struct careful_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::careful";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/careful.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<careful_config> careful;
				struct event_1_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::event_1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Wetter_1.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0x90;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::event_2";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Wetter_2.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0xa0;
				};
				typedef wic::audio_speech<event_2_config> event_2;
				struct event_3_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::event_3";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_InGame_Joe_Track1+2.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0xb0;
				};
				typedef wic::audio_speech<event_3_config> event_3;
				struct failstate_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::failstate";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Failstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0x70;
				};
				typedef wic::audio_speech<failstate_config> failstate;
				struct gminc_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::gminc";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/gminc.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0x60;
				};
				typedef wic::audio_speech<gminc_config> gminc;
				struct ghost_voice_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::ghost_voice";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Joe_verzerrt.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0xc0;
				};
				typedef wic::audio_speech<ghost_voice_config> ghost_voice;
				struct rules_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::rules";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/rules.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0x40;
				};
				typedef wic::audio_speech<rules_config> rules;
				struct techdiff_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::techdiff";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/techdiff.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0x50;
				};
				typedef wic::audio_speech<techdiff_config> techdiff;
				struct winstate_config
				{
					constexpr static const char *name = "ddf::pirate::room_1_content::winstate";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Winstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100080;
					static const uint32_t cfg_member_id = 0x80;
				};
				typedef wic::audio_speech<winstate_config> winstate;

			}

			/// room_2
			struct room_2_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 0;
			};
			typedef wic::audio<room_2_config> room_2;

			namespace room_2_content
			{
				struct chord_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::chord";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<chord_config> chord;
				struct progress_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::progress";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/progress.wav";
					constexpr static const float cfg_gain = 1.3;
				};
				typedef wic::audio_effect<progress_config> progress;
				struct careful_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::careful";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/careful.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<careful_config> careful;
				struct event_1_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::event_1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Wetter_1.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0x90;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::event_2";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Wetter_2.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0xa0;
				};
				typedef wic::audio_speech<event_2_config> event_2;
				struct event_3_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::event_3";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_InGame_Joe_Track1+2.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0xb0;
				};
				typedef wic::audio_speech<event_3_config> event_3;
				struct failstate_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::failstate";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Failstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0x70;
				};
				typedef wic::audio_speech<failstate_config> failstate;
				struct gminc_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::gminc";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/gminc.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0x60;
				};
				typedef wic::audio_speech<gminc_config> gminc;
				struct ghost_voice_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::ghost_voice";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Joe_verzerrt.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0xc0;
				};
				typedef wic::audio_speech<ghost_voice_config> ghost_voice;
				struct rules_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::rules";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/rules.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0x40;
				};
				typedef wic::audio_speech<rules_config> rules;
				struct techdiff_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::techdiff";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/techdiff.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0x50;
				};
				typedef wic::audio_speech<techdiff_config> techdiff;
				struct winstate_config
				{
					constexpr static const char *name = "ddf::pirate::room_2_content::winstate";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Pirate/DDF_EscapeRoom_Geisterpiraten_Winstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x100070;
					static const uint32_t cfg_member_id = 0x80;
				};
				typedef wic::audio_speech<winstate_config> winstate;

			}


			/// tray_camera
			struct tray_camera_config
			{
				constexpr static const char *name = "ddf::pirate::tray_camera";
				constexpr static const char *cfg_source = "rtsp://admin:kewRefuD2s@10.50.66.12:554";
			};
			typedef wic::video<tray_camera_config> tray_camera;

			namespace tray_camera_content
			{
				struct tray_sensor_config
				{
					constexpr static const char *name = "ddf::pirate::tray_camera_content::tray_sensor";
					typedef tray_camera cfg_video;
					static const uint32_t cfg_class_id = 0x100120;
					static const uint32_t cfg_member_id = 0x10;
					static const std::initializer_list<::video::color_checker::area> cfg_areas;
				};
				const std::initializer_list<::video::color_checker::area> tray_sensor_config::cfg_areas = {
						::video::color_checker::area(676,258,68,68,6040352,10),
						::video::color_checker::area(769,250,51,51,5711904,10),
						::video::color_checker::area(715,238,61,61,5121050,10),
						::video::color_checker::area(736,230,32,32,1905422,10)
				};
				typedef wic::video_colorsensor<tray_sensor_config> tray_sensor;

			}

			/// FreezeTimer1
			struct freezetimer1_config
			{
				constexpr static const char *name = "ddf::pirate::freezetimer1";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x190;
				static const uint32_t cfg_interval  = 60000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				constexpr static const char *name = "ddf::pirate::freezetimer5";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1a0;
				static const uint32_t cfg_interval  = 300000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				constexpr static const char *name = "ddf::pirate::gametimer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x180;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;

			/// ghost_blink_timer
			struct ghost_blink_timer_config
			{
				constexpr static const char *name = "ddf::pirate::ghost_blink_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x6c0;
				static const uint32_t cfg_interval  = 200;
			};
			typedef typename wic::timer<ghost_blink_timer_config> ghost_blink_timer;

			/// knock_timer
			struct knock_timer_config
			{
				constexpr static const char *name = "ddf::pirate::knock_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x570;
				static const uint32_t cfg_interval  = 1500;
			};
			typedef typename wic::timer<knock_timer_config> knock_timer;

			/// pin_timeout_timer
			struct pin_timeout_timer_config
			{
				constexpr static const char *name = "ddf::pirate::pin_timeout_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x500;
				static const uint32_t cfg_interval  = 2500;
			};
			typedef typename wic::timer<pin_timeout_timer_config> pin_timeout_timer;

			/// rex_blink_timer
			struct rex_blink_timer_config
			{
				constexpr static const char *name = "ddf::pirate::rex_blink_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x460;
				static const uint32_t cfg_interval  = 300;
			};
			typedef typename wic::timer<rex_blink_timer_config> rex_blink_timer;

			/// timedevent_an_1_timer
			struct timedevent_an_1_timer_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_1_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x730;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_an_1_timer_config> timedevent_an_1_timer;

			/// timedevent_an_2_timer
			struct timedevent_an_2_timer_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_2_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x7b0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_an_2_timer_config> timedevent_an_2_timer;

			/// timedevent_an_3_timer
			struct timedevent_an_3_timer_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_3_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x830;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_an_3_timer_config> timedevent_an_3_timer;

			/// timedevent_ghost_voice_timer
			struct timedevent_ghost_voice_timer_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_ghost_voice_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x6e0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_ghost_voice_timer_config> timedevent_ghost_voice_timer;

			/// timedevent_pc_1_timer
			struct timedevent_pc_1_timer_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_pc_1_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x770;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_pc_1_timer_config> timedevent_pc_1_timer;

			/// timedevent_pc_2_timer
			struct timedevent_pc_2_timer_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_pc_2_timer";
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x7f0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_pc_2_timer_config> timedevent_pc_2_timer;



			/// artificial_game_ending ///		
			struct artificial_game_ending_config
			{
				constexpr static const char *name = "ddf::pirate::artificial_game_ending";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x210;
				static bool cfg_condition()
				{
				typedef typename pirate::gameend ge;
					typedef typename pirate::entrance_hanger_controller::led led;
					return (true && ( 
				led::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gameend ge;
					typedef typename pirate::entrance_hanger_controller::led led;
	
(void)0; {  
				ge::value(1);
			 }
				}
			};
			typedef wic::event<artificial_game_ending_config> artificial_game_ending;

			/// cashier_pin_timeout ///		
			struct cashier_pin_timeout_config
			{
				constexpr static const char *name = "ddf::pirate::cashier_pin_timeout";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x520;
				static bool cfg_condition()
				{
				typedef typename pirate::pin_timeout_timer timer;
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::cash_box box;
					typedef typename pirate::cashier_laser_controller::buzzer buzzer;
					return (true && (  timer::value()  ));
				}
				static void cfg_action()
				{
				typedef typename pirate::pin_timeout_timer timer;
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::cash_box box;
					typedef typename pirate::cashier_laser_controller::buzzer buzzer;
	
(void)0; { 
			timer::stop();
			timer::reset();
			if(box::value())
				box::value(0);
			else
				buzzer::beep(200,200);
			code::value("");
		 }
				}
			};
			typedef wic::event<cashier_pin_timeout_config> cashier_pin_timeout;

			/// display_update ///		
			struct display_update_config
			{
				constexpr static const char *name = "ddf::pirate::display_update";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x550;
				static bool cfg_condition()
				{
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::lcd lcd;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::lcd lcd;
	
(void)0; { 
			lcd::value(code::value());
		 }
				}
			};
			typedef wic::event<display_update_config> display_update;

			/// freeze_1 ///		
			struct freeze_1_config
			{
				constexpr static const char *name = "ddf::pirate::freeze_1";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1c0;
				static bool cfg_condition()
				{
				typedef typename pirate::freezed1 fr;
				typedef typename pirate::gamestate gs;
				typedef typename pirate::freezetimer1 tmr;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::freezed1 fr;
				typedef typename pirate::gamestate gs;
				typedef typename pirate::freezetimer1 tmr;
	
(void)0; { 
				if(fr::value())
					tmr::start();
				else
				{
					tmr::stop();
					tmr::reset();
				}
			 }
				}
			};
			typedef wic::event<freeze_1_config> freeze_1;

			/// freeze_1_timeout ///		
			struct freeze_1_timeout_config
			{
				constexpr static const char *name = "ddf::pirate::freeze_1_timeout";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1d0;
				static bool cfg_condition()
				{
				typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::freezed1 fr;
					return (true && ( 
				tmr::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::freezed1 fr;
	
(void)0; { 
				fr::value(false);
			 }
				}
			};
			typedef wic::event<freeze_1_timeout_config> freeze_1_timeout;

			/// freeze_5 ///		
			struct freeze_5_config
			{
				constexpr static const char *name = "ddf::pirate::freeze_5";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1e0;
				static bool cfg_condition()
				{
				typedef typename pirate::freezed5 fr;
				typedef typename pirate::gamestate gs;
				typedef typename pirate::freezetimer5 tmr;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::freezed5 fr;
				typedef typename pirate::gamestate gs;
				typedef typename pirate::freezetimer5 tmr;
	
(void)0; { 
				if(fr::value())
					tmr::start();
				else
				{
					tmr::stop();
					tmr::reset();
				}
			 }
				}
			};
			typedef wic::event<freeze_5_config> freeze_5;

			/// freeze_5_timeout ///		
			struct freeze_5_timeout_config
			{
				constexpr static const char *name = "ddf::pirate::freeze_5_timeout";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1f0;
				static bool cfg_condition()
				{
				typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::freezed5 fr;
					return (true && ( 
				tmr::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::freezed5 fr;
	
(void)0; { 
				fr::value(false);
			 }
				}
			};
			typedef wic::event<freeze_5_timeout_config> freeze_5_timeout;

			/// game_end_button_push ///		
			struct game_end_button_push_config
			{
				constexpr static const char *name = "ddf::pirate::game_end_button_push";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x220;
				static bool cfg_condition()
				{
					typedef typename pirate::entrance_hanger_controller::debouncer button;
				typedef typename pirate::gameend ge;
				typedef typename pirate::gamestate gs;
				typedef typename pirate::comdev_silence cs;
			typedef room_1_content::winstate winstate_room_1;
			typedef room_2_content::winstate winstate_room_2;
				typedef typename pirate::gametimer tmr;
					return (true && ( 
				button::value() && 1 == ge::value() && 1 == gs::value()
			 ));
				}
				static void cfg_action()
				{
					typedef typename pirate::entrance_hanger_controller::debouncer button;
				typedef typename pirate::gameend ge;
				typedef typename pirate::gamestate gs;
				typedef typename pirate::comdev_silence cs;
			typedef room_1_content::winstate winstate_room_1;
			typedef room_2_content::winstate winstate_room_2;
				typedef typename pirate::gametimer tmr;
	
(void)0; { 
				tmr::stop();
				cs::value(1);
				winstate_room_1::play();
				winstate_room_2::play();
				gs::value(3);
			 }
				}
			};
			typedef wic::event<game_end_button_push_config> game_end_button_push;

			/// game_ending ///		
			struct game_ending_config
			{
				constexpr static const char *name = "ddf::pirate::game_ending";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x200;
				static bool cfg_condition()
				{
				typedef typename pirate::gameend ge;
					typedef typename pirate::entrance_hanger_controller::led led;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::gameend ge;
					typedef typename pirate::entrance_hanger_controller::led led;
	
(void)0; {  
				led::value(1 == ge::value());
			 }
				}
			};
			typedef wic::event<game_ending_config> game_ending;

			/// game_pause_mgmt ///		
			struct game_pause_mgmt_config
			{
				constexpr static const char *name = "ddf::pirate::game_pause_mgmt";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1b0;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::paused p;
				typedef typename pirate::freezed1 f1;
				typedef typename pirate::freezed5 f5;
				typedef typename pirate::gm_help_status gm;
					typedef typename pirate::entrance_hanger_controller::magnetic_sensor ed;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::paused p;
				typedef typename pirate::freezed1 f1;
				typedef typename pirate::freezed5 f5;
				typedef typename pirate::gm_help_status gm;
					typedef typename pirate::entrance_hanger_controller::magnetic_sensor ed;
	
(void)0; { 
				if(ed::value() && !p::value() && !f1::value() && !f5::value() && !gm::value())
				{
					if(gs::value() == 2)
					{
						gs::value(1);
					}
				}
				else if(gs::value() == 1)
				{
					gs::value(2);
				}
			 }
				}
			};
			typedef wic::event<game_pause_mgmt_config> game_pause_mgmt;

			/// gameevent_boat_door_opened ///		
			struct gameevent_boat_door_opened_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_boat_door_opened";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x4d0;
				static bool cfg_condition()
				{
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3 boat_door;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && (  !boat_door::value()  ));
				}
				static void cfg_action()
				{
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3 boat_door;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; { 
			progress_1::play();
			progress_2::play();
		 }
				}
			};
			typedef wic::event<gameevent_boat_door_opened_config> gameevent_boat_door_opened;

			/// gameevent_bright_star ///		
			struct gameevent_bright_star_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_bright_star";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x660;
				static bool cfg_condition()
				{
				typedef typename pirate::star_value sv;
					return (true && ( 
		0x40 == sv::value()
	 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::star_value sv;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_bright_star_config> gameevent_bright_star;

			/// gameevent_brightest_star ///		
			struct gameevent_brightest_star_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_brightest_star";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x670;
				static bool cfg_condition()
				{
				typedef typename pirate::star_value sv;
					return (true && ( 
		0xffff == sv::value()
	 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::star_value sv;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_brightest_star_config> gameevent_brightest_star;

			/// gameevent_call_accepted ///		
			struct gameevent_call_accepted_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_call_accepted";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x2b0;
				static bool cfg_condition()
				{
				typedef typename pirate::incoming_call_status cs;
					return (true && ( 
				2 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_accepted_config> gameevent_call_accepted;

			/// gameevent_call_declined ///		
			struct gameevent_call_declined_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_call_declined";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x2c0;
				static bool cfg_condition()
				{
				typedef typename pirate::incoming_call_status cs;
					return (true && ( 
				3 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_declined_config> gameevent_call_declined;

			/// gameevent_call_finished ///		
			struct gameevent_call_finished_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_call_finished";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x2d0;
				static bool cfg_condition()
				{
				typedef typename pirate::incoming_call_status cs;
					return (true && ( 
				4 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_finished_config> gameevent_call_finished;

			/// gameevent_call_missed ///		
			struct gameevent_call_missed_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_call_missed";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x2e0;
				static bool cfg_condition()
				{
				typedef typename pirate::incoming_call_status cs;
					return (true && ( 
				5 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_missed_config> gameevent_call_missed;

			/// gameevent_call_ringing ///		
			struct gameevent_call_ringing_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_call_ringing";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x2a0;
				static bool cfg_condition()
				{
				typedef typename pirate::incoming_call_status cs;
					return (true && ( 
				1 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_ringing_config> gameevent_call_ringing;

			/// gameevent_cashier_code_mistaken ///		
			struct gameevent_cashier_code_mistaken_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_cashier_code_mistaken";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x530;
				static bool cfg_condition()
				{
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::cash_box box;
					typedef typename pirate::cashier_laser_controller::buzzer buzzer;
				typedef typename pirate::pin_timeout_timer timer;
					return (true && (  ((std::string)code::value()).size() >= 4  && (std::string)code::value() != "8271"  ));
				}
				static void cfg_action()
				{
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::cash_box box;
					typedef typename pirate::cashier_laser_controller::buzzer buzzer;
				typedef typename pirate::pin_timeout_timer timer;
	
(void)0; { 
			buzzer::beep(200,200);
			code::value("");
			timer::stop();
			timer::reset();
		 }
				}
			};
			typedef wic::event<gameevent_cashier_code_mistaken_config> gameevent_cashier_code_mistaken;

			/// gameevent_cashier_opened ///		
			struct gameevent_cashier_opened_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_cashier_opened";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x540;
				static bool cfg_condition()
				{
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::cash_box box;
					typedef typename pirate::cashier_laser_controller::buzzer buzzer;
					return (true && (  ((std::string)code::value()).size() >= 4  && (std::string)code::value() == "8271"  ));
				}
				static void cfg_action()
				{
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::cash_box box;
					typedef typename pirate::cashier_laser_controller::buzzer buzzer;
	
(void)0; { 
			buzzer::beep(800,200);
			code::value("");
			box::value(1);
		 }
				}
			};
			typedef wic::event<gameevent_cashier_opened_config> gameevent_cashier_opened;

			/// gameevent_chest_opening ///		
			struct gameevent_chest_opening_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_chest_opening";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x6b0;
				static bool cfg_condition()
				{
					typedef typename pirate::stone_chest_controller::led_strip chest;
					typedef typename pirate::stone_chest_controller::magnetic_sensor_5 chest_opening_sensor;
					typedef typename pirate::entrance_hanger_controller::debouncer_2 game_end_button;
				typedef typename pirate::gameend ge;
					return (true && (  
	    	!chest_opening_sensor::value() 
	     ));
				}
				static void cfg_action()
				{
					typedef typename pirate::stone_chest_controller::led_strip chest;
					typedef typename pirate::stone_chest_controller::magnetic_sensor_5 chest_opening_sensor;
					typedef typename pirate::entrance_hanger_controller::debouncer_2 game_end_button;
				typedef typename pirate::gameend ge;
	
(void)0; { 
	        chest::value(1);
	        ge::value(1);
	     }
				}
			};
			typedef wic::event<gameevent_chest_opening_config> gameevent_chest_opening;

			/// gameevent_game_fail ///		
			struct gameevent_game_fail_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_game_fail";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x290;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gameend ge;
					return (true && ( 
				3 == gs::value() && 2 == ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gameend ge;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_game_fail_config> gameevent_game_fail;

			/// gameevent_game_finished ///		
			struct gameevent_game_finished_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_game_finished";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x260;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gametimer tmr;
					return (true && ( 
				3 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gametimer tmr;
	
(void)0; { 
				tmr::stop();
				tmr::reset();
			 }
				}
			};
			typedef wic::event<gameevent_game_finished_config> gameevent_game_finished;

			/// gameevent_game_paused ///		
			struct gameevent_game_paused_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_game_paused";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x250;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gametimer tmr;
					return (true && ( 
				2 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gametimer tmr;
	
(void)0; { 
				tmr::stop();
			 }
				}
			};
			typedef wic::event<gameevent_game_paused_config> gameevent_game_paused;

			/// gameevent_game_reset ///		
			struct gameevent_game_reset_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_game_reset";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x270;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gameend ge;
				typedef typename pirate::text_message_sender cd_sender;
				typedef typename pirate::text_message cd_text;
				typedef typename pirate::gm_help_status cd_gmhelp;
				typedef typename pirate::incoming_call cd_call;
				typedef typename pirate::incoming_call_status cd_callstat;
				typedef typename pirate::audio_message_url cd_url;
				typedef typename pirate::comdev_reset cd_reset;
				typedef typename pirate::freezed1 fr1;
				typedef typename pirate::freezed5 fr5;
				typedef typename pirate::paused paused;
				typedef typename pirate::gametimer tmr;
				typedef typename pirate::freezetimer1 frtmr1;
				typedef typename pirate::freezetimer5 frtmr5;
					return (true && ( 
				0 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gameend ge;
				typedef typename pirate::text_message_sender cd_sender;
				typedef typename pirate::text_message cd_text;
				typedef typename pirate::gm_help_status cd_gmhelp;
				typedef typename pirate::incoming_call cd_call;
				typedef typename pirate::incoming_call_status cd_callstat;
				typedef typename pirate::audio_message_url cd_url;
				typedef typename pirate::comdev_reset cd_reset;
				typedef typename pirate::freezed1 fr1;
				typedef typename pirate::freezed5 fr5;
				typedef typename pirate::paused paused;
				typedef typename pirate::gametimer tmr;
				typedef typename pirate::freezetimer1 frtmr1;
				typedef typename pirate::freezetimer5 frtmr5;
	
(void)0; { 
				tmr::stop();
				frtmr1::stop();
				frtmr5::stop();
				frtmr1::reset();
				frtmr5::reset();
				tmr::reset();

				fr1::value(0);
				fr5::value(0);
				paused::value(0);

				cd_reset::value(0);
				ge::value(0);
				cd_sender::value(0xff);
				cd_text::value((std::string)"");
				cd_call::value(0xff);
				cd_callstat::value(0);
				cd_gmhelp::value(0);
				cd_reset::value(1);
			 }
				}
			};
			typedef wic::event<gameevent_game_reset_config> gameevent_game_reset;

			/// gameevent_game_started ///		
			struct gameevent_game_started_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_game_started";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x240;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gametimer tmr;
				typedef typename pirate::paused p;
				typedef typename pirate::freezed1 fr1;
				typedef typename pirate::freezed5 fr5;
					return (true && ( 
				1 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gametimer tmr;
				typedef typename pirate::paused p;
				typedef typename pirate::freezed1 fr1;
				typedef typename pirate::freezed5 fr5;
	
(void)0; { 
				tmr::start();
				fr1::value(false);
				fr5::value(false);
				p::value(false);
			 }
				}
			};
			typedef wic::event<gameevent_game_started_config> gameevent_game_started;

			/// gameevent_game_win ///		
			struct gameevent_game_win_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_game_win";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x280;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gameend ge;
					return (true && ( 
				3 == gs::value() && 1 == ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::gameend ge;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_game_win_config> gameevent_game_win;

			/// gameevent_ghostbox_opened ///		
			struct gameevent_ghostbox_opened_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_ghostbox_opened";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x4b0;
				static bool cfg_condition()
				{
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1 door;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && ( !door::value() ));
				}
				static void cfg_action()
				{
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1 door;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; { 
			progress_1::play();
			progress_2::play();
		 }
				}
			};
			typedef wic::event<gameevent_ghostbox_opened_config> gameevent_ghostbox_opened;

			/// gameevent_key_released ///		
			struct gameevent_key_released_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_key_released";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x610;
				static bool cfg_condition()
				{
					typedef typename pirate::stone_chest_controller::magnetic_lock_1 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && ( !lock::value() ));
				}
				static void cfg_action()
				{
					typedef typename pirate::stone_chest_controller::magnetic_lock_1 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; { 
			progress_1::play();
			progress_2::play();
		 }
				}
			};
			typedef wic::event<gameevent_key_released_config> gameevent_key_released;

			/// gameevent_knock_succeeded ///		
			struct gameevent_knock_succeeded_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_knock_succeeded";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x590;
				static bool cfg_condition()
				{
				typedef typename pirate::knock_count count;
				typedef typename pirate::knock_timer timer;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2 door;
					return (true && ( 
			3 <= count::value() && door::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::knock_count count;
				typedef typename pirate::knock_timer timer;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2 door;
	
(void)0; { 
			timer::stop();
			timer::reset();
			count::value(0);
			door::value(0);
		 }
				}
			};
			typedef wic::event<gameevent_knock_succeeded_config> gameevent_knock_succeeded;

			/// gameevent_lattice_opened ///		
			struct gameevent_lattice_opened_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_lattice_opened";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x6a0;
				static bool cfg_condition()
				{
					typedef typename pirate::stone_chest_controller::magnetic_lock_2 latticelock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && ( !latticelock::value() ));
				}
				static void cfg_action()
				{
					typedef typename pirate::stone_chest_controller::magnetic_lock_2 latticelock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; { 
			progress_1::play();
			progress_2::play();
		 }
				}
			};
			typedef wic::event<gameevent_lattice_opened_config> gameevent_lattice_opened;

			/// gameevent_rex_card_inserted ///		
			struct gameevent_rex_card_inserted_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_rex_card_inserted";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x450;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::rfid_reader rfid;
					return (true && ( 
			0 != rfid::value() && 0x7f00445186 != rfid::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::rfid_reader rfid;
	
(void)0; { 
				en::value(1);
		 }
				}
			};
			typedef wic::event<gameevent_rex_card_inserted_config> gameevent_rex_card_inserted;

			/// gameevent_rex_card_removed ///		
			struct gameevent_rex_card_removed_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_rex_card_removed";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x440;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::rfid_reader rfid;
					return (true && ( 
			0 == rfid::value() || 0x7f00445186 == rfid::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::rfid_reader rfid;
	
(void)0; { 
				en::value(0);
		 }
				}
			};
			typedef wic::event<gameevent_rex_card_removed_config> gameevent_rex_card_removed;

			/// gameevent_rex_game_won ///		
			struct gameevent_rex_game_won_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_rex_game_won";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x430;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
				typedef typename pirate::rex_score score;
					typedef typename pirate::rex_flipper_controller::magnetic_lock lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && ( 
			335 == score::value() && en::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
				typedef typename pirate::rex_score score;
					typedef typename pirate::rex_flipper_controller::magnetic_lock lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; { 
			progress_1::play();
			progress_2::play();
			lock::value(0);
		 }
				}
			};
			typedef wic::event<gameevent_rex_game_won_config> gameevent_rex_game_won;

			/// gameevent_rex_table_retry ///		
			struct gameevent_rex_table_retry_config
			{
				constexpr static const char *name = "ddf::pirate::gameevent_rex_table_retry";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x480;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
				typedef typename pirate::rex_blink_timer tmr;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left trials;
				typedef typename pirate::rex_photosensor_4_value p4v;
				typedef typename pirate::rex_photosensor_5_value p5v;
				typedef typename pirate::rex_photosensor_6_value p6v;
				typedef typename pirate::rex_photosensor_7_value p7v;
				typedef typename pirate::rex_left_column_failure lf;
				typedef typename pirate::rex_middle_column_failure mf;
				typedef typename pirate::rex_right_column_failure rf;
					return (true && ( 
			en::value() && !trials::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
				typedef typename pirate::rex_blink_timer tmr;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left trials;
				typedef typename pirate::rex_photosensor_4_value p4v;
				typedef typename pirate::rex_photosensor_5_value p5v;
				typedef typename pirate::rex_photosensor_6_value p6v;
				typedef typename pirate::rex_photosensor_7_value p7v;
				typedef typename pirate::rex_left_column_failure lf;
				typedef typename pirate::rex_middle_column_failure mf;
				typedef typename pirate::rex_right_column_failure rf;
	
(void)0; { 
			tmr::start();
			score::value(0);
			p4v::value(0);
			p5v::value(0);
			p6v::value(0);
			p7v::value(0);
			lf::value(0);
			mf::value(0);
			rf::value(0);
		 }
				}
			};
			typedef wic::event<gameevent_rex_table_retry_config> gameevent_rex_table_retry;

			/// ghost_blinking ///		
			struct ghost_blinking_config
			{
				constexpr static const char *name = "ddf::pirate::ghost_blinking";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x710;
				static bool cfg_condition()
				{
				typedef typename pirate::ghost_blink_timer tmr;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1 led;
					return (true && ( 
			tmr::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::ghost_blink_timer tmr;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1 led;
	
(void)0; { 
			switch(tmr::value())
			{
				case 1: led::value(0); break;
				case 4: led::value(1); break;
				case 5: led::value(0); break;
				case 6: led::value(1); break;
				case 7: led::value(0); break;
				case 8: led::value(1); break;
				case 9: led::value(0); break;
				case 15: led::value(1); break;
				case 20: led::value(0); break;
				case 26: led::value(1); break;
				case 30: led::value(0); break;
				case 33: led::value(1); break;
				case 34: led::value(0); break;
				case 48: led::value(1); break;
				case 50: led::value(0); break;
				case 60: led::value(1); break;
				case 61: led::value(0); break;
				case 62: led::value(1); break;
				case 64: led::value(0); break;
				case 76: led::value(1); break;
				case 77: led::value(0); break;
				case 78: led::value(1); break;
				case 79: led::value(0); break;
				case 83: led::value(1); break;
				case 85: led::value(0); break;
				case 86: led::value(1); break;
				case 87: led::value(0); break;
				case 88: led::value(1); break;
				case 89: led::value(0); break;
				case 90: led::value(1); break;
				case 91: led::value(0); break;
			}
			if(91 < tmr::value())
			{
				led::value(0);
				tmr::stop();
				tmr::reset();
			}
		 }
				}
			};
			typedef wic::event<ghost_blinking_config> ghost_blinking;

			/// hanger_trigger ///		
			struct hanger_trigger_config
			{
				constexpr static const char *name = "ddf::pirate::hanger_trigger";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x4c0;
				static bool cfg_condition()
				{
					typedef typename pirate::entrance_hanger_controller::debouncer_2 hanger;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3 boat_door;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1 ghostbox_door;
					return (true && (  hanger::value() && !ghostbox_door::value()  ));
				}
				static void cfg_action()
				{
					typedef typename pirate::entrance_hanger_controller::debouncer_2 hanger;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3 boat_door;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1 ghostbox_door;
	
(void)0; {  boat_door::value(0);  }
				}
			};
			typedef wic::event<hanger_trigger_config> hanger_trigger;

			/// knock_accumulate ///		
			struct knock_accumulate_config
			{
				constexpr static const char *name = "ddf::pirate::knock_accumulate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x580;
				static bool cfg_condition()
				{
				typedef typename pirate::knock_count count;
				typedef typename pirate::knock_timer timer;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor sensor;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2 door;
					return (true && (  
		sensor::value() && door::value()
     ));
				}
				static void cfg_action()
				{
				typedef typename pirate::knock_count count;
				typedef typename pirate::knock_timer timer;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor sensor;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2 door;
	
(void)0; { 
		timer::reset();
		timer::start();
		count::value(count::value() + 1);
       }
				}
			};
			typedef wic::event<knock_accumulate_config> knock_accumulate;

			/// knock_reset ///		
			struct knock_reset_config
			{
				constexpr static const char *name = "ddf::pirate::knock_reset";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x5b0;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::knock_timer timer;
				typedef typename pirate::knock_count count;
					return (true && ( 
	  		!gs::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::knock_timer timer;
				typedef typename pirate::knock_count count;
	
(void)0; { 
			timer::stop();
			timer::reset();
			count::value(0);
		 }
				}
			};
			typedef wic::event<knock_reset_config> knock_reset;

			/// knock_timeout ///		
			struct knock_timeout_config
			{
				constexpr static const char *name = "ddf::pirate::knock_timeout";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x5a0;
				static bool cfg_condition()
				{
				typedef typename pirate::knock_timer timer;
				typedef typename pirate::knock_count count;
					return (true && (  timer::value()  ));
				}
				static void cfg_action()
				{
				typedef typename pirate::knock_timer timer;
				typedef typename pirate::knock_count count;
	
(void)0; { 
		timer::stop();
		timer::reset();
		count::value(0);
       }
				}
			};
			typedef wic::event<knock_timeout_config> knock_timeout;

			/// laser_turn_off ///		
			struct laser_turn_off_config
			{
				constexpr static const char *name = "ddf::pirate::laser_turn_off";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x4e0;
				static bool cfg_condition()
				{
					typedef typename pirate::cashier_laser_controller::switch_1 _switch;
					typedef typename pirate::cashier_laser_controller::laser laser;
					return (true && (  
            _switch::value() 
         ));
				}
				static void cfg_action()
				{
					typedef typename pirate::cashier_laser_controller::switch_1 _switch;
					typedef typename pirate::cashier_laser_controller::laser laser;
	
(void)0; { 
            laser::value(0);
         }
				}
			};
			typedef wic::event<laser_turn_off_config> laser_turn_off;

			/// left_column_evaluate ///		
			struct left_column_evaluate_config
			{
				constexpr static const char *name = "ddf::pirate::left_column_evaluate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x3f0;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_3 p0;
					typedef typename pirate::rex_flipper_controller::photosensor_6 p1;
				typedef typename pirate::rex_photosensor_6_value p1v;
				typedef typename pirate::rex_left_column_failure fail;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left tl;
					return (true && ( 
			p0::value() && en::value() && tl::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_3 p0;
					typedef typename pirate::rex_flipper_controller::photosensor_6 p1;
				typedef typename pirate::rex_photosensor_6_value p1v;
				typedef typename pirate::rex_left_column_failure fail;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left tl;
	
(void)0; { 
			if(fail::value())
			{
				p1v::value(false);
				tl::value(tl::value()-1);
				fail::value(false);
				return;
			}

			if(p1v::value())
				score::value(rex_score::value()+45);	// hole 1

			else
				score::value(rex_score::value()+0);		// hole 2

			p1v::value(false);

			if(tl::value())
				tl::value(tl::value()-1);

			else
			{
				score::value(0);
				tl::value(3);
			}
		 }
				}
			};
			typedef wic::event<left_column_evaluate_config> left_column_evaluate;

			/// map_reset ///		
			struct map_reset_config
			{
				constexpr static const char *name = "ddf::pirate::map_reset";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x620;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::map_sensor1_triggered sensor_1;
				typedef typename pirate::map_sensor2_triggered sensor_2;
					return (true && ( 
			!gs::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::map_sensor1_triggered sensor_1;
				typedef typename pirate::map_sensor2_triggered sensor_2;
	
(void)0; { 
			sensor_1::value(0);
			sensor_2::value(0);
		 }
				}
			};
			typedef wic::event<map_reset_config> map_reset;

			/// map_sensor1 ///		
			struct map_sensor1_config
			{
				constexpr static const char *name = "ddf::pirate::map_sensor1";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x5e0;
				static bool cfg_condition()
				{
					typedef typename pirate::map_controller::magnetic_sensor_1 s;
				typedef typename pirate::map_sensor1_triggered p;
					return (true && ( 
			s::value() <= 1600 
		 ));
				}
				static void cfg_action()
				{
					typedef typename pirate::map_controller::magnetic_sensor_1 s;
				typedef typename pirate::map_sensor1_triggered p;
	
(void)0; { 
			p::value(1);
		 }
				}
			};
			typedef wic::event<map_sensor1_config> map_sensor1;

			/// map_sensor2 ///		
			struct map_sensor2_config
			{
				constexpr static const char *name = "ddf::pirate::map_sensor2";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x5f0;
				static bool cfg_condition()
				{
					typedef typename pirate::map_controller::magnetic_sensor_2 s;
				typedef typename pirate::map_sensor2_triggered p;
					return (true && ( 
			s::value() >= 2400
		 ));
				}
				static void cfg_action()
				{
					typedef typename pirate::map_controller::magnetic_sensor_2 s;
				typedef typename pirate::map_sensor2_triggered p;
	
(void)0; { 
			p::value(1);
		 }
				}
			};
			typedef wic::event<map_sensor2_config> map_sensor2;

			/// map_solved ///		
			struct map_solved_config
			{
				constexpr static const char *name = "ddf::pirate::map_solved";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x600;
				static bool cfg_condition()
				{
				typedef typename pirate::map_sensor1_triggered sensor_1;
				typedef typename pirate::map_sensor2_triggered sensor_2;
					typedef typename pirate::stone_chest_controller::magnetic_lock_1 lock;
					return (true && (  
			sensor_1::value() && sensor_2::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::map_sensor1_triggered sensor_1;
				typedef typename pirate::map_sensor2_triggered sensor_2;
					typedef typename pirate::stone_chest_controller::magnetic_lock_1 lock;
	
(void)0; {  
			lock::value(0); 
		 }
				}
			};
			typedef wic::event<map_solved_config> map_solved;

			/// middle_column_evaluate ///		
			struct middle_column_evaluate_config
			{
				constexpr static const char *name = "ddf::pirate::middle_column_evaluate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x410;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_1 p0;
					typedef typename pirate::rex_flipper_controller::photosensor_4 p1;
				typedef typename pirate::rex_photosensor_4_value p1v;
					typedef typename pirate::rex_flipper_controller::photosensor_7 p2;
				typedef typename pirate::rex_photosensor_7_value p2v;
				typedef typename pirate::rex_middle_column_failure fail;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left tl;
					return (true && ( 
			p0::value() && en::value() && tl::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_1 p0;
					typedef typename pirate::rex_flipper_controller::photosensor_4 p1;
				typedef typename pirate::rex_photosensor_4_value p1v;
					typedef typename pirate::rex_flipper_controller::photosensor_7 p2;
				typedef typename pirate::rex_photosensor_7_value p2v;
				typedef typename pirate::rex_middle_column_failure fail;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left tl;
	
(void)0; { 
			if(fail::value())
			{
				p1v::value(false);
				p2v::value(false);
				tl::value(tl::value()-1);
				fail::value(false);
				return;
			}

			if(p1v::value())
			{
				if(p2v::value())
					score::value(rex_score::value()+200);	// hole 1
				else
					score::value(rex_score::value()+75);	// hole 2
			}
			else
				score::value(rex_score::value()+20);		// hole 3

			p1v::value(false);
			p2v::value(false);

			if(tl::value())
				tl::value(tl::value()-1);

			else
			{
				score::value(0);
				tl::value(3);
			}
		 }
				}
			};
			typedef wic::event<middle_column_evaluate_config> middle_column_evaluate;

			/// pin_code_accumulation ///		
			struct pin_code_accumulation_config
			{
				constexpr static const char *name = "ddf::pirate::pin_code_accumulation";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x510;
				static bool cfg_condition()
				{
				typedef typename pirate::pin_timeout_timer timer;
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::pin_pad pin_pad;
					typedef typename pirate::cashier_laser_controller::buzzer buzzer;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::pin_timeout_timer timer;
				typedef typename pirate::pin_code code;
					typedef typename pirate::cashier_laser_controller::pin_pad pin_pad;
					typedef typename pirate::cashier_laser_controller::buzzer buzzer;
	
(void)0; { 
			typename pin_pad::value_type v = pin_pad::value();
			if(!v.state)
				return;

			timer::reset();
			timer::start();
			const uint8_t k = v.key;
			char c;

			if(k < 9)
				c = static_cast<char>(k+49);
			else switch(k)
			{
				case 9 : c = '*'; break;
				case 10: c = '0'; break;
				case 11: c = '#'; break;
				default: c = '?'; break;
			}
			const std::string cv = code::value() + c;
	        code::value(cv);
			if(cv.size() < 4)
				buzzer::beep(210,40);
		 }
				}
			};
			typedef wic::event<pin_code_accumulation_config> pin_code_accumulation;

			/// reset_room ///		
			struct reset_room_config
			{
				constexpr static const char *name = "ddf::pirate::reset_room";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x2f0;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
					typedef typename pirate::map_controller::led_strip starz;
					typedef typename pirate::stone_chest_controller::magnetic_lock_1 key_lock;
					typedef typename pirate::stone_chest_controller::magnetic_lock_2 lattice_lock;
					typedef typename pirate::stone_chest_controller::led_strip chest_light;
					typedef typename pirate::cashier_laser_controller::laser laser;
					typedef typename pirate::cashier_laser_controller::lcd lcd;
					typedef typename pirate::cashier_laser_controller::cash_box cash_box;
					typedef typename pirate::cashier_laser_controller::led_strip win_light;
					typedef typename pirate::rex_flipper_controller::light_controller_1 ir1;
					typedef typename pirate::rex_flipper_controller::light_controller_2 ir2;
					typedef typename pirate::rex_flipper_controller::light_controller_3 ir3;
					typedef typename pirate::rex_flipper_controller::light_controller_4 ir4;
					typedef typename pirate::rex_flipper_controller::light_controller_5 ir5;
					typedef typename pirate::rex_flipper_controller::light_controller_6 ir6;
					typedef typename pirate::rex_flipper_controller::light_controller_7 ir7;
					typedef typename pirate::rex_flipper_controller::magnetic_lock key_holder;
					typedef typename pirate::rex_flipper_controller::led ledstrip;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1 lock1;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2 lock2;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3 lock3;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1 led1;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2 led2;
					typedef typename pirate::entrance_hanger_controller::led led;
					return (true && ( 
		!gs::value()
	 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
					typedef typename pirate::map_controller::led_strip starz;
					typedef typename pirate::stone_chest_controller::magnetic_lock_1 key_lock;
					typedef typename pirate::stone_chest_controller::magnetic_lock_2 lattice_lock;
					typedef typename pirate::stone_chest_controller::led_strip chest_light;
					typedef typename pirate::cashier_laser_controller::laser laser;
					typedef typename pirate::cashier_laser_controller::lcd lcd;
					typedef typename pirate::cashier_laser_controller::cash_box cash_box;
					typedef typename pirate::cashier_laser_controller::led_strip win_light;
					typedef typename pirate::rex_flipper_controller::light_controller_1 ir1;
					typedef typename pirate::rex_flipper_controller::light_controller_2 ir2;
					typedef typename pirate::rex_flipper_controller::light_controller_3 ir3;
					typedef typename pirate::rex_flipper_controller::light_controller_4 ir4;
					typedef typename pirate::rex_flipper_controller::light_controller_5 ir5;
					typedef typename pirate::rex_flipper_controller::light_controller_6 ir6;
					typedef typename pirate::rex_flipper_controller::light_controller_7 ir7;
					typedef typename pirate::rex_flipper_controller::magnetic_lock key_holder;
					typedef typename pirate::rex_flipper_controller::led ledstrip;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1 lock1;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2 lock2;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3 lock3;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1 led1;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2 led2;
					typedef typename pirate::entrance_hanger_controller::led led;
	
(void)0; { 
		starz::value(0);
		key_lock::value(1);
		lattice_lock::value(1);
		chest_light::value(0);
		laser::value(1);
		lcd::value("");
		cash_box::value(0);
		win_light::value(0);
		ir1::value(1);
		ir2::value(1);
		ir3::value(1);
		ir4::value(1);
		ir5::value(1);
		ir6::value(1);
		ir7::value(1);
		key_holder::value(1);
		ledstrip::enabled(false);
		ledstrip::enabled(true);
		ledstrip::value_type v;
		for(int i = 0; i < 3; ++i)
		{
			v.led[i].red = 0;
			v.led[i].green = 0;
			v.led[i].blue = 0;
		}
		ledstrip::value((ledstrip::value_type)v);
		lock1::value(1);
		lock2::value(1);
		lock3::value(1);
		led1::value(0);
		led2::value(0);

		led::value(0);
     }
				}
			};
			typedef wic::event<reset_room_config> reset_room;

			/// rex_blink ///		
			struct rex_blink_config
			{
				constexpr static const char *name = "ddf::pirate::rex_blink";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x470;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_blink_timer tmr;
					typedef typename pirate::rex_flipper_controller::led led;
				typedef typename pirate::rex_trials_left tl;
				typedef typename pirate::rex_enabled en;
					return (true && ( 
			!tl::value() && en::value() && tmr::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_blink_timer tmr;
					typedef typename pirate::rex_flipper_controller::led led;
				typedef typename pirate::rex_trials_left tl;
				typedef typename pirate::rex_enabled en;
	
(void)0; { 
			if(tmr::value() > 5)
			{
				tmr::stop();
				tmr::reset();
				tl::value(3);
			}

			else
			{
				led::value_type v;
				int i = 2;
				for(; i >= tl::value(); --i)
				{
					v.led[i].red = ((tmr::value()+1)%2)*50;
					v.led[i].green = 0;
					v.led[i].blue= 0;
				}
				led::value((led::value_type)v);
			}
			
		 }
				}
			};
			typedef wic::event<rex_blink_config> rex_blink;

			/// rex_led_update ///		
			struct rex_led_update_config
			{
				constexpr static const char *name = "ddf::pirate::rex_led_update";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x420;
				static bool cfg_condition()
				{
					typedef typename pirate::rex_flipper_controller::led led;
				typedef typename pirate::rex_trials_left tl;
					return (true);
				}
				static void cfg_action()
				{
					typedef typename pirate::rex_flipper_controller::led led;
				typedef typename pirate::rex_trials_left tl;
	
(void)0; { 
			led::value_type v;
			int i = 2;
			for(; i >= tl::value(); --i)
			{
				v.led[i].red = 0;
				v.led[i].green = 0;
				v.led[i].blue= 0;
			}
			for(; i >= 0; --i)
			{
				v.led[i].red = 40;
				v.led[i].green = 40;
				v.led[i].blue= 40;
			}
			led::value((led::value_type)v);
		 }
				}
			};
			typedef wic::event<rex_led_update_config> rex_led_update;

			/// rex_photosensor_4_acc ///		
			struct rex_photosensor_4_acc_config
			{
				constexpr static const char *name = "ddf::pirate::rex_photosensor_4_acc";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x3b0;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_4 p;
				typedef typename pirate::rex_photosensor_4_value pv;
				typedef typename pirate::rex_middle_column_failure f;
				typedef typename pirate::rex_trials_left tl;
					return (true && ( 
			p::value() && en::value() && tl::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_4 p;
				typedef typename pirate::rex_photosensor_4_value pv;
				typedef typename pirate::rex_middle_column_failure f;
				typedef typename pirate::rex_trials_left tl;
	
(void)0; { 
			if(pv::value())
				f::value(true);
			else
				pv::value(true);
		 }
				}
			};
			typedef wic::event<rex_photosensor_4_acc_config> rex_photosensor_4_acc;

			/// rex_photosensor_5_acc ///		
			struct rex_photosensor_5_acc_config
			{
				constexpr static const char *name = "ddf::pirate::rex_photosensor_5_acc";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x3c0;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_5 p;
				typedef typename pirate::rex_photosensor_5_value pv;
				typedef typename pirate::rex_right_column_failure f;
				typedef typename pirate::rex_trials_left tl;
					return (true && ( 
			p::value() && en::value() && tl::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_5 p;
				typedef typename pirate::rex_photosensor_5_value pv;
				typedef typename pirate::rex_right_column_failure f;
				typedef typename pirate::rex_trials_left tl;
	
(void)0; { 
			if(pv::value())
				f::value(true);
			else
				pv::value(true);
		 }
				}
			};
			typedef wic::event<rex_photosensor_5_acc_config> rex_photosensor_5_acc;

			/// rex_photosensor_6_acc ///		
			struct rex_photosensor_6_acc_config
			{
				constexpr static const char *name = "ddf::pirate::rex_photosensor_6_acc";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x3d0;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_6 p;
				typedef typename pirate::rex_photosensor_6_value pv;
				typedef typename pirate::rex_left_column_failure f;
				typedef typename pirate::rex_trials_left tl;
					return (true && ( 
			p::value() && en::value() && tl::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_6 p;
				typedef typename pirate::rex_photosensor_6_value pv;
				typedef typename pirate::rex_left_column_failure f;
				typedef typename pirate::rex_trials_left tl;
	
(void)0; { 
			if(pv::value())
				f::value(true);
			else
				pv::value(true);
		 }
				}
			};
			typedef wic::event<rex_photosensor_6_acc_config> rex_photosensor_6_acc;

			/// rex_photosensor_7_acc ///		
			struct rex_photosensor_7_acc_config
			{
				constexpr static const char *name = "ddf::pirate::rex_photosensor_7_acc";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x3e0;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_7 p;
				typedef typename pirate::rex_photosensor_7_value pv;
				typedef typename pirate::rex_middle_column_failure f;
				typedef typename pirate::rex_trials_left tl;
					return (true && ( 
			p::value() && en::value() && tl::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_7 p;
				typedef typename pirate::rex_photosensor_7_value pv;
				typedef typename pirate::rex_middle_column_failure f;
				typedef typename pirate::rex_trials_left tl;
	
(void)0; { 
			if(pv::value())
				f::value(true);
			else
				pv::value(true);
		 }
				}
			};
			typedef wic::event<rex_photosensor_7_acc_config> rex_photosensor_7_acc;

			/// rex_table_state ///		
			struct rex_table_state_config
			{
				constexpr static const char *name = "ddf::pirate::rex_table_state";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x490;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left trials;
				typedef typename pirate::rex_photosensor_4_value p4v;
				typedef typename pirate::rex_photosensor_5_value p5v;
				typedef typename pirate::rex_photosensor_6_value p6v;
				typedef typename pirate::rex_photosensor_7_value p7v;
				typedef typename pirate::rex_left_column_failure lf;
				typedef typename pirate::rex_middle_column_failure mf;
				typedef typename pirate::rex_right_column_failure rf;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left trials;
				typedef typename pirate::rex_photosensor_4_value p4v;
				typedef typename pirate::rex_photosensor_5_value p5v;
				typedef typename pirate::rex_photosensor_6_value p6v;
				typedef typename pirate::rex_photosensor_7_value p7v;
				typedef typename pirate::rex_left_column_failure lf;
				typedef typename pirate::rex_middle_column_failure mf;
				typedef typename pirate::rex_right_column_failure rf;
	
(void)0; { 
			if(en::value())
			{
				trials::value(3);
			}
			else
			{
				trials::value(0);
			}
			score::value(0);
			p4v::value(0);
			p5v::value(0);
			p6v::value(0);
			p7v::value(0);
			lf::value(0);
			mf::value(0);
			rf::value(0);
		 }
				}
			};
			typedef wic::event<rex_table_state_config> rex_table_state;

			/// right_column_evaluate ///		
			struct right_column_evaluate_config
			{
				constexpr static const char *name = "ddf::pirate::right_column_evaluate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x400;
				static bool cfg_condition()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_2 p0;
					typedef typename pirate::rex_flipper_controller::photosensor_5 p1;
				typedef typename pirate::rex_photosensor_5_value p1v;
				typedef typename pirate::rex_right_column_failure fail;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left tl;
					return (true && ( 
			p0::value() && en::value() && tl::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::rex_enabled en;
					typedef typename pirate::rex_flipper_controller::photosensor_2 p0;
					typedef typename pirate::rex_flipper_controller::photosensor_5 p1;
				typedef typename pirate::rex_photosensor_5_value p1v;
				typedef typename pirate::rex_right_column_failure fail;
				typedef typename pirate::rex_score score;
				typedef typename pirate::rex_trials_left tl;
	
(void)0; { 
			if(fail::value())
			{
				p1v::value(false);
				tl::value(tl::value()-1);
				fail::value(false);
				return;
			}

			if(p1v::value())
				score::value(rex_score::value()+60);	// hole 1

			else
				score::value(rex_score::value()+0);		// hole 2

			p1v::value(false);

			if(tl::value())
				tl::value(tl::value()-1);

			else
			{
				score::value(0);
				tl::value(3);
			}
		 }
				}
			};
			typedef wic::event<right_column_evaluate_config> right_column_evaluate;

			/// rotation_update ///		
			struct rotation_update_config
			{
				constexpr static const char *name = "ddf::pirate::rotation_update";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x650;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::star_value sv;
				typedef typename pirate::wheel_last_pos last;
					typedef typename pirate::map_controller::led_strip star;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer wheel;
					return (true && ( 1 == gs::value() ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::star_value sv;
				typedef typename pirate::wheel_last_pos last;
					typedef typename pirate::map_controller::led_strip star;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer wheel;
	
(void)0; { 
		double x;
		if(
  		    (wheel_last_pos::value() > wheel::value()) &&
  		    ((wheel_last_pos::value() - wheel::value()) < 1000)
		)
		{
        		x = sqrt((double)star::value()*3);
        		x += (wheel_last_pos::value() - wheel::value())/31;
        		x*=x;
        		x/=3;
        		if(x > 65535)
        			x=65535;

        	}
        	else if(
        		(wheel_last_pos::value() < wheel::value()) &&
        		((wheel::value() - wheel_last_pos::value()) < 1000)
        	)
        	{
        		x = sqrt((double)star::value()*3);
        		x += (wheel_last_pos::value() - wheel::value())/31;
        		if(x < 0)
        			x = 0;
        		else 
        		{
        			x*=x;
        			x/=3;
        		}
        	}
        	else
        	{
        		wheel_last_pos::value(wheel::value());
        		return;
        	}
        	wheel_last_pos::value(wheel::value());

		sv::value((uint16_t)x);
		star::value((uint16_t)x);
       }
				}
			};
			typedef wic::event<rotation_update_config> rotation_update;

			/// sign_matching ///		
			struct sign_matching_config
			{
				constexpr static const char *name = "ddf::pirate::sign_matching";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x690;
				static bool cfg_condition()
				{
					typedef typename pirate::stone_chest_controller::magnetic_sensor_1 stone_1;
					typedef typename pirate::stone_chest_controller::magnetic_sensor_2 stone_2;
					typedef typename pirate::stone_chest_controller::magnetic_sensor_3 stone_3;
					typedef typename pirate::stone_chest_controller::magnetic_sensor_4 stone_4;
					typedef typename pirate::stone_chest_controller::magnetic_lock_2 latticelock;
					return (true && (  
			stone_1::value() &&
			stone_2::value() &&
			stone_3::value() &&
			stone_4::value()
		 ));
				}
				static void cfg_action()
				{
					typedef typename pirate::stone_chest_controller::magnetic_sensor_1 stone_1;
					typedef typename pirate::stone_chest_controller::magnetic_sensor_2 stone_2;
					typedef typename pirate::stone_chest_controller::magnetic_sensor_3 stone_3;
					typedef typename pirate::stone_chest_controller::magnetic_sensor_4 stone_4;
					typedef typename pirate::stone_chest_controller::magnetic_lock_2 latticelock;
	
(void)0; {  
			latticelock::value(0); 
		 }
				}
			};
			typedef wic::event<sign_matching_config> sign_matching;

			/// stop_audios ///		
			struct stop_audios_config
			{
				constexpr static const char *name = "ddf::pirate::stop_audios";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x300;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
			typedef room_1_content::careful s1;
			typedef room_1_content::rules s2;
			typedef room_1_content::techdiff s3;
			typedef room_1_content::gminc s4;
			typedef room_2_content::careful s5;
			typedef room_2_content::rules s6;
			typedef room_2_content::techdiff s7;
			typedef room_2_content::gminc s8;
			typedef room_1_content::event_1 s9;
			typedef room_1_content::event_2 sa;
			typedef room_1_content::event_3 sb;
			typedef room_1_content::ghost_voice sc;
			typedef room_2_content::event_1 sd;
			typedef room_2_content::event_2 se;
			typedef room_2_content::event_3 sf;
					return (true && ( 
			3 == gs::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
			typedef room_1_content::careful s1;
			typedef room_1_content::rules s2;
			typedef room_1_content::techdiff s3;
			typedef room_1_content::gminc s4;
			typedef room_2_content::careful s5;
			typedef room_2_content::rules s6;
			typedef room_2_content::techdiff s7;
			typedef room_2_content::gminc s8;
			typedef room_1_content::event_1 s9;
			typedef room_1_content::event_2 sa;
			typedef room_1_content::event_3 sb;
			typedef room_1_content::ghost_voice sc;
			typedef room_2_content::event_1 sd;
			typedef room_2_content::event_2 se;
			typedef room_2_content::event_3 sf;
	
(void)0; { 
			s1::cancel();
			s2::cancel();
			s3::cancel();
			s4::cancel();
			s5::cancel();
			s6::cancel();
			s7::cancel();
			s8::cancel();
			s9::cancel();
			sa::cancel();
			sb::cancel();
			sc::cancel();
			sd::cancel();
			se::cancel();
			sf::cancel();
		 }
				}
			};
			typedef wic::event<stop_audios_config> stop_audios;

			/// time_up ///		
			struct time_up_config
			{
				constexpr static const char *name = "ddf::pirate::time_up";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x230;
				static bool cfg_condition()
				{
				typedef typename pirate::gametimer tmr;
				typedef typename pirate::gameend ge;
				typedef typename pirate::gamestate gs;
			typedef room_1_content::failstate failstate_room_1;
			typedef room_2_content::failstate failstate_room_2;
					return (true && ( 
				tmr::value() >= 3600 && tmr::running() && 1 == gs::value() && !ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::gametimer tmr;
				typedef typename pirate::gameend ge;
				typedef typename pirate::gamestate gs;
			typedef room_1_content::failstate failstate_room_1;
			typedef room_2_content::failstate failstate_room_2;
	
(void)0; { 
				tmr::stop();
				failstate_room_1::play();
				failstate_room_2::play();
				ge::value(2);
				gs::value(3);
			 }
				}
			};
			typedef wic::event<time_up_config> time_up;

			/// timedevent_an_1_event_finished ///		
			struct timedevent_an_1_event_finished_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_1_event_finished";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x740;
				static bool cfg_condition()
				{
				typedef typename pirate::timedevent_an_1 __timedevent_at;
				typedef typename pirate::timedevent_an_1_timer __timedevent_timer;
			typedef room_1_content::event_1 r1;
			typedef room_2_content::event_1 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::timedevent_an_1 __timedevent_at;
				typedef typename pirate::timedevent_an_1_timer __timedevent_timer;
			typedef room_1_content::event_1 r1;
			typedef room_2_content::event_1 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_an_1_event_finished_config> timedevent_an_1_event_finished;

			/// timedevent_an_1_event_gamestate ///		
			struct timedevent_an_1_event_gamestate_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_1_event_gamestate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x750;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_an_1_timer tmr;
				typedef typename pirate::timedevent_an_1 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_an_1_timer tmr;
				typedef typename pirate::timedevent_an_1 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_an_1_event_gamestate_config> timedevent_an_1_event_gamestate;

			/// timedevent_an_2_event_finished ///		
			struct timedevent_an_2_event_finished_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_2_event_finished";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x7c0;
				static bool cfg_condition()
				{
				typedef typename pirate::timedevent_an_2 __timedevent_at;
				typedef typename pirate::timedevent_an_2_timer __timedevent_timer;
			typedef room_1_content::event_2 r1;
			typedef room_2_content::event_2 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::timedevent_an_2 __timedevent_at;
				typedef typename pirate::timedevent_an_2_timer __timedevent_timer;
			typedef room_1_content::event_2 r1;
			typedef room_2_content::event_2 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_an_2_event_finished_config> timedevent_an_2_event_finished;

			/// timedevent_an_2_event_gamestate ///		
			struct timedevent_an_2_event_gamestate_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_2_event_gamestate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x7d0;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_an_2_timer tmr;
				typedef typename pirate::timedevent_an_2 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_an_2_timer tmr;
				typedef typename pirate::timedevent_an_2 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_an_2_event_gamestate_config> timedevent_an_2_event_gamestate;

			/// timedevent_an_3_event_finished ///		
			struct timedevent_an_3_event_finished_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_3_event_finished";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x840;
				static bool cfg_condition()
				{
				typedef typename pirate::timedevent_an_3 __timedevent_at;
				typedef typename pirate::timedevent_an_3_timer __timedevent_timer;
			typedef room_1_content::event_3 r1;
			typedef room_2_content::event_3 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::timedevent_an_3 __timedevent_at;
				typedef typename pirate::timedevent_an_3_timer __timedevent_timer;
			typedef room_1_content::event_3 r1;
			typedef room_2_content::event_3 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_an_3_event_finished_config> timedevent_an_3_event_finished;

			/// timedevent_an_3_event_gamestate ///		
			struct timedevent_an_3_event_gamestate_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_an_3_event_gamestate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x850;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_an_3_timer tmr;
				typedef typename pirate::timedevent_an_3 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_an_3_timer tmr;
				typedef typename pirate::timedevent_an_3 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_an_3_event_gamestate_config> timedevent_an_3_event_gamestate;

			/// timedevent_ghost_voice_event_finished ///		
			struct timedevent_ghost_voice_event_finished_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_ghost_voice_event_finished";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x6f0;
				static bool cfg_condition()
				{
				typedef typename pirate::timedevent_ghost_voice __timedevent_at;
				typedef typename pirate::timedevent_ghost_voice_timer __timedevent_timer;
				typedef typename pirate::ghost_blink_timer tmr;
			typedef room_1_content::ghost_voice r1;
			typedef room_2_content::ghost_voice r2;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1 l;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::timedevent_ghost_voice __timedevent_at;
				typedef typename pirate::timedevent_ghost_voice_timer __timedevent_timer;
				typedef typename pirate::ghost_blink_timer tmr;
			typedef room_1_content::ghost_voice r1;
			typedef room_2_content::ghost_voice r2;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1 l;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
			r1::play();
			r2::play();
			l::value(1);
			tmr::value(1);
			tmr::start();
		 }
				}
			};
			typedef wic::event<timedevent_ghost_voice_event_finished_config> timedevent_ghost_voice_event_finished;

			/// timedevent_ghost_voice_event_gamestate ///		
			struct timedevent_ghost_voice_event_gamestate_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_ghost_voice_event_gamestate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x700;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_ghost_voice_timer tmr;
				typedef typename pirate::timedevent_ghost_voice at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_ghost_voice_timer tmr;
				typedef typename pirate::timedevent_ghost_voice at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_ghost_voice_event_gamestate_config> timedevent_ghost_voice_event_gamestate;

			/// timedevent_pc_1_event_finished ///		
			struct timedevent_pc_1_event_finished_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_pc_1_event_finished";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x780;
				static bool cfg_condition()
				{
				typedef typename pirate::timedevent_pc_1 __timedevent_at;
				typedef typename pirate::timedevent_pc_1_timer __timedevent_timer;
				typedef typename pirate::incoming_call call;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::timedevent_pc_1 __timedevent_at;
				typedef typename pirate::timedevent_pc_1_timer __timedevent_timer;
				typedef typename pirate::incoming_call call;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				call::value(2);
			 }
				}
			};
			typedef wic::event<timedevent_pc_1_event_finished_config> timedevent_pc_1_event_finished;

			/// timedevent_pc_1_event_gamestate ///		
			struct timedevent_pc_1_event_gamestate_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_pc_1_event_gamestate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x790;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_pc_1_timer tmr;
				typedef typename pirate::timedevent_pc_1 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_pc_1_timer tmr;
				typedef typename pirate::timedevent_pc_1 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_pc_1_event_gamestate_config> timedevent_pc_1_event_gamestate;

			/// timedevent_pc_2_event_finished ///		
			struct timedevent_pc_2_event_finished_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_pc_2_event_finished";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x800;
				static bool cfg_condition()
				{
				typedef typename pirate::timedevent_pc_2 __timedevent_at;
				typedef typename pirate::timedevent_pc_2_timer __timedevent_timer;
				typedef typename pirate::incoming_call call;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename pirate::timedevent_pc_2 __timedevent_at;
				typedef typename pirate::timedevent_pc_2_timer __timedevent_timer;
				typedef typename pirate::incoming_call call;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				call::value(3);
			 }
				}
			};
			typedef wic::event<timedevent_pc_2_event_finished_config> timedevent_pc_2_event_finished;

			/// timedevent_pc_2_event_gamestate ///		
			struct timedevent_pc_2_event_gamestate_config
			{
				constexpr static const char *name = "ddf::pirate::timedevent_pc_2_event_gamestate";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x810;
				static bool cfg_condition()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_pc_2_timer tmr;
				typedef typename pirate::timedevent_pc_2 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_pc_2_timer tmr;
				typedef typename pirate::timedevent_pc_2 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_pc_2_event_gamestate_config> timedevent_pc_2_event_gamestate;

			/// tray_trigger ///		
			struct tray_trigger_config
			{
				constexpr static const char *name = "ddf::pirate::tray_trigger";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x4a0;
				static bool cfg_condition()
				{
					typedef tray_camera_content::tray_sensor trays;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1 door;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1 led1;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2 led2;
					return (true && ( 0xf == (0xf & trays::value()) ));
				}
				static void cfg_action()
				{
					typedef tray_camera_content::tray_sensor trays;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1 door;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1 led1;
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2 led2;
	
(void)0; { 
			door::value(0);
			led1::value(1);
			led2::value(1);
		 }
				}
			};
			typedef wic::event<tray_trigger_config> tray_trigger;

			/// wheel_reset ///		
			struct wheel_reset_config
			{
				constexpr static const char *name = "ddf::pirate::wheel_reset";
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x680;
				static bool cfg_condition()
				{
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer wheel;
				typedef typename pirate::wheel_last_pos last;
					typedef typename pirate::map_controller::led_strip star;
				typedef typename pirate::star_value sv;
				typedef typename pirate::gamestate gs;
					return (true && ( 
		!gs::value()	
	 ));
				}
				static void cfg_action()
				{
					typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer wheel;
				typedef typename pirate::wheel_last_pos last;
					typedef typename pirate::map_controller::led_strip star;
				typedef typename pirate::star_value sv;
				typedef typename pirate::gamestate gs;
	
(void)0; { 
		last::value(wheel::value());
		star::value(0);
		sv::value(0);
	 }
				}
			};
			typedef wic::event<wheel_reset_config> wheel_reset;
}

	/// Room magician
	namespace magician
	{

			/// cupboard_controller
			namespace cupboard_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - magician - cupboard_controller";
					static const uint32_t cfg_class_id = 0x200010;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::cupboard_controller::debouncer";
					static const uint32_t cfg_class_id = 0x200010;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_config> debouncer;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::cupboard_controller::magnetic_sensor";
					static const uint32_t cfg_class_id = 0x200010;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_config> magnetic_sensor;

				/// magnetic_lock ///
				struct magnetic_lock_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::cupboard_controller::magnetic_lock";
					static const uint32_t cfg_class_id = 0x200010;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_config> magnetic_lock;

				/// led_strip ///
				struct led_strip_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::cupboard_controller::led_strip";
					static const uint32_t cfg_class_id = 0x200010;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::led_strip<led_strip_config> led_strip;

			}

			/// design_board_controller
			namespace design_board_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - magician - design_board_controller";
					static const uint32_t cfg_class_id = 0x200020;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// linear_magnetic_sensor_1 ///
				struct linear_magnetic_sensor_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::design_board_controller::linear_magnetic_sensor_1";
					static const uint32_t cfg_class_id = 0x200020;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<linear_magnetic_sensor_1_config> linear_magnetic_sensor_1;

				/// linear_magnetic_sensor_2 ///
				struct linear_magnetic_sensor_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::design_board_controller::linear_magnetic_sensor_2";
					static const uint32_t cfg_class_id = 0x200020;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<linear_magnetic_sensor_2_config> linear_magnetic_sensor_2;

				/// linear_magnetic_sensor_3 ///
				struct linear_magnetic_sensor_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::design_board_controller::linear_magnetic_sensor_3";
					static const uint32_t cfg_class_id = 0x200020;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<linear_magnetic_sensor_3_config> linear_magnetic_sensor_3;

				/// magnetic_lock ///
				struct magnetic_lock_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::design_board_controller::magnetic_lock";
					static const uint32_t cfg_class_id = 0x200020;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_config> magnetic_lock;

			}

			/// entrance_controller
			namespace entrance_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - magician - entrance_controller";
					static const uint32_t cfg_class_id = 0x200040;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::entrance_controller::debouncer";
					static const uint32_t cfg_class_id = 0x200040;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_config> debouncer;

				/// led ///
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::entrance_controller::led";
					static const uint32_t cfg_class_id = 0x200040;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::led_strip<led_config> led;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::entrance_controller::magnetic_sensor";
					static const uint32_t cfg_class_id = 0x200040;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_config> magnetic_sensor;

			}

			/// futuristic_safe_controller
			namespace futuristic_safe_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - magician - futuristic_safe_controller";
					static const uint32_t cfg_class_id = 0x200030;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::futuristic_safe_controller::debouncer";
					static const uint32_t cfg_class_id = 0x200030;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_config> debouncer;

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
				typedef peripheral::magnetic_lock<magnetic_lock_config> magnetic_lock;
				struct addressable_led_strip_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::futuristic_safe_controller::addressable_led_strip";
					static const uint32_t cfg_class_id = 0x200030;
					static const uint32_t cfg_member_id = 0x50;
					static const uint32_t cfg_cooldown_time = 200;
					static const uint32_t cfg_led_count = 8;
				};
				typedef peripheral::addressable_led_strip<addressable_led_strip_config> addressable_led_strip;

				/// buzzer ///
				struct buzzer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::magician::futuristic_safe_controller::buzzer";
					static const uint32_t cfg_class_id = 0x200030;
					static const uint32_t cfg_member_id = 0x60;
					static const uint32_t cfg_cooldown_time = 10;
				};
				typedef peripheral::buzzer<buzzer_config> buzzer;

			}


			/// Audio Message URL ///
			struct audio_message_url_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::audio_message_url";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0xf0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<audio_message_url_config> audio_message_url;

			/// ComDev Reset ///
			struct comdev_reset_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::comdev_reset";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0xd0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<comdev_reset_config> comdev_reset;

			/// ComDev Silence ///
			struct comdev_silence_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::comdev_silence";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0xe0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<comdev_silence_config> comdev_silence;

			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::freezed1";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x130;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<freezed1_config> freezed1;

			/// Freezed5 ///
			struct freezed5_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::freezed5";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x140;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<freezed5_config> freezed5;

			/// GM Help Status ///
			struct gm_help_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::gm_help_status";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x80;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gm_help_status_config> gm_help_status;

			/// GameEnd ///
			struct gameend_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::gameend";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x110;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gameend_config> gameend;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::gamestate";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x100;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gamestate_config> gamestate;

			/// Incoming Call ///
			struct incoming_call_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::incoming_call";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<incoming_call_config> incoming_call;

			/// Incoming Call Status ///
			struct incoming_call_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::incoming_call_status";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0xa0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<incoming_call_status_config> incoming_call_status;

			/// Paused ///
			struct paused_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::paused";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x120;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<paused_config> paused;

			/// Restart Game ///
			struct restart_game_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::restart_game";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x70;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<restart_game_config> restart_game;

			/// Text Message ///
			struct text_message_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::text_message";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0xb0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<text_message_config> text_message;

			/// Text Message Sender ///
			struct text_message_sender_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::text_message_sender";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0xc0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<text_message_sender_config> text_message_sender;

			/// pin_code ///
			struct pin_code_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::pin_code";
				typedef uint16_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x320;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<pin_code_config> pin_code;

			/// pin_pad_code ///
			struct pin_pad_code_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::pin_pad_code";
				typedef uint16_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x340;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<pin_pad_code_config> pin_pad_code;

			/// rfid_reader_code ///
			struct rfid_reader_code_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::rfid_reader_code";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x310;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<rfid_reader_code_config> rfid_reader_code;

			/// timedevent_an_1 ///
			struct timedevent_an_1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_1";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x3b0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_an_1_config> timedevent_an_1;

			/// timedevent_an_2 ///
			struct timedevent_an_2_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_2";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x430;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_an_2_config> timedevent_an_2;

			/// timedevent_an_4 ///
			struct timedevent_an_4_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_4";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x4b0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_an_4_config> timedevent_an_4;

			/// timedevent_an_6 ///
			struct timedevent_an_6_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_6";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x530;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_an_6_config> timedevent_an_6;

			/// timedevent_ap_1 ///
			struct timedevent_ap_1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::timedevent_ap_1";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x3f0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_ap_1_config> timedevent_ap_1;

			/// timedevent_pc_1 ///
			struct timedevent_pc_1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::timedevent_pc_1";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x470;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_pc_1_config> timedevent_pc_1;

			/// timedevent_pc_2 ///
			struct timedevent_pc_2_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::timedevent_pc_2";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x4f0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_pc_2_config> timedevent_pc_2;


			/// room_1
			struct room_1_config
			{
                		static const uint8_t cfg_device = 1;
				static const uint8_t cfg_channel = 1;
			};
			typedef wic::audio<room_1_config> room_1;

			namespace room_1_content
			{
				struct applause_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::applause";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/EscapeRoomAtmos/DreiFFF_Escape_Applaus2.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<applause_config> applause;
				struct chord_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::chord";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<chord_config> chord;
				struct progress_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::progress";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/progress.wav";
					constexpr static const float cfg_gain = 1.3;
				};
				typedef wic::audio_effect<progress_config> progress;
				struct careful_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::careful";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/careful.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<careful_config> careful;
				struct failstate_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::failstate";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusionen_Failstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0xf0;
				};
				typedef wic::audio_speech<failstate_config> failstate;
				struct gminc_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::gminc";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/gminc.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0x60;
				};
				typedef wic::audio_speech<gminc_config> gminc;
				struct rules_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::rules";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/rules.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0x40;
				};
				typedef wic::audio_speech<rules_config> rules;
				struct techdiff_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::techdiff";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/techdiff.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0x50;
				};
				typedef wic::audio_speech<techdiff_config> techdiff;
				struct winstate_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::winstate";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusionen_Winstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0xe0;
				};
				typedef wic::audio_speech<winstate_config> winstate;
				struct event_1_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::event_1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_0030.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0x80;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::event_2";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_1000.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0x90;
				};
				typedef wic::audio_speech<event_2_config> event_2;
				struct event_3_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::event_3";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_2000.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0xa0;
				};
				typedef wic::audio_speech<event_3_config> event_3;
				struct event_4_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::event_4";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_3000.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0xb0;
				};
				typedef wic::audio_speech<event_4_config> event_4;
				struct event_5_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::event_5";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_4000.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0xc0;
				};
				typedef wic::audio_speech<event_5_config> event_5;
				struct event_6_config
				{
					constexpr static const char *name = "ddf::magician::room_1_content::event_6";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_5500.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200060;
					static const uint32_t cfg_member_id = 0xd0;
				};
				typedef wic::audio_speech<event_6_config> event_6;

			}

			/// room_2
			struct room_2_config
			{
                		static const uint8_t cfg_device = 1;
				static const uint8_t cfg_channel = 0;
			};
			typedef wic::audio<room_2_config> room_2;

			namespace room_2_content
			{
				struct applause_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::applause";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/EscapeRoomAtmos/DreiFFF_Escape_Applaus2.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<applause_config> applause;
				struct chord_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::chord";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<chord_config> chord;
				struct progress_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::progress";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/progress.wav";
					constexpr static const float cfg_gain = 1.3;
				};
				typedef wic::audio_effect<progress_config> progress;
				struct careful_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::careful";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/careful.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<careful_config> careful;
				struct failstate_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::failstate";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusionen_Failstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0xf0;
				};
				typedef wic::audio_speech<failstate_config> failstate;
				struct gminc_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::gminc";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/gminc.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0x60;
				};
				typedef wic::audio_speech<gminc_config> gminc;
				struct rules_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::rules";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/rules.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0x40;
				};
				typedef wic::audio_speech<rules_config> rules;
				struct techdiff_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::techdiff";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/techdiff.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0x50;
				};
				typedef wic::audio_speech<techdiff_config> techdiff;
				struct winstate_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::winstate";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusionen_Winstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0xe0;
				};
				typedef wic::audio_speech<winstate_config> winstate;
				struct event_1_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::event_1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_0030.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0x80;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::event_2";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_1000.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0x90;
				};
				typedef wic::audio_speech<event_2_config> event_2;
				struct event_3_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::event_3";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_2000.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0xa0;
				};
				typedef wic::audio_speech<event_3_config> event_3;
				struct event_4_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::event_4";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_3000.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0xb0;
				};
				typedef wic::audio_speech<event_4_config> event_4;
				struct event_5_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::event_5";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_4000.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0xc0;
				};
				typedef wic::audio_speech<event_5_config> event_5;
				struct event_6_config
				{
					constexpr static const char *name = "ddf::magician::room_2_content::event_6";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Magician/DDF_EscapeRoom_Illusion_Ansager_5500.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x200050;
					static const uint32_t cfg_member_id = 0xd0;
				};
				typedef wic::audio_speech<event_6_config> event_6;

			}


			/// FreezeTimer1
			struct freezetimer1_config
			{
				constexpr static const char *name = "ddf::magician::freezetimer1";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x160;
				static const uint32_t cfg_interval  = 60000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				constexpr static const char *name = "ddf::magician::freezetimer5";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x170;
				static const uint32_t cfg_interval  = 300000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				constexpr static const char *name = "ddf::magician::gametimer";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x150;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;

			/// pin_timeout_timer
			struct pin_timeout_timer_config
			{
				constexpr static const char *name = "ddf::magician::pin_timeout_timer";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x330;
				static const uint32_t cfg_interval  = 100;
			};
			typedef typename wic::timer<pin_timeout_timer_config> pin_timeout_timer;

			/// timedevent_an_1_timer
			struct timedevent_an_1_timer_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_1_timer";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x3c0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_an_1_timer_config> timedevent_an_1_timer;

			/// timedevent_an_2_timer
			struct timedevent_an_2_timer_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_2_timer";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x440;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_an_2_timer_config> timedevent_an_2_timer;

			/// timedevent_an_4_timer
			struct timedevent_an_4_timer_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_4_timer";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x4c0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_an_4_timer_config> timedevent_an_4_timer;

			/// timedevent_an_6_timer
			struct timedevent_an_6_timer_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_6_timer";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x540;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_an_6_timer_config> timedevent_an_6_timer;

			/// timedevent_ap_1_timer
			struct timedevent_ap_1_timer_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_ap_1_timer";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x400;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_ap_1_timer_config> timedevent_ap_1_timer;

			/// timedevent_pc_1_timer
			struct timedevent_pc_1_timer_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_pc_1_timer";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x480;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_pc_1_timer_config> timedevent_pc_1_timer;

			/// timedevent_pc_2_timer
			struct timedevent_pc_2_timer_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_pc_2_timer";
				static const uint32_t cfg_class_id  = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x500;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_pc_2_timer_config> timedevent_pc_2_timer;



			/// artificial_game_ending ///		
			struct artificial_game_ending_config
			{
				constexpr static const char *name = "ddf::magician::artificial_game_ending";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x1e0;
				static bool cfg_condition()
				{
				typedef typename magician::gameend ge;
					typedef typename magician::entrance_controller::led led;
					return (true && ( 
				led::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gameend ge;
					typedef typename magician::entrance_controller::led led;
	
(void)0; {  
				ge::value(1);
			 }
				}
			};
			typedef wic::event<artificial_game_ending_config> artificial_game_ending;

			/// freeze_1 ///		
			struct freeze_1_config
			{
				constexpr static const char *name = "ddf::magician::freeze_1";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x190;
				static bool cfg_condition()
				{
				typedef typename magician::freezed1 fr;
				typedef typename magician::gamestate gs;
				typedef typename magician::freezetimer1 tmr;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::freezed1 fr;
				typedef typename magician::gamestate gs;
				typedef typename magician::freezetimer1 tmr;
	
(void)0; { 
				if(fr::value())
					tmr::start();
				else
				{
					tmr::stop();
					tmr::reset();
				}
			 }
				}
			};
			typedef wic::event<freeze_1_config> freeze_1;

			/// freeze_1_timeout ///		
			struct freeze_1_timeout_config
			{
				constexpr static const char *name = "ddf::magician::freeze_1_timeout";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x1a0;
				static bool cfg_condition()
				{
				typedef typename magician::freezetimer1 tmr;
				typedef typename magician::freezed1 fr;
					return (true && ( 
				tmr::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::freezetimer1 tmr;
				typedef typename magician::freezed1 fr;
	
(void)0; { 
				fr::value(false);
			 }
				}
			};
			typedef wic::event<freeze_1_timeout_config> freeze_1_timeout;

			/// freeze_5 ///		
			struct freeze_5_config
			{
				constexpr static const char *name = "ddf::magician::freeze_5";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x1b0;
				static bool cfg_condition()
				{
				typedef typename magician::freezed5 fr;
				typedef typename magician::gamestate gs;
				typedef typename magician::freezetimer5 tmr;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::freezed5 fr;
				typedef typename magician::gamestate gs;
				typedef typename magician::freezetimer5 tmr;
	
(void)0; { 
				if(fr::value())
					tmr::start();
				else
				{
					tmr::stop();
					tmr::reset();
				}
			 }
				}
			};
			typedef wic::event<freeze_5_config> freeze_5;

			/// freeze_5_timeout ///		
			struct freeze_5_timeout_config
			{
				constexpr static const char *name = "ddf::magician::freeze_5_timeout";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x1c0;
				static bool cfg_condition()
				{
				typedef typename magician::freezetimer5 tmr;
				typedef typename magician::freezed5 fr;
					return (true && ( 
				tmr::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::freezetimer5 tmr;
				typedef typename magician::freezed5 fr;
	
(void)0; { 
				fr::value(false);
			 }
				}
			};
			typedef wic::event<freeze_5_timeout_config> freeze_5_timeout;

			/// game_end_button_push ///		
			struct game_end_button_push_config
			{
				constexpr static const char *name = "ddf::magician::game_end_button_push";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x1f0;
				static bool cfg_condition()
				{
					typedef typename magician::entrance_controller::debouncer button;
				typedef typename magician::gameend ge;
				typedef typename magician::gamestate gs;
				typedef typename magician::comdev_silence cs;
			typedef room_1_content::winstate winstate_room_1;
			typedef room_2_content::winstate winstate_room_2;
				typedef typename magician::gametimer tmr;
					return (true && ( 
				button::value() && 1 == ge::value() && 1 == gs::value()
			 ));
				}
				static void cfg_action()
				{
					typedef typename magician::entrance_controller::debouncer button;
				typedef typename magician::gameend ge;
				typedef typename magician::gamestate gs;
				typedef typename magician::comdev_silence cs;
			typedef room_1_content::winstate winstate_room_1;
			typedef room_2_content::winstate winstate_room_2;
				typedef typename magician::gametimer tmr;
	
(void)0; { 
				tmr::stop();
				cs::value(1);
				winstate_room_1::play();
				winstate_room_2::play();
				gs::value(3);
			 }
				}
			};
			typedef wic::event<game_end_button_push_config> game_end_button_push;

			/// game_ending ///		
			struct game_ending_config
			{
				constexpr static const char *name = "ddf::magician::game_ending";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x1d0;
				static bool cfg_condition()
				{
				typedef typename magician::gameend ge;
					typedef typename magician::entrance_controller::led led;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::gameend ge;
					typedef typename magician::entrance_controller::led led;
	
(void)0; {  
				led::value(1 == ge::value());
			 }
				}
			};
			typedef wic::event<game_ending_config> game_ending;

			/// game_pause_mgmt ///		
			struct game_pause_mgmt_config
			{
				constexpr static const char *name = "ddf::magician::game_pause_mgmt";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x180;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::paused p;
				typedef typename magician::freezed1 f1;
				typedef typename magician::freezed5 f5;
				typedef typename magician::gm_help_status gm;
					typedef typename magician::entrance_controller::magnetic_sensor ed;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::paused p;
				typedef typename magician::freezed1 f1;
				typedef typename magician::freezed5 f5;
				typedef typename magician::gm_help_status gm;
					typedef typename magician::entrance_controller::magnetic_sensor ed;
	
(void)0; { 
				if(ed::value() && !p::value() && !f1::value() && !f5::value() && !gm::value())
				{
					if(gs::value() == 2)
					{
						gs::value(1);
					}
				}
				else if(gs::value() == 1)
				{
					gs::value(2);
				}
			 }
				}
			};
			typedef wic::event<game_pause_mgmt_config> game_pause_mgmt;

			/// gameevent_call_accepted ///		
			struct gameevent_call_accepted_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_call_accepted";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x280;
				static bool cfg_condition()
				{
				typedef typename magician::incoming_call_status cs;
					return (true && ( 
				2 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_accepted_config> gameevent_call_accepted;

			/// gameevent_call_declined ///		
			struct gameevent_call_declined_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_call_declined";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x290;
				static bool cfg_condition()
				{
				typedef typename magician::incoming_call_status cs;
					return (true && ( 
				3 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_declined_config> gameevent_call_declined;

			/// gameevent_call_finished ///		
			struct gameevent_call_finished_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_call_finished";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x2a0;
				static bool cfg_condition()
				{
				typedef typename magician::incoming_call_status cs;
					return (true && ( 
				4 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_finished_config> gameevent_call_finished;

			/// gameevent_call_missed ///		
			struct gameevent_call_missed_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_call_missed";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x2b0;
				static bool cfg_condition()
				{
				typedef typename magician::incoming_call_status cs;
					return (true && ( 
				5 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_missed_config> gameevent_call_missed;

			/// gameevent_call_ringing ///		
			struct gameevent_call_ringing_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_call_ringing";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x270;
				static bool cfg_condition()
				{
				typedef typename magician::incoming_call_status cs;
					return (true && ( 
				1 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_ringing_config> gameevent_call_ringing;

			/// gameevent_cupboard_controller_event_for_labyrinth_task ///		
			struct gameevent_cupboard_controller_event_for_labyrinth_task_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_cupboard_controller_event_for_labyrinth_task";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x300;
				static bool cfg_condition()
				{
					typedef typename magician::cupboard_controller::debouncer debouncer;
					typedef typename magician::cupboard_controller::magnetic_lock magnetic_lock;
					typedef typename magician::futuristic_safe_controller::addressable_led_strip led;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && ( 
            debouncer::value() && magnetic_lock::value()
         ));
				}
				static void cfg_action()
				{
					typedef typename magician::cupboard_controller::debouncer debouncer;
					typedef typename magician::cupboard_controller::magnetic_lock magnetic_lock;
					typedef typename magician::futuristic_safe_controller::addressable_led_strip led;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; { 
            magnetic_lock::value(0);
	    progress_1::play();
	    progress_2::play();
            led::enabled(false);
            led::enabled(true);
            led::value_type x = led::value();
            for(int i = 0; i < led::led_count; ++i)
            {
                x.led[i].red = 255;
                x.led[i].green = 0;
                x.led[i].blue = 0;
            }
            led::value((led::value_type)x);
         }
				}
			};
			typedef wic::event<gameevent_cupboard_controller_event_for_labyrinth_task_config> gameevent_cupboard_controller_event_for_labyrinth_task;

			/// gameevent_door_open_light_turn_on ///		
			struct gameevent_door_open_light_turn_on_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_door_open_light_turn_on";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x2f0;
				static bool cfg_condition()
				{
					typedef typename magician::cupboard_controller::magnetic_sensor sensor;
					typedef typename magician::cupboard_controller::led_strip led;
					return (true && (  
        	!sensor::value() && !led::value() 
         ));
				}
				static void cfg_action()
				{
					typedef typename magician::cupboard_controller::magnetic_sensor sensor;
					typedef typename magician::cupboard_controller::led_strip led;
	
(void)0; {  
        	led::value(1); 
         }
				}
			};
			typedef wic::event<gameevent_door_open_light_turn_on_config> gameevent_door_open_light_turn_on;

			/// gameevent_game_fail ///		
			struct gameevent_game_fail_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_game_fail";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x260;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gameend ge;
					return (true && ( 
				3 == gs::value() && 2 == ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gameend ge;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_game_fail_config> gameevent_game_fail;

			/// gameevent_game_finished ///		
			struct gameevent_game_finished_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_game_finished";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x230;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gametimer tmr;
					return (true && ( 
				3 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gametimer tmr;
	
(void)0; { 
				tmr::stop();
				tmr::reset();
			 }
				}
			};
			typedef wic::event<gameevent_game_finished_config> gameevent_game_finished;

			/// gameevent_game_paused ///		
			struct gameevent_game_paused_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_game_paused";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x220;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gametimer tmr;
					return (true && ( 
				2 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gametimer tmr;
	
(void)0; { 
				tmr::stop();
			 }
				}
			};
			typedef wic::event<gameevent_game_paused_config> gameevent_game_paused;

			/// gameevent_game_reset ///		
			struct gameevent_game_reset_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_game_reset";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x240;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gameend ge;
				typedef typename magician::text_message_sender cd_sender;
				typedef typename magician::text_message cd_text;
				typedef typename magician::gm_help_status cd_gmhelp;
				typedef typename magician::incoming_call cd_call;
				typedef typename magician::incoming_call_status cd_callstat;
				typedef typename magician::audio_message_url cd_url;
				typedef typename magician::comdev_reset cd_reset;
				typedef typename magician::freezed1 fr1;
				typedef typename magician::freezed5 fr5;
				typedef typename magician::paused paused;
				typedef typename magician::gametimer tmr;
				typedef typename magician::freezetimer1 frtmr1;
				typedef typename magician::freezetimer5 frtmr5;
					return (true && ( 
				0 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gameend ge;
				typedef typename magician::text_message_sender cd_sender;
				typedef typename magician::text_message cd_text;
				typedef typename magician::gm_help_status cd_gmhelp;
				typedef typename magician::incoming_call cd_call;
				typedef typename magician::incoming_call_status cd_callstat;
				typedef typename magician::audio_message_url cd_url;
				typedef typename magician::comdev_reset cd_reset;
				typedef typename magician::freezed1 fr1;
				typedef typename magician::freezed5 fr5;
				typedef typename magician::paused paused;
				typedef typename magician::gametimer tmr;
				typedef typename magician::freezetimer1 frtmr1;
				typedef typename magician::freezetimer5 frtmr5;
	
(void)0; { 
				tmr::stop();
				frtmr1::stop();
				frtmr5::stop();
				frtmr1::reset();
				frtmr5::reset();
				tmr::reset();

				fr1::value(0);
				fr5::value(0);
				paused::value(0);

				cd_reset::value(0);
				ge::value(0);
				cd_sender::value(0xff);
				cd_text::value((std::string)"");
				cd_call::value(0xff);
				cd_callstat::value(0);
				cd_gmhelp::value(0);
				cd_reset::value(1);
			 }
				}
			};
			typedef wic::event<gameevent_game_reset_config> gameevent_game_reset;

			/// gameevent_game_started ///		
			struct gameevent_game_started_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_game_started";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x210;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gametimer tmr;
				typedef typename magician::paused p;
				typedef typename magician::freezed1 fr1;
				typedef typename magician::freezed5 fr5;
					return (true && ( 
				1 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gametimer tmr;
				typedef typename magician::paused p;
				typedef typename magician::freezed1 fr1;
				typedef typename magician::freezed5 fr5;
	
(void)0; { 
				tmr::start();
				fr1::value(false);
				fr5::value(false);
				p::value(false);
			 }
				}
			};
			typedef wic::event<gameevent_game_started_config> gameevent_game_started;

			/// gameevent_game_win ///		
			struct gameevent_game_win_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_game_win";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x250;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gameend ge;
					return (true && ( 
				3 == gs::value() && 1 == ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::gameend ge;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_game_win_config> gameevent_game_win;

			/// gameevent_planning_wall_puzzle ///		
			struct gameevent_planning_wall_puzzle_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_planning_wall_puzzle";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x2e0;
				static bool cfg_condition()
				{
					typedef typename magician::design_board_controller::linear_magnetic_sensor_1 sensor_1;
					typedef typename magician::design_board_controller::linear_magnetic_sensor_2 sensor_2;
					typedef typename magician::design_board_controller::linear_magnetic_sensor_3 sensor_3;
					typedef typename magician::design_board_controller::magnetic_lock lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && (  
			sensor_1::value() &&
			sensor_2::value() &&
			sensor_3::value()
		 ));
				}
				static void cfg_action()
				{
					typedef typename magician::design_board_controller::linear_magnetic_sensor_1 sensor_1;
					typedef typename magician::design_board_controller::linear_magnetic_sensor_2 sensor_2;
					typedef typename magician::design_board_controller::linear_magnetic_sensor_3 sensor_3;
					typedef typename magician::design_board_controller::magnetic_lock lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; {  
			lock::value(0); 
			progress_1::play();
			progress_2::play();
		 }
				}
			};
			typedef wic::event<gameevent_planning_wall_puzzle_config> gameevent_planning_wall_puzzle;

			/// gameevent_safe_opened ///		
			struct gameevent_safe_opened_config
			{
				constexpr static const char *name = "ddf::magician::gameevent_safe_opened";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x570;
				static bool cfg_condition()
				{
				typedef typename magician::gameend ge;
					return (true && ( 
			1 == ge::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gameend ge;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_safe_opened_config> gameevent_safe_opened;

			/// keyswitch_active ///		
			struct keyswitch_active_config
			{
				constexpr static const char *name = "ddf::magician::keyswitch_active";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x360;
				static bool cfg_condition()
				{
					typedef typename magician::futuristic_safe_controller::debouncer key_switch;
					typedef typename magician::futuristic_safe_controller::addressable_led_strip led;
					return (true);
				}
				static void cfg_action()
				{
					typedef typename magician::futuristic_safe_controller::debouncer key_switch;
					typedef typename magician::futuristic_safe_controller::addressable_led_strip led;
	
(void)0; { 
            led::value_type x = led::value();
            if(key_switch::value())
            {
                for(int i = 4; i < 8; ++i)
                {
                    x.led[i].red = 0;
                    x.led[i].green = 255;
                    x.led[i].blue = 0;
                }
            }
            else
            {
                for(int i = 4; i < 8; ++i)
                {
                    x.led[i].red = 255;
                    x.led[i].green = 0;
                    x.led[i].blue = 0;
                }
            }
            led::value((led::value_type) x);
         }
				}
			};
			typedef wic::event<keyswitch_active_config> keyswitch_active;

			/// pin_code_accumulation ///		
			struct pin_code_accumulation_config
			{
				constexpr static const char *name = "ddf::magician::pin_code_accumulation";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x380;
				static bool cfg_condition()
				{
					typedef typename magician::futuristic_safe_controller::pin_pad pin_pad;
					typedef typename magician::futuristic_safe_controller::rfid_reader rfid;
					typedef typename magician::futuristic_safe_controller::debouncer key_switch;
					typedef typename magician::futuristic_safe_controller::buzzer buzzer;
				typedef typename magician::pin_timeout_timer timer;
				typedef typename magician::pin_code code;
				typedef typename magician::rfid_reader_code rfid_reader_code;
					return (true && (  
			rfid::value() == rfid_reader_code::value() &&
			key_switch::value()
		 ));
				}
				static void cfg_action()
				{
					typedef typename magician::futuristic_safe_controller::pin_pad pin_pad;
					typedef typename magician::futuristic_safe_controller::rfid_reader rfid;
					typedef typename magician::futuristic_safe_controller::debouncer key_switch;
					typedef typename magician::futuristic_safe_controller::buzzer buzzer;
				typedef typename magician::pin_timeout_timer timer;
				typedef typename magician::pin_code code;
				typedef typename magician::rfid_reader_code rfid_reader_code;
	
(void)0; { 
			keystroke_t v = pin_pad::value();

			if(!v.state)
			{
				return;
			}

			timer::reset();
			timer::start();
			const uint8_t k = v.key;
			uint8_t c;
			if(k < 9)
			{
				c = static_cast<char>(k+1);        
			}
			else if(k == 10)
			{
				c = 0;
			}
			else
				return;

			const uint16_t cv = code::value() * 10 + c;
			code::value(cv);

			if(cv < 1000)
				buzzer::beep(210,40);
			
		 }
				}
			};
			typedef wic::event<pin_code_accumulation_config> pin_code_accumulation;

			/// pin_code_test_alias_safe_activation ///		
			struct pin_code_test_alias_safe_activation_config
			{
				constexpr static const char *name = "ddf::magician::pin_code_test_alias_safe_activation";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x3a0;
				static bool cfg_condition()
				{
				typedef typename magician::pin_timeout_timer timer;
				typedef typename magician::gameend ge;
				typedef typename magician::pin_pad_code original;
					typedef typename magician::futuristic_safe_controller::pin_pad pin_pad;
					typedef typename magician::futuristic_safe_controller::magnetic_lock lock;
					typedef typename magician::futuristic_safe_controller::rfid_reader rfid;
					typedef typename magician::futuristic_safe_controller::debouncer key_switch;
				typedef typename magician::rfid_reader_code rfid_reader_code;
				typedef typename magician::pin_code code;
					typedef typename magician::futuristic_safe_controller::buzzer buzzer;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && ( 
			rfid::value() == rfid_reader_code::value() &&
			key_switch::value() &&
			code::value() >= 1000
		 ));
				}
				static void cfg_action()
				{
				typedef typename magician::pin_timeout_timer timer;
				typedef typename magician::gameend ge;
				typedef typename magician::pin_pad_code original;
					typedef typename magician::futuristic_safe_controller::pin_pad pin_pad;
					typedef typename magician::futuristic_safe_controller::magnetic_lock lock;
					typedef typename magician::futuristic_safe_controller::rfid_reader rfid;
					typedef typename magician::futuristic_safe_controller::debouncer key_switch;
				typedef typename magician::rfid_reader_code rfid_reader_code;
				typedef typename magician::pin_code code;
					typedef typename magician::futuristic_safe_controller::buzzer buzzer;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; { 
			const uint16_t v = code::value();
			code::value(0);
			if(v == original::value())
			{
				buzzer::beep(800,200);
				timer::stop();
				lock::value(0);
				ge::value(1);
				progress_1::play();
				progress_2::play();
			}
			else
				buzzer::beep(200,200);
		 }
				}
			};
			typedef wic::event<pin_code_test_alias_safe_activation_config> pin_code_test_alias_safe_activation;

			/// pin_timeout ///		
			struct pin_timeout_config
			{
				constexpr static const char *name = "ddf::magician::pin_timeout";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x390;
				static bool cfg_condition()
				{
				typedef typename magician::pin_timeout_timer timer;
				typedef typename magician::pin_code code;
					typedef typename magician::futuristic_safe_controller::buzzer buzzer;
					return (true && ( 
			timer::value() > 25 
		 ));
				}
				static void cfg_action()
				{
				typedef typename magician::pin_timeout_timer timer;
				typedef typename magician::pin_code code;
					typedef typename magician::futuristic_safe_controller::buzzer buzzer;
	
(void)0; { 
			timer::stop();
			timer::reset();
			code::value(0);
			buzzer::beep(200,200);
		 }
				}
			};
			typedef wic::event<pin_timeout_config> pin_timeout;

			/// reset_room ///		
			struct reset_room_config
			{
				constexpr static const char *name = "ddf::magician::reset_room";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x2c0;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
					typedef typename magician::cupboard_controller::magnetic_lock cabinet_door;
					typedef typename magician::cupboard_controller::led_strip cabinet_light;
					typedef typename magician::design_board_controller::magnetic_lock board_lock;
					typedef typename magician::futuristic_safe_controller::magnetic_lock safe_lock;
					typedef typename magician::futuristic_safe_controller::addressable_led_strip ledstrip;
					typedef typename magician::entrance_controller::led led;
					return (true && ( 
		!gs::value()
	 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
					typedef typename magician::cupboard_controller::magnetic_lock cabinet_door;
					typedef typename magician::cupboard_controller::led_strip cabinet_light;
					typedef typename magician::design_board_controller::magnetic_lock board_lock;
					typedef typename magician::futuristic_safe_controller::magnetic_lock safe_lock;
					typedef typename magician::futuristic_safe_controller::addressable_led_strip ledstrip;
					typedef typename magician::entrance_controller::led led;
	
(void)0; { 
		cabinet_door::value(1);
		cabinet_light::value(0);
		board_lock::value(1);
		safe_lock::value(1);
		ledstrip::value_type v;
		ledstrip::enabled(false);
		ledstrip::enabled(true);
		for(int i = 0; i < 8; ++i)
		{
			v.led[i].red = 0;
			v.led[i].green = 0;
			v.led[i].blue = 0;
		}

		ledstrip::value((ledstrip::value_type)v);
		led::value(0);
     }
				}
			};
			typedef wic::event<reset_room_config> reset_room;

			/// rfid_tag_correct ///		
			struct rfid_tag_correct_config
			{
				constexpr static const char *name = "ddf::magician::rfid_tag_correct";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x350;
				static bool cfg_condition()
				{
					typedef typename magician::futuristic_safe_controller::addressable_led_strip led;
					typedef typename magician::futuristic_safe_controller::rfid_reader rfid;
				typedef typename magician::rfid_reader_code rfid_reader_code;
					return (true);
				}
				static void cfg_action()
				{
					typedef typename magician::futuristic_safe_controller::addressable_led_strip led;
					typedef typename magician::futuristic_safe_controller::rfid_reader rfid;
				typedef typename magician::rfid_reader_code rfid_reader_code;
	
(void)0; { 
            led::value_type x = led::value();
            if(rfid_reader_code::value() == rfid::value())
            {
                for(int i = 0; i < 4; ++i)
                {
                    x.led[i].red = 0;
                    x.led[i].green = 255;
                    x.led[i].blue = 0;
                }
            }
            else
            {
                for(int i = 0; i < 4; ++i)
                {
                    x.led[i].red = 255;
                    x.led[i].green = 0;
                    x.led[i].blue = 0;
                }
            }
            led::value((led::value_type) x);
         }
				}
			};
			typedef wic::event<rfid_tag_correct_config> rfid_tag_correct;

			/// safecode_entry_activaion ///		
			struct safecode_entry_activaion_config
			{
				constexpr static const char *name = "ddf::magician::safecode_entry_activaion";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x370;
				static bool cfg_condition()
				{
					typedef typename magician::futuristic_safe_controller::rfid_reader rfid;
					typedef typename magician::futuristic_safe_controller::debouncer key_switch;
				typedef typename magician::pin_code code;
					return (true);
				}
				static void cfg_action()
				{
					typedef typename magician::futuristic_safe_controller::rfid_reader rfid;
					typedef typename magician::futuristic_safe_controller::debouncer key_switch;
				typedef typename magician::pin_code code;
	
(void)0; {  
			code::value(0); 
		 }
				}
			};
			typedef wic::event<safecode_entry_activaion_config> safecode_entry_activaion;

			/// stop_audios ///		
			struct stop_audios_config
			{
				constexpr static const char *name = "ddf::magician::stop_audios";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x2d0;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
			typedef room_1_content::careful s1;
			typedef room_1_content::rules s2;
			typedef room_1_content::techdiff s3;
			typedef room_1_content::gminc s4;
			typedef room_2_content::careful s5;
			typedef room_2_content::rules s6;
			typedef room_2_content::techdiff s7;
			typedef room_2_content::gminc s8;
			typedef room_1_content::event_1 s9;
			typedef room_1_content::event_2 sa;
			typedef room_1_content::event_3 sb;
			typedef room_1_content::event_4 sc;
			typedef room_1_content::event_5 sd;
			typedef room_1_content::event_6 se;
			typedef room_2_content::event_1 sf;
			typedef room_2_content::event_2 sg;
			typedef room_2_content::event_3 sh;
			typedef room_2_content::event_4 si;
			typedef room_2_content::event_5 sj;
			typedef room_2_content::event_6 sk;
					return (true && ( 
			3 == gs::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
			typedef room_1_content::careful s1;
			typedef room_1_content::rules s2;
			typedef room_1_content::techdiff s3;
			typedef room_1_content::gminc s4;
			typedef room_2_content::careful s5;
			typedef room_2_content::rules s6;
			typedef room_2_content::techdiff s7;
			typedef room_2_content::gminc s8;
			typedef room_1_content::event_1 s9;
			typedef room_1_content::event_2 sa;
			typedef room_1_content::event_3 sb;
			typedef room_1_content::event_4 sc;
			typedef room_1_content::event_5 sd;
			typedef room_1_content::event_6 se;
			typedef room_2_content::event_1 sf;
			typedef room_2_content::event_2 sg;
			typedef room_2_content::event_3 sh;
			typedef room_2_content::event_4 si;
			typedef room_2_content::event_5 sj;
			typedef room_2_content::event_6 sk;
	
(void)0; { 
			s1::cancel();
			s2::cancel();
			s3::cancel();
			s4::cancel();
			s5::cancel();
			s6::cancel();
			s7::cancel();
			s8::cancel();
			s9::cancel();
			sa::cancel();
			sb::cancel();
			sc::cancel();
			sd::cancel();
			se::cancel();
			sf::cancel();
			sg::cancel();
			sh::cancel();
			si::cancel();
			sj::cancel();
			sk::cancel();
		 }
				}
			};
			typedef wic::event<stop_audios_config> stop_audios;

			/// time_up ///		
			struct time_up_config
			{
				constexpr static const char *name = "ddf::magician::time_up";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x200;
				static bool cfg_condition()
				{
				typedef typename magician::gametimer tmr;
				typedef typename magician::gameend ge;
				typedef typename magician::gamestate gs;
			typedef room_1_content::failstate failstate_room_1;
			typedef room_2_content::failstate failstate_room_2;
					return (true && ( 
				tmr::value() >= 3600 && tmr::running() && 1 == gs::value() && !ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::gametimer tmr;
				typedef typename magician::gameend ge;
				typedef typename magician::gamestate gs;
			typedef room_1_content::failstate failstate_room_1;
			typedef room_2_content::failstate failstate_room_2;
	
(void)0; { 
				tmr::stop();
				failstate_room_1::play();
				failstate_room_2::play();
				ge::value(2);
				gs::value(3);
			 }
				}
			};
			typedef wic::event<time_up_config> time_up;

			/// timedevent_an_1_event_finished ///		
			struct timedevent_an_1_event_finished_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_1_event_finished";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x3d0;
				static bool cfg_condition()
				{
				typedef typename magician::timedevent_an_1 __timedevent_at;
				typedef typename magician::timedevent_an_1_timer __timedevent_timer;
			typedef room_1_content::event_1 r1;
			typedef room_2_content::event_1 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::timedevent_an_1 __timedevent_at;
				typedef typename magician::timedevent_an_1_timer __timedevent_timer;
			typedef room_1_content::event_1 r1;
			typedef room_2_content::event_1 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_an_1_event_finished_config> timedevent_an_1_event_finished;

			/// timedevent_an_1_event_gamestate ///		
			struct timedevent_an_1_event_gamestate_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_1_event_gamestate";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x3e0;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_an_1_timer tmr;
				typedef typename magician::timedevent_an_1 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_an_1_timer tmr;
				typedef typename magician::timedevent_an_1 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_an_1_event_gamestate_config> timedevent_an_1_event_gamestate;

			/// timedevent_an_2_event_finished ///		
			struct timedevent_an_2_event_finished_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_2_event_finished";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x450;
				static bool cfg_condition()
				{
				typedef typename magician::timedevent_an_2 __timedevent_at;
				typedef typename magician::timedevent_an_2_timer __timedevent_timer;
			typedef room_1_content::event_2 r1;
			typedef room_2_content::event_2 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::timedevent_an_2 __timedevent_at;
				typedef typename magician::timedevent_an_2_timer __timedevent_timer;
			typedef room_1_content::event_2 r1;
			typedef room_2_content::event_2 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_an_2_event_finished_config> timedevent_an_2_event_finished;

			/// timedevent_an_2_event_gamestate ///		
			struct timedevent_an_2_event_gamestate_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_2_event_gamestate";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x460;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_an_2_timer tmr;
				typedef typename magician::timedevent_an_2 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_an_2_timer tmr;
				typedef typename magician::timedevent_an_2 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_an_2_event_gamestate_config> timedevent_an_2_event_gamestate;

			/// timedevent_an_4_event_finished ///		
			struct timedevent_an_4_event_finished_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_4_event_finished";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x4d0;
				static bool cfg_condition()
				{
				typedef typename magician::timedevent_an_4 __timedevent_at;
				typedef typename magician::timedevent_an_4_timer __timedevent_timer;
			typedef room_1_content::event_4 r1;
			typedef room_2_content::event_4 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::timedevent_an_4 __timedevent_at;
				typedef typename magician::timedevent_an_4_timer __timedevent_timer;
			typedef room_1_content::event_4 r1;
			typedef room_2_content::event_4 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_an_4_event_finished_config> timedevent_an_4_event_finished;

			/// timedevent_an_4_event_gamestate ///		
			struct timedevent_an_4_event_gamestate_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_4_event_gamestate";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x4e0;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_an_4_timer tmr;
				typedef typename magician::timedevent_an_4 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_an_4_timer tmr;
				typedef typename magician::timedevent_an_4 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_an_4_event_gamestate_config> timedevent_an_4_event_gamestate;

			/// timedevent_an_6_event_finished ///		
			struct timedevent_an_6_event_finished_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_6_event_finished";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x550;
				static bool cfg_condition()
				{
				typedef typename magician::timedevent_an_6 __timedevent_at;
				typedef typename magician::timedevent_an_6_timer __timedevent_timer;
			typedef room_1_content::event_6 r1;
			typedef room_2_content::event_6 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::timedevent_an_6 __timedevent_at;
				typedef typename magician::timedevent_an_6_timer __timedevent_timer;
			typedef room_1_content::event_6 r1;
			typedef room_2_content::event_6 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_an_6_event_finished_config> timedevent_an_6_event_finished;

			/// timedevent_an_6_event_gamestate ///		
			struct timedevent_an_6_event_gamestate_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_an_6_event_gamestate";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x560;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_an_6_timer tmr;
				typedef typename magician::timedevent_an_6 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_an_6_timer tmr;
				typedef typename magician::timedevent_an_6 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_an_6_event_gamestate_config> timedevent_an_6_event_gamestate;

			/// timedevent_ap_1_event_finished ///		
			struct timedevent_ap_1_event_finished_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_ap_1_event_finished";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x410;
				static bool cfg_condition()
				{
				typedef typename magician::timedevent_ap_1 __timedevent_at;
				typedef typename magician::timedevent_ap_1_timer __timedevent_timer;
			typedef room_1_content::applause r1;
			typedef room_2_content::applause r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::timedevent_ap_1 __timedevent_at;
				typedef typename magician::timedevent_ap_1_timer __timedevent_timer;
			typedef room_1_content::applause r1;
			typedef room_2_content::applause r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_ap_1_event_finished_config> timedevent_ap_1_event_finished;

			/// timedevent_ap_1_event_gamestate ///		
			struct timedevent_ap_1_event_gamestate_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_ap_1_event_gamestate";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x420;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_ap_1_timer tmr;
				typedef typename magician::timedevent_ap_1 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_ap_1_timer tmr;
				typedef typename magician::timedevent_ap_1 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_ap_1_event_gamestate_config> timedevent_ap_1_event_gamestate;

			/// timedevent_pc_1_event_finished ///		
			struct timedevent_pc_1_event_finished_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_pc_1_event_finished";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x490;
				static bool cfg_condition()
				{
				typedef typename magician::timedevent_pc_1 __timedevent_at;
				typedef typename magician::timedevent_pc_1_timer __timedevent_timer;
				typedef typename magician::incoming_call call;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::timedevent_pc_1 __timedevent_at;
				typedef typename magician::timedevent_pc_1_timer __timedevent_timer;
				typedef typename magician::incoming_call call;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				call::value(0);
			 }
				}
			};
			typedef wic::event<timedevent_pc_1_event_finished_config> timedevent_pc_1_event_finished;

			/// timedevent_pc_1_event_gamestate ///		
			struct timedevent_pc_1_event_gamestate_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_pc_1_event_gamestate";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x4a0;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_pc_1_timer tmr;
				typedef typename magician::timedevent_pc_1 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_pc_1_timer tmr;
				typedef typename magician::timedevent_pc_1 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_pc_1_event_gamestate_config> timedevent_pc_1_event_gamestate;

			/// timedevent_pc_2_event_finished ///		
			struct timedevent_pc_2_event_finished_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_pc_2_event_finished";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x510;
				static bool cfg_condition()
				{
				typedef typename magician::timedevent_pc_2 __timedevent_at;
				typedef typename magician::timedevent_pc_2_timer __timedevent_timer;
				typedef typename magician::incoming_call call;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename magician::timedevent_pc_2 __timedevent_at;
				typedef typename magician::timedevent_pc_2_timer __timedevent_timer;
				typedef typename magician::incoming_call call;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				call::value(1);
			 }
				}
			};
			typedef wic::event<timedevent_pc_2_event_finished_config> timedevent_pc_2_event_finished;

			/// timedevent_pc_2_event_gamestate ///		
			struct timedevent_pc_2_event_gamestate_config
			{
				constexpr static const char *name = "ddf::magician::timedevent_pc_2_event_gamestate";
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x520;
				static bool cfg_condition()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_pc_2_timer tmr;
				typedef typename magician::timedevent_pc_2 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename magician::gamestate gs;
				typedef typename magician::timedevent_pc_2_timer tmr;
				typedef typename magician::timedevent_pc_2 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_pc_2_event_gamestate_config> timedevent_pc_2_event_gamestate;
}

	/// Room villa
	namespace villa
	{

			/// control_room_controller
			namespace control_room_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - control_room_controller";
					static const uint32_t cfg_class_id = 0x300030;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// switch_1 ///
				struct switch_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::switch_1";
					static const uint32_t cfg_class_id = 0x300030;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<switch_1_config> switch_1;

				/// magnetic_lock ///
				struct magnetic_lock_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::magnetic_lock";
					static const uint32_t cfg_class_id = 0x300030;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_config> magnetic_lock;

				/// debouncer_1 ///
				struct debouncer_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::debouncer_1";
					static const uint32_t cfg_class_id = 0x300030;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_1_config> debouncer_1;

				/// led_1 ///
				struct led_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::led_1";
					static const uint32_t cfg_class_id = 0x300030;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<led_1_config> led_1;

				/// led_2 ///
				struct led_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::control_room_controller::led_2";
					static const uint32_t cfg_class_id = 0x300030;
					static const uint32_t cfg_member_id = 0x50;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::led_strip<led_2_config> led_2;

			}

			/// desk_controller
			namespace desk_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - desk_controller";
					static const uint32_t cfg_class_id = 0x300020;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// debouncer_3 ///
				struct debouncer_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desk_controller::debouncer_3";
					static const uint32_t cfg_class_id = 0x300020;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_3_config> debouncer_3;

				/// debouncer_4 ///
				struct debouncer_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desk_controller::debouncer_4";
					static const uint32_t cfg_class_id = 0x300020;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_4_config> debouncer_4;

			}

			/// desktop_pc
			namespace desktop_pc
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - desktop_pc";
					static const uint32_t cfg_class_id = 0x300050;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// Started ///
				struct started_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::started";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x10;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<started_config> started;

				/// Shutdown ///
				struct shutdown_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::shutdown";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x20;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<shutdown_config> shutdown;

				/// Bad Password ///
				struct bad_password_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::bad_password";

					typedef std::string cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x30;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<bad_password_config> bad_password;

				/// Logged In ///
				struct logged_in_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::logged_in";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x40;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<logged_in_config> logged_in;

				/// Recycled Restore ///
				struct recycled_restore_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::recycled_restore";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x50;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<recycled_restore_config> recycled_restore;

				/// Audioplay started ///
				struct audioplay_started_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audioplay_started";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x60;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<audioplay_started_config> audioplay_started;

				/// Audioplay finished ///
				struct audioplay_finished_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audioplay_finished";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x70;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<audioplay_finished_config> audioplay_finished;

				/// Audioplay paused ///
				struct audioplay_paused_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audioplay_paused";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x80;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<audioplay_paused_config> audioplay_paused;

				/// Restart Game ///
				struct restart_game_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::restart_game";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x90;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<restart_game_config> restart_game;

				/// Audioplay startevent ///
				struct audioplay_startevent_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audioplay_startevent";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0xa0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<audioplay_startevent_config> audioplay_startevent;

				/// Audiopause pauseevent ///
				struct audiopause_pauseevent_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audiopause_pauseevent";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0xb0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<audiopause_pauseevent_config> audiopause_pauseevent;

			}

			/// entrance_controller
			namespace entrance_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - entrance_controller";
					static const uint32_t cfg_class_id = 0x300040;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::entrance_controller::debouncer";
					static const uint32_t cfg_class_id = 0x300040;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_config> debouncer;

				/// led ///
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::entrance_controller::led";
					static const uint32_t cfg_class_id = 0x300040;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::led_strip<led_config> led;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::entrance_controller::magnetic_sensor";
					static const uint32_t cfg_class_id = 0x300040;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_config> magnetic_sensor;

			}

			/// safe_controller
			namespace safe_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - safe_controller";
					static const uint32_t cfg_class_id = 0x300010;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

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
				typedef peripheral::magnetic_lock<magnetic_lock_config> magnetic_lock;

				/// debouncer_1 ///
				struct debouncer_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::safe_controller::debouncer_1";
					static const uint32_t cfg_class_id = 0x300010;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_1_config> debouncer_1;

				/// debouncer_2 ///
				struct debouncer_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::safe_controller::debouncer_2";
					static const uint32_t cfg_class_id = 0x300010;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_2_config> debouncer_2;

				/// buzzer ///
				struct buzzer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::safe_controller::buzzer";
					static const uint32_t cfg_class_id = 0x300010;
					static const uint32_t cfg_member_id = 0x50;
					static const uint32_t cfg_cooldown_time = 10;
				};
				typedef peripheral::buzzer<buzzer_config> buzzer;

			}

			/// video_device
			namespace video_device
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - video_device";
					static const uint32_t cfg_class_id = 0x300060;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// Started ///
				struct started_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::started";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x10;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<started_config> started;

				/// Shutdown ///
				struct shutdown_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::shutdown";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x20;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<shutdown_config> shutdown;

				/// LiveCam started ///
				struct livecam_started_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::livecam_started";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x30;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<livecam_started_config> livecam_started;

				/// LiveCamSlides started ///
				struct livecamslides_started_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::livecamslides_started";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x40;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<livecamslides_started_config> livecamslides_started;

				/// Restart Game ///
				struct restart_game_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::restart_game";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x50;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<restart_game_config> restart_game;

				/// Start LiveCams ///
				struct start_livecams_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::start_livecams";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x60;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<start_livecams_config> start_livecams;

				/// Stop LiveCams ///
				struct stop_livecams_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::stop_livecams";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x70;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<stop_livecams_config> stop_livecams;

				/// Start Tape ///
				struct start_tape_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::start_tape";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x80;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<start_tape_config> start_tape;

				/// Stop Tape ///
				struct stop_tape_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::stop_tape";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x90;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<stop_tape_config> stop_tape;

				/// Pause Tape ///
				struct pause_tape_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::pause_tape";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xa0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<pause_tape_config> pause_tape;

				/// Finished Tape ///
				struct finished_tape_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::finished_tape";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xb0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<finished_tape_config> finished_tape;

				/// enabled ///
				struct enabled_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::enabled";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xc0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<enabled_config> enabled;

				/// Eject ///
				struct eject_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::eject";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xd0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<eject_config> eject;

				/// casette_id ///
				struct casette_id_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::casette_id";

					typedef uint64_t cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xe0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<casette_id_config> casette_id;

				/// play_ongoing ///
				struct play_ongoing_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::play_ongoing";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xf0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<play_ongoing_config> play_ongoing;

				/// livecam_ongoing ///
				struct livecam_ongoing_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::livecam_ongoing";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x100;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<livecam_ongoing_config> livecam_ongoing;

			}


			/// Audio Message URL ///
			struct audio_message_url_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::audio_message_url";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x110;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<audio_message_url_config> audio_message_url;

			/// ComDev Reset ///
			struct comdev_reset_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::comdev_reset";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0xf0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<comdev_reset_config> comdev_reset;

			/// ComDev Silence ///
			struct comdev_silence_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::comdev_silence";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x100;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<comdev_silence_config> comdev_silence;

			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::freezed1";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x150;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<freezed1_config> freezed1;

			/// Freezed5 ///
			struct freezed5_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::freezed5";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x160;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<freezed5_config> freezed5;

			/// GM Help Status ///
			struct gm_help_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::gm_help_status";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0xa0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gm_help_status_config> gm_help_status;

			/// GameEnd ///
			struct gameend_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::gameend";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x130;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gameend_config> gameend;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::gamestate";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x120;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gamestate_config> gamestate;

			/// Incoming Call ///
			struct incoming_call_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::incoming_call";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0xb0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<incoming_call_config> incoming_call;

			/// Incoming Call Status ///
			struct incoming_call_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::incoming_call_status";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0xc0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<incoming_call_status_config> incoming_call_status;

			/// Paused ///
			struct paused_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::paused";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x140;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<paused_config> paused;

			/// Restart Game ///
			struct restart_game_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::restart_game";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<restart_game_config> restart_game;

			/// Text Message ///
			struct text_message_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::text_message";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0xd0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<text_message_config> text_message;

			/// Text Message Sender ///
			struct text_message_sender_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::text_message_sender";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0xe0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<text_message_sender_config> text_message_sender;

			/// pin_code ///
			struct pin_code_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::pin_code";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x350;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<pin_code_config> pin_code;

			/// timedevent_funk_1 ///
			struct timedevent_funk_1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_1";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x3d0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_funk_1_config> timedevent_funk_1;

			/// timedevent_funk_2 ///
			struct timedevent_funk_2_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_2";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x490;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_funk_2_config> timedevent_funk_2;

			/// timedevent_funk_3 ///
			struct timedevent_funk_3_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_3";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x510;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_funk_3_config> timedevent_funk_3;

			/// timedevent_pc_1 ///
			struct timedevent_pc_1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_1";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x410;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_pc_1_config> timedevent_pc_1;

			/// timedevent_pc_2 ///
			struct timedevent_pc_2_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_2";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x450;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_pc_2_config> timedevent_pc_2;

			/// timedevent_pc_3 ///
			struct timedevent_pc_3_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_3";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x4d0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_pc_3_config> timedevent_pc_3;


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
					constexpr static const char *name = "ddf::villa::room_1_content::chord";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<chord_config> chord;
				struct progress_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::progress";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/progress.wav";
					constexpr static const float cfg_gain = 1.3;
				};
				typedef wic::audio_effect<progress_config> progress;
				struct careful_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::careful";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/careful.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300080;
					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<careful_config> careful;
				struct gminc_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::gminc";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/gminc.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300080;
					static const uint32_t cfg_member_id = 0x60;
				};
				typedef wic::audio_speech<gminc_config> gminc;
				struct rules_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::rules";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/rules.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300080;
					static const uint32_t cfg_member_id = 0x40;
				};
				typedef wic::audio_speech<rules_config> rules;
				struct techdiff_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::techdiff";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/techdiff.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300080;
					static const uint32_t cfg_member_id = 0x50;
				};
				typedef wic::audio_speech<techdiff_config> techdiff;
				struct event_1_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::event_1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Anrufbe_Funk1.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300080;
					static const uint32_t cfg_member_id = 0x70;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::event_2";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Anrufbe_Funk2.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300080;
					static const uint32_t cfg_member_id = 0x80;
				};
				typedef wic::audio_speech<event_2_config> event_2;
				struct event_3_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::event_3";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Anrufbe_Funk3.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300080;
					static const uint32_t cfg_member_id = 0x90;
				};
				typedef wic::audio_speech<event_3_config> event_3;
				struct event_4_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::event_4";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Winstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300080;
					static const uint32_t cfg_member_id = 0xa0;
				};
				typedef wic::audio_speech<event_4_config> event_4;
				struct event_5_config
				{
					constexpr static const char *name = "ddf::villa::room_1_content::event_5";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Failstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300080;
					static const uint32_t cfg_member_id = 0xb0;
				};
				typedef wic::audio_speech<event_5_config> event_5;

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
					constexpr static const char *name = "ddf::villa::room_2_content::chord";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<chord_config> chord;
				struct progress_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::progress";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/progress.wav";
					constexpr static const float cfg_gain = 1.3;
				};
				typedef wic::audio_effect<progress_config> progress;
				struct careful_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::careful";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/careful.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300070;
					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<careful_config> careful;
				struct gminc_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::gminc";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/gminc.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300070;
					static const uint32_t cfg_member_id = 0x60;
				};
				typedef wic::audio_speech<gminc_config> gminc;
				struct rules_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::rules";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/rules.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300070;
					static const uint32_t cfg_member_id = 0x40;
				};
				typedef wic::audio_speech<rules_config> rules;
				struct techdiff_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::techdiff";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/techdiff.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300070;
					static const uint32_t cfg_member_id = 0x50;
				};
				typedef wic::audio_speech<techdiff_config> techdiff;
				struct event_1_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::event_1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Anrufbe_Funk1.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300070;
					static const uint32_t cfg_member_id = 0x70;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::event_2";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Anrufbe_Funk2.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300070;
					static const uint32_t cfg_member_id = 0x80;
				};
				typedef wic::audio_speech<event_2_config> event_2;
				struct event_3_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::event_3";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Anrufbe_Funk3.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300070;
					static const uint32_t cfg_member_id = 0x90;
				};
				typedef wic::audio_speech<event_3_config> event_3;
				struct event_4_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::event_4";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Winstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300070;
					static const uint32_t cfg_member_id = 0xa0;
				};
				typedef wic::audio_speech<event_4_config> event_4;
				struct event_5_config
				{
					constexpr static const char *name = "ddf::villa::room_2_content::event_5";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Villa/DDF_EscapeRoom_Totenkopf_Failstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x300070;
					static const uint32_t cfg_member_id = 0xb0;
				};
				typedef wic::audio_speech<event_5_config> event_5;

			}


			/// FreezeTimer1
			struct freezetimer1_config
			{
				constexpr static const char *name = "ddf::villa::freezetimer1";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x180;
				static const uint32_t cfg_interval  = 60000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				constexpr static const char *name = "ddf::villa::freezetimer5";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x190;
				static const uint32_t cfg_interval  = 300000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				constexpr static const char *name = "ddf::villa::gametimer";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x170;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;

			/// eject_wait
			struct eject_wait_config
			{
				constexpr static const char *name = "ddf::villa::eject_wait";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x300;
				static const uint32_t cfg_interval  = 400;
			};
			typedef typename wic::timer<eject_wait_config> eject_wait;

			/// pin_timeout_timer
			struct pin_timeout_timer_config
			{
				constexpr static const char *name = "ddf::villa::pin_timeout_timer";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x360;
				static const uint32_t cfg_interval  = 100;
			};
			typedef typename wic::timer<pin_timeout_timer_config> pin_timeout_timer;

			/// timedevent_funk_1_timer
			struct timedevent_funk_1_timer_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_1_timer";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x3e0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_funk_1_timer_config> timedevent_funk_1_timer;

			/// timedevent_funk_2_timer
			struct timedevent_funk_2_timer_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_2_timer";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x4a0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_funk_2_timer_config> timedevent_funk_2_timer;

			/// timedevent_funk_3_timer
			struct timedevent_funk_3_timer_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_3_timer";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x520;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_funk_3_timer_config> timedevent_funk_3_timer;

			/// timedevent_pc_1_timer
			struct timedevent_pc_1_timer_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_1_timer";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x420;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_pc_1_timer_config> timedevent_pc_1_timer;

			/// timedevent_pc_2_timer
			struct timedevent_pc_2_timer_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_2_timer";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x460;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_pc_2_timer_config> timedevent_pc_2_timer;

			/// timedevent_pc_3_timer
			struct timedevent_pc_3_timer_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_3_timer";
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x4e0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_pc_3_timer_config> timedevent_pc_3_timer;



			/// answering_machine ///		
			struct answering_machine_config
			{
				constexpr static const char *name = "ddf::villa::answering_machine";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x3b0;
				static bool cfg_condition()
				{
				typedef typename villa::desktop_pc::audioplay_started audio_start;
				typedef typename villa::desktop_pc::audioplay_paused audio_pause;
					typedef typename villa::desk_controller::debouncer_4 voice_recorder;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::desktop_pc::audioplay_started audio_start;
				typedef typename villa::desktop_pc::audioplay_paused audio_pause;
					typedef typename villa::desk_controller::debouncer_4 voice_recorder;
	
(void)0; { 
			if(!audio_start::value())
				audio_start::value(voice_recorder::value());
			audio_pause::value(!voice_recorder::value());
		 }
				}
			};
			typedef wic::event<answering_machine_config> answering_machine;

			/// artificial_game_ending ///		
			struct artificial_game_ending_config
			{
				constexpr static const char *name = "ddf::villa::artificial_game_ending";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x200;
				static bool cfg_condition()
				{
				typedef typename villa::gameend ge;
					typedef typename villa::entrance_controller::led led;
					return (true && ( 
				led::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gameend ge;
					typedef typename villa::entrance_controller::led led;
	
(void)0; {  
				ge::value(1);
			 }
				}
			};
			typedef wic::event<artificial_game_ending_config> artificial_game_ending;

			/// freeze_1 ///		
			struct freeze_1_config
			{
				constexpr static const char *name = "ddf::villa::freeze_1";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1b0;
				static bool cfg_condition()
				{
				typedef typename villa::freezed1 fr;
				typedef typename villa::gamestate gs;
				typedef typename villa::freezetimer1 tmr;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::freezed1 fr;
				typedef typename villa::gamestate gs;
				typedef typename villa::freezetimer1 tmr;
	
(void)0; { 
				if(fr::value())
					tmr::start();
				else
				{
					tmr::stop();
					tmr::reset();
				}
			 }
				}
			};
			typedef wic::event<freeze_1_config> freeze_1;

			/// freeze_1_timeout ///		
			struct freeze_1_timeout_config
			{
				constexpr static const char *name = "ddf::villa::freeze_1_timeout";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1c0;
				static bool cfg_condition()
				{
				typedef typename villa::freezetimer1 tmr;
				typedef typename villa::freezed1 fr;
					return (true && ( 
				tmr::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::freezetimer1 tmr;
				typedef typename villa::freezed1 fr;
	
(void)0; { 
				fr::value(false);
			 }
				}
			};
			typedef wic::event<freeze_1_timeout_config> freeze_1_timeout;

			/// freeze_5 ///		
			struct freeze_5_config
			{
				constexpr static const char *name = "ddf::villa::freeze_5";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1d0;
				static bool cfg_condition()
				{
				typedef typename villa::freezed5 fr;
				typedef typename villa::gamestate gs;
				typedef typename villa::freezetimer5 tmr;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::freezed5 fr;
				typedef typename villa::gamestate gs;
				typedef typename villa::freezetimer5 tmr;
	
(void)0; { 
				if(fr::value())
					tmr::start();
				else
				{
					tmr::stop();
					tmr::reset();
				}
			 }
				}
			};
			typedef wic::event<freeze_5_config> freeze_5;

			/// freeze_5_timeout ///		
			struct freeze_5_timeout_config
			{
				constexpr static const char *name = "ddf::villa::freeze_5_timeout";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1e0;
				static bool cfg_condition()
				{
				typedef typename villa::freezetimer5 tmr;
				typedef typename villa::freezed5 fr;
					return (true && ( 
				tmr::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::freezetimer5 tmr;
				typedef typename villa::freezed5 fr;
	
(void)0; { 
				fr::value(false);
			 }
				}
			};
			typedef wic::event<freeze_5_timeout_config> freeze_5_timeout;

			/// game_end_button_push ///		
			struct game_end_button_push_config
			{
				constexpr static const char *name = "ddf::villa::game_end_button_push";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x210;
				static bool cfg_condition()
				{
					typedef typename villa::entrance_controller::debouncer button;
				typedef typename villa::gameend ge;
				typedef typename villa::gamestate gs;
				typedef typename villa::comdev_silence cs;
			typedef room_1_content::event_4 winstate_room_1;
			typedef room_2_content::event_4 winstate_room_2;
				typedef typename villa::gametimer tmr;
					return (true && ( 
				button::value() && 1 == ge::value() && 1 == gs::value()
			 ));
				}
				static void cfg_action()
				{
					typedef typename villa::entrance_controller::debouncer button;
				typedef typename villa::gameend ge;
				typedef typename villa::gamestate gs;
				typedef typename villa::comdev_silence cs;
			typedef room_1_content::event_4 winstate_room_1;
			typedef room_2_content::event_4 winstate_room_2;
				typedef typename villa::gametimer tmr;
	
(void)0; { 
				tmr::stop();
				cs::value(1);
				winstate_room_1::play();
				winstate_room_2::play();
				gs::value(3);
			 }
				}
			};
			typedef wic::event<game_end_button_push_config> game_end_button_push;

			/// game_ending ///		
			struct game_ending_config
			{
				constexpr static const char *name = "ddf::villa::game_ending";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1f0;
				static bool cfg_condition()
				{
				typedef typename villa::gameend ge;
					typedef typename villa::entrance_controller::led led;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::gameend ge;
					typedef typename villa::entrance_controller::led led;
	
(void)0; {  
				led::value(1 == ge::value());
			 }
				}
			};
			typedef wic::event<game_ending_config> game_ending;

			/// game_pause_mgmt ///		
			struct game_pause_mgmt_config
			{
				constexpr static const char *name = "ddf::villa::game_pause_mgmt";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1a0;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::paused p;
				typedef typename villa::freezed1 f1;
				typedef typename villa::freezed5 f5;
				typedef typename villa::gm_help_status gm;
					typedef typename villa::entrance_controller::magnetic_sensor ed;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::paused p;
				typedef typename villa::freezed1 f1;
				typedef typename villa::freezed5 f5;
				typedef typename villa::gm_help_status gm;
					typedef typename villa::entrance_controller::magnetic_sensor ed;
	
(void)0; { 
				if(ed::value() && !p::value() && !f1::value() && !f5::value() && !gm::value())
				{
					if(gs::value() == 2)
					{
						gs::value(1);
					}
				}
				else if(gs::value() == 1)
				{
					gs::value(2);
				}
			 }
				}
			};
			typedef wic::event<game_pause_mgmt_config> game_pause_mgmt;

			/// gameevent_call_accepted ///		
			struct gameevent_call_accepted_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_call_accepted";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x2a0;
				static bool cfg_condition()
				{
				typedef typename villa::incoming_call_status cs;
					return (true && ( 
				2 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_accepted_config> gameevent_call_accepted;

			/// gameevent_call_declined ///		
			struct gameevent_call_declined_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_call_declined";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x2b0;
				static bool cfg_condition()
				{
				typedef typename villa::incoming_call_status cs;
					return (true && ( 
				3 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_declined_config> gameevent_call_declined;

			/// gameevent_call_finished ///		
			struct gameevent_call_finished_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_call_finished";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x2c0;
				static bool cfg_condition()
				{
				typedef typename villa::incoming_call_status cs;
					return (true && ( 
				4 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_finished_config> gameevent_call_finished;

			/// gameevent_call_missed ///		
			struct gameevent_call_missed_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_call_missed";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x2d0;
				static bool cfg_condition()
				{
				typedef typename villa::incoming_call_status cs;
					return (true && ( 
				5 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_missed_config> gameevent_call_missed;

			/// gameevent_call_ringing ///		
			struct gameevent_call_ringing_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_call_ringing";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x290;
				static bool cfg_condition()
				{
				typedef typename villa::incoming_call_status cs;
					return (true && ( 
				1 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_ringing_config> gameevent_call_ringing;

			/// gameevent_casette_eject_trigger ///		
			struct gameevent_casette_eject_trigger_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_casette_eject_trigger";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x310;
				static bool cfg_condition()
				{
					typedef typename villa::control_room_controller::debouncer_1 button;
				typedef typename villa::video_device::eject eject;
					return (true && ( 
			button::value()
		 ));
				}
				static void cfg_action()
				{
					typedef typename villa::control_room_controller::debouncer_1 button;
				typedef typename villa::video_device::eject eject;
	
(void)0; { 
			eject::value(1);
		 }
				}
			};
			typedef wic::event<gameevent_casette_eject_trigger_config> gameevent_casette_eject_trigger;

			/// gameevent_desktop_pc_login ///		
			struct gameevent_desktop_pc_login_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_desktop_pc_login";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x3c0;
				static bool cfg_condition()
				{
				typedef typename villa::desktop_pc::logged_in l;
					return (true && ( l::value() ));
				}
				static void cfg_action()
				{
				typedef typename villa::desktop_pc::logged_in l;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_desktop_pc_login_config> gameevent_desktop_pc_login;

			/// gameevent_finding_the_keys ///		
			struct gameevent_finding_the_keys_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_finding_the_keys";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x340;
				static bool cfg_condition()
				{
					typedef typename villa::safe_controller::debouncer_1 switch_1;
					typedef typename villa::safe_controller::debouncer_2 switch_2;
					typedef typename villa::desk_controller::debouncer_3 switch_3;
					typedef typename villa::control_room_controller::magnetic_lock secret_door;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && (  
			switch_1::value() &&
			switch_2::value() &&
			switch_3::value()
	     ));
				}
				static void cfg_action()
				{
					typedef typename villa::safe_controller::debouncer_1 switch_1;
					typedef typename villa::safe_controller::debouncer_2 switch_2;
					typedef typename villa::desk_controller::debouncer_3 switch_3;
					typedef typename villa::control_room_controller::magnetic_lock secret_door;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; {  
    			secret_door::value(0); 
			progress_1::play();
			progress_2::play();
		 }
				}
			};
			typedef wic::event<gameevent_finding_the_keys_config> gameevent_finding_the_keys;

			/// gameevent_game_fail ///		
			struct gameevent_game_fail_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_game_fail";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x280;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gameend ge;
					return (true && ( 
				3 == gs::value() && 2 == ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gameend ge;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_game_fail_config> gameevent_game_fail;

			/// gameevent_game_finished ///		
			struct gameevent_game_finished_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_game_finished";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x250;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gametimer tmr;
					return (true && ( 
				3 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gametimer tmr;
	
(void)0; { 
				tmr::stop();
				tmr::reset();
			 }
				}
			};
			typedef wic::event<gameevent_game_finished_config> gameevent_game_finished;

			/// gameevent_game_paused ///		
			struct gameevent_game_paused_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_game_paused";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x240;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gametimer tmr;
					return (true && ( 
				2 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gametimer tmr;
	
(void)0; { 
				tmr::stop();
			 }
				}
			};
			typedef wic::event<gameevent_game_paused_config> gameevent_game_paused;

			/// gameevent_game_reset ///		
			struct gameevent_game_reset_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_game_reset";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x260;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gameend ge;
				typedef typename villa::text_message_sender cd_sender;
				typedef typename villa::text_message cd_text;
				typedef typename villa::gm_help_status cd_gmhelp;
				typedef typename villa::incoming_call cd_call;
				typedef typename villa::incoming_call_status cd_callstat;
				typedef typename villa::audio_message_url cd_url;
				typedef typename villa::comdev_reset cd_reset;
				typedef typename villa::freezed1 fr1;
				typedef typename villa::freezed5 fr5;
				typedef typename villa::paused paused;
				typedef typename villa::gametimer tmr;
				typedef typename villa::freezetimer1 frtmr1;
				typedef typename villa::freezetimer5 frtmr5;
					return (true && ( 
				0 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gameend ge;
				typedef typename villa::text_message_sender cd_sender;
				typedef typename villa::text_message cd_text;
				typedef typename villa::gm_help_status cd_gmhelp;
				typedef typename villa::incoming_call cd_call;
				typedef typename villa::incoming_call_status cd_callstat;
				typedef typename villa::audio_message_url cd_url;
				typedef typename villa::comdev_reset cd_reset;
				typedef typename villa::freezed1 fr1;
				typedef typename villa::freezed5 fr5;
				typedef typename villa::paused paused;
				typedef typename villa::gametimer tmr;
				typedef typename villa::freezetimer1 frtmr1;
				typedef typename villa::freezetimer5 frtmr5;
	
(void)0; { 
				tmr::stop();
				frtmr1::stop();
				frtmr5::stop();
				frtmr1::reset();
				frtmr5::reset();
				tmr::reset();

				fr1::value(0);
				fr5::value(0);
				paused::value(0);

				cd_reset::value(0);
				ge::value(0);
				cd_sender::value(0xff);
				cd_text::value((std::string)"");
				cd_call::value(0xff);
				cd_callstat::value(0);
				cd_gmhelp::value(0);
				cd_reset::value(1);
			 }
				}
			};
			typedef wic::event<gameevent_game_reset_config> gameevent_game_reset;

			/// gameevent_game_started ///		
			struct gameevent_game_started_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_game_started";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x230;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gametimer tmr;
				typedef typename villa::paused p;
				typedef typename villa::freezed1 fr1;
				typedef typename villa::freezed5 fr5;
					return (true && ( 
				1 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gametimer tmr;
				typedef typename villa::paused p;
				typedef typename villa::freezed1 fr1;
				typedef typename villa::freezed5 fr5;
	
(void)0; { 
				tmr::start();
				fr1::value(false);
				fr5::value(false);
				p::value(false);
			 }
				}
			};
			typedef wic::event<gameevent_game_started_config> gameevent_game_started;

			/// gameevent_game_win ///		
			struct gameevent_game_win_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_game_win";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x270;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gameend ge;
					return (true && ( 
				3 == gs::value() && 1 == ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::gameend ge;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_game_win_config> gameevent_game_win;

			/// gameevent_safe_code mistaken ///		
			struct gameevent_safe_code_mistaken_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_safe_code_mistaken";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x3a0;
				static bool cfg_condition()
				{
				typedef typename villa::pin_timeout_timer timer;
				typedef typename villa::pin_code code;
					typedef typename villa::safe_controller::buzzer buzzer;
					typedef typename villa::safe_controller::magnetic_lock safe;
					return (true && (  code::value().size() >= 4 && code::value() != "4389" && safe::value()  ));
				}
				static void cfg_action()
				{
				typedef typename villa::pin_timeout_timer timer;
				typedef typename villa::pin_code code;
					typedef typename villa::safe_controller::buzzer buzzer;
					typedef typename villa::safe_controller::magnetic_lock safe;
	
(void)0; { 
			safe::value(1);
			timer::stop();
			timer::reset();
			buzzer::beep(800,200);
			code::value("");
		 }
				}
			};
			typedef wic::event<gameevent_safe_code_mistaken_config> gameevent_safe_code_mistaken;

			/// gameevent_safe_opened ///		
			struct gameevent_safe_opened_config
			{
				constexpr static const char *name = "ddf::villa::gameevent_safe_opened";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x390;
				static bool cfg_condition()
				{
				typedef typename villa::pin_timeout_timer timer;
				typedef typename villa::pin_code code;
					typedef typename villa::safe_controller::buzzer buzzer;
					typedef typename villa::safe_controller::magnetic_lock safe;
					return (true && (  code::value().size() >= 4 && code::value() == "4389" && safe::value()  ));
				}
				static void cfg_action()
				{
				typedef typename villa::pin_timeout_timer timer;
				typedef typename villa::pin_code code;
					typedef typename villa::safe_controller::buzzer buzzer;
					typedef typename villa::safe_controller::magnetic_lock safe;
	
(void)0; { 
			safe::value(0);
			timer::stop();
			timer::reset();
			buzzer::beep(800,200);
			code::value("");
	     }
				}
			};
			typedef wic::event<gameevent_safe_opened_config> gameevent_safe_opened;

			/// pin_code_accumulation ///		
			struct pin_code_accumulation_config
			{
				constexpr static const char *name = "ddf::villa::pin_code_accumulation";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x370;
				static bool cfg_condition()
				{
				typedef typename villa::pin_timeout_timer timer;
				typedef typename villa::pin_code code;
					typedef typename villa::safe_controller::pin_pad pin_pad;
					typedef typename villa::safe_controller::buzzer buzzer;
					typedef typename villa::safe_controller::magnetic_lock safe;
					return (true && ( 
	    	safe::value()
	     ));
				}
				static void cfg_action()
				{
				typedef typename villa::pin_timeout_timer timer;
				typedef typename villa::pin_code code;
					typedef typename villa::safe_controller::pin_pad pin_pad;
					typedef typename villa::safe_controller::buzzer buzzer;
					typedef typename villa::safe_controller::magnetic_lock safe;
	
(void)0; { 
	    	pin_pad::value_type v = pin_pad::value();
			if(!v.state)
				return;
	        timer::reset();
	        timer::start();
	        const uint8_t k = v.key;
	        char c;
	        if(k < 9)
	    	    c = static_cast<char>(k+49);
	        else switch(k)
	        {
	        	case 9 : c = '*'; break;
		        case 10: c = '0'; break;
		        case 11: c = '#'; break;
		        default: c = '?'; break;
	        }
		const std::string cv = code::value() + c;
	        code::value(cv);
		if(cv.size() < 4)
			buzzer::beep(210,40);
	     }
				}
			};
			typedef wic::event<pin_code_accumulation_config> pin_code_accumulation;

			/// pin_timeout ///		
			struct pin_timeout_config
			{
				constexpr static const char *name = "ddf::villa::pin_timeout";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x380;
				static bool cfg_condition()
				{
				typedef typename villa::pin_timeout_timer timer;
				typedef typename villa::pin_code code;
					typedef typename villa::safe_controller::buzzer buzzer;
					return (true && (  timer::value() > 25  ));
				}
				static void cfg_action()
				{
				typedef typename villa::pin_timeout_timer timer;
				typedef typename villa::pin_code code;
					typedef typename villa::safe_controller::buzzer buzzer;
	
(void)0; { 
	        timer::stop();
	        timer::reset();
			buzzer::beep(200,200);
	        code::value("");
	     }
				}
			};
			typedef wic::event<pin_timeout_config> pin_timeout;

			/// reset_room ///		
			struct reset_room_config
			{
				constexpr static const char *name = "ddf::villa::reset_room";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x2e0;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
					typedef typename villa::safe_controller::magnetic_lock safe_lock;
					typedef typename villa::control_room_controller::magnetic_lock fireplace_lock;
					typedef typename villa::entrance_controller::led entrance_led;
				typedef typename villa::desktop_pc::restart_game desktop_pc_reset;
					return (true && ( 
			!gs::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
					typedef typename villa::safe_controller::magnetic_lock safe_lock;
					typedef typename villa::control_room_controller::magnetic_lock fireplace_lock;
					typedef typename villa::entrance_controller::led entrance_led;
				typedef typename villa::desktop_pc::restart_game desktop_pc_reset;
	
(void)0; { 
			desktop_pc_reset::value(1);
			safe_lock::value(1);
			fireplace_lock::value(1);
			entrance_led::value(0);
		 }
				}
			};
			typedef wic::event<reset_room_config> reset_room;

			/// stop_audios ///		
			struct stop_audios_config
			{
				constexpr static const char *name = "ddf::villa::stop_audios";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x2f0;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
			typedef room_1_content::careful s1;
			typedef room_1_content::rules s2;
			typedef room_1_content::techdiff s3;
			typedef room_1_content::gminc s4;
			typedef room_2_content::careful s5;
			typedef room_2_content::rules s6;
			typedef room_2_content::techdiff s7;
			typedef room_2_content::gminc s8;
			typedef room_1_content::event_1 s9;
			typedef room_1_content::event_2 sa;
			typedef room_1_content::event_3 sb;
			typedef room_2_content::event_1 se;
			typedef room_2_content::event_2 sf;
			typedef room_2_content::event_3 sg;
					return (true && ( 
			3 == gs::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
			typedef room_1_content::careful s1;
			typedef room_1_content::rules s2;
			typedef room_1_content::techdiff s3;
			typedef room_1_content::gminc s4;
			typedef room_2_content::careful s5;
			typedef room_2_content::rules s6;
			typedef room_2_content::techdiff s7;
			typedef room_2_content::gminc s8;
			typedef room_1_content::event_1 s9;
			typedef room_1_content::event_2 sa;
			typedef room_1_content::event_3 sb;
			typedef room_2_content::event_1 se;
			typedef room_2_content::event_2 sf;
			typedef room_2_content::event_3 sg;
	
(void)0; { 
			s1::cancel();
			s2::cancel();
			s3::cancel();
			s4::cancel();
			s5::cancel();
			s6::cancel();
			s7::cancel();
			s8::cancel();
			s9::cancel();
			sa::cancel();
			sb::cancel();
			se::cancel();
			sf::cancel();
			sg::cancel();
		 }
				}
			};
			typedef wic::event<stop_audios_config> stop_audios;

			/// the_surveillance_Konsole ///		
			struct the_surveillance_konsole_config
			{
				constexpr static const char *name = "ddf::villa::the_surveillance_konsole";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x320;
				static bool cfg_condition()
				{
					typedef typename villa::control_room_controller::switch_1 my_switch;
					typedef typename villa::control_room_controller::led_1 red_led;
					typedef typename villa::control_room_controller::led_2 green_led;
				typedef typename villa::video_device::enabled enabled;
				typedef typename villa::video_device::start_livecams start_livecams;
				typedef typename villa::video_device::stop_livecams stop_livecams;
				typedef typename villa::video_device::stop_tape stop_tape;
					return (true);
				}
				static void cfg_action()
				{
					typedef typename villa::control_room_controller::switch_1 my_switch;
					typedef typename villa::control_room_controller::led_1 red_led;
					typedef typename villa::control_room_controller::led_2 green_led;
				typedef typename villa::video_device::enabled enabled;
				typedef typename villa::video_device::start_livecams start_livecams;
				typedef typename villa::video_device::stop_livecams stop_livecams;
				typedef typename villa::video_device::stop_tape stop_tape;
	
(void)0; { 
			const bool v = my_switch::value();
			if(v)
			{
				green_led::value(1);
				start_livecams::value(1);
				std::cout << "VILLA: livecams started" << std::endl; 
			}
			else
			{
				green_led::value(0);
				red_led::value(0);
				stop_livecams::value(1);
				stop_tape::value(1);
				std::cout << "VILLA: livecams & tape stopped" << std::endl; 
			}
			enabled::value(v);
		 }
				}
			};
			typedef wic::event<the_surveillance_konsole_config> the_surveillance_konsole;

			/// time_up ///		
			struct time_up_config
			{
				constexpr static const char *name = "ddf::villa::time_up";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x220;
				static bool cfg_condition()
				{
				typedef typename villa::gametimer tmr;
				typedef typename villa::gameend ge;
				typedef typename villa::gamestate gs;
			typedef room_1_content::event_5 failstate_room_1;
			typedef room_2_content::event_5 failstate_room_2;
					return (true && ( 
				tmr::value() >= 3600 && tmr::running() && 1 == gs::value() && !ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::gametimer tmr;
				typedef typename villa::gameend ge;
				typedef typename villa::gamestate gs;
			typedef room_1_content::event_5 failstate_room_1;
			typedef room_2_content::event_5 failstate_room_2;
	
(void)0; { 
				tmr::stop();
				failstate_room_1::play();
				failstate_room_2::play();
				ge::value(2);
				gs::value(3);
			 }
				}
			};
			typedef wic::event<time_up_config> time_up;

			/// timedevent_funk_1_event_finished ///		
			struct timedevent_funk_1_event_finished_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_1_event_finished";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x3f0;
				static bool cfg_condition()
				{
				typedef typename villa::timedevent_funk_1 __timedevent_at;
				typedef typename villa::timedevent_funk_1_timer __timedevent_timer;
			typedef room_1_content::event_1 r1;
			typedef room_2_content::event_1 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::timedevent_funk_1 __timedevent_at;
				typedef typename villa::timedevent_funk_1_timer __timedevent_timer;
			typedef room_1_content::event_1 r1;
			typedef room_2_content::event_1 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_funk_1_event_finished_config> timedevent_funk_1_event_finished;

			/// timedevent_funk_1_event_gamestate ///		
			struct timedevent_funk_1_event_gamestate_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_1_event_gamestate";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x400;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_funk_1_timer tmr;
				typedef typename villa::timedevent_funk_1 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_funk_1_timer tmr;
				typedef typename villa::timedevent_funk_1 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_funk_1_event_gamestate_config> timedevent_funk_1_event_gamestate;

			/// timedevent_funk_2_event_finished ///		
			struct timedevent_funk_2_event_finished_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_2_event_finished";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x4b0;
				static bool cfg_condition()
				{
				typedef typename villa::timedevent_funk_2 __timedevent_at;
				typedef typename villa::timedevent_funk_2_timer __timedevent_timer;
			typedef room_1_content::event_2 r1;
			typedef room_2_content::event_2 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::timedevent_funk_2 __timedevent_at;
				typedef typename villa::timedevent_funk_2_timer __timedevent_timer;
			typedef room_1_content::event_2 r1;
			typedef room_2_content::event_2 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_funk_2_event_finished_config> timedevent_funk_2_event_finished;

			/// timedevent_funk_2_event_gamestate ///		
			struct timedevent_funk_2_event_gamestate_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_2_event_gamestate";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x4c0;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_funk_2_timer tmr;
				typedef typename villa::timedevent_funk_2 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_funk_2_timer tmr;
				typedef typename villa::timedevent_funk_2 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_funk_2_event_gamestate_config> timedevent_funk_2_event_gamestate;

			/// timedevent_funk_3_event_finished ///		
			struct timedevent_funk_3_event_finished_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_3_event_finished";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x530;
				static bool cfg_condition()
				{
				typedef typename villa::timedevent_funk_3 __timedevent_at;
				typedef typename villa::timedevent_funk_3_timer __timedevent_timer;
			typedef room_1_content::event_3 r1;
			typedef room_2_content::event_3 r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::timedevent_funk_3 __timedevent_at;
				typedef typename villa::timedevent_funk_3_timer __timedevent_timer;
			typedef room_1_content::event_3 r1;
			typedef room_2_content::event_3 r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_funk_3_event_finished_config> timedevent_funk_3_event_finished;

			/// timedevent_funk_3_event_gamestate ///		
			struct timedevent_funk_3_event_gamestate_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_funk_3_event_gamestate";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x540;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_funk_3_timer tmr;
				typedef typename villa::timedevent_funk_3 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_funk_3_timer tmr;
				typedef typename villa::timedevent_funk_3 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_funk_3_event_gamestate_config> timedevent_funk_3_event_gamestate;

			/// timedevent_pc_1_event_finished ///		
			struct timedevent_pc_1_event_finished_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_1_event_finished";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x430;
				static bool cfg_condition()
				{
				typedef typename villa::timedevent_pc_1 __timedevent_at;
				typedef typename villa::timedevent_pc_1_timer __timedevent_timer;
				typedef typename villa::incoming_call call;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::timedevent_pc_1 __timedevent_at;
				typedef typename villa::timedevent_pc_1_timer __timedevent_timer;
				typedef typename villa::incoming_call call;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				call::value(4);
			 }
				}
			};
			typedef wic::event<timedevent_pc_1_event_finished_config> timedevent_pc_1_event_finished;

			/// timedevent_pc_1_event_gamestate ///		
			struct timedevent_pc_1_event_gamestate_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_1_event_gamestate";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x440;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_pc_1_timer tmr;
				typedef typename villa::timedevent_pc_1 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_pc_1_timer tmr;
				typedef typename villa::timedevent_pc_1 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_pc_1_event_gamestate_config> timedevent_pc_1_event_gamestate;

			/// timedevent_pc_2_event_finished ///		
			struct timedevent_pc_2_event_finished_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_2_event_finished";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x470;
				static bool cfg_condition()
				{
				typedef typename villa::timedevent_pc_2 __timedevent_at;
				typedef typename villa::timedevent_pc_2_timer __timedevent_timer;
				typedef typename villa::incoming_call call;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::timedevent_pc_2 __timedevent_at;
				typedef typename villa::timedevent_pc_2_timer __timedevent_timer;
				typedef typename villa::incoming_call call;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				call::value(5);
			 }
				}
			};
			typedef wic::event<timedevent_pc_2_event_finished_config> timedevent_pc_2_event_finished;

			/// timedevent_pc_2_event_gamestate ///		
			struct timedevent_pc_2_event_gamestate_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_2_event_gamestate";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x480;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_pc_2_timer tmr;
				typedef typename villa::timedevent_pc_2 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_pc_2_timer tmr;
				typedef typename villa::timedevent_pc_2 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_pc_2_event_gamestate_config> timedevent_pc_2_event_gamestate;

			/// timedevent_pc_3_event_finished ///		
			struct timedevent_pc_3_event_finished_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_3_event_finished";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x4f0;
				static bool cfg_condition()
				{
				typedef typename villa::timedevent_pc_3 __timedevent_at;
				typedef typename villa::timedevent_pc_3_timer __timedevent_timer;
				typedef typename villa::incoming_call call;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename villa::timedevent_pc_3 __timedevent_at;
				typedef typename villa::timedevent_pc_3_timer __timedevent_timer;
				typedef typename villa::incoming_call call;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				call::value(6);
			 }
				}
			};
			typedef wic::event<timedevent_pc_3_event_finished_config> timedevent_pc_3_event_finished;

			/// timedevent_pc_3_event_gamestate ///		
			struct timedevent_pc_3_event_gamestate_config
			{
				constexpr static const char *name = "ddf::villa::timedevent_pc_3_event_gamestate";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x500;
				static bool cfg_condition()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_pc_3_timer tmr;
				typedef typename villa::timedevent_pc_3 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename villa::gamestate gs;
				typedef typename villa::timedevent_pc_3_timer tmr;
				typedef typename villa::timedevent_pc_3 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_pc_3_event_gamestate_config> timedevent_pc_3_event_gamestate;

			/// video_playing ///		
			struct video_playing_config
			{
				constexpr static const char *name = "ddf::villa::video_playing";
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x330;
				static bool cfg_condition()
				{
					typedef typename villa::control_room_controller::led_1 red_led;
				typedef typename villa::video_device::enabled enabled;
				typedef typename villa::video_device::start_tape start_tape;
				typedef typename villa::video_device::casette_id casette_id;
				typedef typename villa::gameend ge;
					return (true && ( 
			enabled::value()
		 ));
				}
				static void cfg_action()
				{
					typedef typename villa::control_room_controller::led_1 red_led;
				typedef typename villa::video_device::enabled enabled;
				typedef typename villa::video_device::start_tape start_tape;
				typedef typename villa::video_device::casette_id casette_id;
				typedef typename villa::gameend ge;
	
(void)0; { 
			if(start_tape::value())
			{
				if(casette_id::value() == 0xff)
					return;

				switch(casette_id::value())
				{
					
					case 0:
						std::cout << "VILLA: playing cassette 1" << std::endl; 
						break;

					
					case 1: 
						std::cout << "VILLA: playing cassette 2" << std::endl; 
						break;

					
					case 2:
						ge::value(1); 
						std::cout << "VILLA: playing cassette 3" << std::endl; 
						break;

					case 0xff:
						std::cout << "VILLA: cassette removed" << std::endl; 
						return;
				}
				red_led::value(1);
			}
			else
			{
				casette_id::value(0xff);
				red_led::value(0);
			}
		 }
				}
			};
			typedef wic::event<video_playing_config> video_playing;
}

	/// Room junkyard
	namespace junkyard
	{

			/// email_client
			namespace email_client
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - junkyard - email_client";
					static const uint32_t cfg_class_id = 0x400040;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// Started ///
				struct started_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::email_client::started";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x400040;
					static const uint32_t cfg_member_id          = 0x10;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<started_config> started;

				/// Shutdown ///
				struct shutdown_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::email_client::shutdown";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x400040;
					static const uint32_t cfg_member_id          = 0x20;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<shutdown_config> shutdown;

				/// Emails Received ///
				struct emails_received_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::email_client::emails_received";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x400040;
					static const uint32_t cfg_member_id          = 0x30;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<emails_received_config> emails_received;

				/// Restart Game ///
				struct restart_game_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::email_client::restart_game";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x400040;
					static const uint32_t cfg_member_id          = 0x40;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<restart_game_config> restart_game;

				/// Search String ///
				struct search_string_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::email_client::search_string";

					typedef std::string cfg_value_type;

					static const uint32_t cfg_class_id           = 0x400040;
					static const uint32_t cfg_member_id          = 0x50;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<search_string_config> search_string;

				/// Opened Email ///
				struct opened_email_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::email_client::opened_email";

					typedef std::string cfg_value_type;

					static const uint32_t cfg_class_id           = 0x400040;
					static const uint32_t cfg_member_id          = 0x60;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef property_external<opened_email_config> opened_email;

			}

			/// entrance_controller
			namespace entrance_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - junkyard - entrance_controller";
					static const uint32_t cfg_class_id = 0x400030;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// debouncer ///
				struct debouncer_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::entrance_controller::debouncer";
					static const uint32_t cfg_class_id = 0x400030;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_config> debouncer;

				/// led ///
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::entrance_controller::led";
					static const uint32_t cfg_class_id = 0x400030;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::led_strip<led_config> led;

				/// magnetic_sensor ///
				struct magnetic_sensor_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::entrance_controller::magnetic_sensor";
					static const uint32_t cfg_class_id = 0x400030;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::magnetic_sensor<magnetic_sensor_config> magnetic_sensor;

			}

			/// secret_box_controller_1
			namespace secret_box_controller_1
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - junkyard - secret_box_controller_1";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

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
				typedef peripheral::button<debouncer_1_config> debouncer_1;

				/// debouncer_2 ///
				struct debouncer_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_2";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_2_config> debouncer_2;

				/// debouncer_3 ///
				struct debouncer_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_3";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_3_config> debouncer_3;

				/// debouncer_4 ///
				struct debouncer_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_4";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0x50;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_4_config> debouncer_4;

				/// debouncer_5 ///
				struct debouncer_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_5";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0x60;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_5_config> debouncer_5;

				/// debouncer_6 ///
				struct debouncer_6_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_6";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0x70;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_6_config> debouncer_6;

				/// debouncer_7 ///
				struct debouncer_7_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::debouncer_7";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0x80;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_7_config> debouncer_7;

				/// magnetic_lock_1 ///
				struct magnetic_lock_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::magnetic_lock_1";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0x90;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_1_config> magnetic_lock_1;

				/// magnetic_lock_2 ///
				struct magnetic_lock_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::magnetic_lock_2";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0xa0;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_2_config> magnetic_lock_2;

				/// magnetic_lock_3 ///
				struct magnetic_lock_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::magnetic_lock_3";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0xb0;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_3_config> magnetic_lock_3;

				/// magnetic_lock_4 ///
				struct magnetic_lock_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::magnetic_lock_4";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0xc0;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_4_config> magnetic_lock_4;
				struct addressable_led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_1::addressable_led";
					static const uint32_t cfg_class_id = 0x400010;
					static const uint32_t cfg_member_id = 0xd0;
					static const uint32_t cfg_cooldown_time = 50;
					static const uint32_t cfg_led_count = 50;
				};
				typedef peripheral::addressable_led_strip<addressable_led_config> addressable_led;

			}

			/// secret_box_controller_2
			namespace secret_box_controller_2
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - junkyard - secret_box_controller_2";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint16_t cfg_multiplicity = 1;
				};
				typedef wic::device_role<device_role_config> device_role;

				/// debouncer_1 ///
				struct debouncer_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_1";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x10;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_1_config> debouncer_1;

				/// debouncer_2 ///
				struct debouncer_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_2";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x20;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_2_config> debouncer_2;

				/// debouncer_3 ///
				struct debouncer_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_3";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x30;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_3_config> debouncer_3;

				/// debouncer_4 ///
				struct debouncer_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_4";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x40;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_4_config> debouncer_4;

				/// debouncer_5 ///
				struct debouncer_5_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_5";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x50;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_5_config> debouncer_5;

				/// debouncer_6 ///
				struct debouncer_6_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_6";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x60;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_6_config> debouncer_6;

				/// debouncer_7 ///
				struct debouncer_7_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_7";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x70;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_7_config> debouncer_7;

				/// debouncer_8 ///
				struct debouncer_8_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_8";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x80;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_8_config> debouncer_8;

				/// debouncer_9 ///
				struct debouncer_9_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_9";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x90;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_9_config> debouncer_9;

				/// debouncer_10 ///
				struct debouncer_10_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_10";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0xa0;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_10_config> debouncer_10;

				/// light_controller ///
				struct light_controller_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::light_controller";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0xb0;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::power_switch<light_controller_config> light_controller;

				/// debouncer_12 ///
				struct debouncer_12_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::debouncer_12";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0xc0;
					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::button<debouncer_12_config> debouncer_12;

				/// magnetic_lock_1 ///
				struct magnetic_lock_1_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::magnetic_lock_1";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0xd0;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_1_config> magnetic_lock_1;

				/// magnetic_lock_2 ///
				struct magnetic_lock_2_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::magnetic_lock_2";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0xe0;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_2_config> magnetic_lock_2;

				/// magnetic_lock_3 ///
				struct magnetic_lock_3_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::magnetic_lock_3";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0xf0;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_3_config> magnetic_lock_3;

				/// magnetic_lock_4 ///
				struct magnetic_lock_4_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::secret_box_controller_2::magnetic_lock_4";
					static const uint32_t cfg_class_id = 0x400020;
					static const uint32_t cfg_member_id = 0x100;
					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::magnetic_lock<magnetic_lock_4_config> magnetic_lock_4;

			}


			/// Audio Message URL ///
			struct audio_message_url_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::audio_message_url";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0xf0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<audio_message_url_config> audio_message_url;

			/// ComDev Reset ///
			struct comdev_reset_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::comdev_reset";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0xd0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<comdev_reset_config> comdev_reset;

			/// ComDev Silence ///
			struct comdev_silence_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::comdev_silence";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0xe0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<comdev_silence_config> comdev_silence;

			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::freezed1";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x130;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<freezed1_config> freezed1;

			/// Freezed5 ///
			struct freezed5_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::freezed5";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x140;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<freezed5_config> freezed5;

			/// GM Help Status ///
			struct gm_help_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::gm_help_status";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x80;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gm_help_status_config> gm_help_status;

			/// GameEnd ///
			struct gameend_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::gameend";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x110;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gameend_config> gameend;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::gamestate";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x100;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<gamestate_config> gamestate;

			/// Incoming Call ///
			struct incoming_call_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::incoming_call";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<incoming_call_config> incoming_call;

			/// Incoming Call Status ///
			struct incoming_call_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::incoming_call_status";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0xa0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<incoming_call_status_config> incoming_call_status;

			/// Paused ///
			struct paused_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::paused";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x120;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<paused_config> paused;

			/// Restart Game ///
			struct restart_game_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::restart_game";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x70;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<restart_game_config> restart_game;

			/// Text Message ///
			struct text_message_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::text_message";
				typedef std::string cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0xb0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<text_message_config> text_message;

			/// Text Message Sender ///
			struct text_message_sender_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::text_message_sender";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0xc0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<text_message_sender_config> text_message_sender;

			/// correct_notes ///
			struct correct_notes_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::correct_notes";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x350;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<correct_notes_config> correct_notes;

			/// led_timer_start ///
			struct led_timer_start_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::led_timer_start";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x2c0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<led_timer_start_config> led_timer_start;

			/// lock_pick_1_pressed ///
			struct lock_pick_1_pressed_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::lock_pick_1_pressed";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x2d0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<lock_pick_1_pressed_config> lock_pick_1_pressed;

			/// lock_pick_2_pressed ///
			struct lock_pick_2_pressed_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::lock_pick_2_pressed";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x2e0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<lock_pick_2_pressed_config> lock_pick_2_pressed;

			/// timedevent_atmo_1 ///
			struct timedevent_atmo_1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_1";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x480;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_atmo_1_config> timedevent_atmo_1;

			/// timedevent_atmo_2 ///
			struct timedevent_atmo_2_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_2";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x4c0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_atmo_2_config> timedevent_atmo_2;

			/// timedevent_atmo_3 ///
			struct timedevent_atmo_3_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_3";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x500;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_atmo_3_config> timedevent_atmo_3;

			/// timedevent_atmo_4 ///
			struct timedevent_atmo_4_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_4";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x540;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_atmo_4_config> timedevent_atmo_4;

			/// timedevent_atmo_5 ///
			struct timedevent_atmo_5_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_5";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x580;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_atmo_5_config> timedevent_atmo_5;

			/// timedevent_atmo_6 ///
			struct timedevent_atmo_6_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_6";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x5c0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_atmo_6_config> timedevent_atmo_6;

			/// timedevent_pc_1 ///
			struct timedevent_pc_1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_pc_1";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x400;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_pc_1_config> timedevent_pc_1;

			/// timedevent_pc_2 ///
			struct timedevent_pc_2_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_pc_2";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x440;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<timedevent_pc_2_config> timedevent_pc_2;


			/// room_1
			struct room_1_config
			{
                		static const uint8_t cfg_device = 3;
				static const uint8_t cfg_channel = 1;
			};
			typedef wic::audio<room_1_config> room_1;

			namespace room_1_content
			{
				struct chord_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::chord";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<chord_config> chord;
				struct progress_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::progress";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/progress.wav";
					constexpr static const float cfg_gain = 1.3;
				};
				typedef wic::audio_effect<progress_config> progress;
				struct atmo_blacky_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::atmo_blacky";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/atmosphere_blacky.wav";
					constexpr static const float cfg_gain = 0.3;
				};
				typedef wic::audio_effect<atmo_blacky_config> atmo_blacky;
				struct atmo_junkyard_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::atmo_junkyard";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/atmosphere_junkyard.wav";
					constexpr static const float cfg_gain = 0.3;
				};
				typedef wic::audio_effect<atmo_junkyard_config> atmo_junkyard;
				struct atmo_telephone_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::atmo_telephone";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/atmosphere_telephone.wav";
					constexpr static const float cfg_gain = 0.3;
				};
				typedef wic::audio_effect<atmo_telephone_config> atmo_telephone;
				struct piano_a1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::piano_a1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/a1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_a1_config> piano_a1;
				struct piano_b1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::piano_b1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/b1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_b1_config> piano_b1;
				struct piano_c1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::piano_c1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/c1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_c1_config> piano_c1;
				struct piano_c2_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::piano_c2";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/c2.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_c2_config> piano_c2;
				struct piano_d1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::piano_d1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/d1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_d1_config> piano_d1;
				struct piano_d2_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::piano_d2";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/d2.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_d2_config> piano_d2;
				struct piano_e1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::piano_e1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/e1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_e1_config> piano_e1;
				struct piano_f1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::piano_f1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/f1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_f1_config> piano_f1;
				struct piano_g1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::piano_g1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/g1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_g1_config> piano_g1;
				struct careful_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::careful";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/careful.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400060;
					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<careful_config> careful;
				struct gminc_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::gminc";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/gminc.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400060;
					static const uint32_t cfg_member_id = 0x60;
				};
				typedef wic::audio_speech<gminc_config> gminc;
				struct rules_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::rules";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/rules.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400060;
					static const uint32_t cfg_member_id = 0x40;
				};
				typedef wic::audio_speech<rules_config> rules;
				struct techdiff_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::techdiff";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/techdiff.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400060;
					static const uint32_t cfg_member_id = 0x50;
				};
				typedef wic::audio_speech<techdiff_config> techdiff;
				struct event_1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::event_1";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Event_1.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400060;
					static const uint32_t cfg_member_id = 0x100;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::event_2";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Event_2.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400060;
					static const uint32_t cfg_member_id = 0x110;
				};
				typedef wic::audio_speech<event_2_config> event_2;
				struct event_3_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::event_3";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Intro_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400060;
					static const uint32_t cfg_member_id = 0x120;
				};
				typedef wic::audio_speech<event_3_config> event_3;
				struct event_4_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::event_4";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Winstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400060;
					static const uint32_t cfg_member_id = 0x130;
				};
				typedef wic::audio_speech<event_4_config> event_4;
				struct event_5_config
				{
					constexpr static const char *name = "ddf::junkyard::room_1_content::event_5";
					typedef room_1 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Failstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400060;
					static const uint32_t cfg_member_id = 0x140;
				};
				typedef wic::audio_speech<event_5_config> event_5;

			}

			/// room_2
			struct room_2_config
			{
                		static const uint8_t cfg_device = 3;
				static const uint8_t cfg_channel = 0;
			};
			typedef wic::audio<room_2_config> room_2;

			namespace room_2_content
			{
				struct chord_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::chord";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/chord.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<chord_config> chord;
				struct progress_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::progress";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/progress.wav";
					constexpr static const float cfg_gain = 1.3;
				};
				typedef wic::audio_effect<progress_config> progress;
				struct atmo_blacky_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::atmo_blacky";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/atmosphere_blacky.wav";
					constexpr static const float cfg_gain = 0.3;
				};
				typedef wic::audio_effect<atmo_blacky_config> atmo_blacky;
				struct atmo_junkyard_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::atmo_junkyard";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/atmosphere_junkyard.wav";
					constexpr static const float cfg_gain = 0.3;
				};
				typedef wic::audio_effect<atmo_junkyard_config> atmo_junkyard;
				struct atmo_telephone_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::atmo_telephone";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/atmosphere_telephone.wav";
					constexpr static const float cfg_gain = 0.3;
				};
				typedef wic::audio_effect<atmo_telephone_config> atmo_telephone;
				struct piano_a1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::piano_a1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/a1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_a1_config> piano_a1;
				struct piano_b1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::piano_b1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/b1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_b1_config> piano_b1;
				struct piano_c1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::piano_c1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/c1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_c1_config> piano_c1;
				struct piano_c2_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::piano_c2";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/c2.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_c2_config> piano_c2;
				struct piano_d1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::piano_d1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/d1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_d1_config> piano_d1;
				struct piano_d2_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::piano_d2";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/d2.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_d2_config> piano_d2;
				struct piano_e1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::piano_e1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/e1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_e1_config> piano_e1;
				struct piano_f1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::piano_f1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/f1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_f1_config> piano_f1;
				struct piano_g1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::piano_g1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/piano/g1.wav";
					constexpr static const float cfg_gain = 1;
				};
				typedef wic::audio_effect<piano_g1_config> piano_g1;
				struct careful_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::careful";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/careful.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400050;
					static const uint32_t cfg_member_id = 0x30;
				};
				typedef wic::audio_speech<careful_config> careful;
				struct gminc_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::gminc";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/gminc.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400050;
					static const uint32_t cfg_member_id = 0x60;
				};
				typedef wic::audio_speech<gminc_config> gminc;
				struct rules_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::rules";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/rules.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400050;
					static const uint32_t cfg_member_id = 0x40;
				};
				typedef wic::audio_speech<rules_config> rules;
				struct techdiff_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::techdiff";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/audio/soundalert/techdiff.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400050;
					static const uint32_t cfg_member_id = 0x50;
				};
				typedef wic::audio_speech<techdiff_config> techdiff;
				struct event_1_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::event_1";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Event_1.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400050;
					static const uint32_t cfg_member_id = 0x100;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::event_2";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Event_2.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400050;
					static const uint32_t cfg_member_id = 0x110;
				};
				typedef wic::audio_speech<event_2_config> event_2;
				struct event_3_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::event_3";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Intro_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400050;
					static const uint32_t cfg_member_id = 0x120;
				};
				typedef wic::audio_speech<event_3_config> event_3;
				struct event_4_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::event_4";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Winstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400050;
					static const uint32_t cfg_member_id = 0x130;
				};
				typedef wic::audio_speech<event_4_config> event_4;
				struct event_5_config
				{
					constexpr static const char *name = "ddf::junkyard::room_2_content::event_5";
					typedef room_2 cfg_audio;
					constexpr static const char *cfg_source = "/usr/share/ddf/Junkyard/DDF_EscapeRoom_Schrottplatz_Failstate_Musik.wav";
					constexpr static const float cfg_gain = 1;
					static const uint32_t cfg_class_id = 0x400050;
					static const uint32_t cfg_member_id = 0x140;
				};
				typedef wic::audio_speech<event_5_config> event_5;

			}


			/// FreezeTimer1
			struct freezetimer1_config
			{
				constexpr static const char *name = "ddf::junkyard::freezetimer1";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x160;
				static const uint32_t cfg_interval  = 60000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				constexpr static const char *name = "ddf::junkyard::freezetimer5";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x170;
				static const uint32_t cfg_interval  = 300000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				constexpr static const char *name = "ddf::junkyard::gametimer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x150;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;

			/// relock_timer
			struct relock_timer_config
			{
				constexpr static const char *name = "ddf::junkyard::relock_timer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x310;
				static const uint32_t cfg_interval  = 8000;
			};
			typedef typename wic::timer<relock_timer_config> relock_timer;

			/// timedevent_atmo_1_timer
			struct timedevent_atmo_1_timer_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_1_timer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x490;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_atmo_1_timer_config> timedevent_atmo_1_timer;

			/// timedevent_atmo_2_timer
			struct timedevent_atmo_2_timer_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_2_timer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x4d0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_atmo_2_timer_config> timedevent_atmo_2_timer;

			/// timedevent_atmo_3_timer
			struct timedevent_atmo_3_timer_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_3_timer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x510;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_atmo_3_timer_config> timedevent_atmo_3_timer;

			/// timedevent_atmo_4_timer
			struct timedevent_atmo_4_timer_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_4_timer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x550;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_atmo_4_timer_config> timedevent_atmo_4_timer;

			/// timedevent_atmo_5_timer
			struct timedevent_atmo_5_timer_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_5_timer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x590;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_atmo_5_timer_config> timedevent_atmo_5_timer;

			/// timedevent_atmo_6_timer
			struct timedevent_atmo_6_timer_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_6_timer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x5d0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_atmo_6_timer_config> timedevent_atmo_6_timer;

			/// timedevent_pc_1_timer
			struct timedevent_pc_1_timer_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_pc_1_timer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x410;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_pc_1_timer_config> timedevent_pc_1_timer;

			/// timedevent_pc_2_timer
			struct timedevent_pc_2_timer_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_pc_2_timer";
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x450;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_pc_2_timer_config> timedevent_pc_2_timer;



			/// Led strip update ///		
			struct led_strip_update_config
			{
				constexpr static const char *name = "ddf::junkyard::led_strip_update";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x340;
				static bool cfg_condition()
				{
				typedef typename junkyard::led_timer_start lts;
				typedef typename junkyard::gametimer tmr;
					typedef typename junkyard::secret_box_controller_1::addressable_led led;
					return (true && ( 
	    	lts::value()
	     ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::led_timer_start lts;
				typedef typename junkyard::gametimer tmr;
					typedef typename junkyard::secret_box_controller_1::addressable_led led;
	
(void)0; { 
			typename led::value_type v = led::value();
			int greens = (int)(((double)(3600-tmr::value()))/(3600-lts::value())*50);
			if(greens > 50)
				greens = 50;

			if(greens < 0)
				greens = 0;

			int blacks = 50-greens;
			int i = 0;
			for(; i < blacks; ++i)
			{
				v.led[50-i].red = 0;
				v.led[50-i].green = 0;
				v.led[50-i].blue = 0;
			}
			for(; i < 50; ++i)
			{
				v.led[50-i].red = 0;
				v.led[50-i].green = 40;
				v.led[50-i].blue = 0;
			}
			led::value((led::value_type)v);
	     }
				}
			};
			typedef wic::event<led_strip_update_config> led_strip_update;

			/// artificial_game_ending ///		
			struct artificial_game_ending_config
			{
				constexpr static const char *name = "ddf::junkyard::artificial_game_ending";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1e0;
				static bool cfg_condition()
				{
				typedef typename junkyard::gameend ge;
					typedef typename junkyard::entrance_controller::led led;
					return (true && ( 
				led::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gameend ge;
					typedef typename junkyard::entrance_controller::led led;
	
(void)0; {  
				ge::value(1);
			 }
				}
			};
			typedef wic::event<artificial_game_ending_config> artificial_game_ending;

			/// freeze_1 ///		
			struct freeze_1_config
			{
				constexpr static const char *name = "ddf::junkyard::freeze_1";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x190;
				static bool cfg_condition()
				{
				typedef typename junkyard::freezed1 fr;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::freezetimer1 tmr;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::freezed1 fr;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::freezetimer1 tmr;
	
(void)0; { 
				if(fr::value())
					tmr::start();
				else
				{
					tmr::stop();
					tmr::reset();
				}
			 }
				}
			};
			typedef wic::event<freeze_1_config> freeze_1;

			/// freeze_1_timeout ///		
			struct freeze_1_timeout_config
			{
				constexpr static const char *name = "ddf::junkyard::freeze_1_timeout";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1a0;
				static bool cfg_condition()
				{
				typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::freezed1 fr;
					return (true && ( 
				tmr::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::freezed1 fr;
	
(void)0; { 
				fr::value(false);
			 }
				}
			};
			typedef wic::event<freeze_1_timeout_config> freeze_1_timeout;

			/// freeze_5 ///		
			struct freeze_5_config
			{
				constexpr static const char *name = "ddf::junkyard::freeze_5";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1b0;
				static bool cfg_condition()
				{
				typedef typename junkyard::freezed5 fr;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::freezetimer5 tmr;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::freezed5 fr;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::freezetimer5 tmr;
	
(void)0; { 
				if(fr::value())
					tmr::start();
				else
				{
					tmr::stop();
					tmr::reset();
				}
			 }
				}
			};
			typedef wic::event<freeze_5_config> freeze_5;

			/// freeze_5_timeout ///		
			struct freeze_5_timeout_config
			{
				constexpr static const char *name = "ddf::junkyard::freeze_5_timeout";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1c0;
				static bool cfg_condition()
				{
				typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::freezed5 fr;
					return (true && ( 
				tmr::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::freezed5 fr;
	
(void)0; { 
				fr::value(false);
			 }
				}
			};
			typedef wic::event<freeze_5_timeout_config> freeze_5_timeout;

			/// game_end_button_push ///		
			struct game_end_button_push_config
			{
				constexpr static const char *name = "ddf::junkyard::game_end_button_push";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1f0;
				static bool cfg_condition()
				{
					typedef typename junkyard::entrance_controller::debouncer button;
				typedef typename junkyard::gameend ge;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::comdev_silence cs;
			typedef room_1_content::event_4 winstate_room_1;
			typedef room_2_content::event_4 winstate_room_2;
				typedef typename junkyard::gametimer tmr;
					return (true && ( 
				button::value() && 1 == ge::value() && 1 == gs::value()
			 ));
				}
				static void cfg_action()
				{
					typedef typename junkyard::entrance_controller::debouncer button;
				typedef typename junkyard::gameend ge;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::comdev_silence cs;
			typedef room_1_content::event_4 winstate_room_1;
			typedef room_2_content::event_4 winstate_room_2;
				typedef typename junkyard::gametimer tmr;
	
(void)0; { 
				tmr::stop();
				cs::value(1);
				winstate_room_1::play();
				winstate_room_2::play();
				gs::value(3);
			 }
				}
			};
			typedef wic::event<game_end_button_push_config> game_end_button_push;

			/// game_ending ///		
			struct game_ending_config
			{
				constexpr static const char *name = "ddf::junkyard::game_ending";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1d0;
				static bool cfg_condition()
				{
				typedef typename junkyard::gameend ge;
					typedef typename junkyard::entrance_controller::led led;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gameend ge;
					typedef typename junkyard::entrance_controller::led led;
	
(void)0; {  
				led::value(1 == ge::value());
			 }
				}
			};
			typedef wic::event<game_ending_config> game_ending;

			/// game_pause_mgmt ///		
			struct game_pause_mgmt_config
			{
				constexpr static const char *name = "ddf::junkyard::game_pause_mgmt";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x180;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::paused p;
				typedef typename junkyard::freezed1 f1;
				typedef typename junkyard::freezed5 f5;
				typedef typename junkyard::gm_help_status gm;
					typedef typename junkyard::entrance_controller::magnetic_sensor ed;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::paused p;
				typedef typename junkyard::freezed1 f1;
				typedef typename junkyard::freezed5 f5;
				typedef typename junkyard::gm_help_status gm;
					typedef typename junkyard::entrance_controller::magnetic_sensor ed;
	
(void)0; { 
				if(ed::value() && !p::value() && !f1::value() && !f5::value() && !gm::value())
				{
					if(gs::value() == 2)
					{
						gs::value(1);
					}
				}
				else if(gs::value() == 1)
				{
					gs::value(2);
				}
			 }
				}
			};
			typedef wic::event<game_pause_mgmt_config> game_pause_mgmt;

			/// gameevent_ampmeter_turn_on ///		
			struct gameevent_ampmeter_turn_on_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_ampmeter_turn_on";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x3b0;
				static bool cfg_condition()
				{
					typedef typename junkyard::secret_box_controller_2::debouncer_10 button;
					typedef typename junkyard::secret_box_controller_2::light_controller indicator;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_3 lock;
					return (true && ( 
        	button::value()
         ));
				}
				static void cfg_action()
				{
					typedef typename junkyard::secret_box_controller_2::debouncer_10 button;
					typedef typename junkyard::secret_box_controller_2::light_controller indicator;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_3 lock;
	
(void)0; { 
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		if(button::value())
	        	lock::value(0);
         }
				}
			};
			typedef wic::event<gameevent_ampmeter_turn_on_config> gameevent_ampmeter_turn_on;

			/// gameevent_anamorphic_module ///		
			struct gameevent_anamorphic_module_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_anamorphic_module";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x3d0;
				static bool cfg_condition()
				{
					typedef typename junkyard::secret_box_controller_2::debouncer_1 switch_1;
					typedef typename junkyard::secret_box_controller_2::debouncer_2 switch_2;
					typedef typename junkyard::secret_box_controller_2::debouncer_3 switch_3;
					typedef typename junkyard::secret_box_controller_2::debouncer_4 switch_4;
					typedef typename junkyard::secret_box_controller_2::debouncer_5 switch_5;
					typedef typename junkyard::secret_box_controller_2::debouncer_6 switch_6;
					typedef typename junkyard::secret_box_controller_2::debouncer_7 switch_7;
					typedef typename junkyard::secret_box_controller_2::debouncer_8 switch_8;
					typedef typename junkyard::secret_box_controller_2::debouncer_9 switch_9;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_4 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && (  
            switch_1::value() && 
            !switch_2::value() && 
            !switch_3::value() && 
            !switch_4::value() && 
            switch_5::value() && 
            !switch_6::value() && 
            switch_7::value() 
         ));
				}
				static void cfg_action()
				{
					typedef typename junkyard::secret_box_controller_2::debouncer_1 switch_1;
					typedef typename junkyard::secret_box_controller_2::debouncer_2 switch_2;
					typedef typename junkyard::secret_box_controller_2::debouncer_3 switch_3;
					typedef typename junkyard::secret_box_controller_2::debouncer_4 switch_4;
					typedef typename junkyard::secret_box_controller_2::debouncer_5 switch_5;
					typedef typename junkyard::secret_box_controller_2::debouncer_6 switch_6;
					typedef typename junkyard::secret_box_controller_2::debouncer_7 switch_7;
					typedef typename junkyard::secret_box_controller_2::debouncer_8 switch_8;
					typedef typename junkyard::secret_box_controller_2::debouncer_9 switch_9;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_4 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; {  
            lock::value(0); 
	    progress_1::play();
	    progress_2::play();
         }
				}
			};
			typedef wic::event<gameevent_anamorphic_module_config> gameevent_anamorphic_module;

			/// gameevent_call_accepted ///		
			struct gameevent_call_accepted_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_call_accepted";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x280;
				static bool cfg_condition()
				{
				typedef typename junkyard::incoming_call_status cs;
					return (true && ( 
				2 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_accepted_config> gameevent_call_accepted;

			/// gameevent_call_declined ///		
			struct gameevent_call_declined_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_call_declined";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x290;
				static bool cfg_condition()
				{
				typedef typename junkyard::incoming_call_status cs;
					return (true && ( 
				3 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_declined_config> gameevent_call_declined;

			/// gameevent_call_finished ///		
			struct gameevent_call_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_call_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x2a0;
				static bool cfg_condition()
				{
				typedef typename junkyard::incoming_call_status cs;
					return (true && ( 
				4 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_finished_config> gameevent_call_finished;

			/// gameevent_call_missed ///		
			struct gameevent_call_missed_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_call_missed";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x2b0;
				static bool cfg_condition()
				{
				typedef typename junkyard::incoming_call_status cs;
					return (true && ( 
				5 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_missed_config> gameevent_call_missed;

			/// gameevent_call_ringing ///		
			struct gameevent_call_ringing_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_call_ringing";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x270;
				static bool cfg_condition()
				{
				typedef typename junkyard::incoming_call_status cs;
					return (true && ( 
				1 == cs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::incoming_call_status cs;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_call_ringing_config> gameevent_call_ringing;

			/// gameevent_email_received ///		
			struct gameevent_email_received_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_email_received";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x3f0;
				static bool cfg_condition()
				{
				typedef typename junkyard::email_client::emails_received e;
					return (true && ( e::value() ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::email_client::emails_received e;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_email_received_config> gameevent_email_received;

			/// gameevent_game_fail ///		
			struct gameevent_game_fail_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_game_fail";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x260;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gameend ge;
					return (true && ( 
				3 == gs::value() && 2 == ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gameend ge;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_game_fail_config> gameevent_game_fail;

			/// gameevent_game_finished ///		
			struct gameevent_game_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_game_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x230;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gametimer tmr;
					return (true && ( 
				3 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gametimer tmr;
	
(void)0; { 
				tmr::stop();
				tmr::reset();
			 }
				}
			};
			typedef wic::event<gameevent_game_finished_config> gameevent_game_finished;

			/// gameevent_game_paused ///		
			struct gameevent_game_paused_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_game_paused";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x220;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gametimer tmr;
					return (true && ( 
				2 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gametimer tmr;
	
(void)0; { 
				tmr::stop();
			 }
				}
			};
			typedef wic::event<gameevent_game_paused_config> gameevent_game_paused;

			/// gameevent_game_reset ///		
			struct gameevent_game_reset_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_game_reset";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x240;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gameend ge;
				typedef typename junkyard::text_message_sender cd_sender;
				typedef typename junkyard::text_message cd_text;
				typedef typename junkyard::gm_help_status cd_gmhelp;
				typedef typename junkyard::incoming_call cd_call;
				typedef typename junkyard::incoming_call_status cd_callstat;
				typedef typename junkyard::audio_message_url cd_url;
				typedef typename junkyard::comdev_reset cd_reset;
				typedef typename junkyard::freezed1 fr1;
				typedef typename junkyard::freezed5 fr5;
				typedef typename junkyard::paused paused;
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::freezetimer1 frtmr1;
				typedef typename junkyard::freezetimer5 frtmr5;
					return (true && ( 
				0 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gameend ge;
				typedef typename junkyard::text_message_sender cd_sender;
				typedef typename junkyard::text_message cd_text;
				typedef typename junkyard::gm_help_status cd_gmhelp;
				typedef typename junkyard::incoming_call cd_call;
				typedef typename junkyard::incoming_call_status cd_callstat;
				typedef typename junkyard::audio_message_url cd_url;
				typedef typename junkyard::comdev_reset cd_reset;
				typedef typename junkyard::freezed1 fr1;
				typedef typename junkyard::freezed5 fr5;
				typedef typename junkyard::paused paused;
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::freezetimer1 frtmr1;
				typedef typename junkyard::freezetimer5 frtmr5;
	
(void)0; { 
				tmr::stop();
				frtmr1::stop();
				frtmr5::stop();
				frtmr1::reset();
				frtmr5::reset();
				tmr::reset();

				fr1::value(0);
				fr5::value(0);
				paused::value(0);

				cd_reset::value(0);
				ge::value(0);
				cd_sender::value(0xff);
				cd_text::value((std::string)"");
				cd_call::value(0xff);
				cd_callstat::value(0);
				cd_gmhelp::value(0);
				cd_reset::value(1);
			 }
				}
			};
			typedef wic::event<gameevent_game_reset_config> gameevent_game_reset;

			/// gameevent_game_started ///		
			struct gameevent_game_started_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_game_started";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x210;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::paused p;
				typedef typename junkyard::freezed1 fr1;
				typedef typename junkyard::freezed5 fr5;
					return (true && ( 
				1 == gs::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::paused p;
				typedef typename junkyard::freezed1 fr1;
				typedef typename junkyard::freezed5 fr5;
	
(void)0; { 
				tmr::start();
				fr1::value(false);
				fr5::value(false);
				p::value(false);
			 }
				}
			};
			typedef wic::event<gameevent_game_started_config> gameevent_game_started;

			/// gameevent_game_win ///		
			struct gameevent_game_win_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_game_win";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x250;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gameend ge;
					return (true && ( 
				3 == gs::value() && 1 == ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gameend ge;
	
(void)0;
				}
			};
			typedef wic::event<gameevent_game_win_config> gameevent_game_win;

			/// gameevent_labyrinth_1 ///		
			struct gameevent_labyrinth_1_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_labyrinth_1";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x380;
				static bool cfg_condition()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_5 button;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_4 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && (  
            button::value() 
         ));
				}
				static void cfg_action()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_5 button;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_4 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; {  
            lock::value(0); 
		progress_1::play();
		progress_2::play();
         }
				}
			};
			typedef wic::event<gameevent_labyrinth_1_config> gameevent_labyrinth_1;

			/// gameevent_labyrinth_2 ///		
			struct gameevent_labyrinth_2_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_labyrinth_2";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x390;
				static bool cfg_condition()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_6 button;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_1 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && (  
            button::value() 
         ));
				}
				static void cfg_action()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_6 button;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_1 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; {  
            lock::value(0); 
		progress_1::play();
		progress_2::play();
         }
				}
			};
			typedef wic::event<gameevent_labyrinth_2_config> gameevent_labyrinth_2;

			/// gameevent_labyrinth_3 ///		
			struct gameevent_labyrinth_3_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_labyrinth_3";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x3a0;
				static bool cfg_condition()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_7 button;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_2 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && (  
            button::value() 
         ));
				}
				static void cfg_action()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_7 button;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_2 lock;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; {  
            lock::value(0); 
		progress_1::play();
		progress_2::play();
         }
				}
			};
			typedef wic::event<gameevent_labyrinth_3_config> gameevent_labyrinth_3;

			/// gameevent_mona_lisa_rescue ///		
			struct gameevent_mona_lisa_rescue_config
			{
				constexpr static const char *name = "ddf::junkyard::gameevent_mona_lisa_rescue";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x3e0;
				static bool cfg_condition()
				{
					typedef typename junkyard::secret_box_controller_2::debouncer_12 picture_switch;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gameend ge;
					return (true && (  
        	!picture_switch::value() && 1 == gs::value()
         ));
				}
				static void cfg_action()
				{
					typedef typename junkyard::secret_box_controller_2::debouncer_12 picture_switch;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::gameend ge;
	
(void)0; {  
        	ge::value(1); 
         }
				}
			};
			typedef wic::event<gameevent_mona_lisa_rescue_config> gameevent_mona_lisa_rescue;

			/// lockpick_module ///		
			struct lockpick_module_config
			{
				constexpr static const char *name = "ddf::junkyard::lockpick_module";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x370;
				static bool cfg_condition()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_2 lock_pick_1;
					typedef typename junkyard::secret_box_controller_1::debouncer_3 lock_pick_2;
					typedef typename junkyard::secret_box_controller_1::debouncer_4 lock_pick_3;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_3 lock;
				typedef typename junkyard::lock_pick_1_pressed lock_pick_1_pressed;
				typedef typename junkyard::lock_pick_2_pressed lock_pick_2_pressed;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
					return (true && ( 
            lock_pick_1::value() ||
            lock_pick_2::value() ||
            lock_pick_3::value()
         ));
				}
				static void cfg_action()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_2 lock_pick_1;
					typedef typename junkyard::secret_box_controller_1::debouncer_3 lock_pick_2;
					typedef typename junkyard::secret_box_controller_1::debouncer_4 lock_pick_3;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_3 lock;
				typedef typename junkyard::lock_pick_1_pressed lock_pick_1_pressed;
				typedef typename junkyard::lock_pick_2_pressed lock_pick_2_pressed;
			typedef room_1_content::progress progress_1;
			typedef room_2_content::progress progress_2;
	
(void)0; { 
            if(lock_pick_1::value())
                lock_pick_1_pressed::value(true);

            else if(lock_pick_2::value())
                lock_pick_2_pressed::value(lock_pick_1_pressed::value());

            else if(lock_pick_3::value())
            {
                if(lock_pick_1_pressed::value() && lock_pick_2_pressed::value())
		{
		    progress_1::play();
		    progress_2::play();
            	    lock::value(0);
		}
            }
         }
				}
			};
			typedef wic::event<lockpick_module_config> lockpick_module;

			/// piano_key_pressed ///		
			struct piano_key_pressed_config
			{
				constexpr static const char *name = "ddf::junkyard::piano_key_pressed";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x360;
				static bool cfg_condition()
				{
				typedef typename junkyard::correct_notes correct_notes;
					typedef typename junkyard::secret_box_controller_1::button_grid kbd;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_2 lock;
			typedef room_1_content::piano_c1 c1;
			typedef room_1_content::piano_d1 d1;
			typedef room_1_content::piano_e1 e1;
			typedef room_1_content::piano_f1 f1;
			typedef room_1_content::piano_g1 g1;
			typedef room_1_content::piano_a1 a1;
			typedef room_1_content::piano_b1 b1;
			typedef room_1_content::piano_c2 c2;
			typedef room_1_content::piano_d2 d2;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::correct_notes correct_notes;
					typedef typename junkyard::secret_box_controller_1::button_grid kbd;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_2 lock;
			typedef room_1_content::piano_c1 c1;
			typedef room_1_content::piano_d1 d1;
			typedef room_1_content::piano_e1 e1;
			typedef room_1_content::piano_f1 f1;
			typedef room_1_content::piano_g1 g1;
			typedef room_1_content::piano_a1 a1;
			typedef room_1_content::piano_b1 b1;
			typedef room_1_content::piano_c2 c2;
			typedef room_1_content::piano_d2 d2;
	
(void)0; { 
	        keystroke_t v = kbd::value();
	        if(!v.state)
	   	     return;

		const uint8_t x = 8-v.key;

	        switch(x)
	        {
	            case 8:
	                c1::play();
	                if( (correct_notes::value() == 1)||
	                    (correct_notes::value() == 3)||
	                    (correct_notes::value() == 5)
			)
	                {
	                    correct_notes::value(correct_notes::value()+1);
	                }
	                else
	                {
	                    correct_notes::value(0);
	                }
	                break;
	            case 7:
	                d1::play();
	                correct_notes::value(0);
	                break;
	            case 6:
	                e1::play();
	                correct_notes::value(0);
	                break;
	            case 5:
	                f1::play();
	                if( (correct_notes::value() == 0)||
	                    (correct_notes::value() == 2)||
	                    (correct_notes::value() == 4)||
	                    (correct_notes::value() == 6)
			)
	                {
	                    correct_notes::value(correct_notes::value()+1);
	                }
	                else
	                {
	                    correct_notes::value(1);
	                }
	                break;
	            case 4:
	                g1::play();
	                correct_notes::value(0);
	                break;
	            case 3:
	                a1::play();
	                if(correct_notes::value() == 7)
	                {
	                    correct_notes::value(correct_notes::value()+1);
	                }
	                else
	                {
	                    correct_notes::value(0);
	                }
	                break;

	            case 2:
	                b1::play();
	                correct_notes::value(0);
	                break;

	            case 1:
	                c2::play();
	                if(correct_notes::value() == 8)
	                {
	                    correct_notes::value(correct_notes::value()+1);
	            	    lock::value(0);
	                }
	                else
	                {
	                    correct_notes::value(0);
	                }
	                break;

	            case 0:
	                d2::play();
	                correct_notes::value(0);
	                break;
	        }
	     }
				}
			};
			typedef wic::event<piano_key_pressed_config> piano_key_pressed;

			/// potato_power_indicator ///		
			struct potato_power_indicator_config
			{
				constexpr static const char *name = "ddf::junkyard::potato_power_indicator";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x3c0;
				static bool cfg_condition()
				{
					typedef typename junkyard::secret_box_controller_2::debouncer_10 button;
					typedef typename junkyard::secret_box_controller_2::light_controller indicator;
					return (true);
				}
				static void cfg_action()
				{
					typedef typename junkyard::secret_box_controller_2::debouncer_10 button;
					typedef typename junkyard::secret_box_controller_2::light_controller indicator;
	
(void)0; { 
		indicator::value(button::value());
         }
				}
			};
			typedef wic::event<potato_power_indicator_config> potato_power_indicator;

			/// relock_event ///		
			struct relock_event_config
			{
				constexpr static const char *name = "ddf::junkyard::relock_event";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x330;
				static bool cfg_condition()
				{
				typedef typename junkyard::relock_timer relock_timer;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_1 top_lock;
					return (true && ( 
			relock_timer::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::relock_timer relock_timer;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_1 top_lock;
	
(void)0; { 
			relock_timer::stop();
			relock_timer::reset();
			top_lock::value(1);
		 }
				}
			};
			typedef wic::event<relock_event_config> relock_event;

			/// reset_room ///		
			struct reset_room_config
			{
				constexpr static const char *name = "ddf::junkyard::reset_room";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x2f0;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::led_timer_start lts;
				typedef typename junkyard::lock_pick_1_pressed lock_pick_1_pressed;
				typedef typename junkyard::lock_pick_2_pressed lock_pick_2_pressed;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_1 lock_11;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_2 lock_12;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_3 lock_13;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_4 lock_14;
					typedef typename junkyard::secret_box_controller_1::addressable_led ledstrip;
					typedef typename junkyard::secret_box_controller_2::light_controller ampmeter;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_1 lock_21;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_2 lock_22;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_3 lock_23;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_4 lock_24;
					typedef typename junkyard::entrance_controller::led led;
				typedef typename junkyard::email_client::restart_game email_client_reset;
					return (true && ( 
		!gs::value()
	 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::led_timer_start lts;
				typedef typename junkyard::lock_pick_1_pressed lock_pick_1_pressed;
				typedef typename junkyard::lock_pick_2_pressed lock_pick_2_pressed;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_1 lock_11;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_2 lock_12;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_3 lock_13;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_4 lock_14;
					typedef typename junkyard::secret_box_controller_1::addressable_led ledstrip;
					typedef typename junkyard::secret_box_controller_2::light_controller ampmeter;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_1 lock_21;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_2 lock_22;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_3 lock_23;
					typedef typename junkyard::secret_box_controller_2::magnetic_lock_4 lock_24;
					typedef typename junkyard::entrance_controller::led led;
				typedef typename junkyard::email_client::restart_game email_client_reset;
	
(void)0; { 
		email_client_reset::value(1);
		lts::value(0);
		lock_11::value(1);
		lock_12::value(1);
		lock_13::value(1);
		lock_14::value(1);
		lock_21::value(1);
		lock_22::value(1);
		lock_23::value(1);
		lock_24::value(1);
		ampmeter::value(0);
		led::value(0);
		ledstrip::value_type v;
		for(int i = 0; i < 50; ++i)
		{
			v.led[i].red = 0;
			v.led[i].green = 0;
			v.led[i].blue = 0;
		}
		ledstrip::value((ledstrip::value_type)v);
		lock_pick_1_pressed::value(false);
		lock_pick_2_pressed::value(false);
	 }
				}
			};
			typedef wic::event<reset_room_config> reset_room;

			/// stop_audios ///		
			struct stop_audios_config
			{
				constexpr static const char *name = "ddf::junkyard::stop_audios";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x300;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
			typedef room_1_content::careful s1;
			typedef room_1_content::rules s2;
			typedef room_1_content::techdiff s3;
			typedef room_1_content::gminc s4;
			typedef room_2_content::careful s5;
			typedef room_2_content::rules s6;
			typedef room_2_content::techdiff s7;
			typedef room_2_content::gminc s8;
			typedef room_1_content::event_1 s9;
			typedef room_1_content::event_2 sa;
			typedef room_1_content::event_3 sb;
			typedef room_2_content::event_1 se;
			typedef room_2_content::event_2 sf;
			typedef room_2_content::event_3 sg;
					return (true && ( 
			3 == gs::value()
		 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
			typedef room_1_content::careful s1;
			typedef room_1_content::rules s2;
			typedef room_1_content::techdiff s3;
			typedef room_1_content::gminc s4;
			typedef room_2_content::careful s5;
			typedef room_2_content::rules s6;
			typedef room_2_content::techdiff s7;
			typedef room_2_content::gminc s8;
			typedef room_1_content::event_1 s9;
			typedef room_1_content::event_2 sa;
			typedef room_1_content::event_3 sb;
			typedef room_2_content::event_1 se;
			typedef room_2_content::event_2 sf;
			typedef room_2_content::event_3 sg;
	
(void)0; { 
			s1::cancel();
			s2::cancel();
			s3::cancel();
			s4::cancel();
			s5::cancel();
			s6::cancel();
			s7::cancel();
			s8::cancel();
			s9::cancel();
			sa::cancel();
			sb::cancel();
			se::cancel();
			sf::cancel();
			sg::cancel();
		 }
				}
			};
			typedef wic::event<stop_audios_config> stop_audios;

			/// time_up ///		
			struct time_up_config
			{
				constexpr static const char *name = "ddf::junkyard::time_up";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x200;
				static bool cfg_condition()
				{
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::gameend ge;
				typedef typename junkyard::gamestate gs;
			typedef room_1_content::event_5 failstate_room_1;
			typedef room_2_content::event_5 failstate_room_2;
					return (true && ( 
				tmr::value() >= 3600 && tmr::running() && 1 == gs::value() && !ge::value()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::gameend ge;
				typedef typename junkyard::gamestate gs;
			typedef room_1_content::event_5 failstate_room_1;
			typedef room_2_content::event_5 failstate_room_2;
	
(void)0; { 
				tmr::stop();
				failstate_room_1::play();
				failstate_room_2::play();
				ge::value(2);
				gs::value(3);
			 }
				}
			};
			typedef wic::event<time_up_config> time_up;

			/// timedevent_atmo_1_event_finished ///		
			struct timedevent_atmo_1_event_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_1_event_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x4a0;
				static bool cfg_condition()
				{
				typedef typename junkyard::timedevent_atmo_1 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_1_timer __timedevent_timer;
			typedef room_1_content::atmo_junkyard r1;
			typedef room_2_content::atmo_junkyard r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::timedevent_atmo_1 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_1_timer __timedevent_timer;
			typedef room_1_content::atmo_junkyard r1;
			typedef room_2_content::atmo_junkyard r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_atmo_1_event_finished_config> timedevent_atmo_1_event_finished;

			/// timedevent_atmo_1_event_gamestate ///		
			struct timedevent_atmo_1_event_gamestate_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_1_event_gamestate";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x4b0;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_1_timer tmr;
				typedef typename junkyard::timedevent_atmo_1 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_1_timer tmr;
				typedef typename junkyard::timedevent_atmo_1 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_atmo_1_event_gamestate_config> timedevent_atmo_1_event_gamestate;

			/// timedevent_atmo_2_event_finished ///		
			struct timedevent_atmo_2_event_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_2_event_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x4e0;
				static bool cfg_condition()
				{
				typedef typename junkyard::timedevent_atmo_2 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_2_timer __timedevent_timer;
			typedef room_1_content::atmo_blacky r1;
			typedef room_2_content::atmo_blacky r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::timedevent_atmo_2 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_2_timer __timedevent_timer;
			typedef room_1_content::atmo_blacky r1;
			typedef room_2_content::atmo_blacky r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_atmo_2_event_finished_config> timedevent_atmo_2_event_finished;

			/// timedevent_atmo_2_event_gamestate ///		
			struct timedevent_atmo_2_event_gamestate_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_2_event_gamestate";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x4f0;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_2_timer tmr;
				typedef typename junkyard::timedevent_atmo_2 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_2_timer tmr;
				typedef typename junkyard::timedevent_atmo_2 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_atmo_2_event_gamestate_config> timedevent_atmo_2_event_gamestate;

			/// timedevent_atmo_3_event_finished ///		
			struct timedevent_atmo_3_event_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_3_event_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x520;
				static bool cfg_condition()
				{
				typedef typename junkyard::timedevent_atmo_3 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_3_timer __timedevent_timer;
			typedef room_1_content::atmo_junkyard r1;
			typedef room_2_content::atmo_junkyard r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::timedevent_atmo_3 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_3_timer __timedevent_timer;
			typedef room_1_content::atmo_junkyard r1;
			typedef room_2_content::atmo_junkyard r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_atmo_3_event_finished_config> timedevent_atmo_3_event_finished;

			/// timedevent_atmo_3_event_gamestate ///		
			struct timedevent_atmo_3_event_gamestate_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_3_event_gamestate";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x530;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_3_timer tmr;
				typedef typename junkyard::timedevent_atmo_3 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_3_timer tmr;
				typedef typename junkyard::timedevent_atmo_3 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_atmo_3_event_gamestate_config> timedevent_atmo_3_event_gamestate;

			/// timedevent_atmo_4_event_finished ///		
			struct timedevent_atmo_4_event_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_4_event_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x560;
				static bool cfg_condition()
				{
				typedef typename junkyard::timedevent_atmo_4 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_4_timer __timedevent_timer;
			typedef room_1_content::atmo_telephone r1;
			typedef room_2_content::atmo_telephone r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::timedevent_atmo_4 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_4_timer __timedevent_timer;
			typedef room_1_content::atmo_telephone r1;
			typedef room_2_content::atmo_telephone r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_atmo_4_event_finished_config> timedevent_atmo_4_event_finished;

			/// timedevent_atmo_4_event_gamestate ///		
			struct timedevent_atmo_4_event_gamestate_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_4_event_gamestate";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x570;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_4_timer tmr;
				typedef typename junkyard::timedevent_atmo_4 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_4_timer tmr;
				typedef typename junkyard::timedevent_atmo_4 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_atmo_4_event_gamestate_config> timedevent_atmo_4_event_gamestate;

			/// timedevent_atmo_5_event_finished ///		
			struct timedevent_atmo_5_event_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_5_event_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x5a0;
				static bool cfg_condition()
				{
				typedef typename junkyard::timedevent_atmo_5 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_5_timer __timedevent_timer;
			typedef room_1_content::atmo_blacky r1;
			typedef room_2_content::atmo_blacky r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::timedevent_atmo_5 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_5_timer __timedevent_timer;
			typedef room_1_content::atmo_blacky r1;
			typedef room_2_content::atmo_blacky r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_atmo_5_event_finished_config> timedevent_atmo_5_event_finished;

			/// timedevent_atmo_5_event_gamestate ///		
			struct timedevent_atmo_5_event_gamestate_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_5_event_gamestate";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x5b0;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_5_timer tmr;
				typedef typename junkyard::timedevent_atmo_5 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_5_timer tmr;
				typedef typename junkyard::timedevent_atmo_5 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_atmo_5_event_gamestate_config> timedevent_atmo_5_event_gamestate;

			/// timedevent_atmo_6_event_finished ///		
			struct timedevent_atmo_6_event_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_6_event_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x5e0;
				static bool cfg_condition()
				{
				typedef typename junkyard::timedevent_atmo_6 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_6_timer __timedevent_timer;
			typedef room_1_content::atmo_blacky r1;
			typedef room_2_content::atmo_blacky r2;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::timedevent_atmo_6 __timedevent_at;
				typedef typename junkyard::timedevent_atmo_6_timer __timedevent_timer;
			typedef room_1_content::atmo_blacky r1;
			typedef room_2_content::atmo_blacky r2;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				r1::play();
				r2::play();
			 }
				}
			};
			typedef wic::event<timedevent_atmo_6_event_finished_config> timedevent_atmo_6_event_finished;

			/// timedevent_atmo_6_event_gamestate ///		
			struct timedevent_atmo_6_event_gamestate_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_atmo_6_event_gamestate";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x5f0;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_6_timer tmr;
				typedef typename junkyard::timedevent_atmo_6 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_atmo_6_timer tmr;
				typedef typename junkyard::timedevent_atmo_6 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_atmo_6_event_gamestate_config> timedevent_atmo_6_event_gamestate;

			/// timedevent_pc_1_event_finished ///		
			struct timedevent_pc_1_event_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_pc_1_event_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x420;
				static bool cfg_condition()
				{
				typedef typename junkyard::timedevent_pc_1 __timedevent_at;
				typedef typename junkyard::timedevent_pc_1_timer __timedevent_timer;
				typedef typename junkyard::incoming_call call;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::timedevent_pc_1 __timedevent_at;
				typedef typename junkyard::timedevent_pc_1_timer __timedevent_timer;
				typedef typename junkyard::incoming_call call;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				call::value(7);
			 }
				}
			};
			typedef wic::event<timedevent_pc_1_event_finished_config> timedevent_pc_1_event_finished;

			/// timedevent_pc_1_event_gamestate ///		
			struct timedevent_pc_1_event_gamestate_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_pc_1_event_gamestate";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x430;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_pc_1_timer tmr;
				typedef typename junkyard::timedevent_pc_1 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_pc_1_timer tmr;
				typedef typename junkyard::timedevent_pc_1 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_pc_1_event_gamestate_config> timedevent_pc_1_event_gamestate;

			/// timedevent_pc_2_event_finished ///		
			struct timedevent_pc_2_event_finished_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_pc_2_event_finished";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x460;
				static bool cfg_condition()
				{
				typedef typename junkyard::timedevent_pc_2 __timedevent_at;
				typedef typename junkyard::timedevent_pc_2_timer __timedevent_timer;
				typedef typename junkyard::incoming_call call;
					return (true && ( 
				__timedevent_at::value() <= __timedevent_timer::value() && __timedevent_timer::running()
			 ));
				}
				static void cfg_action()
				{
				typedef typename junkyard::timedevent_pc_2 __timedevent_at;
				typedef typename junkyard::timedevent_pc_2_timer __timedevent_timer;
				typedef typename junkyard::incoming_call call;
	
(void)0; { 
				__timedevent_timer::stop();
				__timedevent_timer::value(__timedevent_at::value());
			 } { 
				call::value(8);
			 }
				}
			};
			typedef wic::event<timedevent_pc_2_event_finished_config> timedevent_pc_2_event_finished;

			/// timedevent_pc_2_event_gamestate ///		
			struct timedevent_pc_2_event_gamestate_config
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_pc_2_event_gamestate";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x470;
				static bool cfg_condition()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_pc_2_timer tmr;
				typedef typename junkyard::timedevent_pc_2 at;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_pc_2_timer tmr;
				typedef typename junkyard::timedevent_pc_2 at;
	
(void)0; { 
				if(gs::value() == 1)
				{
					if(tmr::value() < at::value())
						tmr::start();
				}
				else
					tmr::stop();

				if(gs::value() == 0)
				{
					tmr::value(0);
					at::value(at::default_value());
				}
			 }
				}
			};
			typedef wic::event<timedevent_pc_2_event_gamestate_config> timedevent_pc_2_event_gamestate;

			/// top_opening ///		
			struct top_opening_config
			{
				constexpr static const char *name = "ddf::junkyard::top_opening";
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x320;
				static bool cfg_condition()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_4 on_switch;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_1 top_lock;
					typedef typename junkyard::secret_box_controller_1::addressable_led led;
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::led_timer_start lts;
				typedef typename junkyard::relock_timer relock_timer;
					return (true && ( 
	    	 on_switch::value() && !lts::value()
    	 ));
				}
				static void cfg_action()
				{
					typedef typename junkyard::secret_box_controller_1::debouncer_4 on_switch;
					typedef typename junkyard::secret_box_controller_1::magnetic_lock_1 top_lock;
					typedef typename junkyard::secret_box_controller_1::addressable_led led;
				typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::led_timer_start lts;
				typedef typename junkyard::relock_timer relock_timer;
	
(void)0; { 
			led::enabled(false);
			led::enabled(true);
	    	top_lock::value(0);
			lts::value(tmr::value());
			relock_timer::start();
	     }
				}
			};
			typedef wic::event<top_opening_config> top_opening;
}

	/// Room service
	namespace service
	{

			/// ComDev
			namespace comdev
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - service - ComDev";
					static const uint32_t cfg_class_id = 0x500080;
					static const uint16_t cfg_multiplicity = 4;
				};
				typedef wic::device_role<device_role_config> device_role;

			}

			/// GMClient
			namespace gmclient
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - service - GMClient";
					static const uint32_t cfg_class_id = 0x500070;
					static const uint16_t cfg_multiplicity = 4;
				};
				typedef wic::device_role<device_role_config> device_role;

			}


			/// ServerCpuStatus ///
			struct servercpustatus_config : public property_config_base
			{
				constexpr static const char *name = "ddf::service::servercpustatus";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x5ffff0;
				static const uint32_t cfg_member_id          = 0x10;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<servercpustatus_config> servercpustatus;

			/// ServerMemoryStatus ///
			struct servermemorystatus_config : public property_config_base
			{
				constexpr static const char *name = "ddf::service::servermemorystatus";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x5ffff0;
				static const uint32_t cfg_member_id          = 0x20;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<servermemorystatus_config> servermemorystatus;

			/// ServerNetworkStatus ///
			struct servernetworkstatus_config : public property_config_base
			{
				constexpr static const char *name = "ddf::service::servernetworkstatus";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x5ffff0;
				static const uint32_t cfg_member_id          = 0x40;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<servernetworkstatus_config> servernetworkstatus;

			/// ServerStorageStatus ///
			struct serverstoragestatus_config : public property_config_base
			{
				constexpr static const char *name = "ddf::service::serverstoragestatus";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x5ffff0;
				static const uint32_t cfg_member_id          = 0x30;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef property_room<serverstoragestatus_config> serverstoragestatus;



			/// StatusTimer
			struct statustimer_config
			{
				constexpr static const char *name = "ddf::service::statustimer";
				static const uint32_t cfg_class_id  = 0x5ffff0;
				static const uint32_t cfg_member_id = 0x50;
				static const uint32_t cfg_interval  = 3000;
			};
			typedef typename wic::timer<statustimer_config> statustimer;



			/// StatusTimerTick ///		
			struct statustimertick_config
			{
				constexpr static const char *name = "ddf::service::statustimertick";
				static const uint32_t cfg_class_id = 0x5ffff0;
				static const uint32_t cfg_member_id = 0x60;
				static bool cfg_condition()
				{
				typedef typename service::statustimer tmr;
				typedef typename service::servercpustatus cpu;
				typedef typename service::servermemorystatus mem;
				typedef typename service::serverstoragestatus dsk;
				typedef typename service::servernetworkstatus net;
					return (true);
				}
				static void cfg_action()
				{
				typedef typename service::statustimer tmr;
				typedef typename service::servercpustatus cpu;
				typedef typename service::servermemorystatus mem;
				typedef typename service::serverstoragestatus dsk;
				typedef typename service::servernetworkstatus net;
	
(void)0; { 
      cpu::value((uint8_t)(status::cpu::usage()*255));
      mem::value((uint8_t)((double)status::memory::used()/status::memory::total()*255));
      dsk::value((uint8_t)((double)status::storage::used()/status::storage::total()*255));
      net::value(0);
     }
				}
			};
			typedef wic::event<statustimertick_config> statustimertick;
}

}

static void init()
{
	ddf::pirate::cashier_laser_controller::device_role::init();
	ddf::pirate::cashier_laser_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::cashier_laser_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::cashier_laser_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::cashier_laser_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::cashier_laser_controller::laser::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::laser::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::cashier_laser_controller::laser::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::cashier_laser_controller::laser::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::cashier_laser_controller::laser::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::cashier_laser_controller::lcd::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::lcd::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::cashier_laser_controller::lcd::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::cashier_laser_controller::lcd::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::cashier_laser_controller::lcd::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::cashier_laser_controller::pin_pad::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::cashier_laser_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::cashier_laser_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::cashier_laser_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::cashier_laser_controller::cash_box::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::cash_box::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::cashier_laser_controller::cash_box::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::cashier_laser_controller::cash_box::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::cashier_laser_controller::cash_box::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::cashier_laser_controller::switch_1::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::cashier_laser_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::cashier_laser_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::cashier_laser_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::cashier_laser_controller::led_strip::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::cashier_laser_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::cashier_laser_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::cashier_laser_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::cashier_laser_controller::buzzer::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::cashier_laser_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::cashier_laser_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::cashier_laser_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::pirate::cashier_laser_controller::device_role>();
	ddf::pirate::entrance_hanger_controller::device_role::init();
	ddf::pirate::entrance_hanger_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::entrance_hanger_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::entrance_hanger_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::entrance_hanger_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::entrance_hanger_controller::debouncer::init(ddf::pirate::entrance_hanger_controller::device_role::instance());
	ddf::pirate::entrance_hanger_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::entrance_hanger_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::entrance_hanger_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::entrance_hanger_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::entrance_hanger_controller::led::init(ddf::pirate::entrance_hanger_controller::device_role::instance());
	ddf::pirate::entrance_hanger_controller::led::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::entrance_hanger_controller::led::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::entrance_hanger_controller::led::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::entrance_hanger_controller::led::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::entrance_hanger_controller::magnetic_sensor::init(ddf::pirate::entrance_hanger_controller::device_role::instance());
	ddf::pirate::entrance_hanger_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::entrance_hanger_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::entrance_hanger_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::entrance_hanger_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::entrance_hanger_controller::debouncer_2::init(ddf::pirate::entrance_hanger_controller::device_role::instance());
	ddf::pirate::entrance_hanger_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::entrance_hanger_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::entrance_hanger_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::entrance_hanger_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::pirate::entrance_hanger_controller::device_role>();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::init();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role>();
	ddf::pirate::map_controller::device_role::init();
	ddf::pirate::map_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::map_controller::magnetic_sensor_1::init(ddf::pirate::map_controller::device_role::instance());
	ddf::pirate::map_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::map_controller::magnetic_sensor_2::init(ddf::pirate::map_controller::device_role::instance());
	ddf::pirate::map_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::map_controller::led_strip::init(ddf::pirate::map_controller::device_role::instance());
	ddf::pirate::map_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::pirate::map_controller::device_role>();
	ddf::pirate::rex_flipper_controller::device_role::init();
	ddf::pirate::rex_flipper_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::light_controller_1::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::light_controller_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::light_controller_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::light_controller_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::light_controller_2::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::light_controller_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::light_controller_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::light_controller_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::light_controller_3::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::light_controller_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::light_controller_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::light_controller_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::light_controller_4::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::light_controller_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::light_controller_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::light_controller_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::light_controller_5::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::light_controller_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::light_controller_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::light_controller_5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::light_controller_6::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_6::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::light_controller_6::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::light_controller_6::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::light_controller_6::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::light_controller_7::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_7::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::light_controller_7::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::light_controller_7::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::light_controller_7::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::photosensor_1::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::photosensor_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::photosensor_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::photosensor_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::photosensor_2::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::photosensor_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::photosensor_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::photosensor_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::photosensor_3::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::photosensor_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::photosensor_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::photosensor_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::photosensor_4::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::photosensor_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::photosensor_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::photosensor_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::photosensor_5::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::photosensor_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::photosensor_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::photosensor_5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::photosensor_6::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_6::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::photosensor_6::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::photosensor_6::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::photosensor_6::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::photosensor_7::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_7::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::photosensor_7::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::photosensor_7::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::photosensor_7::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::rfid_reader::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::magnetic_lock::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_flipper_controller::led::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::led::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_flipper_controller::led::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_flipper_controller::led::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_flipper_controller::led::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::pirate::rex_flipper_controller::device_role>();
	ddf::pirate::stone_chest_controller::device_role::init();
	ddf::pirate::stone_chest_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stone_chest_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stone_chest_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stone_chest_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::stone_chest_controller::magnetic_sensor_1::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stone_chest_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stone_chest_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stone_chest_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::stone_chest_controller::magnetic_sensor_2::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stone_chest_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stone_chest_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stone_chest_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::stone_chest_controller::magnetic_sensor_3::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stone_chest_controller::magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stone_chest_controller::magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stone_chest_controller::magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::stone_chest_controller::magnetic_sensor_4::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stone_chest_controller::magnetic_sensor_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stone_chest_controller::magnetic_sensor_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stone_chest_controller::magnetic_sensor_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::stone_chest_controller::magnetic_sensor_5::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stone_chest_controller::magnetic_sensor_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stone_chest_controller::magnetic_sensor_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stone_chest_controller::magnetic_sensor_5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::stone_chest_controller::magnetic_lock_1::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stone_chest_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stone_chest_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stone_chest_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::stone_chest_controller::magnetic_lock_2::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stone_chest_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stone_chest_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stone_chest_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::stone_chest_controller::led_strip::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stone_chest_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stone_chest_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stone_chest_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::pirate::stone_chest_controller::device_role>();

	ddf::pirate::artificial_game_ending::init();
	ddf::pirate::entrance_hanger_controller::led::value::on_change += ddf::pirate::artificial_game_ending::monitor;

	ddf::pirate::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::cashier_pin_timeout::init();
	ddf::pirate::pin_timeout_timer::on_value_change += ddf::pirate::cashier_pin_timeout::monitor;

	ddf::pirate::cashier_pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::cashier_pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::cashier_pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::cashier_pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::display_update::init();
	ddf::pirate::pin_code::on_change += ddf::pirate::display_update::monitor;

	ddf::pirate::display_update::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::display_update::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::display_update::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::display_update::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::freeze_1::init();
	ddf::pirate::freezed1::on_change += ddf::pirate::freeze_1::monitor;

	ddf::pirate::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::freeze_1_timeout::init();
	ddf::pirate::freezetimer1::on_value_change += ddf::pirate::freeze_1_timeout::monitor;

	ddf::pirate::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::freeze_5::init();
	ddf::pirate::freezed5::on_change += ddf::pirate::freeze_5::monitor;

	ddf::pirate::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::freeze_5_timeout::init();
	ddf::pirate::freezetimer5::on_value_change += ddf::pirate::freeze_5_timeout::monitor;

	ddf::pirate::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::game_end_button_push::init();
	ddf::pirate::entrance_hanger_controller::debouncer::value::on_change += ddf::pirate::game_end_button_push::monitor;

	ddf::pirate::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::game_ending::init();
	ddf::pirate::gameend::on_change += ddf::pirate::game_ending::monitor;

	ddf::pirate::game_ending::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::game_ending::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::game_ending::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::game_ending::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::game_pause_mgmt::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::game_pause_mgmt::monitor;
	ddf::pirate::paused::on_change += ddf::pirate::game_pause_mgmt::monitor;
	ddf::pirate::freezed1::on_change += ddf::pirate::game_pause_mgmt::monitor;
	ddf::pirate::freezed5::on_change += ddf::pirate::game_pause_mgmt::monitor;
	ddf::pirate::gm_help_status::on_change += ddf::pirate::game_pause_mgmt::monitor;
	ddf::pirate::entrance_hanger_controller::magnetic_sensor::value::on_change += ddf::pirate::game_pause_mgmt::monitor;

	ddf::pirate::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_boat_door_opened::init();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3::value::on_change += ddf::pirate::gameevent_boat_door_opened::monitor;

	ddf::pirate::gameevent_boat_door_opened::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_boat_door_opened::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_boat_door_opened::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_boat_door_opened::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_bright_star::init();
	ddf::pirate::star_value::on_change += ddf::pirate::gameevent_bright_star::monitor;

	ddf::pirate::gameevent_bright_star::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_bright_star::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_bright_star::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_bright_star::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_brightest_star::init();
	ddf::pirate::star_value::on_change += ddf::pirate::gameevent_brightest_star::monitor;

	ddf::pirate::gameevent_brightest_star::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_brightest_star::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_brightest_star::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_brightest_star::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_call_accepted::init();
	ddf::pirate::incoming_call_status::on_change += ddf::pirate::gameevent_call_accepted::monitor;

	ddf::pirate::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_call_declined::init();
	ddf::pirate::incoming_call_status::on_change += ddf::pirate::gameevent_call_declined::monitor;

	ddf::pirate::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_call_finished::init();
	ddf::pirate::incoming_call_status::on_change += ddf::pirate::gameevent_call_finished::monitor;

	ddf::pirate::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_call_missed::init();
	ddf::pirate::incoming_call_status::on_change += ddf::pirate::gameevent_call_missed::monitor;

	ddf::pirate::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_call_ringing::init();
	ddf::pirate::incoming_call_status::on_change += ddf::pirate::gameevent_call_ringing::monitor;

	ddf::pirate::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_cashier_code_mistaken::init();
	ddf::pirate::pin_code::on_change += ddf::pirate::gameevent_cashier_code_mistaken::monitor;

	ddf::pirate::gameevent_cashier_code_mistaken::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_cashier_code_mistaken::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_cashier_code_mistaken::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_cashier_code_mistaken::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_cashier_opened::init();
	ddf::pirate::pin_code::on_change += ddf::pirate::gameevent_cashier_opened::monitor;

	ddf::pirate::gameevent_cashier_opened::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_cashier_opened::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_cashier_opened::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_cashier_opened::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_chest_opening::init();
	ddf::pirate::stone_chest_controller::magnetic_sensor_5::value::on_change += ddf::pirate::gameevent_chest_opening::monitor;

	ddf::pirate::gameevent_chest_opening::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_chest_opening::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_chest_opening::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_chest_opening::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_game_fail::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::gameevent_game_fail::monitor;
	ddf::pirate::gameend::on_change += ddf::pirate::gameevent_game_fail::monitor;

	ddf::pirate::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_game_finished::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::gameevent_game_finished::monitor;

	ddf::pirate::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_game_paused::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::gameevent_game_paused::monitor;

	ddf::pirate::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_game_reset::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::gameevent_game_reset::monitor;

	ddf::pirate::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_game_started::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::gameevent_game_started::monitor;

	ddf::pirate::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_game_win::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::gameevent_game_win::monitor;
	ddf::pirate::gameend::on_change += ddf::pirate::gameevent_game_win::monitor;

	ddf::pirate::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_ghostbox_opened::init();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1::value::on_change += ddf::pirate::gameevent_ghostbox_opened::monitor;

	ddf::pirate::gameevent_ghostbox_opened::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_ghostbox_opened::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_ghostbox_opened::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_ghostbox_opened::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_key_released::init();
	ddf::pirate::stone_chest_controller::magnetic_lock_1::value::on_change += ddf::pirate::gameevent_key_released::monitor;

	ddf::pirate::gameevent_key_released::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_key_released::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_key_released::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_key_released::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_knock_succeeded::init();
	ddf::pirate::knock_count::on_change += ddf::pirate::gameevent_knock_succeeded::monitor;

	ddf::pirate::gameevent_knock_succeeded::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_knock_succeeded::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_knock_succeeded::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_knock_succeeded::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_lattice_opened::init();
	ddf::pirate::stone_chest_controller::magnetic_lock_2::value::on_change += ddf::pirate::gameevent_lattice_opened::monitor;

	ddf::pirate::gameevent_lattice_opened::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_lattice_opened::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_lattice_opened::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_lattice_opened::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_rex_card_inserted::init();
	ddf::pirate::rex_flipper_controller::rfid_reader::value::on_change += ddf::pirate::gameevent_rex_card_inserted::monitor;

	ddf::pirate::gameevent_rex_card_inserted::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_rex_card_inserted::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_rex_card_inserted::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_rex_card_inserted::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_rex_card_removed::init();
	ddf::pirate::rex_flipper_controller::rfid_reader::value::on_change += ddf::pirate::gameevent_rex_card_removed::monitor;

	ddf::pirate::gameevent_rex_card_removed::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_rex_card_removed::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_rex_card_removed::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_rex_card_removed::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_rex_game_won::init();
	ddf::pirate::rex_score::on_change += ddf::pirate::gameevent_rex_game_won::monitor;

	ddf::pirate::gameevent_rex_game_won::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_rex_game_won::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_rex_game_won::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_rex_game_won::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gameevent_rex_table_retry::init();
	ddf::pirate::rex_trials_left::on_change += ddf::pirate::gameevent_rex_table_retry::monitor;

	ddf::pirate::gameevent_rex_table_retry::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameevent_rex_table_retry::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameevent_rex_table_retry::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameevent_rex_table_retry::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::ghost_blinking::init();
	ddf::pirate::ghost_blink_timer::on_value_change += ddf::pirate::ghost_blinking::monitor;

	ddf::pirate::ghost_blinking::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghost_blinking::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghost_blinking::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghost_blinking::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::hanger_trigger::init();
	ddf::pirate::entrance_hanger_controller::debouncer_2::value::on_change += ddf::pirate::hanger_trigger::monitor;

	ddf::pirate::hanger_trigger::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::hanger_trigger::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::hanger_trigger::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::hanger_trigger::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::knock_accumulate::init();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::value::on_change += ddf::pirate::knock_accumulate::monitor;

	ddf::pirate::knock_accumulate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::knock_accumulate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::knock_accumulate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::knock_accumulate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::knock_reset::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::knock_reset::monitor;

	ddf::pirate::knock_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::knock_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::knock_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::knock_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::knock_timeout::init();
	ddf::pirate::knock_timer::on_value_change += ddf::pirate::knock_timeout::monitor;

	ddf::pirate::knock_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::knock_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::knock_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::knock_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::laser_turn_off::init();
	ddf::pirate::cashier_laser_controller::switch_1::value::on_change += ddf::pirate::laser_turn_off::monitor;

	ddf::pirate::laser_turn_off::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::laser_turn_off::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::laser_turn_off::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::laser_turn_off::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::left_column_evaluate::init();
	ddf::pirate::rex_flipper_controller::photosensor_3::value::on_change += ddf::pirate::left_column_evaluate::monitor;

	ddf::pirate::left_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::left_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::left_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::left_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::map_reset::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::map_reset::monitor;

	ddf::pirate::map_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::map_sensor1::init();
	ddf::pirate::map_controller::magnetic_sensor_1::value::on_change += ddf::pirate::map_sensor1::monitor;

	ddf::pirate::map_sensor1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_sensor1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_sensor1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_sensor1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::map_sensor2::init();
	ddf::pirate::map_controller::magnetic_sensor_2::value::on_change += ddf::pirate::map_sensor2::monitor;

	ddf::pirate::map_sensor2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_sensor2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_sensor2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_sensor2::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::map_solved::init();
	ddf::pirate::map_sensor1_triggered::on_change += ddf::pirate::map_solved::monitor;
	ddf::pirate::map_sensor2_triggered::on_change += ddf::pirate::map_solved::monitor;

	ddf::pirate::map_solved::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_solved::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_solved::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_solved::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::middle_column_evaluate::init();
	ddf::pirate::rex_flipper_controller::photosensor_1::value::on_change += ddf::pirate::middle_column_evaluate::monitor;

	ddf::pirate::middle_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::middle_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::middle_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::middle_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::pin_code_accumulation::init();
	ddf::pirate::cashier_laser_controller::pin_pad::value::on_change += ddf::pirate::pin_code_accumulation::monitor;

	ddf::pirate::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::reset_room::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::reset_room::monitor;

	ddf::pirate::reset_room::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::reset_room::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::reset_room::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::reset_room::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_blink::init();
	ddf::pirate::rex_blink_timer::on_value_change += ddf::pirate::rex_blink::monitor;

	ddf::pirate::rex_blink::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_blink::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_blink::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_blink::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_led_update::init();
	ddf::pirate::rex_trials_left::on_change += ddf::pirate::rex_led_update::monitor;

	ddf::pirate::rex_led_update::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_led_update::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_led_update::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_led_update::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_photosensor_4_acc::init();
	ddf::pirate::rex_flipper_controller::photosensor_4::value::on_change += ddf::pirate::rex_photosensor_4_acc::monitor;

	ddf::pirate::rex_photosensor_4_acc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_photosensor_4_acc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_photosensor_4_acc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_photosensor_4_acc::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_photosensor_5_acc::init();
	ddf::pirate::rex_flipper_controller::photosensor_5::value::on_change += ddf::pirate::rex_photosensor_5_acc::monitor;

	ddf::pirate::rex_photosensor_5_acc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_photosensor_5_acc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_photosensor_5_acc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_photosensor_5_acc::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_photosensor_6_acc::init();
	ddf::pirate::rex_flipper_controller::photosensor_6::value::on_change += ddf::pirate::rex_photosensor_6_acc::monitor;

	ddf::pirate::rex_photosensor_6_acc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_photosensor_6_acc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_photosensor_6_acc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_photosensor_6_acc::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_photosensor_7_acc::init();
	ddf::pirate::rex_flipper_controller::photosensor_7::value::on_change += ddf::pirate::rex_photosensor_7_acc::monitor;

	ddf::pirate::rex_photosensor_7_acc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_photosensor_7_acc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_photosensor_7_acc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_photosensor_7_acc::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_table_state::init();
	ddf::pirate::rex_enabled::on_change += ddf::pirate::rex_table_state::monitor;

	ddf::pirate::rex_table_state::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_table_state::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_table_state::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_table_state::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::right_column_evaluate::init();
	ddf::pirate::rex_flipper_controller::photosensor_2::value::on_change += ddf::pirate::right_column_evaluate::monitor;

	ddf::pirate::right_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::right_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::right_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::right_column_evaluate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rotation_update::init();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::value::on_change += ddf::pirate::rotation_update::monitor;

	ddf::pirate::rotation_update::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rotation_update::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rotation_update::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rotation_update::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::sign_matching::init();
	ddf::pirate::stone_chest_controller::magnetic_sensor_1::value::on_change += ddf::pirate::sign_matching::monitor;
	ddf::pirate::stone_chest_controller::magnetic_sensor_2::value::on_change += ddf::pirate::sign_matching::monitor;
	ddf::pirate::stone_chest_controller::magnetic_sensor_3::value::on_change += ddf::pirate::sign_matching::monitor;
	ddf::pirate::stone_chest_controller::magnetic_sensor_4::value::on_change += ddf::pirate::sign_matching::monitor;

	ddf::pirate::sign_matching::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::sign_matching::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::sign_matching::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::sign_matching::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::stop_audios::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::stop_audios::monitor;

	ddf::pirate::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::time_up::init();
	ddf::pirate::gametimer::on_value_change += ddf::pirate::time_up::monitor;

	ddf::pirate::time_up::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::time_up::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::time_up::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::time_up::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_an_1_event_finished::init();
	ddf::pirate::timedevent_an_1_timer::on_value_change += ddf::pirate::timedevent_an_1_event_finished::monitor;

	ddf::pirate::timedevent_an_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_an_1_event_gamestate::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::timedevent_an_1_event_gamestate::monitor;

	ddf::pirate::timedevent_an_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_an_2_event_finished::init();
	ddf::pirate::timedevent_an_2_timer::on_value_change += ddf::pirate::timedevent_an_2_event_finished::monitor;

	ddf::pirate::timedevent_an_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_an_2_event_gamestate::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::timedevent_an_2_event_gamestate::monitor;

	ddf::pirate::timedevent_an_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_an_3_event_finished::init();
	ddf::pirate::timedevent_an_3_timer::on_value_change += ddf::pirate::timedevent_an_3_event_finished::monitor;

	ddf::pirate::timedevent_an_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_an_3_event_gamestate::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::timedevent_an_3_event_gamestate::monitor;

	ddf::pirate::timedevent_an_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_ghost_voice_event_finished::init();
	ddf::pirate::timedevent_ghost_voice_timer::on_value_change += ddf::pirate::timedevent_ghost_voice_event_finished::monitor;

	ddf::pirate::timedevent_ghost_voice_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_ghost_voice_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_ghost_voice_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_ghost_voice_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_ghost_voice_event_gamestate::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::timedevent_ghost_voice_event_gamestate::monitor;

	ddf::pirate::timedevent_ghost_voice_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_ghost_voice_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_ghost_voice_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_ghost_voice_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_pc_1_event_finished::init();
	ddf::pirate::timedevent_pc_1_timer::on_value_change += ddf::pirate::timedevent_pc_1_event_finished::monitor;

	ddf::pirate::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_pc_1_event_gamestate::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::timedevent_pc_1_event_gamestate::monitor;

	ddf::pirate::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_pc_2_event_finished::init();
	ddf::pirate::timedevent_pc_2_timer::on_value_change += ddf::pirate::timedevent_pc_2_event_finished::monitor;

	ddf::pirate::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_pc_2_event_gamestate::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::timedevent_pc_2_event_gamestate::monitor;

	ddf::pirate::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::tray_trigger::init();
	ddf::pirate::tray_camera_content::tray_sensor::on_value_change += ddf::pirate::tray_trigger::monitor;

	ddf::pirate::tray_trigger::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::tray_trigger::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::tray_trigger::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::tray_trigger::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::wheel_reset::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::wheel_reset::monitor;

	ddf::pirate::wheel_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::wheel_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::wheel_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::wheel_reset::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::audio_message_url::init(std::string());
	ddf::pirate::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::pirate::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::pirate::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::pirate::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::pirate::comdev_reset::init(bool(false));
	ddf::pirate::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::pirate::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::pirate::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::pirate::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::pirate::comdev_silence::init(bool(false));
	ddf::pirate::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::pirate::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::pirate::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::pirate::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::pirate::freezed1::init(bool());
	ddf::pirate::freezed1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::freezed1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::freezed1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::freezed1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::freezed5::init(bool());
	ddf::pirate::freezed5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::freezed5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::freezed5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::freezed5::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gm_help_status::init(bool());
	ddf::pirate::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::pirate::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::pirate::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::pirate::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::pirate::gameend::init(uint8_t(0));
	ddf::pirate::gameend::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gameend::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gameend::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gameend::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::gamestate::init(uint8_t(3));
	ddf::pirate::gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::incoming_call::init(uint8_t(0xff));
	ddf::pirate::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::incoming_call::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::pirate::incoming_call::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::pirate::incoming_call::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::pirate::incoming_call::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::pirate::incoming_call_status::init(uint8_t());
	ddf::pirate::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::pirate::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::pirate::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::pirate::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::pirate::paused::init(bool());
	ddf::pirate::paused::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::paused::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::paused::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::paused::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::restart_game::init(bool());
	ddf::pirate::restart_game::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::restart_game::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::restart_game::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::restart_game::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::restart_game::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::pirate::restart_game::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::pirate::restart_game::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::pirate::restart_game::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::pirate::text_message::init(std::string());
	ddf::pirate::text_message::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::text_message::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::text_message::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::text_message::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::text_message::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::pirate::text_message::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::pirate::text_message::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::pirate::text_message::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::pirate::text_message_sender::init(uint8_t(0xff));
	ddf::pirate::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::pirate::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::pirate::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::pirate::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::pirate::knock_count::init(uint32_t(0));
	ddf::pirate::knock_count::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::knock_count::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::knock_count::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::knock_count::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::map_sensor1_triggered::init(bool(false));
	ddf::pirate::map_sensor1_triggered::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_sensor1_triggered::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_sensor1_triggered::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_sensor1_triggered::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::map_sensor2_triggered::init(bool(false));
	ddf::pirate::map_sensor2_triggered::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::map_sensor2_triggered::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::map_sensor2_triggered::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::map_sensor2_triggered::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::pin_code::init(std::string());
	ddf::pirate::pin_code::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::pin_code::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::pin_code::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::pin_code::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_enabled::init(bool(false));
	ddf::pirate::rex_enabled::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_enabled::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_enabled::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_enabled::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_left_column_failure::init(bool(false));
	ddf::pirate::rex_left_column_failure::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_left_column_failure::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_left_column_failure::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_left_column_failure::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_middle_column_failure::init(bool(false));
	ddf::pirate::rex_middle_column_failure::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_middle_column_failure::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_middle_column_failure::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_middle_column_failure::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_photosensor_4_value::init(bool(false));
	ddf::pirate::rex_photosensor_4_value::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_photosensor_4_value::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_photosensor_4_value::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_photosensor_4_value::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_photosensor_5_value::init(bool(false));
	ddf::pirate::rex_photosensor_5_value::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_photosensor_5_value::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_photosensor_5_value::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_photosensor_5_value::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_photosensor_6_value::init(bool(false));
	ddf::pirate::rex_photosensor_6_value::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_photosensor_6_value::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_photosensor_6_value::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_photosensor_6_value::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_photosensor_7_value::init(bool(false));
	ddf::pirate::rex_photosensor_7_value::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_photosensor_7_value::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_photosensor_7_value::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_photosensor_7_value::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_right_column_failure::init(bool(false));
	ddf::pirate::rex_right_column_failure::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_right_column_failure::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_right_column_failure::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_right_column_failure::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_score::init(uint32_t(3));
	ddf::pirate::rex_score::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_score::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_score::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_score::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::rex_trials_left::init(uint8_t(0));
	ddf::pirate::rex_trials_left::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_trials_left::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_trials_left::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_trials_left::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::star_value::init(uint16_t(0));
	ddf::pirate::star_value::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::star_value::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::star_value::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::star_value::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_an_1::init(uint64_t(300));
	ddf::pirate::timedevent_an_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_an_2::init(uint64_t(1800));
	ddf::pirate::timedevent_an_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_2::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_an_3::init(uint64_t(3300));
	ddf::pirate::timedevent_an_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_3::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_ghost_voice::init(uint64_t(30));
	ddf::pirate::timedevent_ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_pc_1::init(uint64_t(1200));
	ddf::pirate::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::timedevent_pc_2::init(uint64_t(2400));
	ddf::pirate::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::pirate::wheel_last_pos::init(uint16_t(0));
	ddf::pirate::wheel_last_pos::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::wheel_last_pos::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::wheel_last_pos::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::wheel_last_pos::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1::init();
	ddf::pirate::room_1_content::chord::init();
	ddf::pirate::room_1_content::progress::init();
	ddf::pirate::room_1_content::careful::init();
	ddf::pirate::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1_content::event_1::init();
	ddf::pirate::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1_content::event_2::init();
	ddf::pirate::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1_content::event_3::init();
	ddf::pirate::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1_content::failstate::init();
	ddf::pirate::room_1_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1_content::gminc::init();
	ddf::pirate::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1_content::ghost_voice::init();
	ddf::pirate::room_1_content::ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1_content::rules::init();
	ddf::pirate::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1_content::techdiff::init();
	ddf::pirate::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_1_content::winstate::init();
	ddf::pirate::room_1_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_1_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_1_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_1_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(3));


	ddf::pirate::room_2::init();
	ddf::pirate::room_2_content::chord::init();
	ddf::pirate::room_2_content::progress::init();
	ddf::pirate::room_2_content::careful::init();
	ddf::pirate::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_2_content::event_1::init();
	ddf::pirate::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_2_content::event_2::init();
	ddf::pirate::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_2_content::event_3::init();
	ddf::pirate::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_2_content::failstate::init();
	ddf::pirate::room_2_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_2_content::gminc::init();
	ddf::pirate::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_2_content::ghost_voice::init();
	ddf::pirate::room_2_content::ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::ghost_voice::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_2_content::rules::init();
	ddf::pirate::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_2_content::techdiff::init();
	ddf::pirate::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::room_2_content::winstate::init();
	ddf::pirate::room_2_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::room_2_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::room_2_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::room_2_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(3));



	ddf::pirate::tray_camera::init();
	ddf::pirate::tray_camera_content::tray_sensor::init();



	ddf::pirate::freezetimer1::init();
	ddf::pirate::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::freezetimer5::init();
	ddf::pirate::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::gametimer::init();
	ddf::pirate::gametimer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::gametimer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::gametimer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::gametimer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::ghost_blink_timer::init();
	ddf::pirate::ghost_blink_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::ghost_blink_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::ghost_blink_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::ghost_blink_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::knock_timer::init();
	ddf::pirate::knock_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::knock_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::knock_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::knock_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::pin_timeout_timer::init();
	ddf::pirate::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::rex_blink_timer::init();
	ddf::pirate::rex_blink_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::rex_blink_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::rex_blink_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::rex_blink_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::timedevent_an_1_timer::init();
	ddf::pirate::timedevent_an_1_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_1_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_1_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_1_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::timedevent_an_2_timer::init();
	ddf::pirate::timedevent_an_2_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_2_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_2_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_2_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::timedevent_an_3_timer::init();
	ddf::pirate::timedevent_an_3_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_an_3_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_an_3_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_an_3_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::timedevent_ghost_voice_timer::init();
	ddf::pirate::timedevent_ghost_voice_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_ghost_voice_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_ghost_voice_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_ghost_voice_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::timedevent_pc_1_timer::init();
	ddf::pirate::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::pirate::timedevent_pc_2_timer::init();
	ddf::pirate::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::pirate::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::pirate::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::pirate::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(3));


	ddf::magician::cupboard_controller::device_role::init();
	ddf::magician::cupboard_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::cupboard_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::cupboard_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::cupboard_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::cupboard_controller::debouncer::init(ddf::magician::cupboard_controller::device_role::instance());
	ddf::magician::cupboard_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::cupboard_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::cupboard_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::cupboard_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::cupboard_controller::magnetic_sensor::init(ddf::magician::cupboard_controller::device_role::instance());
	ddf::magician::cupboard_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::cupboard_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::cupboard_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::cupboard_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::cupboard_controller::magnetic_lock::init(ddf::magician::cupboard_controller::device_role::instance());
	ddf::magician::cupboard_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::cupboard_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::cupboard_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::cupboard_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::cupboard_controller::led_strip::init(ddf::magician::cupboard_controller::device_role::instance());
	ddf::magician::cupboard_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::cupboard_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::cupboard_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::cupboard_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::magician::cupboard_controller::device_role>();
	ddf::magician::design_board_controller::device_role::init();
	ddf::magician::design_board_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::design_board_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::design_board_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::design_board_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::design_board_controller::linear_magnetic_sensor_1::init(ddf::magician::design_board_controller::device_role::instance());
	ddf::magician::design_board_controller::linear_magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::design_board_controller::linear_magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::design_board_controller::linear_magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::design_board_controller::linear_magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::design_board_controller::linear_magnetic_sensor_2::init(ddf::magician::design_board_controller::device_role::instance());
	ddf::magician::design_board_controller::linear_magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::design_board_controller::linear_magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::design_board_controller::linear_magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::design_board_controller::linear_magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::design_board_controller::linear_magnetic_sensor_3::init(ddf::magician::design_board_controller::device_role::instance());
	ddf::magician::design_board_controller::linear_magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::design_board_controller::linear_magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::design_board_controller::linear_magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::design_board_controller::linear_magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::design_board_controller::magnetic_lock::init(ddf::magician::design_board_controller::device_role::instance());
	ddf::magician::design_board_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::design_board_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::design_board_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::design_board_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::magician::design_board_controller::device_role>();
	ddf::magician::entrance_controller::device_role::init();
	ddf::magician::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::entrance_controller::debouncer::init(ddf::magician::entrance_controller::device_role::instance());
	ddf::magician::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::entrance_controller::led::init(ddf::magician::entrance_controller::device_role::instance());
	ddf::magician::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::entrance_controller::magnetic_sensor::init(ddf::magician::entrance_controller::device_role::instance());
	ddf::magician::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::magician::entrance_controller::device_role>();
	ddf::magician::futuristic_safe_controller::device_role::init();
	ddf::magician::futuristic_safe_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::futuristic_safe_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::futuristic_safe_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::futuristic_safe_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::futuristic_safe_controller::debouncer::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::futuristic_safe_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::futuristic_safe_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::futuristic_safe_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::futuristic_safe_controller::rfid_reader::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::futuristic_safe_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::futuristic_safe_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::futuristic_safe_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::futuristic_safe_controller::pin_pad::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::futuristic_safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::futuristic_safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::futuristic_safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::futuristic_safe_controller::magnetic_lock::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::futuristic_safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::futuristic_safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::futuristic_safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::futuristic_safe_controller::addressable_led_strip::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::addressable_led_strip::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::futuristic_safe_controller::addressable_led_strip::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::futuristic_safe_controller::addressable_led_strip::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::futuristic_safe_controller::addressable_led_strip::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::futuristic_safe_controller::buzzer::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::futuristic_safe_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::futuristic_safe_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::futuristic_safe_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::magician::futuristic_safe_controller::device_role>();

	ddf::magician::artificial_game_ending::init();
	ddf::magician::entrance_controller::led::value::on_change += ddf::magician::artificial_game_ending::monitor;

	ddf::magician::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::freeze_1::init();
	ddf::magician::freezed1::on_change += ddf::magician::freeze_1::monitor;

	ddf::magician::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::freeze_1_timeout::init();
	ddf::magician::freezetimer1::on_value_change += ddf::magician::freeze_1_timeout::monitor;

	ddf::magician::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::freeze_5::init();
	ddf::magician::freezed5::on_change += ddf::magician::freeze_5::monitor;

	ddf::magician::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::freeze_5_timeout::init();
	ddf::magician::freezetimer5::on_value_change += ddf::magician::freeze_5_timeout::monitor;

	ddf::magician::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::game_end_button_push::init();
	ddf::magician::entrance_controller::debouncer::value::on_change += ddf::magician::game_end_button_push::monitor;

	ddf::magician::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::game_ending::init();
	ddf::magician::gameend::on_change += ddf::magician::game_ending::monitor;

	ddf::magician::game_ending::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::game_ending::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::game_ending::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::game_ending::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::game_pause_mgmt::init();
	ddf::magician::gamestate::on_change += ddf::magician::game_pause_mgmt::monitor;
	ddf::magician::paused::on_change += ddf::magician::game_pause_mgmt::monitor;
	ddf::magician::freezed1::on_change += ddf::magician::game_pause_mgmt::monitor;
	ddf::magician::freezed5::on_change += ddf::magician::game_pause_mgmt::monitor;
	ddf::magician::gm_help_status::on_change += ddf::magician::game_pause_mgmt::monitor;
	ddf::magician::entrance_controller::magnetic_sensor::value::on_change += ddf::magician::game_pause_mgmt::monitor;

	ddf::magician::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_call_accepted::init();
	ddf::magician::incoming_call_status::on_change += ddf::magician::gameevent_call_accepted::monitor;

	ddf::magician::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_call_declined::init();
	ddf::magician::incoming_call_status::on_change += ddf::magician::gameevent_call_declined::monitor;

	ddf::magician::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_call_finished::init();
	ddf::magician::incoming_call_status::on_change += ddf::magician::gameevent_call_finished::monitor;

	ddf::magician::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_call_missed::init();
	ddf::magician::incoming_call_status::on_change += ddf::magician::gameevent_call_missed::monitor;

	ddf::magician::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_call_ringing::init();
	ddf::magician::incoming_call_status::on_change += ddf::magician::gameevent_call_ringing::monitor;

	ddf::magician::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_cupboard_controller_event_for_labyrinth_task::init();
	ddf::magician::cupboard_controller::debouncer::value::on_change += ddf::magician::gameevent_cupboard_controller_event_for_labyrinth_task::monitor;

	ddf::magician::gameevent_cupboard_controller_event_for_labyrinth_task::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_cupboard_controller_event_for_labyrinth_task::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_cupboard_controller_event_for_labyrinth_task::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_cupboard_controller_event_for_labyrinth_task::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_door_open_light_turn_on::init();
	ddf::magician::cupboard_controller::magnetic_sensor::value::on_change += ddf::magician::gameevent_door_open_light_turn_on::monitor;

	ddf::magician::gameevent_door_open_light_turn_on::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_door_open_light_turn_on::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_door_open_light_turn_on::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_door_open_light_turn_on::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_game_fail::init();
	ddf::magician::gamestate::on_change += ddf::magician::gameevent_game_fail::monitor;
	ddf::magician::gameend::on_change += ddf::magician::gameevent_game_fail::monitor;

	ddf::magician::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_game_finished::init();
	ddf::magician::gamestate::on_change += ddf::magician::gameevent_game_finished::monitor;

	ddf::magician::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_game_paused::init();
	ddf::magician::gamestate::on_change += ddf::magician::gameevent_game_paused::monitor;

	ddf::magician::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_game_reset::init();
	ddf::magician::gamestate::on_change += ddf::magician::gameevent_game_reset::monitor;

	ddf::magician::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_game_started::init();
	ddf::magician::gamestate::on_change += ddf::magician::gameevent_game_started::monitor;

	ddf::magician::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_game_win::init();
	ddf::magician::gamestate::on_change += ddf::magician::gameevent_game_win::monitor;
	ddf::magician::gameend::on_change += ddf::magician::gameevent_game_win::monitor;

	ddf::magician::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_planning_wall_puzzle::init();
	ddf::magician::design_board_controller::linear_magnetic_sensor_1::value::on_change += ddf::magician::gameevent_planning_wall_puzzle::monitor;
	ddf::magician::design_board_controller::linear_magnetic_sensor_2::value::on_change += ddf::magician::gameevent_planning_wall_puzzle::monitor;
	ddf::magician::design_board_controller::linear_magnetic_sensor_3::value::on_change += ddf::magician::gameevent_planning_wall_puzzle::monitor;

	ddf::magician::gameevent_planning_wall_puzzle::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_planning_wall_puzzle::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_planning_wall_puzzle::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_planning_wall_puzzle::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gameevent_safe_opened::init();
	ddf::magician::gameend::on_change += ddf::magician::gameevent_safe_opened::monitor;

	ddf::magician::gameevent_safe_opened::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameevent_safe_opened::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameevent_safe_opened::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameevent_safe_opened::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::keyswitch_active::init();
	ddf::magician::futuristic_safe_controller::debouncer::value::on_change += ddf::magician::keyswitch_active::monitor;

	ddf::magician::keyswitch_active::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::keyswitch_active::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::keyswitch_active::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::keyswitch_active::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::pin_code_accumulation::init();
	ddf::magician::futuristic_safe_controller::pin_pad::value::on_change += ddf::magician::pin_code_accumulation::monitor;

	ddf::magician::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::pin_code_test_alias_safe_activation::init();
	ddf::magician::futuristic_safe_controller::rfid_reader::value::on_change += ddf::magician::pin_code_test_alias_safe_activation::monitor;
	ddf::magician::futuristic_safe_controller::debouncer::value::on_change += ddf::magician::pin_code_test_alias_safe_activation::monitor;
	ddf::magician::pin_code::on_change += ddf::magician::pin_code_test_alias_safe_activation::monitor;

	ddf::magician::pin_code_test_alias_safe_activation::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::pin_code_test_alias_safe_activation::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::pin_code_test_alias_safe_activation::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::pin_code_test_alias_safe_activation::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::pin_timeout::init();
	ddf::magician::pin_timeout_timer::on_value_change += ddf::magician::pin_timeout::monitor;

	ddf::magician::pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::reset_room::init();
	ddf::magician::gamestate::on_change += ddf::magician::reset_room::monitor;

	ddf::magician::reset_room::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::reset_room::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::reset_room::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::reset_room::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::rfid_tag_correct::init();
	ddf::magician::futuristic_safe_controller::rfid_reader::value::on_change += ddf::magician::rfid_tag_correct::monitor;
	ddf::magician::rfid_reader_code::on_change += ddf::magician::rfid_tag_correct::monitor;

	ddf::magician::rfid_tag_correct::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::rfid_tag_correct::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::rfid_tag_correct::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::rfid_tag_correct::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::safecode_entry_activaion::init();
	ddf::magician::futuristic_safe_controller::rfid_reader::value::on_change += ddf::magician::safecode_entry_activaion::monitor;
	ddf::magician::futuristic_safe_controller::debouncer::value::on_change += ddf::magician::safecode_entry_activaion::monitor;

	ddf::magician::safecode_entry_activaion::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::safecode_entry_activaion::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::safecode_entry_activaion::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::safecode_entry_activaion::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::stop_audios::init();
	ddf::magician::gamestate::on_change += ddf::magician::stop_audios::monitor;

	ddf::magician::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::time_up::init();
	ddf::magician::gametimer::on_value_change += ddf::magician::time_up::monitor;

	ddf::magician::time_up::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::time_up::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::time_up::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::time_up::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_1_event_finished::init();
	ddf::magician::timedevent_an_1_timer::on_value_change += ddf::magician::timedevent_an_1_event_finished::monitor;

	ddf::magician::timedevent_an_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_1_event_gamestate::init();
	ddf::magician::gamestate::on_change += ddf::magician::timedevent_an_1_event_gamestate::monitor;

	ddf::magician::timedevent_an_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_2_event_finished::init();
	ddf::magician::timedevent_an_2_timer::on_value_change += ddf::magician::timedevent_an_2_event_finished::monitor;

	ddf::magician::timedevent_an_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_2_event_gamestate::init();
	ddf::magician::gamestate::on_change += ddf::magician::timedevent_an_2_event_gamestate::monitor;

	ddf::magician::timedevent_an_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_4_event_finished::init();
	ddf::magician::timedevent_an_4_timer::on_value_change += ddf::magician::timedevent_an_4_event_finished::monitor;

	ddf::magician::timedevent_an_4_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_4_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_4_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_4_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_4_event_gamestate::init();
	ddf::magician::gamestate::on_change += ddf::magician::timedevent_an_4_event_gamestate::monitor;

	ddf::magician::timedevent_an_4_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_4_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_4_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_4_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_6_event_finished::init();
	ddf::magician::timedevent_an_6_timer::on_value_change += ddf::magician::timedevent_an_6_event_finished::monitor;

	ddf::magician::timedevent_an_6_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_6_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_6_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_6_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_6_event_gamestate::init();
	ddf::magician::gamestate::on_change += ddf::magician::timedevent_an_6_event_gamestate::monitor;

	ddf::magician::timedevent_an_6_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_6_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_6_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_6_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_ap_1_event_finished::init();
	ddf::magician::timedevent_ap_1_timer::on_value_change += ddf::magician::timedevent_ap_1_event_finished::monitor;

	ddf::magician::timedevent_ap_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_ap_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_ap_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_ap_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_ap_1_event_gamestate::init();
	ddf::magician::gamestate::on_change += ddf::magician::timedevent_ap_1_event_gamestate::monitor;

	ddf::magician::timedevent_ap_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_ap_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_ap_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_ap_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_pc_1_event_finished::init();
	ddf::magician::timedevent_pc_1_timer::on_value_change += ddf::magician::timedevent_pc_1_event_finished::monitor;

	ddf::magician::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_pc_1_event_gamestate::init();
	ddf::magician::gamestate::on_change += ddf::magician::timedevent_pc_1_event_gamestate::monitor;

	ddf::magician::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_pc_2_event_finished::init();
	ddf::magician::timedevent_pc_2_timer::on_value_change += ddf::magician::timedevent_pc_2_event_finished::monitor;

	ddf::magician::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_pc_2_event_gamestate::init();
	ddf::magician::gamestate::on_change += ddf::magician::timedevent_pc_2_event_gamestate::monitor;

	ddf::magician::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::audio_message_url::init(std::string());
	ddf::magician::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::magician::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::magician::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::magician::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::magician::comdev_reset::init(bool(false));
	ddf::magician::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::magician::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::magician::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::magician::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::magician::comdev_silence::init(bool(false));
	ddf::magician::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::magician::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::magician::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::magician::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::magician::freezed1::init(bool());
	ddf::magician::freezed1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::freezed1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::freezed1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::freezed1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::freezed5::init(bool());
	ddf::magician::freezed5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::freezed5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::freezed5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::freezed5::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gm_help_status::init(bool());
	ddf::magician::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::magician::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::magician::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::magician::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::magician::gameend::init(uint8_t(0));
	ddf::magician::gameend::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gameend::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gameend::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gameend::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::gamestate::init(uint8_t(3));
	ddf::magician::gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::incoming_call::init(uint8_t(0xff));
	ddf::magician::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::incoming_call::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::magician::incoming_call::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::magician::incoming_call::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::magician::incoming_call::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::magician::incoming_call_status::init(uint8_t());
	ddf::magician::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::magician::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::magician::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::magician::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::magician::paused::init(bool());
	ddf::magician::paused::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::paused::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::paused::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::paused::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::restart_game::init(bool());
	ddf::magician::restart_game::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::restart_game::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::restart_game::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::restart_game::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::restart_game::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::magician::restart_game::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::magician::restart_game::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::magician::restart_game::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::magician::text_message::init(std::string());
	ddf::magician::text_message::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::text_message::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::text_message::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::text_message::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::text_message::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::magician::text_message::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::magician::text_message::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::magician::text_message::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::magician::text_message_sender::init(uint8_t(0xff));
	ddf::magician::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::magician::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::magician::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::magician::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::magician::pin_code::init(uint16_t(0));
	ddf::magician::pin_code::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::pin_code::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::pin_code::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::pin_code::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::pin_pad_code::init(uint16_t(5217));
	ddf::magician::pin_pad_code::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::pin_pad_code::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::pin_pad_code::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::pin_pad_code::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::rfid_reader_code::init(uint64_t(0xc044edb));
	ddf::magician::rfid_reader_code::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::rfid_reader_code::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::rfid_reader_code::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::rfid_reader_code::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_1::init(uint64_t(30));
	ddf::magician::timedevent_an_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_2::init(uint64_t(600));
	ddf::magician::timedevent_an_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_2::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_4::init(uint64_t(1800));
	ddf::magician::timedevent_an_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_4::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_an_6::init(uint64_t(3300));
	ddf::magician::timedevent_an_6::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_6::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_6::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_6::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_ap_1::init(uint64_t(42));
	ddf::magician::timedevent_ap_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_ap_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_ap_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_ap_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_pc_1::init(uint64_t(1200));
	ddf::magician::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::magician::timedevent_pc_2::init(uint64_t(2400));
	ddf::magician::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1::init();
	ddf::magician::room_1_content::applause::init();
	ddf::magician::room_1_content::chord::init();
	ddf::magician::room_1_content::progress::init();
	ddf::magician::room_1_content::careful::init();
	ddf::magician::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::failstate::init();
	ddf::magician::room_1_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::gminc::init();
	ddf::magician::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::rules::init();
	ddf::magician::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::techdiff::init();
	ddf::magician::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::winstate::init();
	ddf::magician::room_1_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::event_1::init();
	ddf::magician::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::event_2::init();
	ddf::magician::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::event_3::init();
	ddf::magician::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::event_4::init();
	ddf::magician::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::event_5::init();
	ddf::magician::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_1_content::event_6::init();
	ddf::magician::room_1_content::event_6::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_1_content::event_6::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_1_content::event_6::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_1_content::event_6::remote_add(ddf::service::gmclient::device_role::instance(3));


	ddf::magician::room_2::init();
	ddf::magician::room_2_content::applause::init();
	ddf::magician::room_2_content::chord::init();
	ddf::magician::room_2_content::progress::init();
	ddf::magician::room_2_content::careful::init();
	ddf::magician::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::failstate::init();
	ddf::magician::room_2_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::failstate::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::gminc::init();
	ddf::magician::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::rules::init();
	ddf::magician::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::techdiff::init();
	ddf::magician::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::winstate::init();
	ddf::magician::room_2_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::winstate::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::event_1::init();
	ddf::magician::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::event_2::init();
	ddf::magician::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::event_3::init();
	ddf::magician::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::event_4::init();
	ddf::magician::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::event_5::init();
	ddf::magician::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::room_2_content::event_6::init();
	ddf::magician::room_2_content::event_6::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::room_2_content::event_6::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::room_2_content::event_6::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::room_2_content::event_6::remote_add(ddf::service::gmclient::device_role::instance(3));




	ddf::magician::freezetimer1::init();
	ddf::magician::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::freezetimer5::init();
	ddf::magician::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::gametimer::init();
	ddf::magician::gametimer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::gametimer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::gametimer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::gametimer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::pin_timeout_timer::init();
	ddf::magician::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::timedevent_an_1_timer::init();
	ddf::magician::timedevent_an_1_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_1_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_1_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_1_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::timedevent_an_2_timer::init();
	ddf::magician::timedevent_an_2_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_2_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_2_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_2_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::timedevent_an_4_timer::init();
	ddf::magician::timedevent_an_4_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_4_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_4_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_4_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::timedevent_an_6_timer::init();
	ddf::magician::timedevent_an_6_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_an_6_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_an_6_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_an_6_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::timedevent_ap_1_timer::init();
	ddf::magician::timedevent_ap_1_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_ap_1_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_ap_1_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_ap_1_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::timedevent_pc_1_timer::init();
	ddf::magician::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::magician::timedevent_pc_2_timer::init();
	ddf::magician::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::magician::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::magician::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::magician::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(3));


	ddf::villa::control_room_controller::device_role::init();
	ddf::villa::control_room_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::control_room_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::control_room_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::control_room_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::control_room_controller::switch_1::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::control_room_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::control_room_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::control_room_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::control_room_controller::magnetic_lock::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::control_room_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::control_room_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::control_room_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::control_room_controller::debouncer_1::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::control_room_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::control_room_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::control_room_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::control_room_controller::led_1::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::led_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::control_room_controller::led_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::control_room_controller::led_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::control_room_controller::led_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::control_room_controller::led_2::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::led_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::control_room_controller::led_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::control_room_controller::led_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::control_room_controller::led_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::villa::control_room_controller::device_role>();
	ddf::villa::desk_controller::device_role::init();
	ddf::villa::desk_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desk_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desk_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desk_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desk_controller::debouncer_3::init(ddf::villa::desk_controller::device_role::instance());
	ddf::villa::desk_controller::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desk_controller::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desk_controller::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desk_controller::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desk_controller::debouncer_4::init(ddf::villa::desk_controller::device_role::instance());
	ddf::villa::desk_controller::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desk_controller::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desk_controller::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desk_controller::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::villa::desk_controller::device_role>();
	ddf::villa::desktop_pc::device_role::init();
	ddf::villa::desktop_pc::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::started::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::started::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::shutdown::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::shutdown::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::shutdown::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::shutdown::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::shutdown::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::bad_password::init(ddf::villa::desktop_pc::device_role::instance(),std::string());
	ddf::villa::desktop_pc::bad_password::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::bad_password::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::bad_password::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::bad_password::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::logged_in::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::logged_in::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::logged_in::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::logged_in::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::logged_in::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::recycled_restore::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::recycled_restore::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::recycled_restore::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::recycled_restore::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::recycled_restore::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::audioplay_started::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audioplay_started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::audioplay_started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::audioplay_started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::audioplay_started::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::audioplay_finished::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audioplay_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::audioplay_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::audioplay_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::audioplay_finished::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::audioplay_paused::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audioplay_paused::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::audioplay_paused::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::audioplay_paused::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::audioplay_paused::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::restart_game::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::restart_game::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::restart_game::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::restart_game::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::restart_game::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::audioplay_startevent::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audioplay_startevent::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::audioplay_startevent::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::audioplay_startevent::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::audioplay_startevent::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::desktop_pc::audiopause_pauseevent::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audiopause_pauseevent::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::desktop_pc::audiopause_pauseevent::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::desktop_pc::audiopause_pauseevent::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::desktop_pc::audiopause_pauseevent::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::villa::desktop_pc::device_role>();
	ddf::villa::entrance_controller::device_role::init();
	ddf::villa::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::entrance_controller::debouncer::init(ddf::villa::entrance_controller::device_role::instance());
	ddf::villa::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::entrance_controller::led::init(ddf::villa::entrance_controller::device_role::instance());
	ddf::villa::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::entrance_controller::magnetic_sensor::init(ddf::villa::entrance_controller::device_role::instance());
	ddf::villa::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::villa::entrance_controller::device_role>();
	ddf::villa::safe_controller::device_role::init();
	ddf::villa::safe_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::safe_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::safe_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::safe_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::safe_controller::pin_pad::init(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::safe_controller::magnetic_lock::init(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::safe_controller::debouncer_1::init(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::safe_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::safe_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::safe_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::safe_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::safe_controller::debouncer_2::init(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::safe_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::safe_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::safe_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::safe_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::safe_controller::buzzer::init(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::safe_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::safe_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::safe_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::safe_controller::buzzer::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::villa::safe_controller::device_role>();
	ddf::villa::video_device::device_role::init();
	ddf::villa::video_device::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::started::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::started::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::shutdown::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::shutdown::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::shutdown::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::shutdown::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::shutdown::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::livecam_started::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::livecam_started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::livecam_started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::livecam_started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::livecam_started::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::livecamslides_started::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::livecamslides_started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::livecamslides_started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::livecamslides_started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::livecamslides_started::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::restart_game::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::restart_game::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::restart_game::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::restart_game::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::restart_game::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::start_livecams::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::start_livecams::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::start_livecams::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::start_livecams::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::start_livecams::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::stop_livecams::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::stop_livecams::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::stop_livecams::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::stop_livecams::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::stop_livecams::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::start_tape::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::start_tape::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::start_tape::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::start_tape::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::start_tape::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::stop_tape::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::stop_tape::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::stop_tape::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::stop_tape::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::stop_tape::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::pause_tape::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::pause_tape::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::pause_tape::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::pause_tape::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::pause_tape::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::finished_tape::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::finished_tape::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::finished_tape::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::finished_tape::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::finished_tape::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::enabled::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::enabled::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::enabled::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::enabled::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::enabled::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::eject::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::eject::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::eject::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::eject::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::eject::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::casette_id::init(ddf::villa::video_device::device_role::instance(),uint64_t(0));
	ddf::villa::video_device::casette_id::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::casette_id::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::casette_id::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::casette_id::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::play_ongoing::init(ddf::villa::video_device::device_role::instance(),bool(false));
	ddf::villa::video_device::play_ongoing::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::play_ongoing::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::play_ongoing::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::play_ongoing::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::video_device::livecam_ongoing::init(ddf::villa::video_device::device_role::instance(),bool(false));
	ddf::villa::video_device::livecam_ongoing::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_device::livecam_ongoing::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_device::livecam_ongoing::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_device::livecam_ongoing::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::villa::video_device::device_role>();

	ddf::villa::answering_machine::init();
	ddf::villa::desk_controller::debouncer_4::value::on_change += ddf::villa::answering_machine::monitor;

	ddf::villa::answering_machine::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::answering_machine::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::answering_machine::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::answering_machine::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::artificial_game_ending::init();
	ddf::villa::entrance_controller::led::value::on_change += ddf::villa::artificial_game_ending::monitor;

	ddf::villa::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::freeze_1::init();
	ddf::villa::freezed1::on_change += ddf::villa::freeze_1::monitor;

	ddf::villa::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::freeze_1_timeout::init();
	ddf::villa::freezetimer1::on_value_change += ddf::villa::freeze_1_timeout::monitor;

	ddf::villa::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::freeze_5::init();
	ddf::villa::freezed5::on_change += ddf::villa::freeze_5::monitor;

	ddf::villa::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::freeze_5_timeout::init();
	ddf::villa::freezetimer5::on_value_change += ddf::villa::freeze_5_timeout::monitor;

	ddf::villa::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::game_end_button_push::init();
	ddf::villa::entrance_controller::debouncer::value::on_change += ddf::villa::game_end_button_push::monitor;

	ddf::villa::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::game_ending::init();
	ddf::villa::gameend::on_change += ddf::villa::game_ending::monitor;

	ddf::villa::game_ending::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::game_ending::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::game_ending::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::game_ending::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::game_pause_mgmt::init();
	ddf::villa::gamestate::on_change += ddf::villa::game_pause_mgmt::monitor;
	ddf::villa::paused::on_change += ddf::villa::game_pause_mgmt::monitor;
	ddf::villa::freezed1::on_change += ddf::villa::game_pause_mgmt::monitor;
	ddf::villa::freezed5::on_change += ddf::villa::game_pause_mgmt::monitor;
	ddf::villa::gm_help_status::on_change += ddf::villa::game_pause_mgmt::monitor;
	ddf::villa::entrance_controller::magnetic_sensor::value::on_change += ddf::villa::game_pause_mgmt::monitor;

	ddf::villa::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_call_accepted::init();
	ddf::villa::incoming_call_status::on_change += ddf::villa::gameevent_call_accepted::monitor;

	ddf::villa::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_call_declined::init();
	ddf::villa::incoming_call_status::on_change += ddf::villa::gameevent_call_declined::monitor;

	ddf::villa::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_call_finished::init();
	ddf::villa::incoming_call_status::on_change += ddf::villa::gameevent_call_finished::monitor;

	ddf::villa::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_call_missed::init();
	ddf::villa::incoming_call_status::on_change += ddf::villa::gameevent_call_missed::monitor;

	ddf::villa::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_call_ringing::init();
	ddf::villa::incoming_call_status::on_change += ddf::villa::gameevent_call_ringing::monitor;

	ddf::villa::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_casette_eject_trigger::init();
	ddf::villa::control_room_controller::debouncer_1::value::on_change += ddf::villa::gameevent_casette_eject_trigger::monitor;

	ddf::villa::gameevent_casette_eject_trigger::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_casette_eject_trigger::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_casette_eject_trigger::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_casette_eject_trigger::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_desktop_pc_login::init();
	ddf::villa::desktop_pc::logged_in::on_change += ddf::villa::gameevent_desktop_pc_login::monitor;

	ddf::villa::gameevent_desktop_pc_login::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_desktop_pc_login::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_desktop_pc_login::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_desktop_pc_login::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_finding_the_keys::init();
	ddf::villa::safe_controller::debouncer_1::value::on_change += ddf::villa::gameevent_finding_the_keys::monitor;
	ddf::villa::safe_controller::debouncer_2::value::on_change += ddf::villa::gameevent_finding_the_keys::monitor;
	ddf::villa::desk_controller::debouncer_3::value::on_change += ddf::villa::gameevent_finding_the_keys::monitor;

	ddf::villa::gameevent_finding_the_keys::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_finding_the_keys::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_finding_the_keys::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_finding_the_keys::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_game_fail::init();
	ddf::villa::gamestate::on_change += ddf::villa::gameevent_game_fail::monitor;
	ddf::villa::gameend::on_change += ddf::villa::gameevent_game_fail::monitor;

	ddf::villa::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_game_finished::init();
	ddf::villa::gamestate::on_change += ddf::villa::gameevent_game_finished::monitor;

	ddf::villa::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_game_paused::init();
	ddf::villa::gamestate::on_change += ddf::villa::gameevent_game_paused::monitor;

	ddf::villa::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_game_reset::init();
	ddf::villa::gamestate::on_change += ddf::villa::gameevent_game_reset::monitor;

	ddf::villa::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_game_started::init();
	ddf::villa::gamestate::on_change += ddf::villa::gameevent_game_started::monitor;

	ddf::villa::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_game_win::init();
	ddf::villa::gamestate::on_change += ddf::villa::gameevent_game_win::monitor;
	ddf::villa::gameend::on_change += ddf::villa::gameevent_game_win::monitor;

	ddf::villa::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_safe_code_mistaken::init();
	ddf::villa::pin_code::on_change += ddf::villa::gameevent_safe_code_mistaken::monitor;

	ddf::villa::gameevent_safe_code_mistaken::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_safe_code_mistaken::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_safe_code_mistaken::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_safe_code_mistaken::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gameevent_safe_opened::init();
	ddf::villa::pin_code::on_change += ddf::villa::gameevent_safe_opened::monitor;

	ddf::villa::gameevent_safe_opened::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameevent_safe_opened::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameevent_safe_opened::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameevent_safe_opened::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::pin_code_accumulation::init();
	ddf::villa::safe_controller::pin_pad::value::on_change += ddf::villa::pin_code_accumulation::monitor;

	ddf::villa::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::pin_code_accumulation::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::pin_timeout::init();
	ddf::villa::pin_timeout_timer::on_value_change += ddf::villa::pin_timeout::monitor;

	ddf::villa::pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::pin_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::reset_room::init();
	ddf::villa::gamestate::on_change += ddf::villa::reset_room::monitor;

	ddf::villa::reset_room::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::reset_room::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::reset_room::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::reset_room::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::stop_audios::init();
	ddf::villa::gamestate::on_change += ddf::villa::stop_audios::monitor;

	ddf::villa::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::the_surveillance_konsole::init();
	ddf::villa::control_room_controller::switch_1::value::on_change += ddf::villa::the_surveillance_konsole::monitor;

	ddf::villa::the_surveillance_konsole::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::the_surveillance_konsole::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::the_surveillance_konsole::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::the_surveillance_konsole::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::time_up::init();
	ddf::villa::gametimer::on_value_change += ddf::villa::time_up::monitor;

	ddf::villa::time_up::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::time_up::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::time_up::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::time_up::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_funk_1_event_finished::init();
	ddf::villa::timedevent_funk_1_timer::on_value_change += ddf::villa::timedevent_funk_1_event_finished::monitor;

	ddf::villa::timedevent_funk_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_funk_1_event_gamestate::init();
	ddf::villa::gamestate::on_change += ddf::villa::timedevent_funk_1_event_gamestate::monitor;

	ddf::villa::timedevent_funk_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_funk_2_event_finished::init();
	ddf::villa::timedevent_funk_2_timer::on_value_change += ddf::villa::timedevent_funk_2_event_finished::monitor;

	ddf::villa::timedevent_funk_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_funk_2_event_gamestate::init();
	ddf::villa::gamestate::on_change += ddf::villa::timedevent_funk_2_event_gamestate::monitor;

	ddf::villa::timedevent_funk_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_funk_3_event_finished::init();
	ddf::villa::timedevent_funk_3_timer::on_value_change += ddf::villa::timedevent_funk_3_event_finished::monitor;

	ddf::villa::timedevent_funk_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_funk_3_event_gamestate::init();
	ddf::villa::gamestate::on_change += ddf::villa::timedevent_funk_3_event_gamestate::monitor;

	ddf::villa::timedevent_funk_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_pc_1_event_finished::init();
	ddf::villa::timedevent_pc_1_timer::on_value_change += ddf::villa::timedevent_pc_1_event_finished::monitor;

	ddf::villa::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_pc_1_event_gamestate::init();
	ddf::villa::gamestate::on_change += ddf::villa::timedevent_pc_1_event_gamestate::monitor;

	ddf::villa::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_pc_2_event_finished::init();
	ddf::villa::timedevent_pc_2_timer::on_value_change += ddf::villa::timedevent_pc_2_event_finished::monitor;

	ddf::villa::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_pc_2_event_gamestate::init();
	ddf::villa::gamestate::on_change += ddf::villa::timedevent_pc_2_event_gamestate::monitor;

	ddf::villa::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_pc_3_event_finished::init();
	ddf::villa::timedevent_pc_3_timer::on_value_change += ddf::villa::timedevent_pc_3_event_finished::monitor;

	ddf::villa::timedevent_pc_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_pc_3_event_gamestate::init();
	ddf::villa::gamestate::on_change += ddf::villa::timedevent_pc_3_event_gamestate::monitor;

	ddf::villa::timedevent_pc_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::video_playing::init();
	ddf::villa::video_device::start_tape::on_change += ddf::villa::video_playing::monitor;
	ddf::villa::video_device::casette_id::on_change += ddf::villa::video_playing::monitor;

	ddf::villa::video_playing::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::video_playing::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::video_playing::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::video_playing::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::audio_message_url::init(std::string());
	ddf::villa::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::villa::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::villa::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::villa::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::villa::comdev_reset::init(bool(false));
	ddf::villa::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::villa::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::villa::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::villa::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::villa::comdev_silence::init(bool(false));
	ddf::villa::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::villa::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::villa::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::villa::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::villa::freezed1::init(bool());
	ddf::villa::freezed1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::freezed1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::freezed1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::freezed1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::freezed5::init(bool());
	ddf::villa::freezed5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::freezed5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::freezed5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::freezed5::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gm_help_status::init(bool());
	ddf::villa::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::villa::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::villa::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::villa::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::villa::gameend::init(uint8_t(0));
	ddf::villa::gameend::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gameend::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gameend::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gameend::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::gamestate::init(uint8_t(3));
	ddf::villa::gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::incoming_call::init(uint8_t(0xff));
	ddf::villa::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::incoming_call::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::villa::incoming_call::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::villa::incoming_call::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::villa::incoming_call::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::villa::incoming_call_status::init(uint8_t());
	ddf::villa::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::villa::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::villa::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::villa::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::villa::paused::init(bool());
	ddf::villa::paused::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::paused::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::paused::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::paused::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::restart_game::init(bool());
	ddf::villa::restart_game::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::restart_game::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::restart_game::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::restart_game::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::restart_game::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::villa::restart_game::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::villa::restart_game::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::villa::restart_game::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::villa::text_message::init(std::string());
	ddf::villa::text_message::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::text_message::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::text_message::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::text_message::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::text_message::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::villa::text_message::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::villa::text_message::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::villa::text_message::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::villa::text_message_sender::init(uint8_t(0xff));
	ddf::villa::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::villa::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::villa::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::villa::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::villa::pin_code::init(std::string());
	ddf::villa::pin_code::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::pin_code::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::pin_code::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::pin_code::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_funk_1::init(uint64_t(120));
	ddf::villa::timedevent_funk_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_funk_2::init(uint64_t(1800));
	ddf::villa::timedevent_funk_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_2::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_funk_3::init(uint64_t(3300));
	ddf::villa::timedevent_funk_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_3::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_pc_1::init(uint64_t(600));
	ddf::villa::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_pc_2::init(uint64_t(1500));
	ddf::villa::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::villa::timedevent_pc_3::init(uint64_t(2400));
	ddf::villa::timedevent_pc_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_1::init();
	ddf::villa::room_1_content::chord::init();
	ddf::villa::room_1_content::progress::init();
	ddf::villa::room_1_content::careful::init();
	ddf::villa::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_1_content::gminc::init();
	ddf::villa::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_1_content::rules::init();
	ddf::villa::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_1_content::techdiff::init();
	ddf::villa::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_1_content::event_1::init();
	ddf::villa::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_1_content::event_2::init();
	ddf::villa::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_1_content::event_3::init();
	ddf::villa::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_1_content::event_4::init();
	ddf::villa::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_1_content::event_5::init();
	ddf::villa::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(3));


	ddf::villa::room_2::init();
	ddf::villa::room_2_content::chord::init();
	ddf::villa::room_2_content::progress::init();
	ddf::villa::room_2_content::careful::init();
	ddf::villa::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_2_content::gminc::init();
	ddf::villa::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_2_content::rules::init();
	ddf::villa::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_2_content::techdiff::init();
	ddf::villa::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_2_content::event_1::init();
	ddf::villa::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_2_content::event_2::init();
	ddf::villa::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_2_content::event_3::init();
	ddf::villa::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_2_content::event_4::init();
	ddf::villa::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::room_2_content::event_5::init();
	ddf::villa::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(3));




	ddf::villa::freezetimer1::init();
	ddf::villa::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::freezetimer5::init();
	ddf::villa::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::gametimer::init();
	ddf::villa::gametimer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::gametimer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::gametimer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::gametimer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::eject_wait::init();
	ddf::villa::eject_wait::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::eject_wait::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::eject_wait::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::eject_wait::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::pin_timeout_timer::init();
	ddf::villa::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::pin_timeout_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::timedevent_funk_1_timer::init();
	ddf::villa::timedevent_funk_1_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_1_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_1_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_1_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::timedevent_funk_2_timer::init();
	ddf::villa::timedevent_funk_2_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_2_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_2_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_2_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::timedevent_funk_3_timer::init();
	ddf::villa::timedevent_funk_3_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_funk_3_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_funk_3_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_funk_3_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::timedevent_pc_1_timer::init();
	ddf::villa::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::timedevent_pc_2_timer::init();
	ddf::villa::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::villa::timedevent_pc_3_timer::init();
	ddf::villa::timedevent_pc_3_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::villa::timedevent_pc_3_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::villa::timedevent_pc_3_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::villa::timedevent_pc_3_timer::remote_add(ddf::service::gmclient::device_role::instance(3));


	ddf::junkyard::email_client::device_role::init();
	ddf::junkyard::email_client::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::email_client::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::email_client::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::email_client::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::email_client::started::init(ddf::junkyard::email_client::device_role::instance(),bool());
	ddf::junkyard::email_client::started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::email_client::started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::email_client::started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::email_client::started::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::email_client::shutdown::init(ddf::junkyard::email_client::device_role::instance(),bool());
	ddf::junkyard::email_client::shutdown::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::email_client::shutdown::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::email_client::shutdown::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::email_client::shutdown::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::email_client::emails_received::init(ddf::junkyard::email_client::device_role::instance(),bool());
	ddf::junkyard::email_client::emails_received::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::email_client::emails_received::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::email_client::emails_received::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::email_client::emails_received::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::email_client::restart_game::init(ddf::junkyard::email_client::device_role::instance(),bool());
	ddf::junkyard::email_client::restart_game::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::email_client::restart_game::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::email_client::restart_game::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::email_client::restart_game::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::email_client::search_string::init(ddf::junkyard::email_client::device_role::instance(),std::string());
	ddf::junkyard::email_client::search_string::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::email_client::search_string::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::email_client::search_string::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::email_client::search_string::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::email_client::opened_email::init(ddf::junkyard::email_client::device_role::instance(),std::string());
	ddf::junkyard::email_client::opened_email::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::email_client::opened_email::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::email_client::opened_email::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::email_client::opened_email::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::junkyard::email_client::device_role>();
	ddf::junkyard::entrance_controller::device_role::init();
	ddf::junkyard::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::entrance_controller::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::entrance_controller::debouncer::init(ddf::junkyard::entrance_controller::device_role::instance());
	ddf::junkyard::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::entrance_controller::led::init(ddf::junkyard::entrance_controller::device_role::instance());
	ddf::junkyard::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::entrance_controller::magnetic_sensor::init(ddf::junkyard::entrance_controller::device_role::instance());
	ddf::junkyard::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::junkyard::entrance_controller::device_role>();
	ddf::junkyard::secret_box_controller_1::device_role::init();
	ddf::junkyard::secret_box_controller_1::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::button_grid::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::button_grid::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::button_grid::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::button_grid::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::button_grid::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::debouncer_1::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::debouncer_2::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::debouncer_3::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::debouncer_4::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::debouncer_5::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::debouncer_6::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::debouncer_7::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::magnetic_lock_1::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::magnetic_lock_2::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::magnetic_lock_3::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::magnetic_lock_4::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_1::addressable_led::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::addressable_led::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_1::addressable_led::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_1::addressable_led::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_1::addressable_led::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::junkyard::secret_box_controller_1::device_role>();
	ddf::junkyard::secret_box_controller_2::device_role::init();
	ddf::junkyard::secret_box_controller_2::device_role::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::device_role::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::device_role::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::device_role::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_1::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_2::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_3::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_4::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_5::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_6::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_7::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_8::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_8::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_8::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_8::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_8::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_9::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_9::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_9::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_9::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_9::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_10::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_10::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_10::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_10::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_10::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::light_controller::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::light_controller::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::light_controller::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::light_controller::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::light_controller::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::debouncer_12::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_12::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::debouncer_12::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::debouncer_12::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::debouncer_12::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::magnetic_lock_1::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::magnetic_lock_2::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::magnetic_lock_3::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::secret_box_controller_2::magnetic_lock_4::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::secret_box_controller_2::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	dm::add_role<ddf::junkyard::secret_box_controller_2::device_role>();

	ddf::junkyard::led_strip_update::init();
	ddf::junkyard::gametimer::on_value_change += ddf::junkyard::led_strip_update::monitor;

	ddf::junkyard::led_strip_update::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::led_strip_update::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::led_strip_update::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::led_strip_update::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::artificial_game_ending::init();
	ddf::junkyard::entrance_controller::led::value::on_change += ddf::junkyard::artificial_game_ending::monitor;

	ddf::junkyard::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::artificial_game_ending::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::freeze_1::init();
	ddf::junkyard::freezed1::on_change += ddf::junkyard::freeze_1::monitor;

	ddf::junkyard::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::freeze_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::freeze_1_timeout::init();
	ddf::junkyard::freezetimer1::on_value_change += ddf::junkyard::freeze_1_timeout::monitor;

	ddf::junkyard::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::freeze_5::init();
	ddf::junkyard::freezed5::on_change += ddf::junkyard::freeze_5::monitor;

	ddf::junkyard::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::freeze_5::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::freeze_5_timeout::init();
	ddf::junkyard::freezetimer5::on_value_change += ddf::junkyard::freeze_5_timeout::monitor;

	ddf::junkyard::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::game_end_button_push::init();
	ddf::junkyard::entrance_controller::debouncer::value::on_change += ddf::junkyard::game_end_button_push::monitor;

	ddf::junkyard::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::game_end_button_push::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::game_ending::init();
	ddf::junkyard::gameend::on_change += ddf::junkyard::game_ending::monitor;

	ddf::junkyard::game_ending::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::game_ending::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::game_ending::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::game_ending::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::game_pause_mgmt::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::game_pause_mgmt::monitor;
	ddf::junkyard::paused::on_change += ddf::junkyard::game_pause_mgmt::monitor;
	ddf::junkyard::freezed1::on_change += ddf::junkyard::game_pause_mgmt::monitor;
	ddf::junkyard::freezed5::on_change += ddf::junkyard::game_pause_mgmt::monitor;
	ddf::junkyard::gm_help_status::on_change += ddf::junkyard::game_pause_mgmt::monitor;
	ddf::junkyard::entrance_controller::magnetic_sensor::value::on_change += ddf::junkyard::game_pause_mgmt::monitor;

	ddf::junkyard::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::game_pause_mgmt::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_ampmeter_turn_on::init();
	ddf::junkyard::secret_box_controller_2::debouncer_10::value::on_change += ddf::junkyard::gameevent_ampmeter_turn_on::monitor;

	ddf::junkyard::gameevent_ampmeter_turn_on::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_ampmeter_turn_on::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_ampmeter_turn_on::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_ampmeter_turn_on::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_anamorphic_module::init();
	ddf::junkyard::secret_box_controller_2::debouncer_1::value::on_change += ddf::junkyard::gameevent_anamorphic_module::monitor;
	ddf::junkyard::secret_box_controller_2::debouncer_5::value::on_change += ddf::junkyard::gameevent_anamorphic_module::monitor;
	ddf::junkyard::secret_box_controller_2::debouncer_7::value::on_change += ddf::junkyard::gameevent_anamorphic_module::monitor;

	ddf::junkyard::gameevent_anamorphic_module::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_anamorphic_module::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_anamorphic_module::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_anamorphic_module::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_call_accepted::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_accepted::monitor;

	ddf::junkyard::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_call_declined::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_declined::monitor;

	ddf::junkyard::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_call_finished::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_finished::monitor;

	ddf::junkyard::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_call_missed::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_missed::monitor;

	ddf::junkyard::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_call_ringing::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_ringing::monitor;

	ddf::junkyard::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_email_received::init();

	ddf::junkyard::gameevent_email_received::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_email_received::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_email_received::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_email_received::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_game_fail::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::gameevent_game_fail::monitor;
	ddf::junkyard::gameend::on_change += ddf::junkyard::gameevent_game_fail::monitor;

	ddf::junkyard::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_game_fail::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_game_finished::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::gameevent_game_finished::monitor;

	ddf::junkyard::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_game_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_game_paused::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::gameevent_game_paused::monitor;

	ddf::junkyard::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_game_paused::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_game_reset::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::gameevent_game_reset::monitor;

	ddf::junkyard::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_game_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_game_started::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::gameevent_game_started::monitor;

	ddf::junkyard::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_game_started::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_game_win::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::gameevent_game_win::monitor;
	ddf::junkyard::gameend::on_change += ddf::junkyard::gameevent_game_win::monitor;

	ddf::junkyard::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_game_win::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_labyrinth_1::init();
	ddf::junkyard::secret_box_controller_1::debouncer_5::value::on_change += ddf::junkyard::gameevent_labyrinth_1::monitor;

	ddf::junkyard::gameevent_labyrinth_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_labyrinth_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_labyrinth_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_labyrinth_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_labyrinth_2::init();
	ddf::junkyard::secret_box_controller_1::debouncer_6::value::on_change += ddf::junkyard::gameevent_labyrinth_2::monitor;

	ddf::junkyard::gameevent_labyrinth_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_labyrinth_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_labyrinth_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_labyrinth_2::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_labyrinth_3::init();
	ddf::junkyard::secret_box_controller_1::debouncer_7::value::on_change += ddf::junkyard::gameevent_labyrinth_3::monitor;

	ddf::junkyard::gameevent_labyrinth_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_labyrinth_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_labyrinth_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_labyrinth_3::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gameevent_mona_lisa_rescue::init();
	ddf::junkyard::secret_box_controller_2::debouncer_12::value::on_change += ddf::junkyard::gameevent_mona_lisa_rescue::monitor;

	ddf::junkyard::gameevent_mona_lisa_rescue::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameevent_mona_lisa_rescue::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameevent_mona_lisa_rescue::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameevent_mona_lisa_rescue::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::lockpick_module::init();
	ddf::junkyard::secret_box_controller_1::debouncer_2::value::on_change += ddf::junkyard::lockpick_module::monitor;
	ddf::junkyard::secret_box_controller_1::debouncer_3::value::on_change += ddf::junkyard::lockpick_module::monitor;
	ddf::junkyard::secret_box_controller_1::debouncer_4::value::on_change += ddf::junkyard::lockpick_module::monitor;

	ddf::junkyard::lockpick_module::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::lockpick_module::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::lockpick_module::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::lockpick_module::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::piano_key_pressed::init();
	ddf::junkyard::secret_box_controller_1::button_grid::value::on_change += ddf::junkyard::piano_key_pressed::monitor;

	ddf::junkyard::piano_key_pressed::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::piano_key_pressed::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::piano_key_pressed::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::piano_key_pressed::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::potato_power_indicator::init();
	ddf::junkyard::secret_box_controller_2::debouncer_10::value::on_change += ddf::junkyard::potato_power_indicator::monitor;

	ddf::junkyard::potato_power_indicator::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::potato_power_indicator::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::potato_power_indicator::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::potato_power_indicator::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::relock_event::init();
	ddf::junkyard::relock_timer::on_value_change += ddf::junkyard::relock_event::monitor;

	ddf::junkyard::relock_event::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::relock_event::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::relock_event::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::relock_event::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::reset_room::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::reset_room::monitor;
	ddf::junkyard::led_timer_start::on_change += ddf::junkyard::reset_room::monitor;

	ddf::junkyard::reset_room::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::reset_room::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::reset_room::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::reset_room::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::stop_audios::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::stop_audios::monitor;

	ddf::junkyard::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::stop_audios::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::time_up::init();
	ddf::junkyard::gametimer::on_value_change += ddf::junkyard::time_up::monitor;

	ddf::junkyard::time_up::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::time_up::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::time_up::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::time_up::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_1_event_finished::init();
	ddf::junkyard::timedevent_atmo_1_timer::on_value_change += ddf::junkyard::timedevent_atmo_1_event_finished::monitor;

	ddf::junkyard::timedevent_atmo_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_1_event_gamestate::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::timedevent_atmo_1_event_gamestate::monitor;

	ddf::junkyard::timedevent_atmo_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_2_event_finished::init();
	ddf::junkyard::timedevent_atmo_2_timer::on_value_change += ddf::junkyard::timedevent_atmo_2_event_finished::monitor;

	ddf::junkyard::timedevent_atmo_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_2_event_gamestate::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::timedevent_atmo_2_event_gamestate::monitor;

	ddf::junkyard::timedevent_atmo_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_3_event_finished::init();
	ddf::junkyard::timedevent_atmo_3_timer::on_value_change += ddf::junkyard::timedevent_atmo_3_event_finished::monitor;

	ddf::junkyard::timedevent_atmo_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_3_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_3_event_gamestate::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::timedevent_atmo_3_event_gamestate::monitor;

	ddf::junkyard::timedevent_atmo_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_3_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_4_event_finished::init();
	ddf::junkyard::timedevent_atmo_4_timer::on_value_change += ddf::junkyard::timedevent_atmo_4_event_finished::monitor;

	ddf::junkyard::timedevent_atmo_4_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_4_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_4_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_4_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_4_event_gamestate::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::timedevent_atmo_4_event_gamestate::monitor;

	ddf::junkyard::timedevent_atmo_4_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_4_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_4_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_4_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_5_event_finished::init();
	ddf::junkyard::timedevent_atmo_5_timer::on_value_change += ddf::junkyard::timedevent_atmo_5_event_finished::monitor;

	ddf::junkyard::timedevent_atmo_5_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_5_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_5_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_5_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_5_event_gamestate::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::timedevent_atmo_5_event_gamestate::monitor;

	ddf::junkyard::timedevent_atmo_5_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_5_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_5_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_5_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_6_event_finished::init();
	ddf::junkyard::timedevent_atmo_6_timer::on_value_change += ddf::junkyard::timedevent_atmo_6_event_finished::monitor;

	ddf::junkyard::timedevent_atmo_6_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_6_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_6_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_6_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_6_event_gamestate::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::timedevent_atmo_6_event_gamestate::monitor;

	ddf::junkyard::timedevent_atmo_6_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_6_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_6_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_6_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_pc_1_event_finished::init();
	ddf::junkyard::timedevent_pc_1_timer::on_value_change += ddf::junkyard::timedevent_pc_1_event_finished::monitor;

	ddf::junkyard::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_pc_1_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_pc_1_event_gamestate::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::timedevent_pc_1_event_gamestate::monitor;

	ddf::junkyard::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_pc_1_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_pc_2_event_finished::init();
	ddf::junkyard::timedevent_pc_2_timer::on_value_change += ddf::junkyard::timedevent_pc_2_event_finished::monitor;

	ddf::junkyard::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_pc_2_event_finished::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_pc_2_event_gamestate::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::timedevent_pc_2_event_gamestate::monitor;

	ddf::junkyard::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_pc_2_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::top_opening::init();
	ddf::junkyard::secret_box_controller_1::debouncer_4::value::on_change += ddf::junkyard::top_opening::monitor;

	ddf::junkyard::top_opening::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::top_opening::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::top_opening::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::top_opening::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::audio_message_url::init(std::string());
	ddf::junkyard::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::audio_message_url::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::junkyard::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::junkyard::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::junkyard::audio_message_url::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::junkyard::comdev_reset::init(bool(false));
	ddf::junkyard::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::comdev_reset::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::junkyard::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::junkyard::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::junkyard::comdev_reset::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::junkyard::comdev_silence::init(bool(false));
	ddf::junkyard::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::comdev_silence::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::junkyard::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::junkyard::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::junkyard::comdev_silence::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::junkyard::freezed1::init(bool());
	ddf::junkyard::freezed1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::freezed1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::freezed1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::freezed1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::freezed5::init(bool());
	ddf::junkyard::freezed5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::freezed5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::freezed5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::freezed5::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gm_help_status::init(bool());
	ddf::junkyard::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::junkyard::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::junkyard::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::junkyard::gm_help_status::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::junkyard::gameend::init(uint8_t(0));
	ddf::junkyard::gameend::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gameend::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gameend::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gameend::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::gamestate::init(uint8_t(3));
	ddf::junkyard::gamestate::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gamestate::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gamestate::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gamestate::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::incoming_call::init(uint8_t(0xff));
	ddf::junkyard::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::incoming_call::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::incoming_call::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::junkyard::incoming_call::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::junkyard::incoming_call::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::junkyard::incoming_call::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::junkyard::incoming_call_status::init(uint8_t());
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::junkyard::paused::init(bool());
	ddf::junkyard::paused::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::paused::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::paused::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::paused::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::restart_game::init(bool());
	ddf::junkyard::restart_game::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::restart_game::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::restart_game::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::restart_game::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::restart_game::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::junkyard::restart_game::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::junkyard::restart_game::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::junkyard::restart_game::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::junkyard::text_message::init(std::string());
	ddf::junkyard::text_message::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::text_message::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::text_message::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::text_message::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::text_message::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::junkyard::text_message::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::junkyard::text_message::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::junkyard::text_message::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::junkyard::text_message_sender::init(uint8_t(0xff));
	ddf::junkyard::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::text_message_sender::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(0));
	ddf::junkyard::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(1));
	ddf::junkyard::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(2));
	ddf::junkyard::text_message_sender::remote_add(ddf::service::comdev::device_role::instance(3));
	ddf::junkyard::correct_notes::init(uint8_t(0));
	ddf::junkyard::correct_notes::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::correct_notes::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::correct_notes::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::correct_notes::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::led_timer_start::init(uint64_t(0));
	ddf::junkyard::led_timer_start::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::led_timer_start::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::led_timer_start::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::led_timer_start::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::lock_pick_1_pressed::init(bool(false));
	ddf::junkyard::lock_pick_1_pressed::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::lock_pick_1_pressed::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::lock_pick_1_pressed::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::lock_pick_1_pressed::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::lock_pick_2_pressed::init(bool(false));
	ddf::junkyard::lock_pick_2_pressed::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::lock_pick_2_pressed::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::lock_pick_2_pressed::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::lock_pick_2_pressed::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_1::init(uint64_t(1));
	ddf::junkyard::timedevent_atmo_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_2::init(uint64_t(300));
	ddf::junkyard::timedevent_atmo_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_2::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_3::init(uint64_t(900));
	ddf::junkyard::timedevent_atmo_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_3::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_4::init(uint64_t(1200));
	ddf::junkyard::timedevent_atmo_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_4::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_5::init(uint64_t(1800));
	ddf::junkyard::timedevent_atmo_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_5::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_atmo_6::init(uint64_t(2700));
	ddf::junkyard::timedevent_atmo_6::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_6::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_6::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_6::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_pc_1::init(uint64_t(1200));
	ddf::junkyard::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_pc_1::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::junkyard::timedevent_pc_2::init(uint64_t(2400));
	ddf::junkyard::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_pc_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_1::init();
	ddf::junkyard::room_1_content::chord::init();
	ddf::junkyard::room_1_content::progress::init();
	ddf::junkyard::room_1_content::atmo_blacky::init();
	ddf::junkyard::room_1_content::atmo_junkyard::init();
	ddf::junkyard::room_1_content::atmo_telephone::init();
	ddf::junkyard::room_1_content::piano_a1::init();
	ddf::junkyard::room_1_content::piano_b1::init();
	ddf::junkyard::room_1_content::piano_c1::init();
	ddf::junkyard::room_1_content::piano_c2::init();
	ddf::junkyard::room_1_content::piano_d1::init();
	ddf::junkyard::room_1_content::piano_d2::init();
	ddf::junkyard::room_1_content::piano_e1::init();
	ddf::junkyard::room_1_content::piano_f1::init();
	ddf::junkyard::room_1_content::piano_g1::init();
	ddf::junkyard::room_1_content::careful::init();
	ddf::junkyard::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_1_content::careful::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_1_content::gminc::init();
	ddf::junkyard::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_1_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_1_content::rules::init();
	ddf::junkyard::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_1_content::rules::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_1_content::techdiff::init();
	ddf::junkyard::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_1_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_1_content::event_1::init();
	ddf::junkyard::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_1_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_1_content::event_2::init();
	ddf::junkyard::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_1_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_1_content::event_3::init();
	ddf::junkyard::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_1_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_1_content::event_4::init();
	ddf::junkyard::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_1_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_1_content::event_5::init();
	ddf::junkyard::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_1_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(3));


	ddf::junkyard::room_2::init();
	ddf::junkyard::room_2_content::chord::init();
	ddf::junkyard::room_2_content::progress::init();
	ddf::junkyard::room_2_content::atmo_blacky::init();
	ddf::junkyard::room_2_content::atmo_junkyard::init();
	ddf::junkyard::room_2_content::atmo_telephone::init();
	ddf::junkyard::room_2_content::piano_a1::init();
	ddf::junkyard::room_2_content::piano_b1::init();
	ddf::junkyard::room_2_content::piano_c1::init();
	ddf::junkyard::room_2_content::piano_c2::init();
	ddf::junkyard::room_2_content::piano_d1::init();
	ddf::junkyard::room_2_content::piano_d2::init();
	ddf::junkyard::room_2_content::piano_e1::init();
	ddf::junkyard::room_2_content::piano_f1::init();
	ddf::junkyard::room_2_content::piano_g1::init();
	ddf::junkyard::room_2_content::careful::init();
	ddf::junkyard::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_2_content::careful::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_2_content::gminc::init();
	ddf::junkyard::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_2_content::gminc::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_2_content::rules::init();
	ddf::junkyard::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_2_content::rules::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_2_content::techdiff::init();
	ddf::junkyard::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_2_content::techdiff::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_2_content::event_1::init();
	ddf::junkyard::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_2_content::event_1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_2_content::event_2::init();
	ddf::junkyard::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_2_content::event_2::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_2_content::event_3::init();
	ddf::junkyard::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_2_content::event_3::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_2_content::event_4::init();
	ddf::junkyard::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_2_content::event_4::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::room_2_content::event_5::init();
	ddf::junkyard::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::room_2_content::event_5::remote_add(ddf::service::gmclient::device_role::instance(3));




	ddf::junkyard::freezetimer1::init();
	ddf::junkyard::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::freezetimer5::init();
	ddf::junkyard::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::gametimer::init();
	ddf::junkyard::gametimer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::gametimer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::gametimer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::gametimer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::relock_timer::init();
	ddf::junkyard::relock_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::relock_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::relock_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::relock_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::timedevent_atmo_1_timer::init();
	ddf::junkyard::timedevent_atmo_1_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_1_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_1_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_1_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::timedevent_atmo_2_timer::init();
	ddf::junkyard::timedevent_atmo_2_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_2_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_2_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_2_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::timedevent_atmo_3_timer::init();
	ddf::junkyard::timedevent_atmo_3_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_3_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_3_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_3_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::timedevent_atmo_4_timer::init();
	ddf::junkyard::timedevent_atmo_4_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_4_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_4_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_4_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::timedevent_atmo_5_timer::init();
	ddf::junkyard::timedevent_atmo_5_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_5_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_5_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_5_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::timedevent_atmo_6_timer::init();
	ddf::junkyard::timedevent_atmo_6_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_atmo_6_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_atmo_6_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_atmo_6_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::timedevent_pc_1_timer::init();
	ddf::junkyard::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_pc_1_timer::remote_add(ddf::service::gmclient::device_role::instance(3));

	ddf::junkyard::timedevent_pc_2_timer::init();
	ddf::junkyard::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::junkyard::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::junkyard::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::junkyard::timedevent_pc_2_timer::remote_add(ddf::service::gmclient::device_role::instance(3));


	ddf::service::comdev::device_role::init();

	dm::add_role<ddf::service::comdev::device_role>();
	ddf::service::gmclient::device_role::init();

	dm::add_role<ddf::service::gmclient::device_role>();

	ddf::service::statustimertick::init();
	ddf::service::statustimer::on_value_change += ddf::service::statustimertick::monitor;


	ddf::service::servercpustatus::init(uint8_t());
	ddf::service::servercpustatus::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::service::servercpustatus::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::service::servercpustatus::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::service::servercpustatus::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::service::servermemorystatus::init(uint8_t());
	ddf::service::servermemorystatus::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::service::servermemorystatus::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::service::servermemorystatus::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::service::servermemorystatus::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::service::servernetworkstatus::init(uint8_t());
	ddf::service::servernetworkstatus::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::service::servernetworkstatus::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::service::servernetworkstatus::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::service::servernetworkstatus::remote_add(ddf::service::gmclient::device_role::instance(3));
	ddf::service::serverstoragestatus::init(uint8_t());
	ddf::service::serverstoragestatus::remote_add(ddf::service::gmclient::device_role::instance(0));
	ddf::service::serverstoragestatus::remote_add(ddf::service::gmclient::device_role::instance(1));
	ddf::service::serverstoragestatus::remote_add(ddf::service::gmclient::device_role::instance(2));
	ddf::service::serverstoragestatus::remote_add(ddf::service::gmclient::device_role::instance(3));



	ddf::service::statustimer::init();


}

static void uninit()
{
	ddf::pirate::artificial_game_ending::uninit();
	ddf::pirate::cashier_pin_timeout::uninit();
	ddf::pirate::display_update::uninit();
	ddf::pirate::freeze_1::uninit();
	ddf::pirate::freeze_1_timeout::uninit();
	ddf::pirate::freeze_5::uninit();
	ddf::pirate::freeze_5_timeout::uninit();
	ddf::pirate::game_end_button_push::uninit();
	ddf::pirate::game_ending::uninit();
	ddf::pirate::game_pause_mgmt::uninit();
	ddf::pirate::gameevent_boat_door_opened::uninit();
	ddf::pirate::gameevent_bright_star::uninit();
	ddf::pirate::gameevent_brightest_star::uninit();
	ddf::pirate::gameevent_call_accepted::uninit();
	ddf::pirate::gameevent_call_declined::uninit();
	ddf::pirate::gameevent_call_finished::uninit();
	ddf::pirate::gameevent_call_missed::uninit();
	ddf::pirate::gameevent_call_ringing::uninit();
	ddf::pirate::gameevent_cashier_code_mistaken::uninit();
	ddf::pirate::gameevent_cashier_opened::uninit();
	ddf::pirate::gameevent_chest_opening::uninit();
	ddf::pirate::gameevent_game_fail::uninit();
	ddf::pirate::gameevent_game_finished::uninit();
	ddf::pirate::gameevent_game_paused::uninit();
	ddf::pirate::gameevent_game_reset::uninit();
	ddf::pirate::gameevent_game_started::uninit();
	ddf::pirate::gameevent_game_win::uninit();
	ddf::pirate::gameevent_ghostbox_opened::uninit();
	ddf::pirate::gameevent_key_released::uninit();
	ddf::pirate::gameevent_knock_succeeded::uninit();
	ddf::pirate::gameevent_lattice_opened::uninit();
	ddf::pirate::gameevent_rex_card_inserted::uninit();
	ddf::pirate::gameevent_rex_card_removed::uninit();
	ddf::pirate::gameevent_rex_game_won::uninit();
	ddf::pirate::gameevent_rex_table_retry::uninit();
	ddf::pirate::ghost_blinking::uninit();
	ddf::pirate::hanger_trigger::uninit();
	ddf::pirate::knock_accumulate::uninit();
	ddf::pirate::knock_reset::uninit();
	ddf::pirate::knock_timeout::uninit();
	ddf::pirate::laser_turn_off::uninit();
	ddf::pirate::left_column_evaluate::uninit();
	ddf::pirate::map_reset::uninit();
	ddf::pirate::map_sensor1::uninit();
	ddf::pirate::map_sensor2::uninit();
	ddf::pirate::map_solved::uninit();
	ddf::pirate::middle_column_evaluate::uninit();
	ddf::pirate::pin_code_accumulation::uninit();
	ddf::pirate::reset_room::uninit();
	ddf::pirate::rex_blink::uninit();
	ddf::pirate::rex_led_update::uninit();
	ddf::pirate::rex_photosensor_4_acc::uninit();
	ddf::pirate::rex_photosensor_5_acc::uninit();
	ddf::pirate::rex_photosensor_6_acc::uninit();
	ddf::pirate::rex_photosensor_7_acc::uninit();
	ddf::pirate::rex_table_state::uninit();
	ddf::pirate::right_column_evaluate::uninit();
	ddf::pirate::rotation_update::uninit();
	ddf::pirate::sign_matching::uninit();
	ddf::pirate::stop_audios::uninit();
	ddf::pirate::time_up::uninit();
	ddf::pirate::timedevent_an_1_event_finished::uninit();
	ddf::pirate::timedevent_an_1_event_gamestate::uninit();
	ddf::pirate::timedevent_an_2_event_finished::uninit();
	ddf::pirate::timedevent_an_2_event_gamestate::uninit();
	ddf::pirate::timedevent_an_3_event_finished::uninit();
	ddf::pirate::timedevent_an_3_event_gamestate::uninit();
	ddf::pirate::timedevent_ghost_voice_event_finished::uninit();
	ddf::pirate::timedevent_ghost_voice_event_gamestate::uninit();
	ddf::pirate::timedevent_pc_1_event_finished::uninit();
	ddf::pirate::timedevent_pc_1_event_gamestate::uninit();
	ddf::pirate::timedevent_pc_2_event_finished::uninit();
	ddf::pirate::timedevent_pc_2_event_gamestate::uninit();
	ddf::pirate::tray_trigger::uninit();
	ddf::pirate::wheel_reset::uninit();

	ddf::pirate::cashier_laser_controller::laser::uninit();
	ddf::pirate::cashier_laser_controller::lcd::uninit();
	ddf::pirate::cashier_laser_controller::pin_pad::uninit();
	ddf::pirate::cashier_laser_controller::cash_box::uninit();
	ddf::pirate::cashier_laser_controller::switch_1::uninit();
	ddf::pirate::cashier_laser_controller::led_strip::uninit();
	ddf::pirate::cashier_laser_controller::buzzer::uninit();
	ddf::pirate::entrance_hanger_controller::debouncer::uninit();
	ddf::pirate::entrance_hanger_controller::led::uninit();
	ddf::pirate::entrance_hanger_controller::magnetic_sensor::uninit();
	ddf::pirate::entrance_hanger_controller::debouncer_2::uninit();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1::uninit();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2::uninit();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3::uninit();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer::uninit();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor::uninit();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::uninit();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1::uninit();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2::uninit();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::uninit();
	ddf::pirate::map_controller::magnetic_sensor_1::uninit();
	ddf::pirate::map_controller::magnetic_sensor_2::uninit();
	ddf::pirate::map_controller::led_strip::uninit();
	ddf::pirate::rex_flipper_controller::light_controller_1::uninit();
	ddf::pirate::rex_flipper_controller::light_controller_2::uninit();
	ddf::pirate::rex_flipper_controller::light_controller_3::uninit();
	ddf::pirate::rex_flipper_controller::light_controller_4::uninit();
	ddf::pirate::rex_flipper_controller::light_controller_5::uninit();
	ddf::pirate::rex_flipper_controller::light_controller_6::uninit();
	ddf::pirate::rex_flipper_controller::light_controller_7::uninit();
	ddf::pirate::rex_flipper_controller::photosensor_1::uninit();
	ddf::pirate::rex_flipper_controller::photosensor_2::uninit();
	ddf::pirate::rex_flipper_controller::photosensor_3::uninit();
	ddf::pirate::rex_flipper_controller::photosensor_4::uninit();
	ddf::pirate::rex_flipper_controller::photosensor_5::uninit();
	ddf::pirate::rex_flipper_controller::photosensor_6::uninit();
	ddf::pirate::rex_flipper_controller::photosensor_7::uninit();
	ddf::pirate::rex_flipper_controller::rfid_reader::uninit();
	ddf::pirate::rex_flipper_controller::magnetic_lock::uninit();
	ddf::pirate::rex_flipper_controller::led::uninit();
	ddf::pirate::stone_chest_controller::magnetic_sensor_1::uninit();
	ddf::pirate::stone_chest_controller::magnetic_sensor_2::uninit();
	ddf::pirate::stone_chest_controller::magnetic_sensor_3::uninit();
	ddf::pirate::stone_chest_controller::magnetic_sensor_4::uninit();
	ddf::pirate::stone_chest_controller::magnetic_sensor_5::uninit();
	ddf::pirate::stone_chest_controller::magnetic_lock_1::uninit();
	ddf::pirate::stone_chest_controller::magnetic_lock_2::uninit();
	ddf::pirate::stone_chest_controller::led_strip::uninit();

	ddf::pirate::audio_message_url::uninit();
	ddf::pirate::comdev_reset::uninit();
	ddf::pirate::comdev_silence::uninit();
	ddf::pirate::freezed1::uninit();
	ddf::pirate::freezed5::uninit();
	ddf::pirate::gm_help_status::uninit();
	ddf::pirate::gameend::uninit();
	ddf::pirate::gamestate::uninit();
	ddf::pirate::incoming_call::uninit();
	ddf::pirate::incoming_call_status::uninit();
	ddf::pirate::paused::uninit();
	ddf::pirate::restart_game::uninit();
	ddf::pirate::text_message::uninit();
	ddf::pirate::text_message_sender::uninit();
	ddf::pirate::knock_count::uninit();
	ddf::pirate::map_sensor1_triggered::uninit();
	ddf::pirate::map_sensor2_triggered::uninit();
	ddf::pirate::pin_code::uninit();
	ddf::pirate::rex_enabled::uninit();
	ddf::pirate::rex_left_column_failure::uninit();
	ddf::pirate::rex_middle_column_failure::uninit();
	ddf::pirate::rex_photosensor_4_value::uninit();
	ddf::pirate::rex_photosensor_5_value::uninit();
	ddf::pirate::rex_photosensor_6_value::uninit();
	ddf::pirate::rex_photosensor_7_value::uninit();
	ddf::pirate::rex_right_column_failure::uninit();
	ddf::pirate::rex_score::uninit();
	ddf::pirate::rex_trials_left::uninit();
	ddf::pirate::star_value::uninit();
	ddf::pirate::timedevent_an_1::uninit();
	ddf::pirate::timedevent_an_2::uninit();
	ddf::pirate::timedevent_an_3::uninit();
	ddf::pirate::timedevent_ghost_voice::uninit();
	ddf::pirate::timedevent_pc_1::uninit();
	ddf::pirate::timedevent_pc_2::uninit();
	ddf::pirate::wheel_last_pos::uninit();

	ddf::pirate::room_1_content::chord::uninit();
	ddf::pirate::room_1_content::progress::uninit();
	ddf::pirate::room_1_content::careful::uninit();
	ddf::pirate::room_1_content::event_1::uninit();
	ddf::pirate::room_1_content::event_2::uninit();
	ddf::pirate::room_1_content::event_3::uninit();
	ddf::pirate::room_1_content::failstate::uninit();
	ddf::pirate::room_1_content::gminc::uninit();
	ddf::pirate::room_1_content::ghost_voice::uninit();
	ddf::pirate::room_1_content::rules::uninit();
	ddf::pirate::room_1_content::techdiff::uninit();
	ddf::pirate::room_1_content::winstate::uninit();
	ddf::pirate::room_1::uninit();
	ddf::pirate::room_2_content::chord::uninit();
	ddf::pirate::room_2_content::progress::uninit();
	ddf::pirate::room_2_content::careful::uninit();
	ddf::pirate::room_2_content::event_1::uninit();
	ddf::pirate::room_2_content::event_2::uninit();
	ddf::pirate::room_2_content::event_3::uninit();
	ddf::pirate::room_2_content::failstate::uninit();
	ddf::pirate::room_2_content::gminc::uninit();
	ddf::pirate::room_2_content::ghost_voice::uninit();
	ddf::pirate::room_2_content::rules::uninit();
	ddf::pirate::room_2_content::techdiff::uninit();
	ddf::pirate::room_2_content::winstate::uninit();
	ddf::pirate::room_2::uninit();

	ddf::pirate::tray_camera_content::tray_sensor::uninit();
	ddf::pirate::tray_camera::uninit();

	ddf::pirate::freezetimer1::uninit();
	ddf::pirate::freezetimer5::uninit();
	ddf::pirate::gametimer::uninit();
	ddf::pirate::ghost_blink_timer::uninit();
	ddf::pirate::knock_timer::uninit();
	ddf::pirate::pin_timeout_timer::uninit();
	ddf::pirate::rex_blink_timer::uninit();
	ddf::pirate::timedevent_an_1_timer::uninit();
	ddf::pirate::timedevent_an_2_timer::uninit();
	ddf::pirate::timedevent_an_3_timer::uninit();
	ddf::pirate::timedevent_ghost_voice_timer::uninit();
	ddf::pirate::timedevent_pc_1_timer::uninit();
	ddf::pirate::timedevent_pc_2_timer::uninit();

	ddf::magician::artificial_game_ending::uninit();
	ddf::magician::freeze_1::uninit();
	ddf::magician::freeze_1_timeout::uninit();
	ddf::magician::freeze_5::uninit();
	ddf::magician::freeze_5_timeout::uninit();
	ddf::magician::game_end_button_push::uninit();
	ddf::magician::game_ending::uninit();
	ddf::magician::game_pause_mgmt::uninit();
	ddf::magician::gameevent_call_accepted::uninit();
	ddf::magician::gameevent_call_declined::uninit();
	ddf::magician::gameevent_call_finished::uninit();
	ddf::magician::gameevent_call_missed::uninit();
	ddf::magician::gameevent_call_ringing::uninit();
	ddf::magician::gameevent_cupboard_controller_event_for_labyrinth_task::uninit();
	ddf::magician::gameevent_door_open_light_turn_on::uninit();
	ddf::magician::gameevent_game_fail::uninit();
	ddf::magician::gameevent_game_finished::uninit();
	ddf::magician::gameevent_game_paused::uninit();
	ddf::magician::gameevent_game_reset::uninit();
	ddf::magician::gameevent_game_started::uninit();
	ddf::magician::gameevent_game_win::uninit();
	ddf::magician::gameevent_planning_wall_puzzle::uninit();
	ddf::magician::gameevent_safe_opened::uninit();
	ddf::magician::keyswitch_active::uninit();
	ddf::magician::pin_code_accumulation::uninit();
	ddf::magician::pin_code_test_alias_safe_activation::uninit();
	ddf::magician::pin_timeout::uninit();
	ddf::magician::reset_room::uninit();
	ddf::magician::rfid_tag_correct::uninit();
	ddf::magician::safecode_entry_activaion::uninit();
	ddf::magician::stop_audios::uninit();
	ddf::magician::time_up::uninit();
	ddf::magician::timedevent_an_1_event_finished::uninit();
	ddf::magician::timedevent_an_1_event_gamestate::uninit();
	ddf::magician::timedevent_an_2_event_finished::uninit();
	ddf::magician::timedevent_an_2_event_gamestate::uninit();
	ddf::magician::timedevent_an_4_event_finished::uninit();
	ddf::magician::timedevent_an_4_event_gamestate::uninit();
	ddf::magician::timedevent_an_6_event_finished::uninit();
	ddf::magician::timedevent_an_6_event_gamestate::uninit();
	ddf::magician::timedevent_ap_1_event_finished::uninit();
	ddf::magician::timedevent_ap_1_event_gamestate::uninit();
	ddf::magician::timedevent_pc_1_event_finished::uninit();
	ddf::magician::timedevent_pc_1_event_gamestate::uninit();
	ddf::magician::timedevent_pc_2_event_finished::uninit();
	ddf::magician::timedevent_pc_2_event_gamestate::uninit();

	ddf::magician::cupboard_controller::debouncer::uninit();
	ddf::magician::cupboard_controller::magnetic_sensor::uninit();
	ddf::magician::cupboard_controller::magnetic_lock::uninit();
	ddf::magician::cupboard_controller::led_strip::uninit();
	ddf::magician::design_board_controller::linear_magnetic_sensor_1::uninit();
	ddf::magician::design_board_controller::linear_magnetic_sensor_2::uninit();
	ddf::magician::design_board_controller::linear_magnetic_sensor_3::uninit();
	ddf::magician::design_board_controller::magnetic_lock::uninit();
	ddf::magician::entrance_controller::debouncer::uninit();
	ddf::magician::entrance_controller::led::uninit();
	ddf::magician::entrance_controller::magnetic_sensor::uninit();
	ddf::magician::futuristic_safe_controller::debouncer::uninit();
	ddf::magician::futuristic_safe_controller::rfid_reader::uninit();
	ddf::magician::futuristic_safe_controller::pin_pad::uninit();
	ddf::magician::futuristic_safe_controller::magnetic_lock::uninit();
	ddf::magician::futuristic_safe_controller::addressable_led_strip::uninit();
	ddf::magician::futuristic_safe_controller::buzzer::uninit();

	ddf::magician::audio_message_url::uninit();
	ddf::magician::comdev_reset::uninit();
	ddf::magician::comdev_silence::uninit();
	ddf::magician::freezed1::uninit();
	ddf::magician::freezed5::uninit();
	ddf::magician::gm_help_status::uninit();
	ddf::magician::gameend::uninit();
	ddf::magician::gamestate::uninit();
	ddf::magician::incoming_call::uninit();
	ddf::magician::incoming_call_status::uninit();
	ddf::magician::paused::uninit();
	ddf::magician::restart_game::uninit();
	ddf::magician::text_message::uninit();
	ddf::magician::text_message_sender::uninit();
	ddf::magician::pin_code::uninit();
	ddf::magician::pin_pad_code::uninit();
	ddf::magician::rfid_reader_code::uninit();
	ddf::magician::timedevent_an_1::uninit();
	ddf::magician::timedevent_an_2::uninit();
	ddf::magician::timedevent_an_4::uninit();
	ddf::magician::timedevent_an_6::uninit();
	ddf::magician::timedevent_ap_1::uninit();
	ddf::magician::timedevent_pc_1::uninit();
	ddf::magician::timedevent_pc_2::uninit();

	ddf::magician::room_1_content::applause::uninit();
	ddf::magician::room_1_content::chord::uninit();
	ddf::magician::room_1_content::progress::uninit();
	ddf::magician::room_1_content::careful::uninit();
	ddf::magician::room_1_content::failstate::uninit();
	ddf::magician::room_1_content::gminc::uninit();
	ddf::magician::room_1_content::rules::uninit();
	ddf::magician::room_1_content::techdiff::uninit();
	ddf::magician::room_1_content::winstate::uninit();
	ddf::magician::room_1_content::event_1::uninit();
	ddf::magician::room_1_content::event_2::uninit();
	ddf::magician::room_1_content::event_3::uninit();
	ddf::magician::room_1_content::event_4::uninit();
	ddf::magician::room_1_content::event_5::uninit();
	ddf::magician::room_1_content::event_6::uninit();
	ddf::magician::room_1::uninit();
	ddf::magician::room_2_content::applause::uninit();
	ddf::magician::room_2_content::chord::uninit();
	ddf::magician::room_2_content::progress::uninit();
	ddf::magician::room_2_content::careful::uninit();
	ddf::magician::room_2_content::failstate::uninit();
	ddf::magician::room_2_content::gminc::uninit();
	ddf::magician::room_2_content::rules::uninit();
	ddf::magician::room_2_content::techdiff::uninit();
	ddf::magician::room_2_content::winstate::uninit();
	ddf::magician::room_2_content::event_1::uninit();
	ddf::magician::room_2_content::event_2::uninit();
	ddf::magician::room_2_content::event_3::uninit();
	ddf::magician::room_2_content::event_4::uninit();
	ddf::magician::room_2_content::event_5::uninit();
	ddf::magician::room_2_content::event_6::uninit();
	ddf::magician::room_2::uninit();


	ddf::magician::freezetimer1::uninit();
	ddf::magician::freezetimer5::uninit();
	ddf::magician::gametimer::uninit();
	ddf::magician::pin_timeout_timer::uninit();
	ddf::magician::timedevent_an_1_timer::uninit();
	ddf::magician::timedevent_an_2_timer::uninit();
	ddf::magician::timedevent_an_4_timer::uninit();
	ddf::magician::timedevent_an_6_timer::uninit();
	ddf::magician::timedevent_ap_1_timer::uninit();
	ddf::magician::timedevent_pc_1_timer::uninit();
	ddf::magician::timedevent_pc_2_timer::uninit();

	ddf::villa::answering_machine::uninit();
	ddf::villa::artificial_game_ending::uninit();
	ddf::villa::freeze_1::uninit();
	ddf::villa::freeze_1_timeout::uninit();
	ddf::villa::freeze_5::uninit();
	ddf::villa::freeze_5_timeout::uninit();
	ddf::villa::game_end_button_push::uninit();
	ddf::villa::game_ending::uninit();
	ddf::villa::game_pause_mgmt::uninit();
	ddf::villa::gameevent_call_accepted::uninit();
	ddf::villa::gameevent_call_declined::uninit();
	ddf::villa::gameevent_call_finished::uninit();
	ddf::villa::gameevent_call_missed::uninit();
	ddf::villa::gameevent_call_ringing::uninit();
	ddf::villa::gameevent_casette_eject_trigger::uninit();
	ddf::villa::gameevent_desktop_pc_login::uninit();
	ddf::villa::gameevent_finding_the_keys::uninit();
	ddf::villa::gameevent_game_fail::uninit();
	ddf::villa::gameevent_game_finished::uninit();
	ddf::villa::gameevent_game_paused::uninit();
	ddf::villa::gameevent_game_reset::uninit();
	ddf::villa::gameevent_game_started::uninit();
	ddf::villa::gameevent_game_win::uninit();
	ddf::villa::gameevent_safe_code_mistaken::uninit();
	ddf::villa::gameevent_safe_opened::uninit();
	ddf::villa::pin_code_accumulation::uninit();
	ddf::villa::pin_timeout::uninit();
	ddf::villa::reset_room::uninit();
	ddf::villa::stop_audios::uninit();
	ddf::villa::the_surveillance_konsole::uninit();
	ddf::villa::time_up::uninit();
	ddf::villa::timedevent_funk_1_event_finished::uninit();
	ddf::villa::timedevent_funk_1_event_gamestate::uninit();
	ddf::villa::timedevent_funk_2_event_finished::uninit();
	ddf::villa::timedevent_funk_2_event_gamestate::uninit();
	ddf::villa::timedevent_funk_3_event_finished::uninit();
	ddf::villa::timedevent_funk_3_event_gamestate::uninit();
	ddf::villa::timedevent_pc_1_event_finished::uninit();
	ddf::villa::timedevent_pc_1_event_gamestate::uninit();
	ddf::villa::timedevent_pc_2_event_finished::uninit();
	ddf::villa::timedevent_pc_2_event_gamestate::uninit();
	ddf::villa::timedevent_pc_3_event_finished::uninit();
	ddf::villa::timedevent_pc_3_event_gamestate::uninit();
	ddf::villa::video_playing::uninit();

	ddf::villa::control_room_controller::switch_1::uninit();
	ddf::villa::control_room_controller::magnetic_lock::uninit();
	ddf::villa::control_room_controller::debouncer_1::uninit();
	ddf::villa::control_room_controller::led_1::uninit();
	ddf::villa::control_room_controller::led_2::uninit();
	ddf::villa::desk_controller::debouncer_3::uninit();
	ddf::villa::desk_controller::debouncer_4::uninit();
	ddf::villa::desktop_pc::started::uninit();
	ddf::villa::desktop_pc::shutdown::uninit();
	ddf::villa::desktop_pc::bad_password::uninit();
	ddf::villa::desktop_pc::logged_in::uninit();
	ddf::villa::desktop_pc::recycled_restore::uninit();
	ddf::villa::desktop_pc::audioplay_started::uninit();
	ddf::villa::desktop_pc::audioplay_finished::uninit();
	ddf::villa::desktop_pc::audioplay_paused::uninit();
	ddf::villa::desktop_pc::restart_game::uninit();
	ddf::villa::desktop_pc::audioplay_startevent::uninit();
	ddf::villa::desktop_pc::audiopause_pauseevent::uninit();
	ddf::villa::entrance_controller::debouncer::uninit();
	ddf::villa::entrance_controller::led::uninit();
	ddf::villa::entrance_controller::magnetic_sensor::uninit();
	ddf::villa::safe_controller::pin_pad::uninit();
	ddf::villa::safe_controller::magnetic_lock::uninit();
	ddf::villa::safe_controller::debouncer_1::uninit();
	ddf::villa::safe_controller::debouncer_2::uninit();
	ddf::villa::safe_controller::buzzer::uninit();
	ddf::villa::video_device::started::uninit();
	ddf::villa::video_device::shutdown::uninit();
	ddf::villa::video_device::livecam_started::uninit();
	ddf::villa::video_device::livecamslides_started::uninit();
	ddf::villa::video_device::restart_game::uninit();
	ddf::villa::video_device::start_livecams::uninit();
	ddf::villa::video_device::stop_livecams::uninit();
	ddf::villa::video_device::start_tape::uninit();
	ddf::villa::video_device::stop_tape::uninit();
	ddf::villa::video_device::pause_tape::uninit();
	ddf::villa::video_device::finished_tape::uninit();
	ddf::villa::video_device::enabled::uninit();
	ddf::villa::video_device::eject::uninit();
	ddf::villa::video_device::casette_id::uninit();
	ddf::villa::video_device::play_ongoing::uninit();
	ddf::villa::video_device::livecam_ongoing::uninit();

	ddf::villa::audio_message_url::uninit();
	ddf::villa::comdev_reset::uninit();
	ddf::villa::comdev_silence::uninit();
	ddf::villa::freezed1::uninit();
	ddf::villa::freezed5::uninit();
	ddf::villa::gm_help_status::uninit();
	ddf::villa::gameend::uninit();
	ddf::villa::gamestate::uninit();
	ddf::villa::incoming_call::uninit();
	ddf::villa::incoming_call_status::uninit();
	ddf::villa::paused::uninit();
	ddf::villa::restart_game::uninit();
	ddf::villa::text_message::uninit();
	ddf::villa::text_message_sender::uninit();
	ddf::villa::pin_code::uninit();
	ddf::villa::timedevent_funk_1::uninit();
	ddf::villa::timedevent_funk_2::uninit();
	ddf::villa::timedevent_funk_3::uninit();
	ddf::villa::timedevent_pc_1::uninit();
	ddf::villa::timedevent_pc_2::uninit();
	ddf::villa::timedevent_pc_3::uninit();

	ddf::villa::room_1_content::chord::uninit();
	ddf::villa::room_1_content::progress::uninit();
	ddf::villa::room_1_content::careful::uninit();
	ddf::villa::room_1_content::gminc::uninit();
	ddf::villa::room_1_content::rules::uninit();
	ddf::villa::room_1_content::techdiff::uninit();
	ddf::villa::room_1_content::event_1::uninit();
	ddf::villa::room_1_content::event_2::uninit();
	ddf::villa::room_1_content::event_3::uninit();
	ddf::villa::room_1_content::event_4::uninit();
	ddf::villa::room_1_content::event_5::uninit();
	ddf::villa::room_1::uninit();
	ddf::villa::room_2_content::chord::uninit();
	ddf::villa::room_2_content::progress::uninit();
	ddf::villa::room_2_content::careful::uninit();
	ddf::villa::room_2_content::gminc::uninit();
	ddf::villa::room_2_content::rules::uninit();
	ddf::villa::room_2_content::techdiff::uninit();
	ddf::villa::room_2_content::event_1::uninit();
	ddf::villa::room_2_content::event_2::uninit();
	ddf::villa::room_2_content::event_3::uninit();
	ddf::villa::room_2_content::event_4::uninit();
	ddf::villa::room_2_content::event_5::uninit();
	ddf::villa::room_2::uninit();


	ddf::villa::freezetimer1::uninit();
	ddf::villa::freezetimer5::uninit();
	ddf::villa::gametimer::uninit();
	ddf::villa::eject_wait::uninit();
	ddf::villa::pin_timeout_timer::uninit();
	ddf::villa::timedevent_funk_1_timer::uninit();
	ddf::villa::timedevent_funk_2_timer::uninit();
	ddf::villa::timedevent_funk_3_timer::uninit();
	ddf::villa::timedevent_pc_1_timer::uninit();
	ddf::villa::timedevent_pc_2_timer::uninit();
	ddf::villa::timedevent_pc_3_timer::uninit();

	ddf::junkyard::led_strip_update::uninit();
	ddf::junkyard::artificial_game_ending::uninit();
	ddf::junkyard::freeze_1::uninit();
	ddf::junkyard::freeze_1_timeout::uninit();
	ddf::junkyard::freeze_5::uninit();
	ddf::junkyard::freeze_5_timeout::uninit();
	ddf::junkyard::game_end_button_push::uninit();
	ddf::junkyard::game_ending::uninit();
	ddf::junkyard::game_pause_mgmt::uninit();
	ddf::junkyard::gameevent_ampmeter_turn_on::uninit();
	ddf::junkyard::gameevent_anamorphic_module::uninit();
	ddf::junkyard::gameevent_call_accepted::uninit();
	ddf::junkyard::gameevent_call_declined::uninit();
	ddf::junkyard::gameevent_call_finished::uninit();
	ddf::junkyard::gameevent_call_missed::uninit();
	ddf::junkyard::gameevent_call_ringing::uninit();
	ddf::junkyard::gameevent_email_received::uninit();
	ddf::junkyard::gameevent_game_fail::uninit();
	ddf::junkyard::gameevent_game_finished::uninit();
	ddf::junkyard::gameevent_game_paused::uninit();
	ddf::junkyard::gameevent_game_reset::uninit();
	ddf::junkyard::gameevent_game_started::uninit();
	ddf::junkyard::gameevent_game_win::uninit();
	ddf::junkyard::gameevent_labyrinth_1::uninit();
	ddf::junkyard::gameevent_labyrinth_2::uninit();
	ddf::junkyard::gameevent_labyrinth_3::uninit();
	ddf::junkyard::gameevent_mona_lisa_rescue::uninit();
	ddf::junkyard::lockpick_module::uninit();
	ddf::junkyard::piano_key_pressed::uninit();
	ddf::junkyard::potato_power_indicator::uninit();
	ddf::junkyard::relock_event::uninit();
	ddf::junkyard::reset_room::uninit();
	ddf::junkyard::stop_audios::uninit();
	ddf::junkyard::time_up::uninit();
	ddf::junkyard::timedevent_atmo_1_event_finished::uninit();
	ddf::junkyard::timedevent_atmo_1_event_gamestate::uninit();
	ddf::junkyard::timedevent_atmo_2_event_finished::uninit();
	ddf::junkyard::timedevent_atmo_2_event_gamestate::uninit();
	ddf::junkyard::timedevent_atmo_3_event_finished::uninit();
	ddf::junkyard::timedevent_atmo_3_event_gamestate::uninit();
	ddf::junkyard::timedevent_atmo_4_event_finished::uninit();
	ddf::junkyard::timedevent_atmo_4_event_gamestate::uninit();
	ddf::junkyard::timedevent_atmo_5_event_finished::uninit();
	ddf::junkyard::timedevent_atmo_5_event_gamestate::uninit();
	ddf::junkyard::timedevent_atmo_6_event_finished::uninit();
	ddf::junkyard::timedevent_atmo_6_event_gamestate::uninit();
	ddf::junkyard::timedevent_pc_1_event_finished::uninit();
	ddf::junkyard::timedevent_pc_1_event_gamestate::uninit();
	ddf::junkyard::timedevent_pc_2_event_finished::uninit();
	ddf::junkyard::timedevent_pc_2_event_gamestate::uninit();
	ddf::junkyard::top_opening::uninit();

	ddf::junkyard::email_client::started::uninit();
	ddf::junkyard::email_client::shutdown::uninit();
	ddf::junkyard::email_client::emails_received::uninit();
	ddf::junkyard::email_client::restart_game::uninit();
	ddf::junkyard::email_client::search_string::uninit();
	ddf::junkyard::email_client::opened_email::uninit();
	ddf::junkyard::entrance_controller::debouncer::uninit();
	ddf::junkyard::entrance_controller::led::uninit();
	ddf::junkyard::entrance_controller::magnetic_sensor::uninit();
	ddf::junkyard::secret_box_controller_1::button_grid::uninit();
	ddf::junkyard::secret_box_controller_1::debouncer_1::uninit();
	ddf::junkyard::secret_box_controller_1::debouncer_2::uninit();
	ddf::junkyard::secret_box_controller_1::debouncer_3::uninit();
	ddf::junkyard::secret_box_controller_1::debouncer_4::uninit();
	ddf::junkyard::secret_box_controller_1::debouncer_5::uninit();
	ddf::junkyard::secret_box_controller_1::debouncer_6::uninit();
	ddf::junkyard::secret_box_controller_1::debouncer_7::uninit();
	ddf::junkyard::secret_box_controller_1::magnetic_lock_1::uninit();
	ddf::junkyard::secret_box_controller_1::magnetic_lock_2::uninit();
	ddf::junkyard::secret_box_controller_1::magnetic_lock_3::uninit();
	ddf::junkyard::secret_box_controller_1::magnetic_lock_4::uninit();
	ddf::junkyard::secret_box_controller_1::addressable_led::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_1::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_2::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_3::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_4::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_5::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_6::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_7::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_8::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_9::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_10::uninit();
	ddf::junkyard::secret_box_controller_2::light_controller::uninit();
	ddf::junkyard::secret_box_controller_2::debouncer_12::uninit();
	ddf::junkyard::secret_box_controller_2::magnetic_lock_1::uninit();
	ddf::junkyard::secret_box_controller_2::magnetic_lock_2::uninit();
	ddf::junkyard::secret_box_controller_2::magnetic_lock_3::uninit();
	ddf::junkyard::secret_box_controller_2::magnetic_lock_4::uninit();

	ddf::junkyard::audio_message_url::uninit();
	ddf::junkyard::comdev_reset::uninit();
	ddf::junkyard::comdev_silence::uninit();
	ddf::junkyard::freezed1::uninit();
	ddf::junkyard::freezed5::uninit();
	ddf::junkyard::gm_help_status::uninit();
	ddf::junkyard::gameend::uninit();
	ddf::junkyard::gamestate::uninit();
	ddf::junkyard::incoming_call::uninit();
	ddf::junkyard::incoming_call_status::uninit();
	ddf::junkyard::paused::uninit();
	ddf::junkyard::restart_game::uninit();
	ddf::junkyard::text_message::uninit();
	ddf::junkyard::text_message_sender::uninit();
	ddf::junkyard::correct_notes::uninit();
	ddf::junkyard::led_timer_start::uninit();
	ddf::junkyard::lock_pick_1_pressed::uninit();
	ddf::junkyard::lock_pick_2_pressed::uninit();
	ddf::junkyard::timedevent_atmo_1::uninit();
	ddf::junkyard::timedevent_atmo_2::uninit();
	ddf::junkyard::timedevent_atmo_3::uninit();
	ddf::junkyard::timedevent_atmo_4::uninit();
	ddf::junkyard::timedevent_atmo_5::uninit();
	ddf::junkyard::timedevent_atmo_6::uninit();
	ddf::junkyard::timedevent_pc_1::uninit();
	ddf::junkyard::timedevent_pc_2::uninit();

	ddf::junkyard::room_1_content::chord::uninit();
	ddf::junkyard::room_1_content::progress::uninit();
	ddf::junkyard::room_1_content::atmo_blacky::uninit();
	ddf::junkyard::room_1_content::atmo_junkyard::uninit();
	ddf::junkyard::room_1_content::atmo_telephone::uninit();
	ddf::junkyard::room_1_content::piano_a1::uninit();
	ddf::junkyard::room_1_content::piano_b1::uninit();
	ddf::junkyard::room_1_content::piano_c1::uninit();
	ddf::junkyard::room_1_content::piano_c2::uninit();
	ddf::junkyard::room_1_content::piano_d1::uninit();
	ddf::junkyard::room_1_content::piano_d2::uninit();
	ddf::junkyard::room_1_content::piano_e1::uninit();
	ddf::junkyard::room_1_content::piano_f1::uninit();
	ddf::junkyard::room_1_content::piano_g1::uninit();
	ddf::junkyard::room_1_content::careful::uninit();
	ddf::junkyard::room_1_content::gminc::uninit();
	ddf::junkyard::room_1_content::rules::uninit();
	ddf::junkyard::room_1_content::techdiff::uninit();
	ddf::junkyard::room_1_content::event_1::uninit();
	ddf::junkyard::room_1_content::event_2::uninit();
	ddf::junkyard::room_1_content::event_3::uninit();
	ddf::junkyard::room_1_content::event_4::uninit();
	ddf::junkyard::room_1_content::event_5::uninit();
	ddf::junkyard::room_1::uninit();
	ddf::junkyard::room_2_content::chord::uninit();
	ddf::junkyard::room_2_content::progress::uninit();
	ddf::junkyard::room_2_content::atmo_blacky::uninit();
	ddf::junkyard::room_2_content::atmo_junkyard::uninit();
	ddf::junkyard::room_2_content::atmo_telephone::uninit();
	ddf::junkyard::room_2_content::piano_a1::uninit();
	ddf::junkyard::room_2_content::piano_b1::uninit();
	ddf::junkyard::room_2_content::piano_c1::uninit();
	ddf::junkyard::room_2_content::piano_c2::uninit();
	ddf::junkyard::room_2_content::piano_d1::uninit();
	ddf::junkyard::room_2_content::piano_d2::uninit();
	ddf::junkyard::room_2_content::piano_e1::uninit();
	ddf::junkyard::room_2_content::piano_f1::uninit();
	ddf::junkyard::room_2_content::piano_g1::uninit();
	ddf::junkyard::room_2_content::careful::uninit();
	ddf::junkyard::room_2_content::gminc::uninit();
	ddf::junkyard::room_2_content::rules::uninit();
	ddf::junkyard::room_2_content::techdiff::uninit();
	ddf::junkyard::room_2_content::event_1::uninit();
	ddf::junkyard::room_2_content::event_2::uninit();
	ddf::junkyard::room_2_content::event_3::uninit();
	ddf::junkyard::room_2_content::event_4::uninit();
	ddf::junkyard::room_2_content::event_5::uninit();
	ddf::junkyard::room_2::uninit();


	ddf::junkyard::freezetimer1::uninit();
	ddf::junkyard::freezetimer5::uninit();
	ddf::junkyard::gametimer::uninit();
	ddf::junkyard::relock_timer::uninit();
	ddf::junkyard::timedevent_atmo_1_timer::uninit();
	ddf::junkyard::timedevent_atmo_2_timer::uninit();
	ddf::junkyard::timedevent_atmo_3_timer::uninit();
	ddf::junkyard::timedevent_atmo_4_timer::uninit();
	ddf::junkyard::timedevent_atmo_5_timer::uninit();
	ddf::junkyard::timedevent_atmo_6_timer::uninit();
	ddf::junkyard::timedevent_pc_1_timer::uninit();
	ddf::junkyard::timedevent_pc_2_timer::uninit();

	ddf::service::statustimertick::uninit();


	ddf::service::servercpustatus::uninit();
	ddf::service::servermemorystatus::uninit();
	ddf::service::servernetworkstatus::uninit();
	ddf::service::serverstoragestatus::uninit();



	ddf::service::statustimer::uninit();

}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
template<typename T>
bool set_property(const std::string &x)
{
	if(T::config::name == x)
	{
		typedef typename T::value_type Tv;
		typedef typename std::conditional<std::is_same<Tv,uint8_t>::value,uint16_t,Tv>::type Td;
		Td v;
		std::cin >> v;
		if(!std::cin.good())
		{
			std::string y;
			std::cin >> y;
			std::cout << "\e[31;01m[NOK]\e[0m Invalid value `"<<y<<"'" << std::endl;
		}
		else
		{
			T::value((Tv)v);
			std::cout << "\e[32;01m[OK]\e[0m " << v << std::endl;
		}

		return true;
	}

	else
		return false;
}

template<typename T>
bool get_property(const std::string &x)
{
	if(T::config::name == x)
	{
		typedef typename T::value_type Tv;
		typedef typename std::conditional<std::is_same<Tv,uint8_t>::value,uint16_t,Tv>::type Td;
		Td v = T::value();
		std::cout << "\e[32;01m[OK]\e[0m " << v << std::endl;
		return true;
	}

	else
		return false;
}


template<typename T>
bool set_peripheral(const std::string &x)
{
	if(T::config::name == x)
	{
		typedef typename T::value_type Tv;
		typedef typename std::conditional<std::is_same<Tv,uint8_t>::value,uint16_t,Tv>::type Td;
		Td v;
		std::cin >> v;
		if(!std::cin.good())
		{
			std::string y;
			std::cin >> y;
			std::cout << "\e[31;01m[NOK]\e[0m Invalid value `"<<y<<"'" << std::endl;
		}
		else
			std::cout << "\e[32;01m[OK]\e[0m " << (Td)(Tv)(typename T::value((Tv)v)) << std::endl;

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
		typedef typename T::value_type Tv;
		typename std::conditional<std::is_same<Tv,uint8_t>::value,uint16_t,Tv>::type v = (typename T::value_type)typename T::value();
		std::cout << "\e[32;01m[OK]\e[0m " << v << std::endl;
		return true;
	}

	else
		return false;
}

template<typename T>
void rex_table_sensor_change()
{ std::cout << T::config::name << " " << (int)typename T::value() << std::endl; }

template<typename T>
void add_print_event()
{ T::value::on_change += rex_table_sensor_change<T>; }

template<typename T>
void set1()
{ typename T::value(true); }

void knock()
{
	std::cout << "knock" << std::endl;
}

int main()
{
	journal::init();

	alsa_host::init();

	process::sql_executor::init();

	wicc_earpc::init();

	dm::init();

	init();
	ddf::service::statustimer::start();

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::value::on_change += knock;

	add_print_event<ddf::pirate::rex_flipper_controller::photosensor_1>();
	add_print_event<ddf::pirate::rex_flipper_controller::photosensor_2>();
	add_print_event<ddf::pirate::rex_flipper_controller::photosensor_3>();
	add_print_event<ddf::pirate::rex_flipper_controller::photosensor_4>();
	add_print_event<ddf::pirate::rex_flipper_controller::photosensor_5>();
	add_print_event<ddf::pirate::rex_flipper_controller::photosensor_6>();
	add_print_event<ddf::pirate::rex_flipper_controller::photosensor_7>();

	set1<ddf::pirate::rex_flipper_controller::light_controller_1>();
	set1<ddf::pirate::rex_flipper_controller::light_controller_2>();
	set1<ddf::pirate::rex_flipper_controller::light_controller_3>();
	set1<ddf::pirate::rex_flipper_controller::light_controller_4>();
	set1<ddf::pirate::rex_flipper_controller::light_controller_5>();
	set1<ddf::pirate::rex_flipper_controller::light_controller_6>();
	set1<ddf::pirate::rex_flipper_controller::light_controller_7>();



	std::string x;
	while(true)
	{

		std::cin >> x;
		if(x == "exit")
			break;

		else if(x == "buzz")
		{
			uint16_t freq,len;
			std::cin >> freq;
			std::cin >> len;
			ddf::pirate::cashier_laser_controller::buzzer::value(tone_t(freq,len));
		}

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

		else if(x=="ledon")
			ddf::junkyard::secret_box_controller_1::addressable_led::enabled(true);

		else if(x=="ledoff")
			ddf::junkyard::secret_box_controller_1::addressable_led::enabled(false);

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
			if(get_peripheral<ddf::pirate::entrance_hanger_controller::debouncer>(x)) continue;
			if(get_peripheral<ddf::pirate::entrance_hanger_controller::magnetic_sensor>(x)) continue;
			if(get_peripheral<ddf::pirate::entrance_hanger_controller::debouncer_2>(x)) continue;
			if(get_property<ddf::pirate::restart_game>(x)) continue;
			if(get_property<ddf::pirate::gm_help_status>(x)) continue;
			if(get_property<ddf::pirate::incoming_call>(x)) continue;
			if(get_property<ddf::pirate::incoming_call_status>(x)) continue;
			if(get_property<ddf::pirate::text_message>(x)) continue;
			if(get_property<ddf::pirate::text_message_sender>(x)) continue;
			if(get_property<ddf::pirate::comdev_reset>(x)) continue;
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
			if(get_property<ddf::magician::restart_game>(x)) continue;
			if(get_property<ddf::magician::gm_help_status>(x)) continue;
			if(get_property<ddf::magician::incoming_call>(x)) continue;
			if(get_property<ddf::magician::incoming_call_status>(x)) continue;
			if(get_property<ddf::magician::text_message>(x)) continue;
			if(get_property<ddf::magician::text_message_sender>(x)) continue;
			if(get_property<ddf::magician::comdev_reset>(x)) continue;
//			if(get_peripheral<ddf::villa::safe_controller::pin_pad>(x)) continue;
			if(get_peripheral<ddf::villa::safe_controller::debouncer_1>(x)) continue;
			if(get_peripheral<ddf::villa::safe_controller::debouncer_2>(x)) continue;
			if(get_peripheral<ddf::villa::desk_controller::debouncer_3>(x)) continue;
			if(get_peripheral<ddf::villa::desk_controller::debouncer_4>(x)) continue;
			if(get_peripheral<ddf::villa::control_room_controller::switch_1>(x)) continue;
			if(get_peripheral<ddf::villa::control_room_controller::debouncer_1>(x)) continue;
			if(get_peripheral<ddf::villa::entrance_controller::debouncer>(x)) continue;
			if(get_peripheral<ddf::villa::entrance_controller::magnetic_sensor>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::started>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::shutdown>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::logged_in>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::recycled_restore>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::audioplay_started>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::audioplay_finished>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::audioplay_paused>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::restart_game>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::audioplay_startevent>(x)) continue;
			if(get_property<ddf::villa::desktop_pc::audiopause_pauseevent>(x)) continue;
			if(get_property<ddf::villa::video_device::started>(x)) continue;
			if(get_property<ddf::villa::video_device::shutdown>(x)) continue;
			if(get_property<ddf::villa::video_device::livecam_started>(x)) continue;
			if(get_property<ddf::villa::video_device::livecamslides_started>(x)) continue;
			if(get_property<ddf::villa::video_device::restart_game>(x)) continue;
			if(get_property<ddf::villa::video_device::start_livecams>(x)) continue;
			if(get_property<ddf::villa::video_device::stop_livecams>(x)) continue;
			if(get_property<ddf::villa::video_device::start_tape>(x)) continue;
			if(get_property<ddf::villa::video_device::stop_tape>(x)) continue;
			if(get_property<ddf::villa::video_device::enabled>(x)) continue;
			if(get_property<ddf::villa::video_device::casette_id>(x)) continue;
			if(get_property<ddf::villa::video_device::play_ongoing>(x)) continue;
			if(get_property<ddf::villa::video_device::livecam_ongoing>(x)) continue;
			if(get_property<ddf::villa::restart_game>(x)) continue;
			if(get_property<ddf::villa::gm_help_status>(x)) continue;
			if(get_property<ddf::villa::incoming_call>(x)) continue;
			if(get_property<ddf::villa::incoming_call_status>(x)) continue;
			if(get_property<ddf::villa::text_message>(x)) continue;
			if(get_property<ddf::villa::text_message_sender>(x)) continue;
			if(get_property<ddf::villa::comdev_reset>(x)) continue;
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
			if(get_property<ddf::junkyard::restart_game>(x)) continue;
			if(get_property<ddf::junkyard::gm_help_status>(x)) continue;
			if(get_property<ddf::junkyard::incoming_call>(x)) continue;
			if(get_property<ddf::junkyard::incoming_call_status>(x)) continue;
			if(get_property<ddf::junkyard::text_message>(x)) continue;
			if(get_property<ddf::junkyard::text_message_sender>(x)) continue;
			if(get_property<ddf::junkyard::comdev_reset>(x)) continue;
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
			if(set_peripheral<ddf::pirate::rex_flipper_controller::led>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1>(x)) continue;
			if(set_peripheral<ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2>(x)) continue;
			if(set_property<ddf::pirate::restart_game>(x)) continue;
			if(set_property<ddf::pirate::gm_help_status>(x)) continue;
			if(set_property<ddf::pirate::incoming_call>(x)) continue;
			if(set_property<ddf::pirate::incoming_call_status>(x)) continue;
			if(set_property<ddf::pirate::text_message>(x)) continue;
			if(set_property<ddf::pirate::text_message_sender>(x)) continue;
			if(set_property<ddf::pirate::comdev_reset>(x)) continue;
			if(set_peripheral<ddf::pirate::entrance_hanger_controller::led>(x)) continue;
			if(set_peripheral<ddf::magician::cupboard_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::magician::cupboard_controller::led_strip>(x)) continue;
			if(set_peripheral<ddf::magician::design_board_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::magician::futuristic_safe_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::magician::futuristic_safe_controller::addressable_led_strip>(x)) continue;
			if(set_peripheral<ddf::magician::entrance_controller::led>(x)) continue;
			if(set_property<ddf::magician::restart_game>(x)) continue;
			if(set_property<ddf::magician::gm_help_status>(x)) continue;
			if(set_property<ddf::magician::incoming_call>(x)) continue;
			if(set_property<ddf::magician::incoming_call_status>(x)) continue;
			if(set_property<ddf::magician::text_message>(x)) continue;
			if(set_property<ddf::magician::text_message_sender>(x)) continue;
			if(set_property<ddf::magician::comdev_reset>(x)) continue;
			if(set_peripheral<ddf::villa::safe_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::villa::control_room_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::villa::entrance_controller::led>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::started>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::shutdown>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::logged_in>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::recycled_restore>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::audioplay_started>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::audioplay_finished>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::audioplay_paused>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::restart_game>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::audioplay_startevent>(x)) continue;
			if(set_property<ddf::villa::desktop_pc::audiopause_pauseevent>(x)) continue;
			if(set_property<ddf::villa::restart_game>(x)) continue;
			if(set_property<ddf::villa::gm_help_status>(x)) continue;
			if(set_property<ddf::villa::incoming_call>(x)) continue;
			if(set_property<ddf::villa::incoming_call_status>(x)) continue;
			if(set_property<ddf::villa::text_message>(x)) continue;
			if(set_property<ddf::villa::text_message_sender>(x)) continue;
			if(set_property<ddf::villa::comdev_reset>(x)) continue;
			if(set_property<ddf::villa::video_device::started>(x)) continue;
			if(set_property<ddf::villa::video_device::shutdown>(x)) continue;
			if(set_property<ddf::villa::video_device::livecam_started>(x)) continue;
			if(set_property<ddf::villa::video_device::livecamslides_started>(x)) continue;
			if(set_property<ddf::villa::video_device::restart_game>(x)) continue;
			if(set_property<ddf::villa::video_device::start_livecams>(x)) continue;
			if(set_property<ddf::villa::video_device::stop_livecams>(x)) continue;
			if(set_property<ddf::villa::video_device::start_tape>(x)) continue;
			if(set_property<ddf::villa::video_device::stop_tape>(x)) continue;
			if(set_property<ddf::villa::video_device::enabled>(x)) continue;
			if(set_property<ddf::villa::video_device::casette_id>(x)) continue;
			if(set_property<ddf::villa::video_device::play_ongoing>(x)) continue;
			if(set_property<ddf::villa::video_device::livecam_ongoing>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_1::magnetic_lock_1>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_1::magnetic_lock_2>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_1::magnetic_lock_3>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_1::magnetic_lock_4>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_1::addressable_led>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::light_controller>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::magnetic_lock_1>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::magnetic_lock_2>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::magnetic_lock_3>(x)) continue;
			if(set_peripheral<ddf::junkyard::secret_box_controller_2::magnetic_lock_4>(x)) continue;
//			if(set_peripheral<ddf::junkyard::secret_box_controller_2::spare_out1>(x)) continue;
//			if(set_peripheral<ddf::junkyard::secret_box_controller_2::spare_out2>(x)) continue;
			if(set_peripheral<ddf::junkyard::entrance_controller::led>(x)) continue;
			if(set_property<ddf::junkyard::restart_game>(x)) continue;
			if(set_property<ddf::junkyard::gm_help_status>(x)) continue;
			if(set_property<ddf::junkyard::incoming_call>(x)) continue;
			if(set_property<ddf::junkyard::incoming_call_status>(x)) continue;
			if(set_property<ddf::junkyard::text_message>(x)) continue;
			if(set_property<ddf::junkyard::text_message_sender>(x)) continue;
			if(set_property<ddf::junkyard::comdev_reset>(x)) continue;

			std::cout << "\e[31;01m[NOK]\e[0m No such peripheral" << std::endl;
		}
		else if(x == "game")
		{
			std::string game,action;
			std::cin >> game;
			std::cin >> action;

			uint8_t gamestate=0xff;
			if(action == "start")
				gamestate = 1;

			else if(action == "stop")
				gamestate = 0;

			else if(action == "gametime")
			{
				uint64_t t = 0xff;
				if(game == "pirate")
					t = ddf::pirate::gametimer::value();
				else if(game == "magician")
					t = ddf::magician::gametimer::value();
				else if(game == "villa")
					t = ddf::villa::gametimer::value();
				else if(game == "junkyard")
					t = ddf::junkyard::gametimer::value();
				else
				{
					std::cout << "\e[31;01m[NOK]\e[0m No such game" << std::endl;
					continue;
				}
				std::cout << "\e[32;01m[OK]\e[0m " << std::dec << t << std::endl;
				continue;
			}

			else
			{
				std::cout << "\e[31;01m[NOK]\e[0m No such action for a game" << std::endl;
				continue;
			}

			if(game == "pirate")
				ddf::pirate::gamestate::value(gamestate);
			else if(game == "magician")
				ddf::magician::gamestate::value(gamestate);
			else if(game == "villa")
				ddf::villa::gamestate::value(gamestate);
			else if(game == "junkyard")
				ddf::junkyard::gamestate::value(gamestate);
			else
			{
				std::cout << "\e[31;01m[NOK]\e[0m No such game" << std::endl;
				continue;
			}
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
/*			if(x == "devices")
			{
				for(auto i : dm::roles())
				{
					std::string sstate;
					const uint8_t state = i.second->get_health();

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
			else*/
				std::cout << "\e[31;01m[NOK]\e[0m No such thing to show" << std::endl;
		}

		else if(x == "journal")
		{
			std::cin >> x;
			if(x == "domains")
			{
				for(const auto &i : journal::get_domains())
					std::cout << i << std::endl;
				std::cout << "\e[32;01m[OK]\e[0m" << std::endl;
				
			}
			else if(x == "get")
			{
				std::cin >> x;
				std::cout << "\e[32;01m[OK]\e[0m " << (uint16_t)journal::domain_level(x)<< std::endl;
			}
			else if(x == "set")
			{
				uint16_t i;
				std::cin >> x;
				std::cin >> i;
				if(!std::cin.good())
				{
					std::string y;
					std::cin >> y;
					std::cout << "\e[31;01m[NOK]\e[0m Invalid value `"<<y<<"'" << std::endl;
				}
				else
				{
					journal::domain_level(x,i);
					std::cout << "\e[32;01m[OK]\e[0m"<< std::endl;
				}
			}
			else if(x == "setall")
			{
				uint16_t i;
				std::cin >> i;
				if(!std::cin.good())
				{
					std::string y;
					std::cin >> y;
					std::cout << "\e[31;01m[NOK]\e[0m Invalid value `"<<y<<"'" << std::endl;
				}
				else
				{
					for(const auto &d : journal::get_domains())
						journal::domain_level(d,i);
					std::cout << "\e[32;01m[OK]\e[0m"<< std::endl;
				}
			}
			else
				std::cout << "\e[31;01m[NOK]\e[0m No such thing for journal" << std::endl;
		
		}
		else
			std::cout << "\e[31;01m[NOK]\e[0m Bullshit, I can't hear you" << std::endl;
	}

	uninit();

	journal::uninit();
	return 0;
}

