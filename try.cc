#include "color_sensor.h"




int main(int argc, char **argv)
{
    
    std::vector<color_sensor::area> x = 
    {
        color_sensor::area(0,0,500,500,color(254,1,1),5),
        color_sensor::area(500,500,500,500,color(1,1,254),5),
        color_sensor::area(1250,1150,500,500,color(1,254,1),5)
    };
    color_sensor c(x);
    picture p("colortest2.png");
    //c.__test_color(p);
    c.check_for_color(p);
    for (int i=0;i<x.size();i++)
    {
        const bool b = c.get_result(i);
        std::cout << (b?"true":"false") << std::endl;
    }
    return 0;
}
