#ifndef PICTURE
#define PICTURE
#include <stdio.h>
extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
}
#include <vector>
#include "color.h"

struct picture 
{
	int width;
	int height;
	AVFrame* data; //todo: private
	

	
	/*picture(const std::string &path) {
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
	}*/
	picture(int _width,int _height, AVFrame* frame) : width(_width), height(_height)
	{
		data=frame;
		//std::cout << "width: " << width << "  height: " << height;
	}
	


	color get(int x, int y) const
	{
		color c;
		uint8_t *p = reinterpret_cast<uint8_t*>(data->data[0]+y*data->linesize[0]+x*3);
		c.red = p[0];
		c.green = p[1];
		c.blue = p[2];
		return c;
	}
};
#endif
