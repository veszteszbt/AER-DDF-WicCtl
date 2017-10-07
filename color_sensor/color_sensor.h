#ifndef COLOR_SENSOR
#define COLOR_SENSOR

#include <cmath>
#include <cstdint>
#include <vector>
#include <iostream>
#include <Imlib2.h>


class color_sensor{
public:
    class color{
    public:
        uint8_t red, green, blue;
        color() : red(0), green(0), blue(0) {}
        color(uint8_t r,uint8_t g,uint8_t b) : red(r), green(g), blue(b) {}
        bool is_near(color _c, uint8_t _eps)
        {
            return
            ((abs(_c.red - red) <= _eps) &&
            (abs(_c.green - green) <= _eps) &&
            (abs(_c.blue - blue) <= _eps));
        }
    };

    class area{
    public:
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

    class picture{
    public:
        int width;
        int height;
        DATA32* data;
    
        picture(const std::string &path){
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
    
    color get(int x,int y) const
    {
        color c;
        uint8_t *p = reinterpret_cast<uint8_t*>(&data[y*width+x]);
        c.red = p[1];
        c.green = p[2];
        c.blue = p[3];
        return c;
    }
    
    };

    const std::vector<area> _a;
    bool* result;

    color_sensor(const std::vector<area> &_vec) : _a(_vec) 
    {
        result = new bool[_vec.size()];
    }

    void check_for_color(const picture _p)
    {
        uint64_t totalred[_a.size()];
        uint64_t totalgreen[_a.size()];
        uint64_t totalblue[_a.size()];
        for (unsigned int _i=0;_i < _a.size(); _i++)
        {
            totalred[_i] = 0;
            totalgreen[_i] = 0;
            totalblue[_i] = 0;
        }
        int _x = 0;
        int _y = 0;
        unsigned int i = 0;
        color _c;
        while (_y < _p.height)
        {   
            while (_x < _p.width)
            {
                i=0;
                while (i < _a.size())
                {
                    if(_a[i].contains(_x,_y))
                    {
                        _c = _p.get(_x,_y);
                        totalred[i] += _c.red;
                        totalgreen[i] += _c.green;
                        totalblue[i] += _c.blue;
                    }
                    i++;
                }
                _x++;
            }
            _x = 0;
            _y++;
        }
        int tp;
        for (unsigned int _i=0;_i < _a.size(); _i++)
        {
            tp = _a[_i].totalpixel();
            _c.red = static_cast<uint8_t>(totalred[_i] / tp);
            _c.green = static_cast<uint8_t>(totalgreen[_i] / tp);
            _c.blue = static_cast<uint8_t>(totalblue[_i] / tp);
            result[_i] =  _c.is_near(_a[_i].c, _a[i].eps);
        }
    }
};

#endif