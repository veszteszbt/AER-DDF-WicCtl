#ifndef PICTURE
#define PICTURE
#include <Imlib2.h>
#include "color.h""
//#include <cstdint> already included in color.h ??

struct picture 
{
	int width;
	int height;
	DATA32* data;

	picture(const std::string &path) {
		Imlib_Image image;
		image = imlib_load_image(path.c_str());
		if (image)
		{
			imlib_context_set_image(image);
			width = imlib_image_get_width();
			height = imlib_image_get_height();
			data = imlib_image_get_data_for_reading_only();
		}
		else
		{
			std::cerr << "Error: cannot load image!" << std::endl;
		}
	}

	color get(int x, int y) const
	{
		color c;
		uint8_t *p = reinterpret_cast<uint8_t*>(&data[y*width + x]);
		c.red = p[1];
		c.green = p[2];
		c.blue = p[3];
		return c;
	}

};
#endif
