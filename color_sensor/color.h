#ifndef COLOR
#define COLOR
#include <cmath>
#include <cstdint>
struct color {
	uint8_t red, green, blue;
	color() : red(0), green(0), blue(0) {}
	color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
	bool is_near(color _c, uint8_t _eps)
	{
		return
			((abs(_c.red - red) <= _eps) &&
			(abs(_c.green - green) <= _eps) &&
				(abs(_c.blue - blue) <= _eps));
	}
};

#endif