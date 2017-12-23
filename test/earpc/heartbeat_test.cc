#include <earpc/earpc.h>
#include <iostream>

#pragma pack(push,1)
struct heartbeat
{
	uint64_t serial;
	uint32_t counter;
};
#pragma pack(pop)
void heartbeat_handler(earpc::default_earpc::incoming_call_handle<bool,heartbeat> h)
{
	const heartbeat x(h.value());
	journal(journal::info,"test.earpc") << "\e[32marg: {"<<std::hex<<x.serial<<","<<std::dec<<x.counter<<"}\e[0m" << journal::end;
	h.respond(true);
}

int main()
{
	journal::init();
	earpc::default_earpc::init();
	earpc::default_earpc::set_command(0xffffffff0ffff000,heartbeat_handler);	

	std::string x;
	std::cin >> x;
	earpc::default_earpc::uninit();
	journal::uninit();
};
