#ifndef TRANSPORT_INTTYPES_H
# define TRANSPORT_INTTYPES_H
namespace interop {
namespace transport {

class boolean
{
	bool data;
public:

	boolean(bool v)
		: data(v)
	{}

	operator bool()
	{ return data; }

};

class uint8
{
	uint8_t data;
public:

	uint8(uint8_t v)
		: data(v)
	{}

	operator uint8_t()
	{ return data; }

};

class uint16
{
	uint16_t data;
public:

	uint16(uint16_t v)
		: data(v)
	{}

	operator uint16_t()
	{ return data; }

};
class uint32
{
	uint32_t data;
public:

	uint32(uint32_t v)
		: data(v)
	{}

	operator uint32_t()
	{ return data; }

};
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

class int8
{
	int8_t data;
public:

	int8(int8_t v)
		: data(v)
	{}

	operator int8_t()
	{ return data; }

};

class int16
{
	int16_t data;
public:

	int16(int16_t v)
		: data(v)
	{}

	operator int16_t()
	{ return data; }

};
class int32
{
	int32_t data;
public:

	int32(int32_t v)
		: data(v)
	{}

	operator int32_t()
	{ return data; }

};
class int64
{
	int64_t data;
public:

	int64(int64_t v)
		: data(v)
	{}

	operator int64_t()
	{ return data; }

};


}}
#endif
