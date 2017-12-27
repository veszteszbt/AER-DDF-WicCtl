#include <earpc/earpc.h>
#include <iostream>

#pragma pack(push,1)
struct heartbeat
{
	uint64_t serial;
	uint32_t counter;
};
#pragma pack(pop)

void name_callback(earpc::default_earpc::outgoing_call_handle<std::string,bool> h)
{
	switch(h.reason)
	{
		case earpc::reason::success:
			std::cout << "\e[32mname:" << h.value() << "\e[0m" << std::endl;
			break;

		case earpc::reason::expired:
			std::cout << "\e[31mname: (call expired)\e[0m" << std::endl;
			break;

		case earpc::reason::cancelled:
			std::cout << "\e[33mname: (call cancelled)\e[0m" << std::endl;
			break;
	}

	uint32_t cid = earpc::default_earpc::call(
		net::ipv4_address(192,168,10,1),
		0xffffffff00004003,
		true,
		name_callback
	);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	earpc::default_earpc::reroute(cid,net::ipv4_address(10,1,0,56));
	std::this_thread::sleep_for(std::chrono::milliseconds(600));
	earpc::default_earpc::cancel(cid);
}

void heartbeat_handler(earpc::default_earpc::incoming_call_handle<bool,heartbeat> h)
{
	if(h.reason == earpc::reason::process)
	{
		const heartbeat x(h.value());
		journal(journal::info,"test.earpc") << "\e[32marg: {"<<std::hex<<x.serial<<","<<std::dec<<x.counter<<"}\e[0m" << journal::end;
		h.respond(true);
	}
}

int main()
{
	journal::init();
	earpc::default_earpc::init();
	earpc::default_earpc::set_command(0xffffffff0ffff000,heartbeat_handler);	
	earpc::default_earpc::call(
		net::ipv4_address(192,168,10,1),
		0xffffffff00004003,
		true,
		name_callback
	);

	std::string x;
	std::cin >> x;
	earpc::default_earpc::uninit();
	journal::uninit();
};
