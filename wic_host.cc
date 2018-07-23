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
#include <command_line/shell.hh>

struct dm_config
{
	typedef wicc_earpc cfg_earpc;

	static const uint32_t cfg_expiry_timeout = 3200;
};
typedef devman::devman<dm_config> dm;

/// Site DDF
namespace ddf
{
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

template<typename... Targs>
struct shell_filler;

template<typename T, typename... Targs>
struct shell_filler<T, Targs...>
{
	static void exec(commandline::shell &s)
	{ shell_filler<Targs...>::exec(s); }
};

/* code of exec here >) */
template<typename TConfig, typename... Targs>
struct shell_filler<property_room<TConfig>, Targs...>
{
	static void foo(typename TConfig::cfg_value_type x)
	{ property_room<TConfig>::value(x); }


	static typename TConfig::cfg_value_type bar()
	{ return property_room<TConfig>::value(); }

	static void exec(commandline::shell &s)
	{
    	s.add_command(std::string(TConfig::name)+"::get", bar );
    	s.add_command(std::string(TConfig::name)+"::set", foo );
    	shell_filler<Targs...>::exec(s);
	}
};

template<>
struct shell_filler<>
{
	static void exec(commandline::shell &s)
	{ return; }
};

int main()
{
	journal::init();

	alsa_host::init();

	//process::sql_executor::init();

	wicc_earpc::init();

	dm::init();

	init();
	ddf::service::statustimer::start();

	commandline::shell s;
	shell_filler<
	        ddf::magician::keyswitch_active,
		ddf::magician::pin_code_accumulation,
		ddf::magician::pin_code_test_alias_safe_activation,
		ddf::magician::pin_timeout,
		ddf::magician::reset_room,
		ddf::magician::rfid_tag_correct,
		ddf::magician::safecode_entry_activaion,
		ddf::magician::stop_audios,
		ddf::magician::time_up
	>::exec(s);

	s.execute();

	uninit();

	journal::uninit();
	return 0;
}

