#include <earpc/earpc.h>
#include <iostream>

typedef std::chrono::high_resolution_clock clk;

int main()
{
	std::cout << ::types::time::timestamp(clk::now()) << std::endl;
	return 0;
}
