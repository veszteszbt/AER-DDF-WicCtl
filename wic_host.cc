#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <cstdint>
#include <audio.h>
#include <earpc/udp.h>
#include <earpc/earpc.h>
#include <net/algorithm.h>
#include <wicp/local_property.h>
#include <wicp/remote_property.h>
#include <string>
#include <device_state.h>
#include <game_event.h>
#include <timer.h>
#include <process/sql_executor.h>
#include <property_config_base.h>

#include <peripheral/gpio_output.h>
#include <peripheral/pin_pad.h>


earpc::udp wicc_earpc_config::connection(1234, 1234);

struct devstat_config
{
	typedef wicc_earpc cfg_earpc;
};
typedef device_state<devstat_config> devstat;

/// Site Pin Pad Test
namespace pin_pad_test
{

	/// Room Test Room 1
	namespace test_room_1
	{
		namespace devices
		{

			/// Test Device 1
			namespace test_device_1
			{

				/// Pin Pad ///
				struct pin_pad_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100010;

					static const uint32_t cfg_member_id = 0x10;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::pin_pad<pin_pad_config> pin_pad;

				/// Magnet Lock ///
				struct magnet_lock_config : public property_config_base
				{
					static const uint32_t cfg_class_id = 0x100010;

					static const uint32_t cfg_member_id = 0x20;

					static const uint32_t cfg_cooldown_time = 50;
				};
				typedef peripheral::gpio_output<magnet_lock_config> magnet_lock;

				static void init(net::ipv4_address ip)
				{
					pin_pad::init(ip);
					magnet_lock::init(ip);

				}

				static void uninit()
				{
					pin_pad::uninit();
					magnet_lock::uninit();

				}
			}

		}

		namespace properties
		{

			/// Pin Code ///
			struct pin_code_config : public property_config_base
			{
				typedef std::string cfg_value_type;

				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x20;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<pin_code_config> pin_code;

			/// Typed Pin Code ///
			struct typed_pin_code_config : public property_config_base
			{
				typedef std::string cfg_value_type;

				static const uint32_t cfg_class_id           = 0x1ffff0;
				static const uint32_t cfg_member_id          = 0x30;
				static const uint32_t cfg_cooldown_time      = 10;
				static const bool     cfg_commit_change_only = true;
			};
			typedef wicp::local_property<typed_pin_code_config> typed_pin_code;

		}

		namespace audio
		{

			/// Beeper
			struct beeper_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 1;
			};
			typedef wic::audio<beeper_config> beeper;

		}

		namespace timers
		{
			/// Pin Timeout Timer
			struct pin_timeout_timer_config
			{
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x40;
				static const uint32_t cfg_interval  = 3000;
			};
			typedef typename wic::timer<pin_timeout_timer_config> pin_timeout_timer;


		}

		namespace events
		{
			void pin_timeout()
			{
				typedef typename test_room_1::timers::pin_timeout_timer tmr;
				typedef typename test_room_1::devices::test_device_1::magnet_lock l;
				typedef typename test_room_1::properties::typed_pin_code code;
				typedef typename test_room_1::audio::beeper b;

				if(true && ( tmr::value() ))
				{
					game_event(1,1,6).propagate();
					(void)0; { 
	tmr::stop();
        tmr::reset();
	l::value(1);
	code::value("");
	b::play("/home/torokg/work/escape/audio/test/1");
	std::cout << "\e[33;01mResetting code and closing lock\e[0m" << std::endl;
       }
				}
			}
			void code_test()
			{
				typedef typename test_room_1::properties::typed_pin_code code;
				typedef typename test_room_1::properties::pin_code pin;
				typedef typename test_room_1::devices::test_device_1::magnet_lock l;
				typedef typename test_room_1::timers::pin_timeout_timer tmr;
				typedef typename test_room_1::audio::beeper b;

				if(true && ( code::value().size() > 4 ))
				{
					game_event(1,1,7).propagate();
					(void)0; { 
        const std::string v = code::value();
	code::value("");
        if(v == pin::value())
	{
		std::cout << "\e[32;01m";
		l::value(0);
		tmr::stop();
		b::play("/home/torokg/work/escape/audio/test/2");
	}
	else if(!l::value())
	{
		std::cout << "\e[31;01m"; 
		l::value(1);
		pin::value(v);
		tmr::stop();
		b::play("/home/torokg/work/escape/audio/test/3");
	}
	std::cout << v << "\e[0m" << std::endl;
       }
				}
			}
			void code_accumulate()
			{
				typedef typename test_room_1::devices::test_device_1::pin_pad pp;
				typedef typename test_room_1::properties::typed_pin_code code;
				typedef typename test_room_1::timers::pin_timeout_timer tmr;
				typedef typename test_room_1::audio::beeper b;

				if(true && ( pp::value().state ))
				{
					game_event(1,1,8).propagate();
					(void)0; { 
      	tmr::reset();
        tmr::start();
      	const uint8_t k = pp::value().key;
      	char c;
        if(k < 9)
		c = static_cast<char>(k+49);
	else switch(k)
	{
		b::play("/home/torokg/work/escape/audio/test/4");
		case 9: c = '*'; break;
		case 10: c = '0'; break;
		case 11: c = '#'; break;
		default: c = '?'; break;
	}

	code::value(code::value()+c);
       }
				}
			}

		}

		static void init()
		{
			devices::test_device_1::init(net::ipv4_address(192,168,100,17));

			timers::pin_timeout_timer::on_change += events::pin_timeout;
			properties::typed_pin_code::on_change += events::code_test;
			devices::test_device_1::pin_pad::on_change += events::code_accumulate;

			properties::pin_code::init();

			properties::typed_pin_code::init();


            pin_pad_test::test_room_1::audio::beeper::init();

			timers::pin_timeout_timer::init();

		}

		static void uninit()
		{
			timers::pin_timeout_timer::on_change -= events::pin_timeout;
			properties::typed_pin_code::on_change -= events::code_test;
			devices::test_device_1::pin_pad::on_change -= events::code_accumulate;

			devices::test_device_1::uninit();

			properties::pin_code::uninit();
			properties::typed_pin_code::uninit();

            pin_pad_test::test_room_1::audio::beeper::uninit();

			timers::pin_timeout_timer::init();

		}
	}

}

int main()
{
	alsa_host::init();

	process::sql_executor::init();

	wicc_earpc::init();

	devstat::init();

	pin_pad_test::test_room_1::init();


	std::string x;
	while(true)
	{
		std::cin >> x;
		if(x == "exit")
			break;
	}

	pin_pad_test::test_room_1::init();


	return 0;
}

