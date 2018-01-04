#ifndef DEVMAN_TYPES_H
# define DEVMAN_TYES_H
namespace devman {
namespace types {

#pragma pack(push,1)
struct
heartbeat_payload_type
{
	uint64_t serial;
	uint32_t counter;

	explicit operator std::string() const
	{
		std::stringstream s;
		s << '{' << std::hex << serial << ',' << std::dec << counter << '}';
		return s.str();
	}
};
#pragma pack(pop)

struct state
{
	static const uint8_t unseen = 0;

	static const uint8_t identify = 1;

	static const uint8_t active = 2;
};

}}
#endif
