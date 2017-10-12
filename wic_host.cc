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



earpc::udp wicc_earpc_config::connection(1234, 1234);

struct devstat_config
{
	typedef wicc_earpc cfg_earpc;
};
typedef device_state<devstat_config> devstat;

/// Site Audio test
namespace audio_test
{

	/// Room Test Room 1
	namespace test_room_1
	{
		namespace devices
		{

		}

		namespace properties
		{

		}

		namespace audio
		{

			/// Right
			struct right_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 0;
			};
			typedef wic::audio<right_config> right;

			/// Left
			struct left_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 1;
			};
			typedef wic::audio<left_config> left;

		}

		namespace timers
		{
			/// Beep Timer
			struct beep_timer_config
			{
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x10;
				static const uint32_t cfg_interval  = 2000;
			};
			typedef typename wic::timer<beep_timer_config> beep_timer;


		}

		namespace events
		{
			void beep_timeout()
			{
				typedef typename test_room_1::timers::beep_timer tmr;
				typedef typename test_room_1::audio::right r;
				typedef typename test_room_1::audio::left l;

				if(true && ( tmr::value() ))
				{
					game_event(1,1,4).propagate();
					(void)0; { 
         r::play("/home/nadiia/x.cpp");
       }
				}
			}

		}

		static void init()
		{

			timers::beep_timer::on_change += events::beep_timeout;


            audio_test::test_room_1::audio::right::init();
            audio_test::test_room_1::audio::left::init();

			timers::beep_timer::init();

		}

		static void uninit()
		{
			timers::beep_timer::on_change -= events::beep_timeout;



            audio_test::test_room_1::audio::right::uninit();
            audio_test::test_room_1::audio::left::uninit();

			timers::beep_timer::init();

		}
	}

}

int main()
{
	alsa_host::init();

	process::sql_executor::init();

	wicc_earpc::init();

	devstat::init();

	audio_test::test_room_1::init();


	std::string x;
	while(true)
	{
		std::cin >> x;
		if(x == "exit")
			break;

		else if(x == "start")
			audio_test::test_room_1::timers::beep_timer::start();
		else if(x == "stop")
			audio_test::test_room_1::timers::beep_timer::stop();

		
	}

	audio_test::test_room_1::init();


	return 0;
}

