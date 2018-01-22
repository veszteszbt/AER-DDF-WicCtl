#ifndef TRANSPORT_INTTYPES_H
# define TRANSPORT_INTTYPES_H
namespace interop {
namespace transport {


class uint64
{
	uint64_t data;
public:

	uint64(uint64_t v)
		: data(v)
	{}

	operator uint64_t()
	{ return data; }

};

}}
#endif
