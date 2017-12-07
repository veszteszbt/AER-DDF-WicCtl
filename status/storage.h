#ifndef STATUS_STORAGE_H
# define STATUS_STORAGE_H
# include <sys/statvfs.h>
namespace status {
	class storage
	{
	public:
		static void init()
		{}

		static void uninit()
		{}

		static uint64_t total()
		{
			struct statvfs buf;
			statvfs("/var/",&buf);
			return buf.f_blocks*buf.f_bsize;
		}

		static uint64_t free()
		{	
			struct statvfs buf;
			statvfs("/var/",&buf);
			return buf.f_bavail*buf.f_bsize;
		}

		static uint64_t used()
		{ return total()-free(); }
	};
}
#endif
