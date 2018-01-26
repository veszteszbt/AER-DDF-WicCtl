#ifndef COLOR_CHECKER
#define COLOR_CHECKER

//#include <cmath> already included in color.h ??
//#include <cstdint> already included in color.h ??
#include <vector>
#include <iostream>
#include <video/frame.h>
#include <video/color.h>
#include <journal.h>

namespace video
{
	struct color_checker
	{
		struct area
		{
			int x, y, w, h;
			color c;
			uint8_t eps;

			constexpr area(int _x,int _y,int _w,int _h,color _c,uint8_t _eps)
				: x(_x), y(_y), w(_w), h(_h), c(_c), eps(_eps)
			{}

			bool contains(int _x, int _y) const
			{ return (x <= _x && _x < x+w && y <= _y && _y < y+h); }
		};
	private:
		const std::vector<area> _a;
		bool *result;

	public:


		color_checker(const std::initializer_list<area> &_vec)
			: _a(_vec), result(new bool[_vec.size()])
		{}

		size_t size() const
		{ return _a.size(); }

		bool get_result(int index)
		{ return result[index]; }

		void check_for_color(const frame _p)
		{
			bool not_out_of_bounds[_a.size()];
			uint64_t totalred[_a.size()];
			uint64_t totalgreen[_a.size()];
			uint64_t totalblue[_a.size()];
			uint64_t totalpixels[_a.size()];
			for (unsigned int _i=0;_i < _a.size(); _i++)
			{
				not_out_of_bounds[_i] = false;
				totalred[_i] = 0;
				totalgreen[_i] = 0;
				totalblue[_i] = 0;
				totalpixels[_i] = 0;
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
							++totalpixels[i];
							not_out_of_bounds[i] = true;
							_c = _p.get(_x,_y);

							totalred[i] += _c.red;
							totalgreen[i] += _c.green;
							totalblue[i] += _c.blue;
						}
					}
				}
			}

			for (unsigned int _i=0;_i < _a.size(); _i++)
			{
				if(not_out_of_bounds[_i])
				{
					_c.red = static_cast<uint8_t>(totalred[_i] / totalpixels[_i]);
					_c.green = static_cast<uint8_t>(totalgreen[_i] / totalpixels[_i]);
					_c.blue = static_cast<uint8_t>(totalblue[_i] / totalpixels[_i]);
					const bool r = _c.is_near(_a[_i].c, _a[_i].eps);
					result[_i] = r;

					journal(journal::debug,"video.color_checker") <<
						"area: " << _i <<
						"; " << (r?"match":"no match") <<
						"; avg area color: (" << std::dec <<
						(int)_c.red << ',' << (int)_c.green << ',' << (int)_c.blue << ")" <<
						"; expected color: ("  <<
						(int)_a[_i].c.red << ',' << (int)_a[_i].c.green << ',' << (int)_a[_i].c.blue << ")" <<
						" +- " << (int)_a[_i].eps <<
						journal::end;
				}
				else
				{
					journal(journal::error,"video.color_checker") <<
						"area index " << _i << ": no image pixel within specified bounds" << std::dec <<
						"; frame size: " << _p.width << 'x' << _p.height <<
						"; area bounds: " << _a[_i].x << ',' << _a[_i].y << ' ' << _a[_i].w << 'x' << _a[_i].h <<
						journal::end;
					result[_i] = false;
				}
			}
		}
	};
}
#endif
