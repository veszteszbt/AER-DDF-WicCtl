#include "color_sensor.h"




int main(int argc, char **argv)
{
    
    std::vector<color_sensor::area> x = {
        color_sensor::area(0,0,500,500,color_sensor::color(254,1,1),3),
        color_sensor::area(500,500,500,500,color_sensor::color(1,1,254),3)
    };
    color_sensor c(x);
    color_sensor::picture p("colortest.png");
    color_sensor::check_for_color(p);
    return 0;
}
