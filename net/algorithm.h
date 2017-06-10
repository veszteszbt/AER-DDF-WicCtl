#ifndef NET_ALGORITHM_H
# define NET_ALGORITHM_H
# include <types/integer.h>
namespace net
{
	namespace algorithm
	{
		bool checksum_create(volatile void *target, uint16_t length, uint16_t checksum_pos)
		{
			volatile uint16_t *const data = reinterpret_cast<volatile uint16_t*>(target);
			if(reinterpret_cast<uintptr_t>(data)&1)
				return false;
			if(checksum_pos >= length-1)
				return false;
			uint32_t r = 0;
			const uint32_t ci = checksum_pos/2;
			const uint32_t l = length/2;
			for(int i = 0; i < ci; ++i)
				r += data[i];
			for(int i = ci+1; i < l; ++i)
				r += data[i];
			while(r > 0xffff)
				r = (r & 0xffff) + (r>>16);

			data[ci] = static_cast<uint16_t>(~r);
			return true;
		}

		uint32_t checksum_add(const volatile void *source, uint16_t length)
		{
			const volatile uint8_t *const data = reinterpret_cast<const volatile uint8_t*>(source);
			uint32_t r = 0;
			for(int i = 0; i < length; i++)
				if (i & 1)
					r += static_cast<uint32_t>(data[i]) << 8;
				else
					r += static_cast<uint32_t>(data[i]);
			return r;
		}

		uint16_t checksum_finish(uint32_t s)
		{
			while(s>>16)
				s = (s & 0xffff) + (s >> 16);
			return ::types::integer::htons(static_cast<uint16_t>(~s));
		}

		bool checksum_verify(uint32_t s)
		{ return !checksum_finish(s); }

		bool checksum_verify(const volatile void *source, uint16_t length)
		{ return checksum_verify(checksum_add(source,length)); }
	}
}
#endif
