#ifndef WIC_COLOR_SENSOR_H
#define WIC_COLOR_SENSOR_H

#include "color_sensor/try/color_checker.h"
#include "color_sensor/try/stream_reader.h"

namespace wic
{
    template<typename TConfig>
    class color_sensor
    {

        static color_checker* c;
        static stream_reader* sr;
        static volatile bool disposed;
        static std::thread* proc;
        static std::vector<color_checker::area> x = TConfig::cfg_areas;
        
        static void thread_start()
		{
			while(!disposed)
			{
                sr.process_frame(std::bind(&color_checker::check_for_color,&c,std::placeholders::_1));
                for (int i=0;i<x.size();i++)
                {
                    const bool b = c.get_result(i);
                    std::cout << (b?"true":"false") << std::endl;
                }

            }
		}
        
    public:
		static void init()
		{
			property::init();
			disposed = false;
			proc = new std::thread(thread_start);
		}

		static void uninit()
		{
			delete proc;
			property::uninit();
        }
        
        static void start()
		{
			disposed = true;
        }
        
        static void stop()
        {
            disposed = false;
        }
    }


    template<typename c>
    volatile bool color_sensor<c>::disposed;

    template<typename c>
    std::thread *color_sensor<c>::proc;
    
    template<typename c>
    *color_sensor<c>::c;

    template<typename c>
    *color_sensor<c>::sr;

}





#endif
