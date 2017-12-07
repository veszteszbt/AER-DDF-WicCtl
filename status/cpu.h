#ifndef STATUS_CPU_H
# define STATUS_CPU_H
# include <fstream>
# include <string>
namespace status {

	class cpu
	{
		
	public:
		static void init()
		{}

		static void uninit()
		{}

		static uint32_t cores()
		{
			std::ifstream f("/proc/cpuinfo");
			if(!f)
				return 1;

			uint32_t r = 0;
			while(f)
			{
				std::string x;
				f >> x;
				if(x != "processor")
					continue;
				f >> x;
				if(x != ":")
					continue;	

				uint32_t y;
				f >> y;
				if(!f)
					continue;
				++r;
			}
			f.close();
			return r;
		}

		static double usage()
		{

			std::ifstream f("/proc/loadavg");
			if(!f)
				return 0;

			double r = 0;
			f >> r;
		
			if(!f)
				return 0;
			f.close();
			r /= cores();
			if(r > 1)
				r = 1;

			return r;
		}
	};
}
#endif
