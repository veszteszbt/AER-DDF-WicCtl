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

#include <device_state.h>
#include <game_event.h>

#include <audio.h>
#include <audio_effect.h>
#include <audio_speech.h>
#include <timer.h>



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
				static const uint8_t cfg_channel = 0;
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

			/// Speaker 2
			struct speaker_2_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 1;
			};
			typedef wic::audio<speaker_2_config> speaker_2;

			namespace speaker_2_content
			{
				struct chord_config
				{
					typedef speaker_2 cfg_audio;

					constexpr static const char *cfg_source = "/home/torokg/work/escape/audio/test/4";
				};
				typedef wic::audio_effect<chord_config> chord;

			}

			/// Speaker 3
			struct speaker_3_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 2;
			};
			typedef wic::audio<speaker_3_config> speaker_3;

			namespace speaker_3_content
			{
				struct chord_config
				{
					typedef speaker_3 cfg_audio;

					constexpr static const char *cfg_source = "/home/torokg/work/escape/audio/test/4";
				};
				typedef wic::audio_effect<chord_config> chord;
				struct test_speech_config
				{
					typedef speaker_3 cfg_audio;

					constexpr static const char *cfg_source = "/home/torokg/work/escape/audio/test/1";

					static const uint32_t cfg_class_id = 0x100070;

					static const uint32_t cfg_member_id = 0x20;
				};
				typedef wic::audio_speech<test_speech_config> test_speech;

			}

			/// Speaker 4
			struct speaker_4_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 3;
			};
			typedef wic::audio<speaker_4_config> speaker_4;

			namespace speaker_4_content
			{
				struct chord_config
				{
					typedef speaker_4 cfg_audio;

					constexpr static const char *cfg_source = "/home/torokg/work/escape/audio/test/4";
				};
				typedef wic::audio_effect<chord_config> chord;

			}

			/// Speaker 5
			struct speaker_5_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 4;
			};
			typedef wic::audio<speaker_5_config> speaker_5;

			namespace speaker_5_content
			{
				struct chord_config
				{
					typedef speaker_5 cfg_audio;

					constexpr static const char *cfg_source = "/home/torokg/work/escape/audio/test/4";
				};
				typedef wic::audio_effect<chord_config> chord;

			}

			/// Speaker 6
			struct speaker_6_config
			{
                		static const uint8_t cfg_device = 0;
				static const uint8_t cfg_channel = 5;
			};
			typedef wic::audio<speaker_6_config> speaker_6;

			namespace speaker_6_content
			{
				struct chord_config
				{
					typedef speaker_6 cfg_audio;

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
					game_event(1,1,13).propagate();
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
					game_event(1,1,14).propagate();
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
					game_event(1,1,15).propagate();
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
					game_event(1,1,16).propagate();
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
					game_event(1,1,17).propagate();
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
					game_event(1,1,18).propagate();
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
					game_event(1,1,19).propagate();
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
					game_event(1,1,12).propagate();
					(void)0; { gt::value(tmr::value()); }
				}
			}
			void speech_test()
			{
			typedef speaker_3_content::test_speech p;

				if(true)
				{
					game_event(1,1,11).propagate();
					(void)0; { 
      	std::cout << "\e[32;01mspeech " << (p::playing()?"playing":"finished") << "\e[0m" << std::endl;
       }
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
			speaker_3_content::test_speech::playing::on_change += speech_test;


			gmclient_test::test_room_1::speaker_1::init();
			speaker_1_content::chord::init();

			gmclient_test::test_room_1::speaker_2::init();
			speaker_2_content::chord::init();

			gmclient_test::test_room_1::speaker_3::init();
			speaker_3_content::chord::init();
			speaker_3_content::test_speech::init();

			gmclient_test::test_room_1::speaker_4::init();
			speaker_4_content::chord::init();

			gmclient_test::test_room_1::speaker_5::init();
			speaker_5_content::chord::init();

			gmclient_test::test_room_1::speaker_6::init();
			speaker_6_content::chord::init();


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
			speaker_3_content::test_speech::playing::on_change -= speech_test;

			gmclient::uninit();


			speaker_1_content::chord::uninit();

			gmclient_test::test_room_1::speaker_1::uninit();
			speaker_2_content::chord::uninit();

			gmclient_test::test_room_1::speaker_2::uninit();
			speaker_3_content::chord::uninit();
			speaker_3_content::test_speech::uninit();

			gmclient_test::test_room_1::speaker_3::uninit();
			speaker_4_content::chord::uninit();

			gmclient_test::test_room_1::speaker_4::uninit();
			speaker_5_content::chord::uninit();

			gmclient_test::test_room_1::speaker_5::uninit();
			speaker_6_content::chord::uninit();

			gmclient_test::test_room_1::speaker_6::uninit();

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
		else if(x=="start")
                        gmclient_test::test_room_1::speaker_3_content::test_speech::playing(true);
                else if(x=="stop")
                        gmclient_test::test_room_1::speaker_3_content::test_speech::playing(false);
		else if(x == "1")
			gmclient_test::test_room_1::speaker_1_content::chord::play();
		else if(x == "2")
			gmclient_test::test_room_1::speaker_2_content::chord::play();
		else if(x == "3")
			gmclient_test::test_room_1::speaker_3_content::chord::play();
		else if(x == "4")
			gmclient_test::test_room_1::speaker_4_content::chord::play();
		else if(x == "5")
			gmclient_test::test_room_1::speaker_5_content::chord::play();
		else if(x == "6")
			gmclient_test::test_room_1::speaker_6_content::chord::play();
		else if(x == "hallo")
			gmclient_test::test_room_1::speaker_6::play("/home/torokg/work/escape/audio/test/1");
		else if(x == "delay")
		{
			int delay;
			std::cin >> delay;

			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}

		else if(x == "gamestate")
		{
			int state;
			std::cin >> state;
			gmclient_test::test_room_1::gmclient::gamestate::value(state);

		}

	}

	gmclient_test::test_room_1::init();


	return 0;
}

