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
#include <device_role.h>
#include <process/sql_executor.h>
#include <devman/devman.h>

#include <status.h>
#include <event.h>

#include <audio.h>
#include <audio_effect.h>
#include <audio_speech.h>
#include <timer.h>

#include <peripheral/addressable_led_strip.h>
#include <peripheral/gpio_input.h>
#include <peripheral/gpio_output.h>
#include <peripheral/pin_pad.h>
#include <peripheral/pwm_output.h>
#include <peripheral/rfid.h>
#include <peripheral/text_display.h>
#include <peripheral/voltage_level.h>


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

			}

			/// entrance_hanger_controller
			namespace entrance_hanger_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - pirate - entrance_hanger_controller";
					static const uint32_t cfg_class_id = 0x100060;
				};
				typedef wic::device_role<device_role_config> device_role;

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

			}

			/// ghostbox_picture_laser_boat_wheel_controller
			namespace ghostbox_picture_laser_boat_wheel_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - pirate - ghostbox_picture_laser_boat_wheel_controller";
					static const uint32_t cfg_class_id = 0x100050;
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

			}

			/// map_controller
			namespace map_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - pirate - map_controller";
					static const uint32_t cfg_class_id = 0x100010;
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

			}

			/// rex_flipper_controller
			namespace rex_flipper_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - pirate - rex_flipper_controller";
					static const uint32_t cfg_class_id = 0x100040;
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
				struct led_config : public property_config_base
				{
					constexpr static const char *name = "ddf::pirate::rex_flipper_controller::led";
					static const uint32_t cfg_class_id = 0x100040;
					static const uint32_t cfg_member_id = 0x110;
					static const uint32_t cfg_cooldown_time = 50;
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

			}


			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::freezed1";
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
				constexpr static const char *name = "ddf::pirate::freezed5";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0xb0;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed5_config> freezed5;

			/// GM Help Status ///
			struct gm_help_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::gm_help_status";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x180;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gm_help_status_config> gm_help_status;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::gamestate";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gamestate_config> gamestate;

			/// Incoming Call ///
			struct incoming_call_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::incoming_call";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x190;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<incoming_call_config> incoming_call;

			/// Incoming Call Status ///
			struct incoming_call_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::incoming_call_status";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x1a0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<incoming_call_status_config> incoming_call_status;

			/// Restart Game ///
			struct restart_game_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::restart_game";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x170;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<restart_game_config> restart_game;

			/// timedevent_test ///
			struct timedevent_test_config : public property_config_base
			{
				constexpr static const char *name = "ddf::pirate::timedevent_test";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x1c0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<timedevent_test_config> timedevent_test;


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

			/// timedevent_test_timer
			struct timedevent_test_timer_config
			{
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1d0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_test_timer_config> timedevent_test_timer;



			/// Freeze 1 Start ///		
			struct freeze_1_start_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x110;
				static bool cfg_condition()
				{
									typedef typename pirate::freezed1 fr;
				typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::gamestate gs;

					return (true && ( fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename pirate::freezed1 fr;
				typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::gamestate gs;

					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			};
			typedef wic::event<freeze_1_start_config> freeze_1_start;

			/// Freeze 1 Stop ///		
			struct freeze_1_stop_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x120;
				static bool cfg_condition()
				{
									typedef typename pirate::freezed1 fr;
				typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::gamestate gs;

					return (true && ( !fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename pirate::freezed1 fr;
				typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::gamestate gs;

					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			};
			typedef wic::event<freeze_1_stop_config> freeze_1_stop;

			/// Freeze 1 Timeout ///		
			struct freeze_1_timeout_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x130;
				static bool cfg_condition()
				{
									typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::freezed1 fr;

					return (true && ( tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename pirate::freezetimer1 tmr;
				typedef typename pirate::freezed1 fr;

					(void)0; { fr::value(false); }
				}
			};
			typedef wic::event<freeze_1_timeout_config> freeze_1_timeout;

			/// Freeze 5 Start ///		
			struct freeze_5_start_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x140;
				static bool cfg_condition()
				{
									typedef typename pirate::freezed5 fr;
				typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::gamestate gs;

					return (true && ( fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename pirate::freezed5 fr;
				typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::gamestate gs;

					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			};
			typedef wic::event<freeze_5_start_config> freeze_5_start;

			/// Freeze 5 Stop ///		
			struct freeze_5_stop_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x150;
				static bool cfg_condition()
				{
									typedef typename pirate::freezed5 fr;
				typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::gamestate gs;

					return (true && ( !fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename pirate::freezed5 fr;
				typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::gamestate gs;

					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			};
			typedef wic::event<freeze_5_stop_config> freeze_5_stop;

			/// Freeze 5 Timeout ///		
			struct freeze_5_timeout_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x160;
				static bool cfg_condition()
				{
									typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::freezed5 fr;

					return (true && ( tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename pirate::freezetimer5 tmr;
				typedef typename pirate::freezed5 fr;

					(void)0; { fr::value(false); }
				}
			};
			typedef wic::event<freeze_5_timeout_config> freeze_5_timeout;

			/// Game Timer Expired ///		
			struct game_timer_expired_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0xf0;
				static bool cfg_condition()
				{
									typedef typename pirate::gametimer tmr;
				typedef typename pirate::gamestate gs;

					return (true && ( tmr::value() >= 3600 ));
				}
				static void cfg_action()
				{
									typedef typename pirate::gametimer tmr;
				typedef typename pirate::gamestate gs;

					(void)0; { gs::value(3); }
				}
			};
			typedef wic::event<game_timer_expired_config> game_timer_expired;

			/// gameevent_Game State Changed ///		
			struct gameevent_game_state_changed_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x100;
				static bool cfg_condition()
				{
									typedef typename pirate::gametimer tmr;
				typedef typename pirate::gamestate gs;
				typedef typename pirate::freezed1 fr1;
				typedef typename pirate::freezed5 fr5;

					return (true);
				}
				static void cfg_action()
				{
									typedef typename pirate::gametimer tmr;
				typedef typename pirate::gamestate gs;
				typedef typename pirate::freezed1 fr1;
				typedef typename pirate::freezed5 fr5;

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
			};
			typedef wic::event<gameevent_game_state_changed_config> gameevent_game_state_changed;

			/// rotation_update ///		
			struct rotation_update_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1b0;
				static bool cfg_condition()
				{
									typedef typename pirate::map_controller::led_strip starlight;
				typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer potentiometer;

					return (true);
				}
				static void cfg_action()
				{
									typedef typename pirate::map_controller::led_strip starlight;
				typedef typename pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer potentiometer;

					(void)0; { 
        const uint16_t v = (potentiometer::value()>>5)+1;
        starlight::value(v*v);
       }
				}
			};
			typedef wic::event<rotation_update_config> rotation_update;

			/// timedevent_test_event_finished ///		
			struct timedevent_test_event_finished_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1e0;
				static bool cfg_condition()
				{
									typedef typename pirate::timedevent_test at;
				typedef typename pirate::timedevent_test_timer tmr;

					return (true && ( at::value() <= tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename pirate::timedevent_test at;
				typedef typename pirate::timedevent_test_timer tmr;

					(void)0; { 
	 tmr::value(at::value());
         tmr::stop();
        }
				}
			};
			typedef wic::event<timedevent_test_event_finished_config> timedevent_test_event_finished;

			/// timedevent_test_event_gamestate ///		
			struct timedevent_test_event_gamestate_config
			{
				static const uint32_t cfg_class_id = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x1f0;
				static bool cfg_condition()
				{
									typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_test_timer tmr;

					return (true);
				}
				static void cfg_action()
				{
									typedef typename pirate::gamestate gs;
				typedef typename pirate::timedevent_test_timer tmr;

					(void)0; { 
       	 if(gs::value() == 1)
	 	tmr::start();
	 else
	 	tmr::stop();
        }
				}
			};
			typedef wic::event<timedevent_test_event_gamestate_config> timedevent_test_event_gamestate;
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

			}

			/// design_board_controller
			namespace design_board_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - magician - design_board_controller";
					static const uint32_t cfg_class_id = 0x200020;
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

			}

			/// entrance_controller
			namespace entrance_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - magician - entrance_controller";
					static const uint32_t cfg_class_id = 0x200040;
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

			}

			/// futuristic_safe_controller
			namespace futuristic_safe_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - magician - futuristic_safe_controller";
					static const uint32_t cfg_class_id = 0x200030;
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

			}


			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::freezed1";
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
				constexpr static const char *name = "ddf::magician::freezed5";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed5_config> freezed5;

			/// GM Help Status ///
			struct gm_help_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::gm_help_status";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x160;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gm_help_status_config> gm_help_status;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::gamestate";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x70;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gamestate_config> gamestate;

			/// Incoming Call ///
			struct incoming_call_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::incoming_call";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x170;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<incoming_call_config> incoming_call;

			/// Incoming Call Status ///
			struct incoming_call_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::incoming_call_status";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x180;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<incoming_call_status_config> incoming_call_status;

			/// Restart Game ///
			struct restart_game_config : public property_config_base
			{
				constexpr static const char *name = "ddf::magician::restart_game";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x2ffff0;
				static const uint32_t cfg_member_id          = 0x150;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<restart_game_config> restart_game;


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



			/// Freeze 1 Start ///		
			struct freeze_1_start_config
			{
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0xf0;
				static bool cfg_condition()
				{
									typedef typename magician::freezed1 fr;
				typedef typename magician::freezetimer1 tmr;
				typedef typename magician::gamestate gs;

					return (true && ( fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename magician::freezed1 fr;
				typedef typename magician::freezetimer1 tmr;
				typedef typename magician::gamestate gs;

					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			};
			typedef wic::event<freeze_1_start_config> freeze_1_start;

			/// Freeze 1 Stop ///		
			struct freeze_1_stop_config
			{
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x100;
				static bool cfg_condition()
				{
									typedef typename magician::freezed1 fr;
				typedef typename magician::freezetimer1 tmr;
				typedef typename magician::gamestate gs;

					return (true && ( !fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename magician::freezed1 fr;
				typedef typename magician::freezetimer1 tmr;
				typedef typename magician::gamestate gs;

					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			};
			typedef wic::event<freeze_1_stop_config> freeze_1_stop;

			/// Freeze 1 Timeout ///		
			struct freeze_1_timeout_config
			{
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x110;
				static bool cfg_condition()
				{
									typedef typename magician::freezetimer1 tmr;
				typedef typename magician::freezed1 fr;

					return (true && ( tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename magician::freezetimer1 tmr;
				typedef typename magician::freezed1 fr;

					(void)0; { fr::value(false); }
				}
			};
			typedef wic::event<freeze_1_timeout_config> freeze_1_timeout;

			/// Freeze 5 Start ///		
			struct freeze_5_start_config
			{
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x120;
				static bool cfg_condition()
				{
									typedef typename magician::freezed5 fr;
				typedef typename magician::freezetimer5 tmr;
				typedef typename magician::gamestate gs;

					return (true && ( fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename magician::freezed5 fr;
				typedef typename magician::freezetimer5 tmr;
				typedef typename magician::gamestate gs;

					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			};
			typedef wic::event<freeze_5_start_config> freeze_5_start;

			/// Freeze 5 Stop ///		
			struct freeze_5_stop_config
			{
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x130;
				static bool cfg_condition()
				{
									typedef typename magician::freezed5 fr;
				typedef typename magician::freezetimer5 tmr;
				typedef typename magician::gamestate gs;

					return (true && ( !fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename magician::freezed5 fr;
				typedef typename magician::freezetimer5 tmr;
				typedef typename magician::gamestate gs;

					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			};
			typedef wic::event<freeze_5_stop_config> freeze_5_stop;

			/// Freeze 5 Timeout ///		
			struct freeze_5_timeout_config
			{
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x140;
				static bool cfg_condition()
				{
									typedef typename magician::freezetimer5 tmr;
				typedef typename magician::freezed5 fr;

					return (true && ( tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename magician::freezetimer5 tmr;
				typedef typename magician::freezed5 fr;

					(void)0; { fr::value(false); }
				}
			};
			typedef wic::event<freeze_5_timeout_config> freeze_5_timeout;

			/// Game Timer Expired ///		
			struct game_timer_expired_config
			{
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0xd0;
				static bool cfg_condition()
				{
									typedef typename magician::gametimer tmr;
				typedef typename magician::gamestate gs;

					return (true && ( tmr::value() >= 3600 ));
				}
				static void cfg_action()
				{
									typedef typename magician::gametimer tmr;
				typedef typename magician::gamestate gs;

					(void)0; { gs::value(3); }
				}
			};
			typedef wic::event<game_timer_expired_config> game_timer_expired;

			/// cupboard_controller_event_for_labyrinth_task ///		
			struct cupboard_controller_event_for_labyrinth_task_config
			{
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0x190;
				static bool cfg_condition()
				{
									typedef typename magician::cupboard_controller::debouncer debouncer;
				typedef typename magician::cupboard_controller::magnetic_lock magnetic_lock;

					return (true && (  debouncer::value()  ));
				}
				static void cfg_action()
				{
									typedef typename magician::cupboard_controller::debouncer debouncer;
				typedef typename magician::cupboard_controller::magnetic_lock magnetic_lock;

					(void)0; {  magnetic_lock::value(0);  }
				}
			};
			typedef wic::event<cupboard_controller_event_for_labyrinth_task_config> cupboard_controller_event_for_labyrinth_task;

			/// gameevent_Game State Changed ///		
			struct gameevent_game_state_changed_config
			{
				static const uint32_t cfg_class_id = 0x2ffff0;
				static const uint32_t cfg_member_id = 0xe0;
				static bool cfg_condition()
				{
									typedef typename magician::gametimer tmr;
				typedef typename magician::gamestate gs;
				typedef typename magician::freezed1 fr1;
				typedef typename magician::freezed5 fr5;

					return (true);
				}
				static void cfg_action()
				{
									typedef typename magician::gametimer tmr;
				typedef typename magician::gamestate gs;
				typedef typename magician::freezed1 fr1;
				typedef typename magician::freezed5 fr5;

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
			};
			typedef wic::event<gameevent_game_state_changed_config> gameevent_game_state_changed;
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

			}

			/// desk_controller
			namespace desk_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - desk_controller";
					static const uint32_t cfg_class_id = 0x300020;
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

			}

			/// desktop_pc
			namespace desktop_pc
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - desktop_pc";
					static const uint32_t cfg_class_id = 0x300050;
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
				typedef wicp::forward_property<started_config> started;

				/// Shutdown ///
				struct shutdown_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::shutdown";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x20;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<shutdown_config> shutdown;

				/// Logged In ///
				struct logged_in_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::logged_in";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x30;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<logged_in_config> logged_in;

				/// Recycled Restore ///
				struct recycled_restore_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::recycled_restore";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x40;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<recycled_restore_config> recycled_restore;

				/// Audioplay started ///
				struct audioplay_started_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audioplay_started";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x50;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audioplay_started_config> audioplay_started;

				/// Audioplay finished ///
				struct audioplay_finished_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audioplay_finished";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x60;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audioplay_finished_config> audioplay_finished;

				/// Audioplay paused ///
				struct audioplay_paused_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audioplay_paused";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x70;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audioplay_paused_config> audioplay_paused;

				/// Restart Game ///
				struct restart_game_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::restart_game";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x80;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<restart_game_config> restart_game;

				/// Audioplay startevent ///
				struct audioplay_startevent_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audioplay_startevent";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0x90;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audioplay_startevent_config> audioplay_startevent;

				/// Audiopause pauseevent ///
				struct audiopause_pauseevent_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::desktop_pc::audiopause_pauseevent";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300050;
					static const uint32_t cfg_member_id          = 0xa0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<audiopause_pauseevent_config> audiopause_pauseevent;

			}

			/// entrance_controller
			namespace entrance_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - entrance_controller";
					static const uint32_t cfg_class_id = 0x300040;
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

			}

			/// safe_controller
			namespace safe_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - safe_controller";
					static const uint32_t cfg_class_id = 0x300010;
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

			}

			/// video_device
			namespace video_device
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - villa - video_device";
					static const uint32_t cfg_class_id = 0x300060;
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
				typedef wicp::forward_property<started_config> started;

				/// Shutdown ///
				struct shutdown_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::shutdown";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x20;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<shutdown_config> shutdown;

				/// LiveCam started ///
				struct livecam_started_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::livecam_started";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x30;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<livecam_started_config> livecam_started;

				/// LiveCamSlides started ///
				struct livecamslides_started_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::livecamslides_started";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x40;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<livecamslides_started_config> livecamslides_started;

				/// Restart Game ///
				struct restart_game_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::restart_game";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x50;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<restart_game_config> restart_game;

				/// Start LiveCams ///
				struct start_livecams_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::start_livecams";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x60;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<start_livecams_config> start_livecams;

				/// Stop LiveCams ///
				struct stop_livecams_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::stop_livecams";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x70;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<stop_livecams_config> stop_livecams;

				/// Start Tape ///
				struct start_tape_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::start_tape";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x80;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<start_tape_config> start_tape;

				/// Stop Tape ///
				struct stop_tape_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::stop_tape";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0x90;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<stop_tape_config> stop_tape;

				/// enabled ///
				struct enabled_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::enabled";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xa0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<enabled_config> enabled;

				/// casette_id ///
				struct casette_id_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::casette_id";

					typedef uint64_t cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xb0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<casette_id_config> casette_id;

				/// play_ongoing ///
				struct play_ongoing_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::play_ongoing";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xc0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<play_ongoing_config> play_ongoing;

				/// livecam_ongoing ///
				struct livecam_ongoing_config : public property_config_base
				{
					constexpr static const char *name = "ddf::villa::video_device::livecam_ongoing";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x300060;
					static const uint32_t cfg_member_id          = 0xd0;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<livecam_ongoing_config> livecam_ongoing;

			}


			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::freezed1";
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
				constexpr static const char *name = "ddf::villa::freezed5";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0xb0;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed5_config> freezed5;

			/// GM Help Status ///
			struct gm_help_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::gm_help_status";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x180;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gm_help_status_config> gm_help_status;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::gamestate";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gamestate_config> gamestate;

			/// Incoming Call ///
			struct incoming_call_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::incoming_call";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x190;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<incoming_call_config> incoming_call;

			/// Incoming Call Status ///
			struct incoming_call_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::incoming_call_status";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x1a0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<incoming_call_status_config> incoming_call_status;

			/// Restart Game ///
			struct restart_game_config : public property_config_base
			{
				constexpr static const char *name = "ddf::villa::restart_game";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x3ffff0;
				static const uint32_t cfg_member_id          = 0x170;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<restart_game_config> restart_game;


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

			/// eject_wait
			struct eject_wait_config
			{
				static const uint32_t cfg_class_id  = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1b0;
				static const uint32_t cfg_interval  = 400;
			};
			typedef typename wic::timer<eject_wait_config> eject_wait;



			/// Freeze 1 Start ///		
			struct freeze_1_start_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x110;
				static bool cfg_condition()
				{
									typedef typename villa::freezed1 fr;
				typedef typename villa::freezetimer1 tmr;
				typedef typename villa::gamestate gs;

					return (true && ( fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename villa::freezed1 fr;
				typedef typename villa::freezetimer1 tmr;
				typedef typename villa::gamestate gs;

					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			};
			typedef wic::event<freeze_1_start_config> freeze_1_start;

			/// Freeze 1 Stop ///		
			struct freeze_1_stop_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x120;
				static bool cfg_condition()
				{
									typedef typename villa::freezed1 fr;
				typedef typename villa::freezetimer1 tmr;
				typedef typename villa::gamestate gs;

					return (true && ( !fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename villa::freezed1 fr;
				typedef typename villa::freezetimer1 tmr;
				typedef typename villa::gamestate gs;

					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			};
			typedef wic::event<freeze_1_stop_config> freeze_1_stop;

			/// Freeze 1 Timeout ///		
			struct freeze_1_timeout_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x130;
				static bool cfg_condition()
				{
									typedef typename villa::freezetimer1 tmr;
				typedef typename villa::freezed1 fr;

					return (true && ( tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename villa::freezetimer1 tmr;
				typedef typename villa::freezed1 fr;

					(void)0; { fr::value(false); }
				}
			};
			typedef wic::event<freeze_1_timeout_config> freeze_1_timeout;

			/// Freeze 5 Start ///		
			struct freeze_5_start_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x140;
				static bool cfg_condition()
				{
									typedef typename villa::freezed5 fr;
				typedef typename villa::freezetimer5 tmr;
				typedef typename villa::gamestate gs;

					return (true && ( fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename villa::freezed5 fr;
				typedef typename villa::freezetimer5 tmr;
				typedef typename villa::gamestate gs;

					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			};
			typedef wic::event<freeze_5_start_config> freeze_5_start;

			/// Freeze 5 Stop ///		
			struct freeze_5_stop_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x150;
				static bool cfg_condition()
				{
									typedef typename villa::freezed5 fr;
				typedef typename villa::freezetimer5 tmr;
				typedef typename villa::gamestate gs;

					return (true && ( !fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename villa::freezed5 fr;
				typedef typename villa::freezetimer5 tmr;
				typedef typename villa::gamestate gs;

					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			};
			typedef wic::event<freeze_5_stop_config> freeze_5_stop;

			/// Freeze 5 Timeout ///		
			struct freeze_5_timeout_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x160;
				static bool cfg_condition()
				{
									typedef typename villa::freezetimer5 tmr;
				typedef typename villa::freezed5 fr;

					return (true && ( tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename villa::freezetimer5 tmr;
				typedef typename villa::freezed5 fr;

					(void)0; { fr::value(false); }
				}
			};
			typedef wic::event<freeze_5_timeout_config> freeze_5_timeout;

			/// Game Timer Expired ///		
			struct game_timer_expired_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0xf0;
				static bool cfg_condition()
				{
									typedef typename villa::gametimer tmr;
				typedef typename villa::gamestate gs;

					return (true && ( tmr::value() >= 3600 ));
				}
				static void cfg_action()
				{
									typedef typename villa::gametimer tmr;
				typedef typename villa::gamestate gs;

					(void)0; { gs::value(3); }
				}
			};
			typedef wic::event<game_timer_expired_config> game_timer_expired;

			/// casette_ejection_event ///		
			struct casette_ejection_event_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1d0;
				static bool cfg_condition()
				{
									typedef typename villa::control_room_controller::video_eject eject;
				typedef typename villa::eject_wait eject_wait;

					return (true && (  true /* eject_wait::on_value_change() */  ));
				}
				static void cfg_action()
				{
									typedef typename villa::control_room_controller::video_eject eject;
				typedef typename villa::eject_wait eject_wait;

					(void)0; { 
      eject_wait::stop();
      eject::value(0);
     }
				}
			};
			typedef wic::event<casette_ejection_event_config> casette_ejection_event;

			/// gameevent_Game State Changed ///		
			struct gameevent_game_state_changed_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x100;
				static bool cfg_condition()
				{
									typedef typename villa::gametimer tmr;
				typedef typename villa::gamestate gs;
				typedef typename villa::freezed1 fr1;
				typedef typename villa::freezed5 fr5;

					return (true);
				}
				static void cfg_action()
				{
									typedef typename villa::gametimer tmr;
				typedef typename villa::gamestate gs;
				typedef typename villa::freezed1 fr1;
				typedef typename villa::freezed5 fr5;

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
			};
			typedef wic::event<gameevent_game_state_changed_config> gameevent_game_state_changed;

			/// gameevent_casette_eject_trigger ///		
			struct gameevent_casette_eject_trigger_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1c0;
				static bool cfg_condition()
				{
									typedef typename villa::control_room_controller::debouncer_1 button;
				typedef typename villa::control_room_controller::video_eject eject;
				typedef typename villa::video_device::start_livecams liveCamsStart;
				typedef typename villa::eject_wait eject_wait;

					return (true && (  button::value()  ));
				}
				static void cfg_action()
				{
									typedef typename villa::control_room_controller::debouncer_1 button;
				typedef typename villa::control_room_controller::video_eject eject;
				typedef typename villa::video_device::start_livecams liveCamsStart;
				typedef typename villa::eject_wait eject_wait;

					(void)0; { 
      eject::value(1);
      eject_wait::start();
     }
				}
			};
			typedef wic::event<gameevent_casette_eject_trigger_config> gameevent_casette_eject_trigger;

			/// gameevent_finding_the_keys ///		
			struct gameevent_finding_the_keys_config
			{
				static const uint32_t cfg_class_id = 0x3ffff0;
				static const uint32_t cfg_member_id = 0x1e0;
				static bool cfg_condition()
				{
									typedef typename villa::safe_controller::debouncer_1 switch_1;
				typedef typename villa::safe_controller::debouncer_2 switch_2;
				typedef typename villa::desk_controller::debouncer_3 switch_3;
				typedef typename villa::control_room_controller::magnetic_lock secret_door;

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

					(void)0; {  secret_door::value(0);  }
				}
			};
			typedef wic::event<gameevent_finding_the_keys_config> gameevent_finding_the_keys;
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
				typedef wicp::forward_property<started_config> started;

				/// Shutdown ///
				struct shutdown_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::email_client::shutdown";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x400040;
					static const uint32_t cfg_member_id          = 0x20;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<shutdown_config> shutdown;

				/// Restart Game ///
				struct restart_game_config : public property_config_base
				{
					constexpr static const char *name = "ddf::junkyard::email_client::restart_game";

					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x400040;
					static const uint32_t cfg_member_id          = 0x30;
					static const uint32_t cfg_cooldown_time      = 0;
				};
				typedef wicp::forward_property<restart_game_config> restart_game;

			}

			/// entrance_controller
			namespace entrance_controller
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - junkyard - entrance_controller";
					static const uint32_t cfg_class_id = 0x400030;
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

			}

			/// secret_box_controller_1
			namespace secret_box_controller_1
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - junkyard - secret_box_controller_1";
					static const uint32_t cfg_class_id = 0x400010;
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

			}

			/// secret_box_controller_2
			namespace secret_box_controller_2
			{
				struct device_role_config : public property_config_base
				{
					constexpr static const char *cfg_name = "DDF - junkyard - secret_box_controller_2";
					static const uint32_t cfg_class_id = 0x400020;
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

			}


			/// Freezed1 ///
			struct freezed1_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::freezed1";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x80;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed1_config> freezed1;

			/// Freezed5 ///
			struct freezed5_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::freezed5";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x90;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<freezed5_config> freezed5;

			/// GM Help Status ///
			struct gm_help_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::gm_help_status";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x160;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gm_help_status_config> gm_help_status;

			/// GameState ///
			struct gamestate_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::gamestate";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x70;
				static const uint32_t cfg_cooldown_time      = 1000;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<gamestate_config> gamestate;

			/// Incoming Call ///
			struct incoming_call_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::incoming_call";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x170;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<incoming_call_config> incoming_call;

			/// Incoming Call Status ///
			struct incoming_call_status_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::incoming_call_status";
				typedef uint8_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x180;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<incoming_call_status_config> incoming_call_status;

			/// Restart Game ///
			struct restart_game_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::restart_game";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x150;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<restart_game_config> restart_game;

			/// lock_pick_1_pressed ///
			struct lock_pick_1_pressed_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::lock_pick_1_pressed";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x190;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<lock_pick_1_pressed_config> lock_pick_1_pressed;

			/// lock_pick_2_pressed ///
			struct lock_pick_2_pressed_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::lock_pick_2_pressed";
				typedef bool cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x1a0;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<lock_pick_2_pressed_config> lock_pick_2_pressed;

			/// timedevent_test ///
			struct timedevent_test_config : public property_config_base
			{
				constexpr static const char *name = "ddf::junkyard::timedevent_test";
				typedef uint64_t cfg_value_type;
				static const uint32_t cfg_class_id           = 0x4ffff0;
				static const uint32_t cfg_member_id          = 0x210;
				static const uint32_t cfg_cooldown_time      = 0;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<timedevent_test_config> timedevent_test;


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

					static const uint32_t cfg_class_id = 0x400060;

					static const uint32_t cfg_member_id = 0x20;
				};
				typedef wic::audio_speech<event_1_config> event_1;
				struct event_2_config
				{
					typedef room_1 cfg_audio;

					constexpr static const char *cfg_source = "/usr/share/ddf/junkyard/event_2.wav";

					static const uint32_t cfg_class_id = 0x400060;

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
				static const uint32_t cfg_member_id = 0xb0;
				static const uint32_t cfg_interval  = 3000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0xc0;
				static const uint32_t cfg_interval  = 15000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0xa0;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;

			/// timedevent_test_timer
			struct timedevent_test_timer_config
			{
				static const uint32_t cfg_class_id  = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x220;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<timedevent_test_timer_config> timedevent_test_timer;



			/// Freeze 1 Start ///		
			struct freeze_1_start_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0xf0;
				static bool cfg_condition()
				{
									typedef typename junkyard::freezed1 fr;
				typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::gamestate gs;

					return (true && ( fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::freezed1 fr;
				typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::gamestate gs;

					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			};
			typedef wic::event<freeze_1_start_config> freeze_1_start;

			/// Freeze 1 Stop ///		
			struct freeze_1_stop_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x100;
				static bool cfg_condition()
				{
									typedef typename junkyard::freezed1 fr;
				typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::gamestate gs;

					return (true && ( !fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::freezed1 fr;
				typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::gamestate gs;

					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			};
			typedef wic::event<freeze_1_stop_config> freeze_1_stop;

			/// Freeze 1 Timeout ///		
			struct freeze_1_timeout_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x110;
				static bool cfg_condition()
				{
									typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::freezed1 fr;

					return (true && ( tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::freezetimer1 tmr;
				typedef typename junkyard::freezed1 fr;

					(void)0; { fr::value(false); }
				}
			};
			typedef wic::event<freeze_1_timeout_config> freeze_1_timeout;

			/// Freeze 5 Start ///		
			struct freeze_5_start_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x120;
				static bool cfg_condition()
				{
									typedef typename junkyard::freezed5 fr;
				typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::gamestate gs;

					return (true && ( fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::freezed5 fr;
				typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::gamestate gs;

					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			};
			typedef wic::event<freeze_5_start_config> freeze_5_start;

			/// Freeze 5 Stop ///		
			struct freeze_5_stop_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x130;
				static bool cfg_condition()
				{
									typedef typename junkyard::freezed5 fr;
				typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::gamestate gs;

					return (true && ( !fr::value() ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::freezed5 fr;
				typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::gamestate gs;

					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			};
			typedef wic::event<freeze_5_stop_config> freeze_5_stop;

			/// Freeze 5 Timeout ///		
			struct freeze_5_timeout_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x140;
				static bool cfg_condition()
				{
									typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::freezed5 fr;

					return (true && ( tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::freezetimer5 tmr;
				typedef typename junkyard::freezed5 fr;

					(void)0; { fr::value(false); }
				}
			};
			typedef wic::event<freeze_5_timeout_config> freeze_5_timeout;

			/// Game Timer Expired ///		
			struct game_timer_expired_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0xd0;
				static bool cfg_condition()
				{
									typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::gamestate gs;

					return (true && ( tmr::value() >= 3600 ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::gamestate gs;

					(void)0; { gs::value(3); }
				}
			};
			typedef wic::event<game_timer_expired_config> game_timer_expired;

			/// gameevent_Game State Changed ///		
			struct gameevent_game_state_changed_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0xe0;
				static bool cfg_condition()
				{
									typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::freezed1 fr1;
				typedef typename junkyard::freezed5 fr5;

					return (true);
				}
				static void cfg_action()
				{
									typedef typename junkyard::gametimer tmr;
				typedef typename junkyard::gamestate gs;
				typedef typename junkyard::freezed1 fr1;
				typedef typename junkyard::freezed5 fr5;

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
			};
			typedef wic::event<gameevent_game_state_changed_config> gameevent_game_state_changed;

			/// gameevent_ampmeter_turn_on ///		
			struct gameevent_ampmeter_turn_on_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1f0;
				static bool cfg_condition()
				{
									typedef typename junkyard::secret_box_controller_2::debouncer_10 button;
				typedef typename junkyard::secret_box_controller_2::light_controller indicator;
				typedef typename junkyard::secret_box_controller_2::magnetic_lock_3 lock;

					return (true && (  button::value()  ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::secret_box_controller_2::debouncer_10 button;
				typedef typename junkyard::secret_box_controller_2::light_controller indicator;
				typedef typename junkyard::secret_box_controller_2::magnetic_lock_3 lock;

					(void)0; {  indicator::value(1); lock::value(0);  }
				}
			};
			typedef wic::event<gameevent_ampmeter_turn_on_config> gameevent_ampmeter_turn_on;

			/// gameevent_call_accepted ///		
			struct gameevent_call_accepted_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x260;
				static bool cfg_condition()
				{
									typedef typename junkyard::incoming_call_status cs;

					return (true && ( 2 == cs::value() ));
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
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x270;
				static bool cfg_condition()
				{
									typedef typename junkyard::incoming_call_status cs;

					return (true && ( 3 == cs::value() ));
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
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x280;
				static bool cfg_condition()
				{
									typedef typename junkyard::incoming_call_status cs;

					return (true && ( 4 == cs::value() ));
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
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x290;
				static bool cfg_condition()
				{
									typedef typename junkyard::incoming_call_status cs;

					return (true && ( 5 == cs::value() ));
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
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x250;
				static bool cfg_condition()
				{
									typedef typename junkyard::incoming_call_status cs;

					return (true && ( 1 == cs::value() ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::incoming_call_status cs;

					(void)0;
				}
			};
			typedef wic::event<gameevent_call_ringing_config> gameevent_call_ringing;

			/// gameevent_labirynth_1 ///		
			struct gameevent_labirynth_1_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1c0;
				static bool cfg_condition()
				{
									typedef typename junkyard::secret_box_controller_1::debouncer_5 button;
				typedef typename junkyard::secret_box_controller_1::magnetic_lock_4 lock;

					return (true && (  button::value()  ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::secret_box_controller_1::debouncer_5 button;
				typedef typename junkyard::secret_box_controller_1::magnetic_lock_4 lock;

					(void)0; {  lock::value(0);  }
				}
			};
			typedef wic::event<gameevent_labirynth_1_config> gameevent_labirynth_1;

			/// gameevent_labirynth_2 ///		
			struct gameevent_labirynth_2_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1d0;
				static bool cfg_condition()
				{
									typedef typename junkyard::secret_box_controller_1::debouncer_6 button;
				typedef typename junkyard::secret_box_controller_2::magnetic_lock_1 lock;

					return (true && (  button::value()  ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::secret_box_controller_1::debouncer_6 button;
				typedef typename junkyard::secret_box_controller_2::magnetic_lock_1 lock;

					(void)0; {  lock::value(0);  }
				}
			};
			typedef wic::event<gameevent_labirynth_2_config> gameevent_labirynth_2;

			/// gameevent_labirynth_3 ///		
			struct gameevent_labirynth_3_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1e0;
				static bool cfg_condition()
				{
									typedef typename junkyard::secret_box_controller_1::debouncer_7 button;
				typedef typename junkyard::secret_box_controller_2::magnetic_lock_2 lock;

					return (true && (  button::value()  ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::secret_box_controller_1::debouncer_7 button;
				typedef typename junkyard::secret_box_controller_2::magnetic_lock_2 lock;

					(void)0; {  lock::value(0);  }
				}
			};
			typedef wic::event<gameevent_labirynth_3_config> gameevent_labirynth_3;

			/// gameevent_lockpick_module ///		
			struct gameevent_lockpick_module_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x1b0;
				static bool cfg_condition()
				{
									typedef typename junkyard::secret_box_controller_1::debouncer_2 lock_pick_1;
				typedef typename junkyard::secret_box_controller_1::debouncer_3 lock_pick_2;
				typedef typename junkyard::secret_box_controller_1::debouncer_4 lock_pick_3;
				typedef typename junkyard::secret_box_controller_1::magnetic_lock_3 lock;
				typedef typename junkyard::lock_pick_1_pressed lock_pick_1_pressed;
				typedef typename junkyard::lock_pick_2_pressed lock_pick_2_pressed;

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

					(void)0; {  
      if(lock_pick_1::value())
        lock_pick_1_pressed::value(true);
      else if(lock_pick_2::value())
        lock_pick_2_pressed::value(lock_pick_1_pressed::value());
      else if(lock_pick_3::value())
      { 
        if(lock_pick_1_pressed::value() && lock_pick_2_pressed::value())
          lock::value(0);
        else
        { lock_pick_1_pressed::value(false); lock_pick_2_pressed::value(false); }
      }
     }
				}
			};
			typedef wic::event<gameevent_lockpick_module_config> gameevent_lockpick_module;

			/// gameevent_mona_lisa_rescue ///		
			struct gameevent_mona_lisa_rescue_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x200;
				static bool cfg_condition()
				{
									typedef typename junkyard::secret_box_controller_2::debouncer_12 picture_switch;
				typedef typename junkyard::gamestate gs;

					return (true && (  picture_switch::value()  ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::secret_box_controller_2::debouncer_12 picture_switch;
				typedef typename junkyard::gamestate gs;

					(void)0; {  gs::value(3);  }
				}
			};
			typedef wic::event<gameevent_mona_lisa_rescue_config> gameevent_mona_lisa_rescue;

			/// timedevent_test_event_finished ///		
			struct timedevent_test_event_finished_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x230;
				static bool cfg_condition()
				{
									typedef typename junkyard::timedevent_test at;
				typedef typename junkyard::timedevent_test_timer tmr;
				typedef typename junkyard::incoming_call call;

					return (true && ( at::value() <= tmr::value() ));
				}
				static void cfg_action()
				{
									typedef typename junkyard::timedevent_test at;
				typedef typename junkyard::timedevent_test_timer tmr;
				typedef typename junkyard::incoming_call call;

					(void)0; { 
        tmr::value(at::value());
        tmr::stop();
	call::value(8);
       }
				}
			};
			typedef wic::event<timedevent_test_event_finished_config> timedevent_test_event_finished;

			/// timedevent_test_event_gamestate ///		
			struct timedevent_test_event_gamestate_config
			{
				static const uint32_t cfg_class_id = 0x4ffff0;
				static const uint32_t cfg_member_id = 0x240;
				static bool cfg_condition()
				{
									typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_test at;
				typedef typename junkyard::timedevent_test_timer tmr;

					return (true);
				}
				static void cfg_action()
				{
									typedef typename junkyard::gamestate gs;
				typedef typename junkyard::timedevent_test at;
				typedef typename junkyard::timedevent_test_timer tmr;

					(void)0; { 
      switch(gs::value())
      {
      	// Not started
      	case 0:
      		tmr::stop();
		tmr::reset();
		at::value(300);
      		break;

      	// Started
      	case 1:
      		tmr::start();
      		break;

      	// Paused
      	case 2:
      		tmr::stop();
      		break;

      	// Finished
      	case 3:
      		tmr::stop();
		tmr::reset();
		at::value(300);
      		break;
      }
       }
				}
			};
			typedef wic::event<timedevent_test_event_gamestate_config> timedevent_test_event_gamestate;
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
			typedef wicp::local_property<servercpustatus_config> servercpustatus;

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
			typedef wicp::local_property<servermemorystatus_config> servermemorystatus;

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
			typedef wicp::local_property<servernetworkstatus_config> servernetworkstatus;

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
			typedef wicp::local_property<serverstoragestatus_config> serverstoragestatus;


			/// StatusTimer
			struct statustimer_config
			{
				static const uint32_t cfg_class_id  = 0x5ffff0;
				static const uint32_t cfg_member_id = 0x50;
				static const uint32_t cfg_interval  = 3000;
			};
			typedef typename wic::timer<statustimer_config> statustimer;



			/// StatusTimerTick ///		
			struct statustimertick_config
			{
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
	ddf::pirate::cashier_laser_controller::laser::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::laser::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::cashier_laser_controller::lcd::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::lcd::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::cashier_laser_controller::pin_pad::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::cashier_laser_controller::cash_box::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::cash_box::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::cashier_laser_controller::switch_1::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::cashier_laser_controller::led_strip::init(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::cashier_laser_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::pirate::cashier_laser_controller::device_role::instance());
	ddf::pirate::entrance_hanger_controller::device_role::init();
	ddf::pirate::entrance_hanger_controller::debouncer_1::init(ddf::pirate::entrance_hanger_controller::device_role::instance());
	ddf::pirate::entrance_hanger_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::entrance_hanger_controller::led::init(ddf::pirate::entrance_hanger_controller::device_role::instance());
	ddf::pirate::entrance_hanger_controller::led::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::entrance_hanger_controller::magnetic_sensor::init(ddf::pirate::entrance_hanger_controller::device_role::instance());
	ddf::pirate::entrance_hanger_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::entrance_hanger_controller::debouncer_2::init(ddf::pirate::entrance_hanger_controller::device_role::instance());
	ddf::pirate::entrance_hanger_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::pirate::entrance_hanger_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::init();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::photosensor::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::knock_sensor::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::led_strip_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::init(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::device_role::instance());
	ddf::pirate::map_controller::device_role::init();
	ddf::pirate::map_controller::magnetic_sensor_1::init(ddf::pirate::map_controller::device_role::instance());
	ddf::pirate::map_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::map_controller::magnetic_sensor_2::init(ddf::pirate::map_controller::device_role::instance());
	ddf::pirate::map_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::map_controller::led_strip::init(ddf::pirate::map_controller::device_role::instance());
	ddf::pirate::map_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::pirate::map_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::device_role::init();
	ddf::pirate::rex_flipper_controller::light_controller_1::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::light_controller_2::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::light_controller_3::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::light_controller_4::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_4::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::light_controller_5::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_5::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::light_controller_6::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_6::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::light_controller_7::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::light_controller_7::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::photosensor_1::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::photosensor_2::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::photosensor_3::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::photosensor_4::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_4::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::photosensor_5::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_5::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::photosensor_6::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_6::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::photosensor_7::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::photosensor_7::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::rfid_reader::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::magnetic_lock::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::rex_flipper_controller::led::init(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::rex_flipper_controller::led::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::pirate::rex_flipper_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::device_role::init();
	ddf::pirate::stone_chest_controller::magnetic_sensor_1::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::stone_chest_controller::magnetic_sensor_2::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::stone_chest_controller::magnetic_sensor_3::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::stone_chest_controller::magnetic_sensor_4::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_4::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::stone_chest_controller::magnetic_sensor_5::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_sensor_5::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::stone_chest_controller::magnetic_lock_1::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::stone_chest_controller::magnetic_lock_2::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::stone_chest_controller::led_strip::init(ddf::pirate::stone_chest_controller::device_role::instance());
	ddf::pirate::stone_chest_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::pirate::stone_chest_controller::device_role::instance());

	ddf::pirate::freeze_1_start::init();
	ddf::pirate::freezed1::on_change += ddf::pirate::freeze_1_start::monitor;

	ddf::pirate::freeze_1_start::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::freeze_1_stop::init();
	ddf::pirate::freezed1::on_change += ddf::pirate::freeze_1_stop::monitor;

	ddf::pirate::freeze_1_stop::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::freeze_1_timeout::init();
	ddf::pirate::freezetimer1::on_value_change += ddf::pirate::freeze_1_timeout::monitor;

	ddf::pirate::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::freeze_5_start::init();
	ddf::pirate::freezed5::on_change += ddf::pirate::freeze_5_start::monitor;

	ddf::pirate::freeze_5_start::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::freeze_5_stop::init();
	ddf::pirate::freezed5::on_change += ddf::pirate::freeze_5_stop::monitor;

	ddf::pirate::freeze_5_stop::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::freeze_5_timeout::init();
	ddf::pirate::freezetimer5::on_value_change += ddf::pirate::freeze_5_timeout::monitor;

	ddf::pirate::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::game_timer_expired::init();
	ddf::pirate::gametimer::on_value_change += ddf::pirate::game_timer_expired::monitor;

	ddf::pirate::game_timer_expired::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::gameevent_game_state_changed::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::gameevent_game_state_changed::monitor;

	ddf::pirate::gameevent_game_state_changed::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::rotation_update::init();
	ddf::pirate::ghostbox_picture_laser_boat_wheel_controller::potentiometer::value::on_change += ddf::pirate::rotation_update::monitor;

	ddf::pirate::rotation_update::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::timedevent_test_event_finished::init();
	ddf::pirate::timedevent_test_timer::on_value_change += ddf::pirate::timedevent_test_event_finished::monitor;

	ddf::pirate::timedevent_test_event_finished::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::timedevent_test_event_gamestate::init();
	ddf::pirate::gamestate::on_change += ddf::pirate::timedevent_test_event_gamestate::monitor;

	ddf::pirate::timedevent_test_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::freezed1::init(bool());
	ddf::pirate::freezed1::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::freezed5::init(bool());
	ddf::pirate::freezed5::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::gm_help_status::init(bool());
	ddf::pirate::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::gm_help_status::remote_add(ddf::service::comdev::device_role::instance());
	ddf::pirate::gamestate::init(uint8_t());
	ddf::pirate::gamestate::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::incoming_call::init(uint8_t(0xff));
	ddf::pirate::incoming_call::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::incoming_call::remote_add(ddf::service::comdev::device_role::instance());
	ddf::pirate::incoming_call_status::init(uint8_t());
	ddf::pirate::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance());
	ddf::pirate::restart_game::init(bool());
	ddf::pirate::restart_game::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::pirate::restart_game::remote_add(ddf::service::comdev::device_role::instance());
	ddf::pirate::timedevent_test::init(uint64_t(150));
	ddf::pirate::timedevent_test::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::room_1::init();
	ddf::pirate::room_1_content::chord::init();

	ddf::pirate::room_2::init();
	ddf::pirate::room_2_content::chord::init();


	ddf::pirate::freezetimer1::init();
	ddf::pirate::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::freezetimer5::init();
	ddf::pirate::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::gametimer::init();
	ddf::pirate::gametimer::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::pirate::timedevent_test_timer::init();
	ddf::pirate::timedevent_test_timer::remote_add(ddf::service::gmclient::device_role::instance());


	ddf::magician::cupboard_controller::device_role::init();
	ddf::magician::cupboard_controller::debouncer::init(ddf::magician::cupboard_controller::device_role::instance());
	ddf::magician::cupboard_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::cupboard_controller::magnetic_sensor::init(ddf::magician::cupboard_controller::device_role::instance());
	ddf::magician::cupboard_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::cupboard_controller::magnetic_lock::init(ddf::magician::cupboard_controller::device_role::instance());
	ddf::magician::cupboard_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::cupboard_controller::led_strip::init(ddf::magician::cupboard_controller::device_role::instance());
	ddf::magician::cupboard_controller::led_strip::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::magician::cupboard_controller::device_role::instance());
	ddf::magician::design_board_controller::device_role::init();
	ddf::magician::design_board_controller::linear_magnetic_sensor_1::init(ddf::magician::design_board_controller::device_role::instance());
	ddf::magician::design_board_controller::linear_magnetic_sensor_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::design_board_controller::linear_magnetic_sensor_2::init(ddf::magician::design_board_controller::device_role::instance());
	ddf::magician::design_board_controller::linear_magnetic_sensor_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::design_board_controller::linear_magnetic_sensor_3::init(ddf::magician::design_board_controller::device_role::instance());
	ddf::magician::design_board_controller::linear_magnetic_sensor_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::design_board_controller::magnetic_lock::init(ddf::magician::design_board_controller::device_role::instance());
	ddf::magician::design_board_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::magician::design_board_controller::device_role::instance());
	ddf::magician::entrance_controller::device_role::init();
	ddf::magician::entrance_controller::debouncer::init(ddf::magician::entrance_controller::device_role::instance());
	ddf::magician::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::entrance_controller::led::init(ddf::magician::entrance_controller::device_role::instance());
	ddf::magician::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::entrance_controller::magnetic_sensor::init(ddf::magician::entrance_controller::device_role::instance());
	ddf::magician::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::magician::entrance_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::device_role::init();
	ddf::magician::futuristic_safe_controller::debouncer::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::futuristic_safe_controller::rfid_reader::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::rfid_reader::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::futuristic_safe_controller::pin_pad::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::futuristic_safe_controller::magnetic_lock::init(ddf::magician::futuristic_safe_controller::device_role::instance());
	ddf::magician::futuristic_safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::magician::futuristic_safe_controller::device_role::instance());

	ddf::magician::freeze_1_start::init();
	ddf::magician::freezed1::on_change += ddf::magician::freeze_1_start::monitor;

	ddf::magician::freeze_1_start::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::freeze_1_stop::init();
	ddf::magician::freezed1::on_change += ddf::magician::freeze_1_stop::monitor;

	ddf::magician::freeze_1_stop::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::freeze_1_timeout::init();
	ddf::magician::freezetimer1::on_value_change += ddf::magician::freeze_1_timeout::monitor;

	ddf::magician::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::freeze_5_start::init();
	ddf::magician::freezed5::on_change += ddf::magician::freeze_5_start::monitor;

	ddf::magician::freeze_5_start::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::freeze_5_stop::init();
	ddf::magician::freezed5::on_change += ddf::magician::freeze_5_stop::monitor;

	ddf::magician::freeze_5_stop::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::freeze_5_timeout::init();
	ddf::magician::freezetimer5::on_value_change += ddf::magician::freeze_5_timeout::monitor;

	ddf::magician::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::game_timer_expired::init();
	ddf::magician::gametimer::on_value_change += ddf::magician::game_timer_expired::monitor;

	ddf::magician::game_timer_expired::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::cupboard_controller_event_for_labyrinth_task::init();
	ddf::magician::cupboard_controller::debouncer::value::on_change += ddf::magician::cupboard_controller_event_for_labyrinth_task::monitor;

	ddf::magician::cupboard_controller_event_for_labyrinth_task::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::gameevent_game_state_changed::init();
	ddf::magician::gamestate::on_change += ddf::magician::gameevent_game_state_changed::monitor;

	ddf::magician::gameevent_game_state_changed::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::freezed1::init(bool());
	ddf::magician::freezed1::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::freezed5::init(bool());
	ddf::magician::freezed5::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::gm_help_status::init(bool());
	ddf::magician::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::gm_help_status::remote_add(ddf::service::comdev::device_role::instance());
	ddf::magician::gamestate::init(uint8_t());
	ddf::magician::gamestate::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::incoming_call::init(uint8_t(0xff));
	ddf::magician::incoming_call::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::incoming_call::remote_add(ddf::service::comdev::device_role::instance());
	ddf::magician::incoming_call_status::init(uint8_t());
	ddf::magician::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance());
	ddf::magician::restart_game::init(bool());
	ddf::magician::restart_game::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::magician::restart_game::remote_add(ddf::service::comdev::device_role::instance());

	ddf::magician::room_1::init();
	ddf::magician::room_1_content::chord::init();
	ddf::magician::room_1_content::event_1::init();

	ddf::magician::room_1_content::event_2::init();


	ddf::magician::room_2::init();
	ddf::magician::room_2_content::chord::init();


	ddf::magician::freezetimer1::init();
	ddf::magician::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::freezetimer5::init();
	ddf::magician::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::magician::gametimer::init();
	ddf::magician::gametimer::remote_add(ddf::service::gmclient::device_role::instance());


	ddf::villa::control_room_controller::device_role::init();
	ddf::villa::control_room_controller::switch_1::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::switch_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::control_room_controller::rfid::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::rfid::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::control_room_controller::magnetic_lock::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::control_room_controller::debouncer_1::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::control_room_controller::video_eject::init(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::control_room_controller::video_eject::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::villa::control_room_controller::device_role::instance());
	ddf::villa::desk_controller::device_role::init();
	ddf::villa::desk_controller::debouncer_3::init(ddf::villa::desk_controller::device_role::instance());
	ddf::villa::desk_controller::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desk_controller::debouncer_4::init(ddf::villa::desk_controller::device_role::instance());
	ddf::villa::desk_controller::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::villa::desk_controller::device_role::instance());
	ddf::villa::desktop_pc::device_role::init();
	ddf::villa::desktop_pc::started::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::started::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desktop_pc::shutdown::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::shutdown::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desktop_pc::logged_in::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::logged_in::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desktop_pc::recycled_restore::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::recycled_restore::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desktop_pc::audioplay_started::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audioplay_started::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desktop_pc::audioplay_finished::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audioplay_finished::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desktop_pc::audioplay_paused::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audioplay_paused::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desktop_pc::restart_game::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::restart_game::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desktop_pc::audioplay_startevent::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audioplay_startevent::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::desktop_pc::audiopause_pauseevent::init(ddf::villa::desktop_pc::device_role::instance(),bool());
	ddf::villa::desktop_pc::audiopause_pauseevent::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::villa::desktop_pc::device_role::instance());
	ddf::villa::entrance_controller::device_role::init();
	ddf::villa::entrance_controller::debouncer::init(ddf::villa::entrance_controller::device_role::instance());
	ddf::villa::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::entrance_controller::led::init(ddf::villa::entrance_controller::device_role::instance());
	ddf::villa::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::entrance_controller::magnetic_sensor::init(ddf::villa::entrance_controller::device_role::instance());
	ddf::villa::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::villa::entrance_controller::device_role::instance());
	ddf::villa::safe_controller::device_role::init();
	ddf::villa::safe_controller::pin_pad::init(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::safe_controller::pin_pad::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::safe_controller::magnetic_lock::init(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::safe_controller::magnetic_lock::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::safe_controller::debouncer_1::init(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::safe_controller::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::safe_controller::debouncer_2::init(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::safe_controller::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::villa::safe_controller::device_role::instance());
	ddf::villa::video_device::device_role::init();
	ddf::villa::video_device::started::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::started::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::shutdown::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::shutdown::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::livecam_started::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::livecam_started::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::livecamslides_started::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::livecamslides_started::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::restart_game::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::restart_game::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::start_livecams::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::start_livecams::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::stop_livecams::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::stop_livecams::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::start_tape::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::start_tape::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::stop_tape::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::stop_tape::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::enabled::init(ddf::villa::video_device::device_role::instance(),bool());
	ddf::villa::video_device::enabled::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::casette_id::init(ddf::villa::video_device::device_role::instance(),uint64_t(0));
	ddf::villa::video_device::casette_id::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::play_ongoing::init(ddf::villa::video_device::device_role::instance(),bool(false));
	ddf::villa::video_device::play_ongoing::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::video_device::livecam_ongoing::init(ddf::villa::video_device::device_role::instance(),bool(false));
	ddf::villa::video_device::livecam_ongoing::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::villa::video_device::device_role::instance());

	ddf::villa::freeze_1_start::init();
	ddf::villa::freezed1::on_change += ddf::villa::freeze_1_start::monitor;

	ddf::villa::freeze_1_start::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::freeze_1_stop::init();
	ddf::villa::freezed1::on_change += ddf::villa::freeze_1_stop::monitor;

	ddf::villa::freeze_1_stop::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::freeze_1_timeout::init();
	ddf::villa::freezetimer1::on_value_change += ddf::villa::freeze_1_timeout::monitor;

	ddf::villa::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::freeze_5_start::init();
	ddf::villa::freezed5::on_change += ddf::villa::freeze_5_start::monitor;

	ddf::villa::freeze_5_start::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::freeze_5_stop::init();
	ddf::villa::freezed5::on_change += ddf::villa::freeze_5_stop::monitor;

	ddf::villa::freeze_5_stop::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::freeze_5_timeout::init();
	ddf::villa::freezetimer5::on_value_change += ddf::villa::freeze_5_timeout::monitor;

	ddf::villa::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::game_timer_expired::init();
	ddf::villa::gametimer::on_value_change += ddf::villa::game_timer_expired::monitor;

	ddf::villa::game_timer_expired::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::casette_ejection_event::init();
	ddf::villa::eject_wait::on_value_change += ddf::villa::casette_ejection_event::monitor;

	ddf::villa::casette_ejection_event::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::gameevent_game_state_changed::init();
	ddf::villa::gamestate::on_change += ddf::villa::gameevent_game_state_changed::monitor;

	ddf::villa::gameevent_game_state_changed::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::gameevent_casette_eject_trigger::init();
	ddf::villa::control_room_controller::debouncer_1::value::on_change += ddf::villa::gameevent_casette_eject_trigger::monitor;

	ddf::villa::gameevent_casette_eject_trigger::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::gameevent_finding_the_keys::init();
	ddf::villa::safe_controller::debouncer_1::value::on_change += ddf::villa::gameevent_finding_the_keys::monitor;
	ddf::villa::safe_controller::debouncer_2::value::on_change += ddf::villa::gameevent_finding_the_keys::monitor;
	ddf::villa::desk_controller::debouncer_3::value::on_change += ddf::villa::gameevent_finding_the_keys::monitor;

	ddf::villa::gameevent_finding_the_keys::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::freezed1::init(bool());
	ddf::villa::freezed1::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::freezed5::init(bool());
	ddf::villa::freezed5::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::gm_help_status::init(bool());
	ddf::villa::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::gm_help_status::remote_add(ddf::service::comdev::device_role::instance());
	ddf::villa::gamestate::init(uint8_t());
	ddf::villa::gamestate::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::incoming_call::init(uint8_t(0xff));
	ddf::villa::incoming_call::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::incoming_call::remote_add(ddf::service::comdev::device_role::instance());
	ddf::villa::incoming_call_status::init(uint8_t());
	ddf::villa::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance());
	ddf::villa::restart_game::init(bool());
	ddf::villa::restart_game::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::villa::restart_game::remote_add(ddf::service::comdev::device_role::instance());

	ddf::villa::room_1::init();
	ddf::villa::room_1_content::chord::init();
	ddf::villa::room_1_content::event_1::init();

	ddf::villa::room_1_content::event_2::init();

	ddf::villa::room_1_content::event_3::init();


	ddf::villa::room_2::init();
	ddf::villa::room_2_content::chord::init();


	ddf::villa::freezetimer1::init();
	ddf::villa::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::freezetimer5::init();
	ddf::villa::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::gametimer::init();
	ddf::villa::gametimer::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::villa::eject_wait::init();
	ddf::villa::eject_wait::remote_add(ddf::service::gmclient::device_role::instance());


	ddf::junkyard::email_client::device_role::init();
	ddf::junkyard::email_client::started::init(ddf::junkyard::email_client::device_role::instance(),bool());
	ddf::junkyard::email_client::started::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::email_client::shutdown::init(ddf::junkyard::email_client::device_role::instance(),bool());
	ddf::junkyard::email_client::shutdown::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::email_client::restart_game::init(ddf::junkyard::email_client::device_role::instance(),bool());
	ddf::junkyard::email_client::restart_game::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::junkyard::email_client::device_role::instance());
	ddf::junkyard::entrance_controller::device_role::init();
	ddf::junkyard::entrance_controller::debouncer::init(ddf::junkyard::entrance_controller::device_role::instance());
	ddf::junkyard::entrance_controller::debouncer::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::entrance_controller::led::init(ddf::junkyard::entrance_controller::device_role::instance());
	ddf::junkyard::entrance_controller::led::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::entrance_controller::magnetic_sensor::init(ddf::junkyard::entrance_controller::device_role::instance());
	ddf::junkyard::entrance_controller::magnetic_sensor::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::junkyard::entrance_controller::device_role::instance());
	ddf::junkyard::secret_box_controller_1::device_role::init();
	ddf::junkyard::secret_box_controller_1::button_grid::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::button_grid::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::debouncer_1::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::debouncer_2::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::debouncer_3::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::debouncer_4::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::debouncer_5::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::debouncer_6::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::debouncer_7::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::magnetic_lock_1::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::magnetic_lock_2::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::magnetic_lock_3::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_1::magnetic_lock_4::init(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_1::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::junkyard::secret_box_controller_1::device_role::instance());
	ddf::junkyard::secret_box_controller_2::device_role::init();
	ddf::junkyard::secret_box_controller_2::debouncer_1::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_2::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_3::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_4::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_4::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_5::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_5::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_6::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_6::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_7::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_7::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_8::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_8::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_9::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_9::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_10::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_10::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::light_controller::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::light_controller::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::debouncer_12::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::debouncer_12::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::magnetic_lock_1::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::magnetic_lock_1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::magnetic_lock_2::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::magnetic_lock_2::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::magnetic_lock_3::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::magnetic_lock_3::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::secret_box_controller_2::magnetic_lock_4::init(ddf::junkyard::secret_box_controller_2::device_role::instance());
	ddf::junkyard::secret_box_controller_2::magnetic_lock_4::remote_add(ddf::service::gmclient::device_role::instance());

	dm::add_role(ddf::junkyard::secret_box_controller_2::device_role::instance());

	ddf::junkyard::freeze_1_start::init();
	ddf::junkyard::freezed1::on_change += ddf::junkyard::freeze_1_start::monitor;

	ddf::junkyard::freeze_1_start::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::freeze_1_stop::init();
	ddf::junkyard::freezed1::on_change += ddf::junkyard::freeze_1_stop::monitor;

	ddf::junkyard::freeze_1_stop::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::freeze_1_timeout::init();
	ddf::junkyard::freezetimer1::on_value_change += ddf::junkyard::freeze_1_timeout::monitor;

	ddf::junkyard::freeze_1_timeout::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::freeze_5_start::init();
	ddf::junkyard::freezed5::on_change += ddf::junkyard::freeze_5_start::monitor;

	ddf::junkyard::freeze_5_start::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::freeze_5_stop::init();
	ddf::junkyard::freezed5::on_change += ddf::junkyard::freeze_5_stop::monitor;

	ddf::junkyard::freeze_5_stop::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::freeze_5_timeout::init();
	ddf::junkyard::freezetimer5::on_value_change += ddf::junkyard::freeze_5_timeout::monitor;

	ddf::junkyard::freeze_5_timeout::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::game_timer_expired::init();
	ddf::junkyard::gametimer::on_value_change += ddf::junkyard::game_timer_expired::monitor;

	ddf::junkyard::game_timer_expired::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_game_state_changed::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::gameevent_game_state_changed::monitor;

	ddf::junkyard::gameevent_game_state_changed::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_ampmeter_turn_on::init();

	ddf::junkyard::gameevent_ampmeter_turn_on::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_call_accepted::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_accepted::monitor;

	ddf::junkyard::gameevent_call_accepted::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_call_declined::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_declined::monitor;

	ddf::junkyard::gameevent_call_declined::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_call_finished::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_finished::monitor;

	ddf::junkyard::gameevent_call_finished::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_call_missed::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_missed::monitor;

	ddf::junkyard::gameevent_call_missed::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_call_ringing::init();
	ddf::junkyard::incoming_call_status::on_change += ddf::junkyard::gameevent_call_ringing::monitor;

	ddf::junkyard::gameevent_call_ringing::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_labirynth_1::init();
	ddf::junkyard::secret_box_controller_1::debouncer_5::value::on_change += ddf::junkyard::gameevent_labirynth_1::monitor;

	ddf::junkyard::gameevent_labirynth_1::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_labirynth_2::init();
	ddf::junkyard::secret_box_controller_1::debouncer_6::value::on_change += ddf::junkyard::gameevent_labirynth_2::monitor;

	ddf::junkyard::gameevent_labirynth_2::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_labirynth_3::init();
	ddf::junkyard::secret_box_controller_1::debouncer_7::value::on_change += ddf::junkyard::gameevent_labirynth_3::monitor;

	ddf::junkyard::gameevent_labirynth_3::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_lockpick_module::init();
	ddf::junkyard::secret_box_controller_1::debouncer_2::value::on_change += ddf::junkyard::gameevent_lockpick_module::monitor;
	ddf::junkyard::secret_box_controller_1::debouncer_3::value::on_change += ddf::junkyard::gameevent_lockpick_module::monitor;
	ddf::junkyard::secret_box_controller_1::debouncer_4::value::on_change += ddf::junkyard::gameevent_lockpick_module::monitor;

	ddf::junkyard::gameevent_lockpick_module::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gameevent_mona_lisa_rescue::init();
	ddf::junkyard::secret_box_controller_2::debouncer_12::value::on_change += ddf::junkyard::gameevent_mona_lisa_rescue::monitor;

	ddf::junkyard::gameevent_mona_lisa_rescue::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::timedevent_test_event_finished::init();
	ddf::junkyard::timedevent_test_timer::on_value_change += ddf::junkyard::timedevent_test_event_finished::monitor;

	ddf::junkyard::timedevent_test_event_finished::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::timedevent_test_event_gamestate::init();
	ddf::junkyard::gamestate::on_change += ddf::junkyard::timedevent_test_event_gamestate::monitor;

	ddf::junkyard::timedevent_test_event_gamestate::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::freezed1::init(bool());
	ddf::junkyard::freezed1::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::freezed5::init(bool());
	ddf::junkyard::freezed5::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gm_help_status::init(bool());
	ddf::junkyard::gm_help_status::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::gm_help_status::remote_add(ddf::service::comdev::device_role::instance());
	ddf::junkyard::gamestate::init(uint8_t());
	ddf::junkyard::gamestate::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::incoming_call::init(uint8_t(0xff));
	ddf::junkyard::incoming_call::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::incoming_call::remote_add(ddf::service::comdev::device_role::instance());
	ddf::junkyard::incoming_call_status::init(uint8_t());
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::incoming_call_status::remote_add(ddf::service::comdev::device_role::instance());
	ddf::junkyard::restart_game::init(bool());
	ddf::junkyard::restart_game::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::restart_game::remote_add(ddf::service::comdev::device_role::instance());
	ddf::junkyard::lock_pick_1_pressed::init(bool(false));
	ddf::junkyard::lock_pick_1_pressed::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::lock_pick_2_pressed::init(bool(false));
	ddf::junkyard::lock_pick_2_pressed::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::junkyard::timedevent_test::init(uint64_t(300));
	ddf::junkyard::timedevent_test::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::room_1::init();
	ddf::junkyard::room_1_content::chord::init();
	ddf::junkyard::room_1_content::event_1::init();

	ddf::junkyard::room_1_content::event_2::init();


	ddf::junkyard::room_2::init();
	ddf::junkyard::room_2_content::chord::init();


	ddf::junkyard::freezetimer1::init();
	ddf::junkyard::freezetimer1::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::freezetimer5::init();
	ddf::junkyard::freezetimer5::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::gametimer::init();
	ddf::junkyard::gametimer::remote_add(ddf::service::gmclient::device_role::instance());

	ddf::junkyard::timedevent_test_timer::init();
	ddf::junkyard::timedevent_test_timer::remote_add(ddf::service::gmclient::device_role::instance());


	ddf::service::comdev::device_role::init();
	dm::add_role(ddf::service::comdev::device_role::instance());
	ddf::service::gmclient::device_role::init();
	dm::add_role(ddf::service::gmclient::device_role::instance());

	ddf::service::statustimertick::init();
	ddf::service::statustimer::on_value_change += ddf::service::statustimertick::monitor;


	ddf::service::servercpustatus::init(uint8_t());
	ddf::service::servercpustatus::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::service::servermemorystatus::init(uint8_t());
	ddf::service::servermemorystatus::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::service::servernetworkstatus::init(uint8_t());
	ddf::service::servernetworkstatus::remote_add(ddf::service::gmclient::device_role::instance());
	ddf::service::serverstoragestatus::init(uint8_t());
	ddf::service::serverstoragestatus::remote_add(ddf::service::gmclient::device_role::instance());


	ddf::service::statustimer::init();


}

static void uninit()
{
	ddf::pirate::freeze_1_start::uninit();
	ddf::pirate::freeze_1_stop::uninit();
	ddf::pirate::freeze_1_timeout::uninit();
	ddf::pirate::freeze_5_start::uninit();
	ddf::pirate::freeze_5_stop::uninit();
	ddf::pirate::freeze_5_timeout::uninit();
	ddf::pirate::game_timer_expired::uninit();
	ddf::pirate::gameevent_game_state_changed::uninit();
	ddf::pirate::rotation_update::uninit();
	ddf::pirate::timedevent_test_event_finished::uninit();
	ddf::pirate::timedevent_test_event_gamestate::uninit();

	ddf::pirate::cashier_laser_controller::laser::uninit();
	ddf::pirate::cashier_laser_controller::lcd::uninit();
	ddf::pirate::cashier_laser_controller::pin_pad::uninit();
	ddf::pirate::cashier_laser_controller::cash_box::uninit();
	ddf::pirate::cashier_laser_controller::switch_1::uninit();
	ddf::pirate::cashier_laser_controller::led_strip::uninit();
	ddf::pirate::entrance_hanger_controller::debouncer_1::uninit();
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

	ddf::pirate::freezed1::uninit();
	ddf::pirate::freezed5::uninit();
	ddf::pirate::gm_help_status::uninit();
	ddf::pirate::gamestate::uninit();
	ddf::pirate::incoming_call::uninit();
	ddf::pirate::incoming_call_status::uninit();
	ddf::pirate::restart_game::uninit();
	ddf::pirate::timedevent_test::uninit();

	ddf::pirate::room_1_content::chord::uninit();
	ddf::pirate::room_1::uninit();
	ddf::pirate::room_2_content::chord::uninit();
	ddf::pirate::room_2::uninit();

	ddf::pirate::freezetimer1::uninit();
	ddf::pirate::freezetimer5::uninit();
	ddf::pirate::gametimer::uninit();
	ddf::pirate::timedevent_test_timer::uninit();

	ddf::magician::freeze_1_start::uninit();
	ddf::magician::freeze_1_stop::uninit();
	ddf::magician::freeze_1_timeout::uninit();
	ddf::magician::freeze_5_start::uninit();
	ddf::magician::freeze_5_stop::uninit();
	ddf::magician::freeze_5_timeout::uninit();
	ddf::magician::game_timer_expired::uninit();
	ddf::magician::cupboard_controller_event_for_labyrinth_task::uninit();
	ddf::magician::gameevent_game_state_changed::uninit();

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

	ddf::magician::freezed1::uninit();
	ddf::magician::freezed5::uninit();
	ddf::magician::gm_help_status::uninit();
	ddf::magician::gamestate::uninit();
	ddf::magician::incoming_call::uninit();
	ddf::magician::incoming_call_status::uninit();
	ddf::magician::restart_game::uninit();

	ddf::magician::room_1_content::chord::uninit();
	ddf::magician::room_1_content::event_1::uninit();
	ddf::magician::room_1_content::event_2::uninit();
	ddf::magician::room_1::uninit();
	ddf::magician::room_2_content::chord::uninit();
	ddf::magician::room_2::uninit();

	ddf::magician::freezetimer1::uninit();
	ddf::magician::freezetimer5::uninit();
	ddf::magician::gametimer::uninit();

	ddf::villa::freeze_1_start::uninit();
	ddf::villa::freeze_1_stop::uninit();
	ddf::villa::freeze_1_timeout::uninit();
	ddf::villa::freeze_5_start::uninit();
	ddf::villa::freeze_5_stop::uninit();
	ddf::villa::freeze_5_timeout::uninit();
	ddf::villa::game_timer_expired::uninit();
	ddf::villa::casette_ejection_event::uninit();
	ddf::villa::gameevent_game_state_changed::uninit();
	ddf::villa::gameevent_casette_eject_trigger::uninit();
	ddf::villa::gameevent_finding_the_keys::uninit();

	ddf::villa::control_room_controller::switch_1::uninit();
	ddf::villa::control_room_controller::rfid::uninit();
	ddf::villa::control_room_controller::magnetic_lock::uninit();
	ddf::villa::control_room_controller::debouncer_1::uninit();
	ddf::villa::control_room_controller::video_eject::uninit();
	ddf::villa::desk_controller::debouncer_3::uninit();
	ddf::villa::desk_controller::debouncer_4::uninit();
	ddf::villa::desktop_pc::started::uninit();
	ddf::villa::desktop_pc::shutdown::uninit();
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
	ddf::villa::video_device::started::uninit();
	ddf::villa::video_device::shutdown::uninit();
	ddf::villa::video_device::livecam_started::uninit();
	ddf::villa::video_device::livecamslides_started::uninit();
	ddf::villa::video_device::restart_game::uninit();
	ddf::villa::video_device::start_livecams::uninit();
	ddf::villa::video_device::stop_livecams::uninit();
	ddf::villa::video_device::start_tape::uninit();
	ddf::villa::video_device::stop_tape::uninit();
	ddf::villa::video_device::enabled::uninit();
	ddf::villa::video_device::casette_id::uninit();
	ddf::villa::video_device::play_ongoing::uninit();
	ddf::villa::video_device::livecam_ongoing::uninit();

	ddf::villa::freezed1::uninit();
	ddf::villa::freezed5::uninit();
	ddf::villa::gm_help_status::uninit();
	ddf::villa::gamestate::uninit();
	ddf::villa::incoming_call::uninit();
	ddf::villa::incoming_call_status::uninit();
	ddf::villa::restart_game::uninit();

	ddf::villa::room_1_content::chord::uninit();
	ddf::villa::room_1_content::event_1::uninit();
	ddf::villa::room_1_content::event_2::uninit();
	ddf::villa::room_1_content::event_3::uninit();
	ddf::villa::room_1::uninit();
	ddf::villa::room_2_content::chord::uninit();
	ddf::villa::room_2::uninit();

	ddf::villa::freezetimer1::uninit();
	ddf::villa::freezetimer5::uninit();
	ddf::villa::gametimer::uninit();
	ddf::villa::eject_wait::uninit();

	ddf::junkyard::freeze_1_start::uninit();
	ddf::junkyard::freeze_1_stop::uninit();
	ddf::junkyard::freeze_1_timeout::uninit();
	ddf::junkyard::freeze_5_start::uninit();
	ddf::junkyard::freeze_5_stop::uninit();
	ddf::junkyard::freeze_5_timeout::uninit();
	ddf::junkyard::game_timer_expired::uninit();
	ddf::junkyard::gameevent_game_state_changed::uninit();
	ddf::junkyard::gameevent_ampmeter_turn_on::uninit();
	ddf::junkyard::gameevent_call_accepted::uninit();
	ddf::junkyard::gameevent_call_declined::uninit();
	ddf::junkyard::gameevent_call_finished::uninit();
	ddf::junkyard::gameevent_call_missed::uninit();
	ddf::junkyard::gameevent_call_ringing::uninit();
	ddf::junkyard::gameevent_labirynth_1::uninit();
	ddf::junkyard::gameevent_labirynth_2::uninit();
	ddf::junkyard::gameevent_labirynth_3::uninit();
	ddf::junkyard::gameevent_lockpick_module::uninit();
	ddf::junkyard::gameevent_mona_lisa_rescue::uninit();
	ddf::junkyard::timedevent_test_event_finished::uninit();
	ddf::junkyard::timedevent_test_event_gamestate::uninit();

	ddf::junkyard::email_client::started::uninit();
	ddf::junkyard::email_client::shutdown::uninit();
	ddf::junkyard::email_client::restart_game::uninit();
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

	ddf::junkyard::freezed1::uninit();
	ddf::junkyard::freezed5::uninit();
	ddf::junkyard::gm_help_status::uninit();
	ddf::junkyard::gamestate::uninit();
	ddf::junkyard::incoming_call::uninit();
	ddf::junkyard::incoming_call_status::uninit();
	ddf::junkyard::restart_game::uninit();
	ddf::junkyard::lock_pick_1_pressed::uninit();
	ddf::junkyard::lock_pick_2_pressed::uninit();
	ddf::junkyard::timedevent_test::uninit();

	ddf::junkyard::room_1_content::chord::uninit();
	ddf::junkyard::room_1_content::event_1::uninit();
	ddf::junkyard::room_1_content::event_2::uninit();
	ddf::junkyard::room_1::uninit();
	ddf::junkyard::room_2_content::chord::uninit();
	ddf::junkyard::room_2::uninit();

	ddf::junkyard::freezetimer1::uninit();
	ddf::junkyard::freezetimer5::uninit();
	ddf::junkyard::gametimer::uninit();
	ddf::junkyard::timedevent_test_timer::uninit();

	ddf::service::statustimertick::uninit();


	ddf::service::servercpustatus::uninit();
	ddf::service::servermemorystatus::uninit();
	ddf::service::servernetworkstatus::uninit();
	ddf::service::serverstoragestatus::uninit();


	ddf::service::statustimer::uninit();

}

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
int main()
{
	journal::init();

	alsa_host::init();

	process::sql_executor::init();

	wicc_earpc::init();

	dm::init();

	init();
	ddf::service::statustimer::start();

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
			if(get_property<ddf::pirate::restart_game>(x)) continue;
			if(get_property<ddf::pirate::gm_help_status>(x)) continue;
			if(get_property<ddf::pirate::incoming_call>(x)) continue;
			if(get_property<ddf::pirate::incoming_call_status>(x)) continue;
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
			if(set_property<ddf::pirate::restart_game>(x)) continue;
			if(set_property<ddf::pirate::gm_help_status>(x)) continue;
			if(set_property<ddf::pirate::incoming_call>(x)) continue;
			if(set_property<ddf::pirate::incoming_call_status>(x)) continue;
			if(set_peripheral<ddf::pirate::entrance_hanger_controller::led>(x)) continue;
			if(set_peripheral<ddf::magician::cupboard_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::magician::cupboard_controller::led_strip>(x)) continue;
			if(set_peripheral<ddf::magician::design_board_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::magician::futuristic_safe_controller::magnetic_lock>(x)) continue;
//			if(get_peripheral<ddf::magician::futuristic_safe_controller::addressable_led_strip>(x)) continue;
			if(set_peripheral<ddf::magician::entrance_controller::led>(x)) continue;
			if(set_property<ddf::magician::restart_game>(x)) continue;
			if(set_property<ddf::magician::gm_help_status>(x)) continue;
			if(set_property<ddf::magician::incoming_call>(x)) continue;
			if(set_property<ddf::magician::incoming_call_status>(x)) continue;
			if(set_peripheral<ddf::villa::safe_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::villa::control_room_controller::magnetic_lock>(x)) continue;
			if(set_peripheral<ddf::villa::control_room_controller::video_eject>(x)) continue;
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
//			if(get_peripheral<ddf::junkyard::secret_box_controller_1::addressable_led>(x)) continue;
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
	}

	uninit();

	journal::uninit();
	return 0;
}

