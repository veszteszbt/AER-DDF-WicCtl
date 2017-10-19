#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <cstdint>
#include <audio.h>
#include <audio_effect.h>
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

/// Site GMClient Test
namespace gmclient_test
{

	/// Room Test Room 1
	namespace test_room_1
	{

			/// GMClient
			namespace gmclient
			{

				/// GameTime ///
				struct gametime_config : public property_config_base
				{
					typedef uint32_t cfg_value_type;

					static const uint32_t cfg_class_id           = 0x100010;
					static const uint32_t cfg_member_id          = 0x10;
					static const uint32_t cfg_cooldown_time      = 10;
				};
				typedef wicp::remote_property<gametime_config> gametime;

				/// GameState ///
				struct gamestate_config : public property_config_base
				{
					typedef uint8_t cfg_value_type;

					static const uint32_t cfg_class_id           = 0x100010;
					static const uint32_t cfg_member_id          = 0x20;
					static const uint32_t cfg_cooldown_time      = 10;
				};
				typedef wicp::remote_property<gamestate_config> gamestate;

				/// Freezed1 ///
				struct freezed1_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x100010;
					static const uint32_t cfg_member_id          = 0x30;
					static const uint32_t cfg_cooldown_time      = 10;
				};
				typedef wicp::remote_property<freezed1_config> freezed1;

				/// Freezed5 ///
				struct freezed5_config : public property_config_base
				{
					typedef bool cfg_value_type;

					static const uint32_t cfg_class_id           = 0x100010;
					static const uint32_t cfg_member_id          = 0x40;
					static const uint32_t cfg_cooldown_time      = 10;
				};
				typedef wicp::remote_property<freezed5_config> freezed5;

				static void init(net::ipv4_address ip)
				{
					gmclient::gametime::init(ip);
					gmclient::gamestate::init(ip);
					gmclient::freezed1::init(ip);
					gmclient::freezed5::init(ip);

				}

				static void uninit()
				{
					gmclient::gametime::uninit();
					gmclient::gamestate::uninit();
					gmclient::freezed1::uninit();
					gmclient::freezed5::uninit();

				}
			}



			/// Speaker 1
			struct speaker_1_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 1;
			};
			typedef wic::audio<speaker_1_config> speaker_1;

			namespace speaker_1_content
			{
				struct chord_config
				{
					typedef speaker_1 cfg_audio;

					constexpr static const char *cfg_source = "/home/torokg/work/escape/audio/test/4";
				};
				typedef wic::audio_effect<chord_config> chord;

			}

			/// FreezeTimer1
			struct freezetimer1_config
			{
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x30;
				static const uint32_t cfg_interval  = 3000;
			};
			typedef typename wic::timer<freezetimer1_config> freezetimer1;

			/// FreezeTimer5
			struct freezetimer5_config
			{
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x40;
				static const uint32_t cfg_interval  = 15000;
			};
			typedef typename wic::timer<freezetimer5_config> freezetimer5;

			/// GameTimer
			struct gametimer_config
			{
				static const uint32_t cfg_class_id  = 0x1ffff0;
				static const uint32_t cfg_member_id = 0x20;
				static const uint32_t cfg_interval  = 1000;
			};
			typedef typename wic::timer<gametimer_config> gametimer;


			void freeze_1_start()
			{
				typedef typename test_room_1::gmclient::freezed1 fr;
				typedef typename test_room_1::freezetimer1 tmr;
				typedef typename test_room_1::gmclient::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,1,7).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_1_stop()
			{
				typedef typename test_room_1::gmclient::freezed1 fr;
				typedef typename test_room_1::freezetimer1 tmr;
				typedef typename test_room_1::gmclient::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,1,8).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_1_timeout()
			{
				typedef typename test_room_1::freezetimer1 tmr;
				typedef typename test_room_1::gmclient::freezed1 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,1,9).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void freeze_5_start()
			{
				typedef typename test_room_1::gmclient::freezed5 fr;
				typedef typename test_room_1::freezetimer5 tmr;
				typedef typename test_room_1::gmclient::gamestate gs;

				if(true && ( fr::value() ))
				{
					game_event(1,1,10).propagate();
					(void)0; { 
        gs::value(2);
	tmr::start();
       }
				}
			}
			void freeze_5_stop()
			{
				typedef typename test_room_1::gmclient::freezed5 fr;
				typedef typename test_room_1::freezetimer5 tmr;
				typedef typename test_room_1::gmclient::gamestate gs;

				if(true && ( !fr::value() ))
				{
					game_event(1,1,11).propagate();
					(void)0; { 
	tmr::stop();
	tmr::reset();
	gs::value(1);
       }
				}
			}
			void freeze_5_timeout()
			{
				typedef typename test_room_1::freezetimer5 tmr;
				typedef typename test_room_1::gmclient::freezed5 fr;

				if(true && ( tmr::value() ))
				{
					game_event(1,1,12).propagate();
					(void)0; { fr::value(false); }
				}
			}
			void game_state_changed()
			{
				typedef typename test_room_1::gametimer tmr;
			typedef speaker_1_content::chord chord;
				typedef typename test_room_1::gmclient::gamestate gs;
				typedef typename test_room_1::gmclient::freezed1 fr1;
				typedef typename test_room_1::gmclient::freezed5 fr5;

				if(true)
				{
					game_event(1,1,13).propagate();
					(void)0; { 
      	chord::play();
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
			void game_timer_changed()
			{
				typedef typename test_room_1::gametimer tmr;
				typedef typename test_room_1::gmclient::gametime gt;

				if(true)
				{
					game_event(1,1,6).propagate();
					(void)0; { gt::value(tmr::value()); }
				}
			}


		static void init()
		{
			gmclient::init(net::ipv4_address(192,168,1,64));

			gmclient::freezed1::on_change += freeze_1_start;
			gmclient::freezed1::on_change += freeze_1_stop;
			freezetimer1::on_change += freeze_1_timeout;
			gmclient::freezed5::on_change += freeze_5_start;
			gmclient::freezed5::on_change += freeze_5_stop;
			freezetimer5::on_change += freeze_5_timeout;
			gmclient::gamestate::on_change += game_state_changed;
			gametimer::on_change += game_timer_changed;


			gmclient_test::test_room_1::speaker_1::init();
			speaker_1_content::chord::init();


			freezetimer1::init();
			freezetimer5::init();
			gametimer::init();

		}

		static void uninit()
		{
			gmclient::freezed1::on_change -= freeze_1_start;
			gmclient::freezed1::on_change -= freeze_1_stop;
			freezetimer1::on_change -= freeze_1_timeout;
			gmclient::freezed5::on_change -= freeze_5_start;
			gmclient::freezed5::on_change -= freeze_5_stop;
			freezetimer5::on_change -= freeze_5_timeout;
			gmclient::gamestate::on_change -= game_state_changed;
			gametimer::on_change -= game_timer_changed;

			gmclient::uninit();


			speaker_1_content::chord::uninit();

			gmclient_test::test_room_1::speaker_1::uninit();

			freezetimer1::init();
			freezetimer5::init();
			gametimer::init();

		}
	}

}

int main()
{
	alsa_host::init();

	process::sql_executor::init();

	wicc_earpc::init();

	devstat::init();

	gmclient_test::test_room_1::init();


	std::string x;
	while(true)
	{
		std::cin >> x;
		if(x == "exit")
			break;
	}

	gmclient_test::test_room_1::init();


	return 0;
}

