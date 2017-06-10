#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <cstdint>
#include <earpc/udp.h>
#include <earpc/earpc.h>
#include <net/algorithm.h>

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

static void cmd_handler(
	wicc_earpc::call_handle<uint8_t> call_handle,
	const uint8_t *color
)
{
	std::cout << "color: \e[3" << (int)((*color)&7) << ";01m####\e[0m" << std::endl;
	call_handle.respond(*color);
}

int main()
{
	wicc_earpc::set_command(4,cmd_handler);
	wicc_earpc::init().join();

	return 0;
}

