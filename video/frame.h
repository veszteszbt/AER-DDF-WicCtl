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
#include <video/color.h>

namespace video {

class frame 
{
	AVFrame * const data;
public:
	const int width;

	const int height;

	frame(int _width,int _height, AVFrame* frame)
		: width(_width), height(_height), data(frame)
	{}
	
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

}
#endif
