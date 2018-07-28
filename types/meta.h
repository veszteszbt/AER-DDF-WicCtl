#ifndef TYPES_META_H
# define TYPES_META_H
# include <type_traits>

namespace types 
{
	template <typename Tkey, typename Tvalue, typename... Targs>
	class static_map : public static_map<Targs...>
	{
		typedef typename Tkey::value_type key_type;

		typedef Tvalue value_type;

		constexpr static const key_type key = Tkey::value;

		static value_type value;

		static_map() = delete;
	public:

		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, Tkey>, 
			value_type&
		> get()
		{ return value; }

		template <typename T>
		static std::enable_if_t<
			!std::is_same_v<T,Tkey>, 
			decltype(std::declval<static_map<Targs...>>().template get<T>())
		> get()
		{ return static_map<Targs...>::template get<T>(); }
	};

	template <typename Tkey, typename Tvalue>
	class static_map<Tkey, Tvalue>
	{
		typedef typename Tkey::value_type key_type;

		typedef Tvalue value_type;

		constexpr static const key_type key = Tkey::value;

		static value_type value;

		static_map() = delete;
	public:
	
		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T,Tkey>, 
			value_type&
		> get()
		{ return value; }

		template <typename T>
		static std::enable_if_t<
			!std::is_same_v<T,Tkey>, 
			value_type&
		> get()
		{ static_assert(std::is_same_v<T,Tkey>, "No such element"); }
	};

	template <typename T, typename... Targs>
	class static_keyed_map : public static_keyed_map<Targs...>
	{
		typedef typename T::first_type::value_type key_type;

		typedef typename T::second_type value_type;

		constexpr static const key_type key = T::first_type::value;

		value_type value;
	public:

		template <typename Tx>
		std::enable_if_t<
			std::is_same_v<Tx, typename T::first_type>, 
			value_type&
		> get()
		{ return value; }

		template <typename Tx>
		std::enable_if_t<
			!std::is_same_v<Tx, typename T::first_type>, 
			decltype(std::declval<static_keyed_map<Targs...>>().template get<T>())
		> get()
		{ return static_keyed_map<Targs...>::template get<T>(); }
	};

	template <typename T>
	class static_keyed_map<T>
	{
		typedef typename T::first_type::value_type key_type;

		typedef typename T::second_type value_type;

		constexpr static const key_type key = T::first_type::value;

		value_type value;
	public:

		template <typename Tx>
		std::enable_if_t<
			std::is_same_v<Tx, typename T::first_type>, 
			value_type&
		> get()
		{ return value; }

		template <typename Tx>
		std::enable_if_t<
			!std::is_same_v<Tx, typename T::first_type>, 
			value_type&
		> get()
		{ static_assert(std::is_same_v<Tx,T::first_type>, "No such element"); }
	};
	
	template <typename Tkey, typename Tvalue, typename... Targs>
	typename static_map<Tkey, Tvalue, Targs...>::value_type static_map<Tkey, Tvalue, Targs...>::value;

	template <typename Tkey, typename Tvalue>
	typename static_map<Tkey, Tvalue>::value_type static_map<Tkey, Tvalue>::value;

}

#endif
