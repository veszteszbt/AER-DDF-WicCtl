#include <iostream>
#include <earpc/earpc.h>
#include <wicp/local_property.h>
#include <wicp/remote_property.h>

typedef earpc::earpc<earpc::config<uint64_t,uint32_t,1234,1234>> rpc;

int main()
{
	journal::init();
	journal::min_level = 0;
	rpc::init();

	std::string x;
	std::cin >> x;

	rpc::uninit();
	journal::uninit();
};
