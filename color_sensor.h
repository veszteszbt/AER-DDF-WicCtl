#ifndef COLOR_SENSOR
#define COLOR_SENSOR

//#include <cmath> already included in color.h ??
//#include <cstdint> already included in color.h ??
#include <vector>
#include <iostream>
//#include "color.h" already included in picture.h ??
#include "picture.h"


struct color_sensor
{
    
    struct area
	{
        int x, y, w, h;
        color c;
        uint8_t eps;
        int totalpixel() const
        {
            return w*h;
        }
        area(int _x,int _y,int _w,int _h,color _c,uint8_t _eps) : x(_x), y(_y), w(_w), h(_h), c(_c), eps(_eps) {}

        bool contains(int _x, int _y) const
        {
            return (x <= _x && _x < x+h && y <= _y && _y < y+w);
        }
    };

   

    const std::vector<area> _a;
    bool *result;

	color_sensor(const std::vector<area> &_vec) : _a(_vec), result(new bool[_vec.size()]) {}

    bool get_result(int index)
    {
        return result[index];
    }

    void check_for_color(const picture _p)
    {
        bool not_out_of_bounds[_a.size()];
        uint64_t totalred[_a.size()];
        uint64_t totalgreen[_a.size()];
        uint64_t totalblue[_a.size()];
        for (unsigned int _i=0;_i < _a.size(); _i++)
        {
            not_out_of_bounds[_i] = false;
            totalred[_i] = 0;
            totalgreen[_i] = 0;
            totalblue[_i] = 0;
        }
        color _c;
        for(int _y=0 ; _y < _p.height ; _y++)
        {   
            for(int _x=0; _x < _p.width; _x++)
            {
                for(unsigned int i=0 ; i < _a.size() ; i++)
                {
                    if(_a[i].contains(_x,_y))
                    {
                        not_out_of_bounds[i] = true;
                        _c = _p.picture::get(_x,_y);
                        totalred[i] += _c.red;
                        totalgreen[i] += _c.green;
                        totalblue[i] += _c.blue;
                    }
                }
            }
        }
        int tp;
        for (unsigned int _i=0;_i < _a.size(); _i++)
        {
            if(not_out_of_bounds[_i])
            {
            tp = _a[_i].totalpixel();
            _c.red = static_cast<uint8_t>(totalred[_i] / tp);
            _c.green = static_cast<uint8_t>(totalgreen[_i] / tp);
            _c.blue = static_cast<uint8_t>(totalblue[_i] / tp);
            result[_i] =  _c.is_near(_a[_i].c, _a[_i].eps);
            }
            else 
            {
                std::cout << "Error: area index " << _i << " (the " << _i+1 << ". area) is out of bounds" << std::endl;
                result[_i] = false;
            }
        }
    }
};

#endif