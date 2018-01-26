#ifndef COLOR
#define COLOR

#include <cmath>
#include <cstdint>

namespace video {

struct color
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	constexpr color()
		: red(0), green(0), blue(0)
	{}

	constexpr color(uint8_t r, uint8_t g, uint8_t b)
		: red(r), green(g), blue(b)

	{}

	constexpr color(uint32_t c)
		: red((c>>16)&0xff)
		, green((c>>8)&0xff)
		, blue(c&0xff)
	{}

	bool is_near(color _c, uint8_t _eps) const
	{
		return
			abs((int)_c.red - (int)red) <= _eps &&
			abs((int)_c.green - (int)green) <= _eps &&
			abs((int)_c.blue - (int)blue) <= _eps
		;
	}
};

}
#endif
