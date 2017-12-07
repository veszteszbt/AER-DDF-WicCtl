#ifndef STATUS_MEMORY_H
# define STATUS_MEMORY_H
namespace status{
	class memory
	{
		static uint64_t read_meminfo_field(const std::string &field)
		{
			const std::string k = field+':';
			std::ifstream f("/proc/meminfo");
			if(!f)
				return 0;

			std::string x;
			uint64_t r = 0;
			while(f)
			{
				f >> x;
				if(x != k)
					continue;
				f >> r;
				break;
			}
			
			f.close();
			return r;
			
		}
	public:
		static void init() {}

		static void uninit() {}

		static uint64_t total()
		{ return read_meminfo_field("MemTotal"); }

		static uint64_t free()
		{ return read_meminfo_field("MemAvailable"); }

		static uint64_t used()
		{ return total()-free(); }

	};
}
#endif
