#ifndef EARPC_SERIALIZER_H
# define EARPC_SERIALIZER_H
namespace earpc {
namespace serializer {

template<typename T>
bool serialize(T t, std::vector<uint8_t> &out)
{
	static_assert(sizeof(T)<=512,"Objects greater than 512 bytes cannot be sent via earpc");
	out.reserve(sizeof(T));
	out.clear();
	const uint8_t *b = reinterpret_cast<uint8_t*>(&t);
	out.insert(b,b+sizeof(T));
	return true;
}

template<>
bool serialize(std::string t, std::vector<uint8_t> &out)
{
	if(t.size() > 512)
		return false;
	out.reserve(t.size());
	out.clear();
	const uint8_t *b = reinterpret_cast<uint8_t*>(t.c_str());
	out.insert(b,b+t.size());
	return true;
}
}}
#endif
