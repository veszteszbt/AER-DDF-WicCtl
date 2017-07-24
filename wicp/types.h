#ifndef WICP_TYPES_H
# define WICP_TYPES_H
namespace wicp {
namespace types
{
	struct function
	{
		static const uint8_t call = 0;
		static const uint8_t get = 1;
		static const uint8_t set = 2;
		static const uint8_t notify = 3;
	};
	
}}
#endif
