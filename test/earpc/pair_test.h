typedef earpc::earpc<earpc::config<uint64_t,uint32_t,sport,dport>> rpc;

#pragma pack(push,1)
struct heartbeat
{
	uint64_t serial;
	uint32_t counter;
};
#pragma pack(pop)

static volatile double acc_usecs = 0;
static volatile uint64_t divisor = 0;

static volatile int64_t started_calls = 0;
static volatile int64_t finished_calls = 0;

static std::mutex lock;

void callback(rpc::outgoing_call_handle<std::string,bool> h)
{
	switch(h.reason)
	{
		case earpc::reason::success:
			journal(journal::info,"test.earpc") << "\e[32mcall succeeded\e[0m" << journal::end;
			 break;

		case earpc::reason::expired:
			journal(journal::info,"test.earpc") << "\e[31m(call expired)\e[0m" << journal::end;
			break;

		case earpc::reason::cancelled:
			journal(journal::info,"test.earpc") << "\e[33m(call cancelled)\e[0m" << journal::end;
			break;
	}

	const double fu = types::time::fusec(h.finished-h.activated);
	journal(journal::info,"test.earpc") << "\e[32mcall dt: " << std::dec << fu << " usec\e[0m" << journal::end;

	lock.lock();
	acc_usecs += fu;
	++divisor;
	++finished_calls;
	const int64_t unfinished_calls = started_calls-finished_calls;
	if(acc_usecs > 3000000)
	{
		std::cerr <<
			"number of calls: " << std::dec << divisor <<
			"; avg transmit dt: " << acc_usecs/divisor << " usec" <<
			"; started calls: " << started_calls << 
			"; finished calls: " << finished_calls <<
			"; unfinished calls: " << unfinished_calls << std::endl;

		acc_usecs = 0;
		divisor = 0;
		lock.unlock();
	
		if(unfinished_calls <= 0)
			for(int i = 0; i < 16384; ++i)
			{
				lock.lock();
				++started_calls;
				lock.unlock();
				rpc::call(
					h.ip,
					0x100,
					true,
					callback
				);
			}
	}
	else
		lock.unlock();

	if(unfinished_calls <= 0)
	{
		lock.lock();
		++started_calls;
		lock.unlock();
		rpc::call(
			h.ip,
			0x100,
			true,
			callback
		);
	}
}

void handler(rpc::incoming_call_handle<std::string,bool> h)
{
	if(h.reason == earpc::reason::process)
	{
		journal(journal::info,"test.earpc") << "\e[37marg: {"<<h.value()<<"}\e[0m" << journal::end;
		h.respond("asdf");
	}
}

int main()
{
	journal::init();
	journal::min_level = 0;
	rpc::init();
	rpc::set_command(0x100,handler);

	++started_calls;
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
