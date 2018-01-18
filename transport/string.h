#ifndef INTEROP_TRANSPORT_STRING_H
# define INTEROP:TRANSPORT_STRING_H
namespace interop {
namespace transport {

void destroy(void *v)
{ delete v; }

class string
{
	char     *data;
	uint32_t  size;

public:
	string(const std::string &s)
	{
		data = new char[s.size()];
		size = s.size();
		memcpy(data,s.data());
	}
};

}}

extern "C" __declspec(dllexport)
void transport_string_release(interop::transport::string s)
{ s.size = 0; delete s.data; }
#endif
