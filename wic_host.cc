#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <cstdint>
#include <alsa_host.h>
#include <earpc/udp.h>
#include <earpc/earpc.h>
#include <net/algorithm.h>
#include <wicp/remote_property.h>
#include <string>

#include <peripheral/gpio_input.h>
#include <peripheral/gpio_output.h>
#include <peripheral/pwm_adjuster.h>
#include <peripheral/pwm_output.h>
#include <peripheral/resistor_sequence.h>
#include <peripheral/rfid.h>
#include <peripheral/text_display.h>
#include <peripheral/voltage_level.h>


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
		namespace devices
		{

			/// Map Controller
			namespace map_controller
			{

				/// Magnetic Sensor 1 ///
				struct magnetic_sensor_1_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100010;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_input<magnetic_sensor_1_config> magnetic_sensor_1;

				/// Magnetic Sensor 2 ///
				struct magnetic_sensor_2_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100010;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_input<magnetic_sensor_2_config> magnetic_sensor_2;

				static void init(net::ipv4_address ip)
				{
					magnetic_sensor_1::init(ip);
					magnetic_sensor_2::init(ip);

				}

				static void uninit()
				{
					magnetic_sensor_1::uninit();
					magnetic_sensor_2::uninit();

				}
			}

			/// Stone Chest Controller
			namespace stone_chest_controller
			{

				/// Stone 1 ///
				struct stone_1_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_input<stone_1_config> stone_1;

				/// Stone 2 ///
				struct stone_2_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_input<stone_2_config> stone_2;

				/// Stone 3 ///
				struct stone_3_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_input<stone_3_config> stone_3;

				/// Stone 4 ///
				struct stone_4_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_input<stone_4_config> stone_4;

				/// Chest Opening ///
				struct chest_opening_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_input<chest_opening_config> chest_opening;

				/// Key Holder ///
				struct key_holder_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<key_holder_config> key_holder;

				/// Grid Lock ///
				struct grid_lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x70;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<grid_lock_config> grid_lock;

				/// LED Strip ///
				struct led_strip_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100020;

					static const uint32_t cfg_member_id = 0x80;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<led_strip_config> led_strip;

				static void init(net::ipv4_address ip)
				{
					stone_1::init(ip);
					stone_2::init(ip);
					stone_3::init(ip);
					stone_4::init(ip);
					chest_opening::init(ip);
					key_holder::init(ip);
					grid_lock::init(ip);
					led_strip::init(ip);

				}

				static void uninit()
				{
					stone_1::uninit();
					stone_2::uninit();
					stone_3::uninit();
					stone_4::uninit();
					chest_opening::uninit();
					key_holder::uninit();
					grid_lock::uninit();
					led_strip::uninit();

				}
			}

			/// Cashier Laser Controller
			namespace cashier_laser_controller
			{

				/// LASER ///
				struct laser_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<laser_config> laser;

				/// LCD ///
				struct lcd_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::text_display<lcd_config> lcd;

				/// Cash Box ///
				struct cash_box_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<cash_box_config> cash_box;

				/// Wall Lights ///
				struct wall_lights_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<wall_lights_config> wall_lights;

				/// Fake Cable ///
				struct fake_cable_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100030;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_input<fake_cable_config> fake_cable;

				static void init(net::ipv4_address ip)
				{
					laser::init(ip);
					lcd::init(ip);
					cash_box::init(ip);
					wall_lights::init(ip);
					fake_cable::init(ip);

				}

				static void uninit()
				{
					laser::uninit();
					lcd::uninit();
					cash_box::uninit();
					wall_lights::uninit();
					fake_cable::uninit();

				}
			}

			/// Rex Flipper Controller
			namespace rex_flipper_controller
			{

				/// IR LED 1 ///
				struct ir_led_1_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<ir_led_1_config> ir_led_1;

				/// IR Sensor 1 ///
				struct ir_sensor_1_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<ir_sensor_1_config> ir_sensor_1;

				/// IR LED 2 ///
				struct ir_led_2_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<ir_led_2_config> ir_led_2;

				/// IR Sensor 2 ///
				struct ir_sensor_2_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<ir_sensor_2_config> ir_sensor_2;

				/// IR LED 3 ///
				struct ir_led_3_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<ir_led_3_config> ir_led_3;

				/// IR Sensor 3 ///
				struct ir_sensor_3_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<ir_sensor_3_config> ir_sensor_3;

				/// IR LED 4 ///
				struct ir_led_4_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x70;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<ir_led_4_config> ir_led_4;

				/// IR Sensor 4 ///
				struct ir_sensor_4_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x80;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<ir_sensor_4_config> ir_sensor_4;

				/// IR LED 5 ///
				struct ir_led_5_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0x90;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<ir_led_5_config> ir_led_5;

				/// IR Sensor 5 ///
				struct ir_sensor_5_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xa0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<ir_sensor_5_config> ir_sensor_5;

				/// RFID ///
				struct rfid_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xb0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::rfid<rfid_config> rfid;

				/// LED 1 ///
				struct led_1_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xc0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<led_1_config> led_1;

				/// LED 2 ///
				struct led_2_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xd0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<led_2_config> led_2;

				/// LED 3 ///
				struct led_3_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xe0;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<led_3_config> led_3;

				/// Key Holder ///
				struct key_holder_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100040;

					static const uint32_t cfg_member_id = 0xf0;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<key_holder_config> key_holder;

				static void init(net::ipv4_address ip)
				{
					ir_led_1::init(ip);
					ir_sensor_1::init(ip);
					ir_led_2::init(ip);
					ir_sensor_2::init(ip);
					ir_led_3::init(ip);
					ir_sensor_3::init(ip);
					ir_led_4::init(ip);
					ir_sensor_4::init(ip);
					ir_led_5::init(ip);
					ir_sensor_5::init(ip);
					rfid::init(ip);
					led_1::init(ip);
					led_2::init(ip);
					led_3::init(ip);
					key_holder::init(ip);

				}

				static void uninit()
				{
					ir_led_1::uninit();
					ir_sensor_1::uninit();
					ir_led_2::uninit();
					ir_sensor_2::uninit();
					ir_led_3::uninit();
					ir_sensor_3::uninit();
					ir_led_4::uninit();
					ir_sensor_4::uninit();
					ir_led_5::uninit();
					ir_sensor_5::uninit();
					rfid::uninit();
					led_1::uninit();
					led_2::uninit();
					led_3::uninit();
					key_holder::uninit();

				}
			}

			/// Ghostbox Picture Laser Hanger Boat Controller
			namespace ghostbox_picture_laser_hanger_boat_controller
			{

				/// Entrance Lock ///
				struct entrance_lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<entrance_lock_config> entrance_lock;

				/// Magnetic Lock ///
				struct magnetic_lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<magnetic_lock_config> magnetic_lock;

				/// Boat Door Lock ///
				struct boat_door_lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<boat_door_lock_config> boat_door_lock;

				/// Ghostbox Switch ///
				struct ghostbox_switch_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<ghostbox_switch_config> ghostbox_switch;

				/// Hanger Switch ///
				struct hanger_switch_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<hanger_switch_config> hanger_switch;

				/// Laser Sensor ///
				struct laser_sensor_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<laser_sensor_config> laser_sensor;

				/// Knock Sensor ///
				struct knock_sensor_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x70;

					static const uint32_t cfg_cooldown_time = 70;
				};
				typedef peripheral::gpio_input<knock_sensor_config> knock_sensor;

				/// Corridor Light ///
				struct corridor_light_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100050;

					static const uint32_t cfg_member_id = 0x80;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::pwm_output<corridor_light_config> corridor_light;

				static void init(net::ipv4_address ip)
				{
					entrance_lock::init(ip);
					magnetic_lock::init(ip);
					boat_door_lock::init(ip);
					ghostbox_switch::init(ip);
					hanger_switch::init(ip);
					laser_sensor::init(ip);
					knock_sensor::init(ip);
					corridor_light::init(ip);

				}

				static void uninit()
				{
					entrance_lock::uninit();
					magnetic_lock::uninit();
					boat_door_lock::uninit();
					ghostbox_switch::uninit();
					hanger_switch::uninit();
					laser_sensor::uninit();
					knock_sensor::uninit();
					corridor_light::uninit();

				}
			}

			/// Wheel Controller
			namespace wheel_controller
			{

				/// Wheel and Stars ///
				struct wheel_and_stars_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100060;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::pwm_adjuster<wheel_and_stars_config> wheel_and_stars;

				static void init(net::ipv4_address ip)
				{
					wheel_and_stars::init(ip);

				}

				static void uninit()
				{
					wheel_and_stars::uninit();

				}
			}

			/// Entrance Controller
			namespace entrance_controller
			{

				/// Big Dome Button ///
				struct big_dome_button_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100070;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<big_dome_button_config> big_dome_button;

				/// Big Dome Button LED ///
				struct big_dome_button_led_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100070;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<big_dome_button_led_config> big_dome_button_led;

				/// Door Sensor ///
				struct door_sensor_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100070;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<door_sensor_config> door_sensor;

				static void init(net::ipv4_address ip)
				{
					big_dome_button::init(ip);
					big_dome_button_led::init(ip);
					door_sensor::init(ip);

				}

				static void uninit()
				{
					big_dome_button::uninit();
					big_dome_button_led::uninit();
					door_sensor::uninit();

				}
			}

		}

		namespace events
		{

		}

		static void init()
		{
			devices::map_controller::init(net::ipv4_address(192,168,100,1));
			devices::stone_chest_controller::init(net::ipv4_address(192,168,100,2));
			devices::cashier_laser_controller::init(net::ipv4_address(192,168,100,3));
			devices::rex_flipper_controller::init(net::ipv4_address(192,168,100,4));
			devices::ghostbox_picture_laser_hanger_boat_controller::init(net::ipv4_address(192,168,100,5));
			devices::wheel_controller::init(net::ipv4_address(192,168,100,6));
			devices::entrance_controller::init(net::ipv4_address(192,168,100,7));


		}

		static void uninit()
		{

			devices::map_controller::uninit();
			devices::stone_chest_controller::uninit();
			devices::cashier_laser_controller::uninit();
			devices::rex_flipper_controller::uninit();
			devices::ghostbox_picture_laser_hanger_boat_controller::uninit();
			devices::wheel_controller::uninit();
			devices::entrance_controller::uninit();

		}
	}

	/// Room Magician
	namespace magician
	{
		namespace devices
		{

			/// Cupboard Controller
			namespace cupboard_controller
			{

				/// Door Sensor ///
				struct door_sensor_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200010;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<door_sensor_config> door_sensor;

				/// Emergency Open Button ///
				struct emergency_open_button_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200010;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<emergency_open_button_config> emergency_open_button;

				/// Light ///
				struct light_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200010;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<light_config> light;

				/// Ball Switch ///
				struct ball_switch_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200010;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<ball_switch_config> ball_switch;

				/// Lock ///
				struct lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200010;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<lock_config> lock;

				static void init(net::ipv4_address ip)
				{
					door_sensor::init(ip);
					emergency_open_button::init(ip);
					light::init(ip);
					ball_switch::init(ip);
					lock::init(ip);

				}

				static void uninit()
				{
					door_sensor::uninit();
					emergency_open_button::uninit();
					light::uninit();
					ball_switch::uninit();
					lock::uninit();

				}
			}

			/// CD Player Controller
			namespace cd_player_controller
			{

				/// Play Button ///
				struct play_button_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200020;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<play_button_config> play_button;

				/// Eject Button ///
				struct eject_button_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200020;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<eject_button_config> eject_button;

				static void init(net::ipv4_address ip)
				{
					play_button::init(ip);
					eject_button::init(ip);

				}

				static void uninit()
				{
					play_button::uninit();
					eject_button::uninit();

				}
			}

			/// Design Board Controller
			namespace design_board_controller
			{

				/// Magnetic Sensor 1 ///
				struct magnetic_sensor_1_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200030;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::voltage_level<magnetic_sensor_1_config> magnetic_sensor_1;

				/// Magnetic Sensor 2 ///
				struct magnetic_sensor_2_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200030;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::voltage_level<magnetic_sensor_2_config> magnetic_sensor_2;

				/// Magnetic Sensor 3 ///
				struct magnetic_sensor_3_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200030;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::voltage_level<magnetic_sensor_3_config> magnetic_sensor_3;

				/// Lock ///
				struct lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200030;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<lock_config> lock;

				static void init(net::ipv4_address ip)
				{
					magnetic_sensor_1::init(ip);
					magnetic_sensor_2::init(ip);
					magnetic_sensor_3::init(ip);
					lock::init(ip);

				}

				static void uninit()
				{
					magnetic_sensor_1::uninit();
					magnetic_sensor_2::uninit();
					magnetic_sensor_3::uninit();
					lock::uninit();

				}
			}

			/// Futuristic Safe Controller
			namespace futuristic_safe_controller
			{

				/// Lock ///
				struct lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200040;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<lock_config> lock;

				/// Key Switch ///
				struct key_switch_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200040;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<key_switch_config> key_switch;

				/// RFID ///
				struct rfid_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200040;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 1;
				};
				typedef peripheral::rfid<rfid_config> rfid;

				static void init(net::ipv4_address ip)
				{
					lock::init(ip);
					key_switch::init(ip);
					rfid::init(ip);

				}

				static void uninit()
				{
					lock::uninit();
					key_switch::uninit();
					rfid::uninit();

				}
			}

			/// Entrance Controller
			namespace entrance_controller
			{

				/// Big Dome Button ///
				struct big_dome_button_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200050;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<big_dome_button_config> big_dome_button;

				/// Big Dome Button LED ///
				struct big_dome_button_led_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200050;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<big_dome_button_led_config> big_dome_button_led;

				/// Door Sensor ///
				struct door_sensor_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x200050;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<door_sensor_config> door_sensor;

				static void init(net::ipv4_address ip)
				{
					big_dome_button::init(ip);
					big_dome_button_led::init(ip);
					door_sensor::init(ip);

				}

				static void uninit()
				{
					big_dome_button::uninit();
					big_dome_button_led::uninit();
					door_sensor::uninit();

				}
			}

		}

		namespace events
		{
			void cabinet_unlock()
			{
				typedef typename magician::devices::cupboard_controller::ball_switch sw;
				typedef typename magician::devices::cupboard_controller::lock lk;

				if(sw::value())
				{
					lk::value(0);
				}
			}
			void light_toggling()
			{
				typedef typename magician::devices::cupboard_controller::ball_switch sensor;
				typedef typename magician::devices::cupboard_controller::light light;

				if(true)
				{
					light::value(sensor::value());
				}
			}

		}

		static void init()
		{
			devices::cupboard_controller::init(net::ipv4_address(192,168,100,8));
			devices::cd_player_controller::init(net::ipv4_address(192,168,100,9));
			devices::design_board_controller::init(net::ipv4_address(192,168,100,10));
			devices::futuristic_safe_controller::init(net::ipv4_address(192,168,100,11));
			devices::entrance_controller::init(net::ipv4_address(192,168,100,12));

			devices::cupboard_controller::ball_switch::on_change += events::cabinet_unlock;
			devices::cupboard_controller::ball_switch::on_change += events::light_toggling;

		}

		static void uninit()
		{
			devices::cupboard_controller::ball_switch::on_change -= events::cabinet_unlock;
			devices::cupboard_controller::ball_switch::on_change -= events::light_toggling;

			devices::cupboard_controller::uninit();
			devices::cd_player_controller::uninit();
			devices::design_board_controller::uninit();
			devices::futuristic_safe_controller::uninit();
			devices::entrance_controller::uninit();

		}
	}

	/// Room Villa
	namespace villa
	{
		namespace devices
		{

			/// Safe Controller
			namespace safe_controller
			{

				/// Lock ///
				struct lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300010;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<lock_config> lock;

				static void init(net::ipv4_address ip)
				{
					lock::init(ip);

				}

				static void uninit()
				{
					lock::uninit();

				}
			}

			/// Fireplace Controller
			namespace fireplace_controller
			{

				/// Key Switch 1 ///
				struct key_switch_1_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300020;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<key_switch_1_config> key_switch_1;

				/// Key Switch 2 ///
				struct key_switch_2_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300020;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<key_switch_2_config> key_switch_2;

				/// Key Switch 3 ///
				struct key_switch_3_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300020;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<key_switch_3_config> key_switch_3;

				/// Lock ///
				struct lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300020;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<lock_config> lock;

				/// Flask Lock ///
				struct flask_lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300020;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 200;
				};
				typedef peripheral::gpio_output<flask_lock_config> flask_lock;

				static void init(net::ipv4_address ip)
				{
					key_switch_1::init(ip);
					key_switch_2::init(ip);
					key_switch_3::init(ip);
					lock::init(ip);
					flask_lock::init(ip);

				}

				static void uninit()
				{
					key_switch_1::uninit();
					key_switch_2::uninit();
					key_switch_3::uninit();
					lock::uninit();
					flask_lock::uninit();

				}
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
				};
				typedef peripheral::resistor_sequence<switch_1_config> switch_1;

				/// Switch 2 ///
				struct switch_2_config : public property_config_base
				{
					typedef uint8_t cfg_value_type;

					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::resistor_sequence<switch_2_config> switch_2;

				/// Switch 3 ///
				struct switch_3_config : public property_config_base
				{
					typedef uint8_t cfg_value_type;

					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::resistor_sequence<switch_3_config> switch_3;

				/// Switch 4 ///
				struct switch_4_config : public property_config_base
				{
					typedef uint8_t cfg_value_type;

					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x40;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::resistor_sequence<switch_4_config> switch_4;

				/// Switch 5 ///
				struct switch_5_config : public property_config_base
				{
					typedef uint8_t cfg_value_type;

					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x50;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::resistor_sequence<switch_5_config> switch_5;

				/// RFID ///
				struct rfid_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x60;

					static const uint32_t cfg_cooldown_time = 1;
				};
				typedef peripheral::rfid<rfid_config> rfid;

				/// Eject ///
				struct eject_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300030;

					static const uint32_t cfg_member_id = 0x70;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<eject_config> eject;

				static void init(net::ipv4_address ip)
				{
					switch_1::init(ip);
					switch_2::init(ip);
					switch_3::init(ip);
					switch_4::init(ip);
					switch_5::init(ip);
					rfid::init(ip);
					eject::init(ip);

				}

				static void uninit()
				{
					switch_1::uninit();
					switch_2::uninit();
					switch_3::uninit();
					switch_4::uninit();
					switch_5::uninit();
					rfid::uninit();
					eject::uninit();

				}
			}

			/// Entrance Controller
			namespace entrance_controller
			{

				/// Big Dome Button ///
				struct big_dome_button_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300040;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<big_dome_button_config> big_dome_button;

				/// Big Dome Button LED ///
				struct big_dome_button_led_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300040;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<big_dome_button_led_config> big_dome_button_led;

				/// Door Sensor ///
				struct door_sensor_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x300040;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<door_sensor_config> door_sensor;

				static void init(net::ipv4_address ip)
				{
					big_dome_button::init(ip);
					big_dome_button_led::init(ip);
					door_sensor::init(ip);

				}

				static void uninit()
				{
					big_dome_button::uninit();
					big_dome_button_led::uninit();
					door_sensor::uninit();

				}
			}

		}

		namespace events
		{

		}

		static void init()
		{
			devices::safe_controller::init(net::ipv4_address(192,168,100,14));
			devices::fireplace_controller::init(net::ipv4_address(192,168,100,15));
			devices::control_room_controller::init(net::ipv4_address(192,168,100,16));
			devices::entrance_controller::init(net::ipv4_address(192,168,100,17));


		}

		static void uninit()
		{

			devices::safe_controller::uninit();
			devices::fireplace_controller::uninit();
			devices::control_room_controller::uninit();
			devices::entrance_controller::uninit();

		}
	}

	/// Room Junkyard
	namespace junkyard
	{
		namespace devices
		{

			/// Secret Box 1 Controller
			namespace secret_box_1_controller
			{

				static void init(net::ipv4_address ip)
				{

				}

				static void uninit()
				{

				}
			}

			/// Secret Box 2 Controller
			namespace secret_box_2_controller
			{

				static void init(net::ipv4_address ip)
				{

				}

				static void uninit()
				{

				}
			}

			/// Entrance Controller
			namespace entrance_controller
			{

				/// Big Dome Button ///
				struct big_dome_button_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x400030;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<big_dome_button_config> big_dome_button;

				/// Big Dome Button LED ///
				struct big_dome_button_led_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x400030;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<big_dome_button_led_config> big_dome_button_led;

				/// Door Sensor ///
				struct door_sensor_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x400030;

					static const uint32_t cfg_member_id = 0x30;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_input<door_sensor_config> door_sensor;

				static void init(net::ipv4_address ip)
				{
					big_dome_button::init(ip);
					big_dome_button_led::init(ip);
					door_sensor::init(ip);

				}

				static void uninit()
				{
					big_dome_button::uninit();
					big_dome_button_led::uninit();
					door_sensor::uninit();

				}
			}

		}

		namespace events
		{

		}

		static void init()
		{
			devices::secret_box_1_controller::init(net::ipv4_address(192,168,100,18));
			devices::secret_box_2_controller::init(net::ipv4_address(192,168,100,19));
			devices::entrance_controller::init(net::ipv4_address(192,168,100,20));


		}

		static void uninit()
		{

			devices::secret_box_1_controller::uninit();
			devices::secret_box_2_controller::uninit();
			devices::entrance_controller::uninit();

		}
	}

}

int main()
{
	alsa_host::init();
	std::thread t = wicc_earpc::init();

	ddf::pirate::init();
	ddf::magician::init();
	ddf::villa::init();
	ddf::junkyard::init();


	t.join();

	ddf::pirate::init();
	ddf::magician::init();
	ddf::villa::init();
	ddf::junkyard::init();


	return 0;
}

