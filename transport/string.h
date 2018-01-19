#ifndef INTEROP_TRANSPORT_STRING_H
# define INTEROP_TRANSPORT_STRING_H
#include <string>
namespace interop {
namespace transport {

class string
{
	char     *data;
	uint32_t  size;

public:
	string(uint32_t psize)
		: data(new char[psize])
		, size(psize)
	{}
		
	string(const std::string &s)
		: data(new char[s.size()])
		, size(s.size())
	{ memcpy(data,s.data(),size); }

	void release()
	{
		delete data;
		data = 0;
		size = 0;
	}

	operator std::string()
	{
		if(data)
		{
			const std::string rv(data,data+size);
			release();
			return rv;
		}
		return std::string();
	}

};

}}

extern "C"
#ifndef __linux__
__declspec(dllexport)
#endif
interop::transport::string interop_transport_string_alloc(uint32_t size)
{ return interop::transport::string(size); }

extern "C"
#ifndef __linux__
__declspec(dllexport)
#endif
void interop_transport_string_free(interop::transport::string s)
{ s.release(); }

#endif
