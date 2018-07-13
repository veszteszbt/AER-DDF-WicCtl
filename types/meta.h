#ifndef TYPES_META_H
# define TYPES_META_H
# include <type_traits>

namespace types {

	template <typename Tkey, Tkey tKey, typename Tvalue, typename... Targs>
	class static_map : public static_map<Tkey, Targs...>
	{
		typedef Tkey key_type;

		typedef Tvalue value_type;

		constexpr static const key_type key = tKey;

		static value_type value;

		static_map() = delete;
	public:

		template <key_type _key>
		std::enable_if_t<_key == key, value_type&> 
		get()
		{ return value; }

		template <key_type _key>
		std::enable_if_t<_key != key, value_type&> 
		get()
		{ return static_map<Targs...>::get<_key>(); }
	};

	template <typename Tkey, Tkey tKey, typename Tvalue>
	class static_map
	{
		typedef Tkey key_type;

		typedef Tvalue value_type;

		constexpr static const key_type key = tKey;

		static value_type value;

		static_map() = delete;
	public:
	
		template <key_type _key>
		std::enable_if_t<_key == key, value_type&>
		get()
		{ return value; }

		template <key_type _key>
		std::enable_if_t<_key != key, value_type&>
		get()
		{ static_assert(_key == key, "No such element"); }
	};
	
}

#endif