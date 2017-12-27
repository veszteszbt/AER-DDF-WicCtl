#ifndef EARPC_SERIALIZER_H
# define EARPC_SERIALIZER_H
namespace earpc {

template<typename T>
struct serializer
{
	static bool serialize(const T &t, std::vector<uint8_t> &out)
	{
		static_assert(sizeof(T)<=512,"Objects greater than 512 bytes cannot be sent via earpc");
		out.reserve(sizeof(T));
		out.clear();
		const uint8_t *b = reinterpret_cast<const uint8_t*>(&t);
		out.insert(out.end(),b,b+sizeof(T));
		return true;
	}

	static bool deserialize(T &t, const std::vector<uint8_t> &in)
	{
		if(sizeof(T) != in.size())
			return false;

		uint8_t *b = reinterpret_cast<uint8_t*>(&t);
		std::copy(in.begin(),in.end(),b);
		return true;
	}

	static uint16_t size()
	{ return sizeof(T); }
};

template<>
bool serializer<std::string>::serialize(const std::string &t, std::vector<uint8_t> &out)
{
	if(t.size() > 512)
		return false;
	out.reserve(t.size());
	out.clear();
	const uint8_t *b = reinterpret_cast<const uint8_t*>(t.c_str());
	out.insert(out.end(),b,b+t.size());
	return true;
}

template<>
bool serializer<std::string>::deserialize(std::string &t, const std::vector<uint8_t> &in)
{
	t.reserve(in.size());
	t.clear();
	t.insert(t.end(),in.begin(),in.end());
	return true;
}

template<>
uint16_t serializer<std::string>::size()
{ return 0xffff; }

}
#endif
