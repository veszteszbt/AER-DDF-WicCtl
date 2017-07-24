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

namespace pirate {
namespace map {

	struct magnet1_config : public property_config_base
	{
		typedef bool cfg_value_type;

		static const bool cfg_commit_change_only = true;

		static const uint32_t cfg_class_id = 0x100010;

		static const uint32_t cfg_member_id = 0x10;

		static const uint32_t cfg_cooldown_time = 200;

	};
	typedef wicp::remote_property<magnet1_config> magnet1;
}
}

namespace villa {
namespace control
{

		struct switch1_config : public property_config_base
		{
			typedef uint8_t cfg_value_type;

			static const bool cfg_commit_change_only = true;

			static const uint32_t cfg_class_id = 0x300030;

			static const uint32_t cfg_member_id = 0x10;

			static const uint32_t cfg_cooldown_time = 50;

		};
		typedef wicp::remote_property<switch1_config> switch1;

		struct switch2_config : public property_config_base
		{
			typedef uint8_t cfg_value_type;

			static const bool cfg_commit_change_only = true;

			static const uint32_t cfg_class_id = 0x300030;

			static const uint32_t cfg_member_id = 0x20;

			static const uint32_t cfg_cooldown_time = 50;

		};
		typedef wicp::remote_property<switch2_config> switch2;
	
		static void switch1_notify()
		{
			std::cout << "\e[37;01mSwitch 1: " << std::dec << (int)switch1::value() << "\e[0m" << std::endl;
		}

		static void switch2_notify()
		{
			std::cout << "\e[37;01mSwitch 2: " << std::dec << (int)switch2::value() << "\e[0m" << std::endl;
		}
}}

int main()
{
	std::thread t = wicc_earpc::init();

	pirate::map::magnet1::init(net::ipv4_address(192,168,100,1));

	villa::control::switch1::init(net::ipv4_address(192,168,100,16));
	villa::control::switch1::on_change(villa::control::switch1_notify);

	villa::control::switch2::init(net::ipv4_address(192,168,100,16));
	villa::control::switch2::on_change(villa::control::switch2_notify);

	int c;
	while(std::cin)
	{

	}

	t.join();
	return 0;
}

