#ifndef DEVMAN_PROCESS_EXPIRY_H
# define DEVMAN_PROCESS_EXPIRY_H
namespace devman {
namespace process {

template<typename TEnv>
class expiry
{
public:
	static void init()
	{}

	static void uninit()
	{}

	static void notify()
	{}
};
}}
#endif
