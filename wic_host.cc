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

static void call_finished(net::ipv4_address,uint64_t,const uint8_t *v)
{
	if(v)
		std::cout << "Owl notified" << std::endl;
	else
		std::cout << "Could not notify owl" << std::endl;
}

static void cmd_handler(
	wicc_earpc::call_handle<uint8_t> call_handle,
	const bool *door_state
)
{
	std::cout << "Door state: " << ((*door_state)?"open":"closed") << std::endl;
	wicc_earpc::call(net::ipv4_address(192,168,1,102),0x10000000b,*door_state,&call_finished);
	wicc_earpc::call(net::ipv4_address(192,168,1,100),0x10000000b,*door_state,&call_finished);
	call_handle.respond(1);
}

int main()
{
	wicc_earpc::set_command(0x10000000b,cmd_handler);
	wicc_earpc::init().join();

	while(std::cin)
	{
		std::cin.get();
	}

	return 0;
}

