#ifndef TYPES_INTEGER_H
# define TYPES_INTEGER_H
# include <algorithm>
# include <type_traits>
# include <cstdint>
namespace types
{
	namespace integer
	{
		//! Provides a type large enough for \a value
		/*! Provides an unsigned integral member type <code>type</code>, which is large enough for
		    <code>value</code> to fit in
		  */
		template<uint64_t value>
		struct ufit
		{
			//! An unsigned integral type in which \a value fits 
			typedef typename std::conditional<
				value <= static_cast<uint8_t>(-1),
				uint8_t,
				typename std::conditional<
					value <= static_cast<uint16_t>(-1),
					uint16_t,
					typename std::conditional<
						value <= static_cast<uint32_t>(-1),
						uint32_t,
						uint64_t
					>::type
				>::type
			>::type type;
		};


		//! Provides an unsigned type which consists of at least \a bits bits
		/*! Provides an unsigned integral member type <code>type</code>, which consists of at least
		    <code>bits</code> bits
		  */
		template<uint8_t bits>
		struct ubits
		{
			static_assert(bits <= 64, "The largest unsigned integer representation is 64 bits long");

			typedef typename std::conditional<
				bits <= 8,
				uint8_t,
				typename std::conditional <
					bits <= 16,
					uint16_t,
					typename std::conditional <
						bits <= 32,
						uint32_t,
						uint64_t
					>::type
				>::type
			>::type type;
		};

		//! Provides a type which consists of at least \a bits bits
		/*! Provides a signed integral member type <code>type</code>, which consists of at least
		    <code>bits</code> bits
		  */
		template<uint8_t bits>
		struct sbits
		{
			static_assert(bits <= 64, "The largest signed integer representation is 64 bits long");

			typedef typename std::conditional<
				bits <= 8,
				int8_t,
				typename std::conditional <
					bits <= 16,
					int16_t,
					typename std::conditional <
						bits <= 32,
						int32_t,
						int64_t
					>::type
				>::type
			>::type type;
		};


		//! Provides a type which is the signed equivalent of \a T
		/*! Provides a signed integral member type <code>type</code>, which is the signed equivalent
		    of <code>T</code>
		 */
		template<typename T>
		struct sequ
		{
			static_assert(
				std::is_integral<T>::value,
				"value must be of an integral type"
			);
			typedef typename sbits<sizeof(T)*8>::type type;
		};

		//! Provides a type which is the unsigned equivalent of \a T
		/*! Provides an unsigned integral member type <code>type</code>, which is the unsigned equivalent
		    of <code>T</code>
		 */
		template<typename T>
		struct uequ
		{
			static_assert(
				std::is_integral<T>::value,
				"value must be of an integral type"
			);
			typedef typename ubits<sizeof(T)*8>::type type;
		};

		//! Provides a signed type large enough for \a value
		/*! Provides an signed integral member type <code>type</code>, which is large enough for
		    <code>value</code> to fit in
		  */
		template<int64_t value>
		struct sfit
		{ typedef typename sequ<typename ufit<static_cast<uint64_t>(value)>::type>::type type; };


		//! Returns the absolute value of the integer passed via \a value
		template<typename T>
		T abs(T value)
		{
			static_assert(
				std::is_integral<T>::value,
				"value must be of an integral type"
			);

			return (value < 0) ? -value : value;
		}

		//! Converts integer specified via \a value to string according to the base given via \a tBase
		template<unsigned tBase,typename T>
		void itoa(T value, char *buffer, unsigned size)
		{
			static_assert(tBase <= 16,"base must be at most 16");
			static_assert(tBase > 1,"base must be at least 2");
			static_assert(
				std::is_integral<T>::value,
				"value must be of an integral type"
			);

			constexpr static const char *digits = "0123456789abcdef";
				
			if(!size)
				return;

			--size;
			if(!size)
			{
				buffer[0] = 0;
				return;
			}

			int i = 0;
			if(value)
			{
				if(value < 0)
				{
					*buffer++ = '-';
					--size;
					value *= -1;
				}
				for(; value > 0 && i < size; value /= tBase)
					buffer[i++] = digits[value%tBase];
			}
			else 
				buffer[i++] = '0';
			buffer[i] = 0;
			if(i > 1)
			{
				const int l = i;
				for(--i; i >= l/2; --i)
					std::swap(buffer[i],buffer[l-i-1]);
			}
		}

		//! Converts string specified via \a buffer and \a size to integer according to the base given via \a tBase
		template<unsigned tBase, typename T>
		void atoi(T &value, char *buffer, unsigned size)
		{
			static_assert(tBase <= 16,"base must be at most 16");
			static_assert(tBase > 1,"base must be at least 2");
			static_assert(
				std::is_integral<T>::value,
				"value must be of an integral type"
			);

			if(!size--)
				return;

			int i = 0;

			for(value = 0; i < size; ++i)
			{
				const uint8_t d = static_cast<uint8_t>(buffer[i]);
				if(d != ' ' && d != '\t' && d != '\v' && d != '\r' && d != '\n')
					break;
			}
			const char s = buffer[i];
			if(s == '-' || s == '+')
				++i;

			for(value = 0; i < size; ++i)
			{
				value *= tBase;
				const uint8_t d = static_cast<uint8_t>(buffer[i]);
				if(d >= '0' && d <= '9')
					value += d-'0';
				else if(d >= 'A' && d <= 'F')
					value += d-'A';
				else if(d >= 'a' && d <= 'f')
					value += d-'a';
				else break;
			}
			if(s == '-')
				value *= -1;
		}

		template<typename T>
		typename std::remove_reference<
			typename std::remove_cv<T>::type
		>::type
		htons(T value)
		{
			static_assert(
				std::is_integral<T>::value,
				"value must be of an integral type"
			);

			decltype(htons(value)) rv = value;

			volatile uint8_t * const x = reinterpret_cast<uint8_t*>(&rv);

			for(int i = 0; i < sizeof(rv)/2; ++i)
				std::swap(x[i],x[sizeof(T)-1-i]);

			return rv;
		}
	}
}
#endif
