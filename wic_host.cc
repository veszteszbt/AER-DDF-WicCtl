#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <cstdint>
#include <earpc/udp.h>
#include <earpc/earpc.h>
#include <net/algorithm.h>
#include <wicp/remote_property.h>
#include <string>
#include <sstream>

struct wicc_earpc_config
{
	static earpc::udp connection;

	typedef uint64_t command_id_type;

	typedef uint32_t call_id_type;

	static const command_id_type command_id_ack = -1;

	static const command_id_type command_id_nak = -2;

	static const command_id_type command_id_return = -3;

	static const command_id_type command_id_exception = -4;
};
typedef earpc::earpc<wicc_earpc_config> wicc_earpc;

earpc::udp wicc_earpc_config::connection(1234, 1234);

struct property_config_base
{
	typedef std::chrono::high_resolution_clock    cfg_clock;

	typedef wicc_earpc cfg_earpc;

	typedef uint32_t cfg_class_id_type;

	typedef uint32_t cfg_member_id_type;
};

/// Site DDF
namespace ddf
{

	/// Room Pirate
	namespace pirate
	{
	
		/// Map Controller
		namespace map_controller
		{

			/// Magnetic Sensor 1 ///
			struct magnetic_sensor_1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100010;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<magnetic_sensor_1_config> magnetic_sensor_1;

			/// Magnetic Sensor 2 ///
			struct magnetic_sensor_2_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100010;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<magnetic_sensor_2_config> magnetic_sensor_2;

		}

		/// Stone Chest Controller
		namespace stone_chest_controller
		{

			/// Stone 1 ///
			struct stone_1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100020;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<stone_1_config> stone_1;

			/// Stone 2 ///
			struct stone_2_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100020;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<stone_2_config> stone_2;

			/// Stone 3 ///
			struct stone_3_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100020;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<stone_3_config> stone_3;

			/// Stone 4 ///
			struct stone_4_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100020;

				static const uint32_t cfg_member_id = 0x40;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<stone_4_config> stone_4;

			/// Chest Opening ///
			struct chest_opening_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100020;

				static const uint32_t cfg_member_id = 0x50;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<chest_opening_config> chest_opening;

			/// Key Holder ///
			struct key_holder_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100020;

				static const uint32_t cfg_member_id = 0x60;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<key_holder_config> key_holder;

			/// Grid Lock ///
			struct grid_lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100020;

				static const uint32_t cfg_member_id = 0x70;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<grid_lock_config> grid_lock;

			/// LED Strip ///
			struct led_strip_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100020;

				static const uint32_t cfg_member_id = 0x80;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<led_strip_config> led_strip;

		}

		/// Cashier Laser Controller
		namespace cashier_laser_controller
		{

			/// LASER ///
			struct laser_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100030;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<laser_config> laser;

			/// LCD ///
			struct lcd_config : public property_config_base
			{
				struct cfg_value_type
				{
					char data[32];

					cfg_value_type() {}

					cfg_value_type(const char *x)
					{
						for(int i = 0; i < 32; ++i)
							data[i] = x[i];
						
					}

					cfg_value_type &operator=(const char *x)
					{
						for(int i = 0; i < 32; ++i)
							data[i] = x[i];

						return *this;
					}

					cfg_value_type &operator=(const cfg_value_type &x)
					{
						for(int i = 0; i < 32; ++i)
							data[i] = x.data[i];

						return *this;
					}

					bool operator==(const cfg_value_type &x) const
					{
						for(int i = 0; i < 32; ++i)
							if(data[i] != x.data[i])
								return false;

						return true;
					}

					bool operator!=(const cfg_value_type &x) const
					{
						for(int i = 0; i < 32; ++i)
							if(data[i] != x.data[i])
								return true;

						return false;
					}
				};

				static const uint32_t cfg_class_id = 0x100030;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<lcd_config> lcd;

			/// Cash Box ///
			struct cash_box_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100030;

				static const uint32_t cfg_member_id = 0x40;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<cash_box_config> cash_box;

			/// Wall Lights ///
			struct wall_lights_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100030;

				static const uint32_t cfg_member_id = 0x50;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<wall_lights_config> wall_lights;

			/// Fake Cable ///
			struct fake_cable_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100030;

				static const uint32_t cfg_member_id = 0x60;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<fake_cable_config> fake_cable;

		}

		/// Rex Flipper Controller
		namespace rex_flipper_controller
		{

			/// IR LED 1 ///
			struct ir_led_1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<ir_led_1_config> ir_led_1;

			/// IR Sensor 1 ///
			struct ir_sensor_1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<ir_sensor_1_config> ir_sensor_1;

			/// IR LED 2 ///
			struct ir_led_2_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<ir_led_2_config> ir_led_2;

			/// IR Sensor 2 ///
			struct ir_sensor_2_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0x40;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<ir_sensor_2_config> ir_sensor_2;

			/// IR LED 3 ///
			struct ir_led_3_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0x50;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<ir_led_3_config> ir_led_3;

			/// IR Sensor 3 ///
			struct ir_sensor_3_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0x60;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<ir_sensor_3_config> ir_sensor_3;

			/// IR LED 4 ///
			struct ir_led_4_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0x70;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<ir_led_4_config> ir_led_4;

			/// IR Sensor 4 ///
			struct ir_sensor_4_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0x80;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<ir_sensor_4_config> ir_sensor_4;

			/// IR LED 5 ///
			struct ir_led_5_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0x90;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<ir_led_5_config> ir_led_5;

			/// IR Sensor 5 ///
			struct ir_sensor_5_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0xa0;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<ir_sensor_5_config> ir_sensor_5;

			/// RFID ///
			struct rfid_config : public property_config_base
			{
				typedef uint64_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0xb0;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<rfid_config> rfid;

			/// LED 1 ///
			struct led_1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0xc0;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<led_1_config> led_1;

			/// LED 2 ///
			struct led_2_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0xd0;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<led_2_config> led_2;

			/// LED 3 ///
			struct led_3_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0xe0;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<led_3_config> led_3;

			/// Key Holder ///
			struct key_holder_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100040;

				static const uint32_t cfg_member_id = 0xf0;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<key_holder_config> key_holder;

		}

		/// Ghostbox Picture Laser Hanger Boat Controller
		namespace ghostbox_picture_laser_hanger_boat_controller
		{

			/// Entrance Lock ///
			struct entrance_lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100050;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<entrance_lock_config> entrance_lock;

			/// Magnetic Lock ///
			struct magnetic_lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100050;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<magnetic_lock_config> magnetic_lock;

			/// Boat Door Lock ///
			struct boat_door_lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100050;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<boat_door_lock_config> boat_door_lock;

			/// Ghostbox Switch ///
			struct ghostbox_switch_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100050;

				static const uint32_t cfg_member_id = 0x40;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<ghostbox_switch_config> ghostbox_switch;

			/// Hanger Switch ///
			struct hanger_switch_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100050;

				static const uint32_t cfg_member_id = 0x50;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<hanger_switch_config> hanger_switch;

			/// Laser Sensor ///
			struct laser_sensor_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100050;

				static const uint32_t cfg_member_id = 0x60;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<laser_sensor_config> laser_sensor;

			/// Knock Sensor ///
			struct knock_sensor_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100050;

				static const uint32_t cfg_member_id = 0x70;

				static const uint32_t cfg_cooldown_time = 70;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<knock_sensor_config> knock_sensor;

			/// Corridor Light ///
			struct corridor_light_config : public property_config_base
			{
				typedef uint16_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x100050;

				static const uint32_t cfg_member_id = 0x80;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<corridor_light_config> corridor_light;

		}

		/// Wheel Controller
		namespace wheel_controller
		{

			/// Wheel and Stars ///
			struct wheel_and_stars_config : public property_config_base
			{
				typedef uint16_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x100060;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<wheel_and_stars_config> wheel_and_stars;

		}

		/// Entrance Controller
		namespace entrance_controller
		{

			/// Big Dome Button ///
			struct big_dome_button_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100070;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<big_dome_button_config> big_dome_button;

			/// Big Dome Button LED ///
			struct big_dome_button_led_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100070;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<big_dome_button_led_config> big_dome_button_led;

			/// Door Sensor ///
			struct door_sensor_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x100070;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<door_sensor_config> door_sensor;

		}

	}

	/// Room Magician
	namespace magician
	{
	
		/// Cupboard Controller
		namespace cupboard_controller
		{

			/// Door Sensor ///
			struct door_sensor_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200010;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<door_sensor_config> door_sensor;

			/// Emergency Open Button ///
			struct emergency_open_button_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200010;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<emergency_open_button_config> emergency_open_button;

			/// Light ///
			struct light_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200010;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<light_config> light;

			/// Ball Switch ///
			struct ball_switch_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200010;

				static const uint32_t cfg_member_id = 0x40;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<ball_switch_config> ball_switch;

			/// Lock ///
			struct lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200010;

				static const uint32_t cfg_member_id = 0x50;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<lock_config> lock;

		}

		/// CD Player Controller
		namespace cd_player_controller
		{

			/// Play Button ///
			struct play_button_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200020;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<play_button_config> play_button;

			/// Eject Button ///
			struct eject_button_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200020;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<eject_button_config> eject_button;

		}

		/// Design Board Controller
		namespace design_board_controller
		{

			/// Magnetic Sensor 1 ///
			struct magnetic_sensor_1_config : public property_config_base
			{
				typedef uint16_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x200030;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<magnetic_sensor_1_config> magnetic_sensor_1;

			/// Magnetic Sensor 2 ///
			struct magnetic_sensor_2_config : public property_config_base
			{
				typedef uint16_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x200030;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<magnetic_sensor_2_config> magnetic_sensor_2;

			/// Magnetic Sensor 3 ///
			struct magnetic_sensor_3_config : public property_config_base
			{
				typedef uint16_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x200030;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<magnetic_sensor_3_config> magnetic_sensor_3;

			/// Lock ///
			struct lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200030;

				static const uint32_t cfg_member_id = 0x40;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<lock_config> lock;

		}

		/// Futuristic Safe Controller
		namespace futuristic_safe_controller
		{

			/// Lock ///
			struct lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200040;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<lock_config> lock;

			/// Key Switch ///
			struct key_switch_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200040;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<key_switch_config> key_switch;

			/// RFID ///
			struct rfid_config : public property_config_base
			{
				typedef uint64_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x200040;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 1;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<rfid_config> rfid;

		}

		/// Entrance Controller
		namespace entrance_controller
		{

			/// Big Dome Button ///
			struct big_dome_button_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200050;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<big_dome_button_config> big_dome_button;

			/// Big Dome Button LED ///
			struct big_dome_button_led_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200050;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<big_dome_button_led_config> big_dome_button_led;

			/// Door Sensor ///
			struct door_sensor_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x200050;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<door_sensor_config> door_sensor;

		}

	}

	/// Room Villa
	namespace villa
	{
	
		/// Safe Controller
		namespace safe_controller
		{

			/// Lock ///
			struct lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300010;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<lock_config> lock;

		}

		/// Fireplace Controller
		namespace fireplace_controller
		{

			/// Key Switch 1 ///
			struct key_switch_1_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300020;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<key_switch_1_config> key_switch_1;

			/// Key Switch 2 ///
			struct key_switch_2_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300020;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<key_switch_2_config> key_switch_2;

			/// Key Switch 3 ///
			struct key_switch_3_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300020;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<key_switch_3_config> key_switch_3;

			/// Lock ///
			struct lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300020;

				static const uint32_t cfg_member_id = 0x40;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<lock_config> lock;

			/// Flask Lock ///
			struct flask_lock_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300020;

				static const uint32_t cfg_member_id = 0x50;

				static const uint32_t cfg_cooldown_time = 200;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<flask_lock_config> flask_lock;

		}

		/// Control Room Controller
		namespace control_room_controller
		{

			/// Switch 1 ///
			struct switch_1_config : public property_config_base
			{
				typedef uint8_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x300030;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<switch_1_config> switch_1;

			/// Switch 2 ///
			struct switch_2_config : public property_config_base
			{
				typedef uint8_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x300030;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<switch_2_config> switch_2;

			/// Switch 3 ///
			struct switch_3_config : public property_config_base
			{
				typedef uint8_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x300030;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<switch_3_config> switch_3;

			/// Switch 4 ///
			struct switch_4_config : public property_config_base
			{
				typedef uint8_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x300030;

				static const uint32_t cfg_member_id = 0x40;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<switch_4_config> switch_4;

			/// Switch 5 ///
			struct switch_5_config : public property_config_base
			{
				typedef uint8_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x300030;

				static const uint32_t cfg_member_id = 0x50;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<switch_5_config> switch_5;

			/// RFID ///
			struct rfid_config : public property_config_base
			{
				typedef uint64_t cfg_value_type;

				static const uint32_t cfg_class_id = 0x300030;

				static const uint32_t cfg_member_id = 0x60;

				static const uint32_t cfg_cooldown_time = 1;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<rfid_config> rfid;

			/// Eject ///
			struct eject_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300030;

				static const uint32_t cfg_member_id = 0x70;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<eject_config> eject;

		}

		/// Entrance Controller
		namespace entrance_controller
		{

			/// Big Dome Button ///
			struct big_dome_button_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300040;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<big_dome_button_config> big_dome_button;

			/// Big Dome Button LED ///
			struct big_dome_button_led_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300040;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<big_dome_button_led_config> big_dome_button_led;

			/// Door Sensor ///
			struct door_sensor_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x300040;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<door_sensor_config> door_sensor;

		}

	}

	/// Room Junkyard
	namespace junkyard
	{
	
		/// Secret Box 1 Controller
		namespace secret_box_1_controller
		{

		}

		/// Secret Box 2 Controller
		namespace secret_box_2_controller
		{

		}

		/// Entrance Controller
		namespace entrance_controller
		{

			/// Big Dome Button ///
			struct big_dome_button_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x400030;

				static const uint32_t cfg_member_id = 0x10;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<big_dome_button_config> big_dome_button;

			/// Big Dome Button LED ///
			struct big_dome_button_led_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x400030;

				static const uint32_t cfg_member_id = 0x20;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = true;
			};
			typedef wicp::remote_property<big_dome_button_led_config> big_dome_button_led;

			/// Door Sensor ///
			struct door_sensor_config : public property_config_base
			{
				typedef bool cfg_value_type;

				static const uint32_t cfg_class_id = 0x400030;

				static const uint32_t cfg_member_id = 0x30;

				static const uint32_t cfg_cooldown_time = 50;

				static const bool cfg_commit_change_only = true;

				static const bool cfg_read = true;

				static const bool cfg_write = false;
			};
			typedef wicp::remote_property<door_sensor_config> door_sensor;

		}

	}

}

// TODO: event handlers

void display_switches()
{
	std::stringstream ss;
	char x[32];
	
	ss << (int)ddf::villa::control_room_controller::switch_1::value() << ' ' <<
		(int)ddf::villa::control_room_controller::switch_2::value();

	std::string s = ss.str().c_str();
	int i = 0;
	for(; i < s.size();++i)
		x[i] = s[i];

	for(;i<32;++i)
		x[i] = ' ';

	std::cout << "\e[37;01m" <<s << "\e[0m" << std::endl;
	ddf::pirate::cashier_laser_controller::lcd::value(x);
	
}

int main()
{
	std::thread t = wicc_earpc::init();

// TODO: event handler init

	ddf::pirate::map_controller::magnetic_sensor_1::init(net::ipv4_address(192,168,100,1));
	ddf::pirate::map_controller::magnetic_sensor_2::init(net::ipv4_address(192,168,100,1));
	ddf::pirate::stone_chest_controller::stone_1::init(net::ipv4_address(192,168,100,2));
	ddf::pirate::stone_chest_controller::stone_2::init(net::ipv4_address(192,168,100,2));
	ddf::pirate::stone_chest_controller::stone_3::init(net::ipv4_address(192,168,100,2));
	ddf::pirate::stone_chest_controller::stone_4::init(net::ipv4_address(192,168,100,2));
	ddf::pirate::stone_chest_controller::chest_opening::init(net::ipv4_address(192,168,100,2));
	ddf::pirate::stone_chest_controller::key_holder::init(net::ipv4_address(192,168,100,2));
	ddf::pirate::stone_chest_controller::grid_lock::init(net::ipv4_address(192,168,100,2));
	ddf::pirate::stone_chest_controller::led_strip::init(net::ipv4_address(192,168,100,2));
	ddf::pirate::cashier_laser_controller::laser::init(net::ipv4_address(192,168,100,3));
	ddf::pirate::cashier_laser_controller::lcd::init(net::ipv4_address(192,168,100,3));
	ddf::pirate::cashier_laser_controller::cash_box::init(net::ipv4_address(192,168,100,3));
	ddf::pirate::cashier_laser_controller::wall_lights::init(net::ipv4_address(192,168,100,3));
	ddf::pirate::cashier_laser_controller::fake_cable::init(net::ipv4_address(192,168,100,3));
	ddf::pirate::rex_flipper_controller::ir_led_1::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::ir_sensor_1::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::ir_led_2::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::ir_sensor_2::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::ir_led_3::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::ir_sensor_3::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::ir_led_4::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::ir_sensor_4::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::ir_led_5::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::ir_sensor_5::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::rfid::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::led_1::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::led_2::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::led_3::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::rex_flipper_controller::key_holder::init(net::ipv4_address(192,168,100,4));
	ddf::pirate::ghostbox_picture_laser_hanger_boat_controller::entrance_lock::init(net::ipv4_address(192,168,100,5));
	ddf::pirate::ghostbox_picture_laser_hanger_boat_controller::magnetic_lock::init(net::ipv4_address(192,168,100,5));
	ddf::pirate::ghostbox_picture_laser_hanger_boat_controller::boat_door_lock::init(net::ipv4_address(192,168,100,5));
	ddf::pirate::ghostbox_picture_laser_hanger_boat_controller::ghostbox_switch::init(net::ipv4_address(192,168,100,5));
	ddf::pirate::ghostbox_picture_laser_hanger_boat_controller::hanger_switch::init(net::ipv4_address(192,168,100,5));
	ddf::pirate::ghostbox_picture_laser_hanger_boat_controller::laser_sensor::init(net::ipv4_address(192,168,100,5));
	ddf::pirate::ghostbox_picture_laser_hanger_boat_controller::knock_sensor::init(net::ipv4_address(192,168,100,5));
	ddf::pirate::ghostbox_picture_laser_hanger_boat_controller::corridor_light::init(net::ipv4_address(192,168,100,5));
	ddf::pirate::wheel_controller::wheel_and_stars::init(net::ipv4_address(192,168,100,6));
	ddf::pirate::entrance_controller::big_dome_button::init(net::ipv4_address(192,168,100,7));
	ddf::pirate::entrance_controller::big_dome_button_led::init(net::ipv4_address(192,168,100,7));
	ddf::pirate::entrance_controller::door_sensor::init(net::ipv4_address(192,168,100,7));
	ddf::magician::cupboard_controller::door_sensor::init(net::ipv4_address(192,168,100,8));
	ddf::magician::cupboard_controller::emergency_open_button::init(net::ipv4_address(192,168,100,8));
	ddf::magician::cupboard_controller::light::init(net::ipv4_address(192,168,100,8));
	ddf::magician::cupboard_controller::ball_switch::init(net::ipv4_address(192,168,100,8));
	ddf::magician::cupboard_controller::lock::init(net::ipv4_address(192,168,100,8));
	ddf::magician::cd_player_controller::play_button::init(net::ipv4_address(192,168,100,9));
	ddf::magician::cd_player_controller::eject_button::init(net::ipv4_address(192,168,100,9));
	ddf::magician::design_board_controller::magnetic_sensor_1::init(net::ipv4_address(192,168,100,10));
	ddf::magician::design_board_controller::magnetic_sensor_2::init(net::ipv4_address(192,168,100,10));
	ddf::magician::design_board_controller::magnetic_sensor_3::init(net::ipv4_address(192,168,100,10));
	ddf::magician::design_board_controller::lock::init(net::ipv4_address(192,168,100,10));
	ddf::magician::futuristic_safe_controller::lock::init(net::ipv4_address(192,168,100,11));
	ddf::magician::futuristic_safe_controller::key_switch::init(net::ipv4_address(192,168,100,11));
	ddf::magician::futuristic_safe_controller::rfid::init(net::ipv4_address(192,168,100,11));
	ddf::magician::entrance_controller::big_dome_button::init(net::ipv4_address(192,168,100,12));
	ddf::magician::entrance_controller::big_dome_button_led::init(net::ipv4_address(192,168,100,12));
	ddf::magician::entrance_controller::door_sensor::init(net::ipv4_address(192,168,100,12));
	ddf::villa::safe_controller::lock::init(net::ipv4_address(192,168,100,14));
	ddf::villa::fireplace_controller::key_switch_1::init(net::ipv4_address(192,168,100,15));
	ddf::villa::fireplace_controller::key_switch_2::init(net::ipv4_address(192,168,100,15));
	ddf::villa::fireplace_controller::key_switch_3::init(net::ipv4_address(192,168,100,15));
	ddf::villa::fireplace_controller::lock::init(net::ipv4_address(192,168,100,15));
	ddf::villa::fireplace_controller::flask_lock::init(net::ipv4_address(192,168,100,15));
	ddf::villa::control_room_controller::switch_1::init(net::ipv4_address(192,168,100,16));
	ddf::villa::control_room_controller::switch_2::init(net::ipv4_address(192,168,100,16));
	ddf::villa::control_room_controller::switch_3::init(net::ipv4_address(192,168,100,16));
	ddf::villa::control_room_controller::switch_4::init(net::ipv4_address(192,168,100,16));
	ddf::villa::control_room_controller::switch_5::init(net::ipv4_address(192,168,100,16));
	ddf::villa::control_room_controller::rfid::init(net::ipv4_address(192,168,100,16));
	ddf::villa::control_room_controller::eject::init(net::ipv4_address(192,168,100,16));
	ddf::villa::entrance_controller::big_dome_button::init(net::ipv4_address(192,168,100,17));
	ddf::villa::entrance_controller::big_dome_button_led::init(net::ipv4_address(192,168,100,17));
	ddf::villa::entrance_controller::door_sensor::init(net::ipv4_address(192,168,100,17));
	ddf::junkyard::entrance_controller::big_dome_button::init(net::ipv4_address(192,168,100,20));
	ddf::junkyard::entrance_controller::big_dome_button_led::init(net::ipv4_address(192,168,100,20));
	ddf::junkyard::entrance_controller::door_sensor::init(net::ipv4_address(192,168,100,20));

	ddf::villa::control_room_controller::switch_1::on_change(display_switches);
	ddf::villa::control_room_controller::switch_2::on_change(display_switches);


	t.join();
	return 0;
}

