#include <earpc/earpc.h>
#include <iostream>

typedef earpc::earpc<earpc::config<uint64_t,uint32_t,1235,1234>> rpc;

#pragma pack(push,1)
struct heartbeat
{
	uint64_t serial;
	uint32_t counter;
};
#pragma pack(pop)

void callback(rpc::outgoing_call_handle<std::string,bool> h)
{
	switch(h.reason)
	{
		case earpc::reason::success:
			journal(journal::info,"test.earpc") << "\e[32mname:" << h.value() << "\e[0m" << journal::end;
			break;

		case earpc::reason::expired:
			journal(journal::info,"test.earpc") << "\e[31mname: (call expired)\e[0m" << journal::end;
			break;

		case earpc::reason::cancelled:
			journal(journal::info,"test.earpc") << "\e[33mname: (call cancelled)\e[0m" << journal::end;
			break;
	}

	rpc::call(
		h.ip,
		0x100,
		true,
		callback
	);
}

void handler(rpc::incoming_call_handle<std::string,bool> h)
{
	if(h.reason == earpc::reason::process)
	{
		journal(journal::info,"test.earpc") << "\e[32marg: {"<<h.value()<<"}\e[0m" << journal::end;
		h.respond("asdf");
	}
}

int main()
{
	journal::init();
	rpc::init();
	rpc::set_command(0x100,handler);

	rpc::call(
		net::ipv4_address(127,0,0,1),
		0x100,
		true,
		callback
	);

	std::string x;
	std::cin >> x;
	earpc::default_earpc::uninit();
	journal::uninit();
};
