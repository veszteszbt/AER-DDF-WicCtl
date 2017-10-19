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

	color()
		: red(0), green(0), blue(0)
	{}

	color(uint8_t r, uint8_t g, uint8_t b)
		: red(r), green(g), blue(b)

	{}

	bool is_near(color _c, uint8_t _eps)
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
