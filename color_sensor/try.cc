#include "color_sensor.h"
#include "stream_reader.h"



int main(int argc, char **argv)
{
    
    std::vector<color_sensor::area> x = 
    {
        color_sensor::area(0,0,1280,720,color(186,193,192),25)
    };
    color_sensor c(x);
    //picture p("colortest2.png");
    //c.__test_color(p);
    stream_reader sr("rtsp://admin:Almafa123@192.168.1.108:554");
    while (true)
    {
        sr.process_frame(std::bind(&color_sensor::check_for_color,&c,std::placeholders::_1));
        for (int i=0;i<x.size();i++)
        {
            const bool b = c.get_result(i);
            std::cout << (b?"true":"false") << std::endl;
        }
    }
    return 0;
}
