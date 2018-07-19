#include "type.h"
#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
namespace types{
namespace type{
std::string demangle(const std::string &n)
{

	int status = -4; // some arbitrary value to eliminate the compiler warning

	// enable c++11 by passing the flag -std=c++11 to g++
	std::unique_ptr<char, void(*)(void*)> res {
		abi::__cxa_demangle(n.c_str(), NULL, NULL, &status),
		std::free
	};

	return (status==0) ? res.get() : n ;
}
}
}
#else
namespace types
{
// does nothing if not g++

std::string demangle(const std::string &n)
{ return n; }

}
#endif
