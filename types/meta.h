#ifndef TYPES_META_H
# define TYPES_META_H
# include <type_traits>

namespace types 
{
	template <typename T, typename... Targs>
	class static_map : public static_map<Targs...>
	{
		typedef typename T::first_type::value_type key_type;

		typedef typename T::second_type value_type;

		constexpr static const key_type key = T::first_type::value;

		static value_type value;

		static_map() = delete;
	public:

		template <typename Tx>
		static std::enable_if_t<
			std::is_same_v<Tx, typename T::first_type>, 
			value_type&
		> get()
		{ return value; }

		template <typename Tx>
		static std::enable_if_t<
			!std::is_same_v<Tx, typename T::first_type>, 
			decltype(std::declval<static_map<Targs...>>().template get<Tx>())
		> get()
		{ return static_map<Targs...>::template get<Tx>(); }
	};

	template <typename T>
	class static_map<T>
	{
		typedef typename T::first_type::value_type key_type;

		typedef typename T::second_type value_type;

		constexpr static const key_type key = T::first_type::value;

		static value_type value;

		static_map() = delete;
	public:
	
		template <typename Tx>
		static std::enable_if_t<
			std::is_same_v<Tx, typename T::first_type>, 
			value_type&
		> get()
		{ return value; }

		template <typename Tx>
		static std::enable_if_t<
			!std::is_same_v<Tx, typename T::first_type>, 
			value_type&
		> get()
		{ static_assert(std::is_same_v<Tx, typename T::first_type>, "No such element"); }
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
		{ static_assert(std::is_same_v<Tx,typename T::first_type>, "No such element"); }
	};
	
	template <typename T, typename... Targs>
	typename static_map<T, Targs...>::value_type static_map<T, Targs...>::value;

	template <typename T>
	typename static_map<T>::value_type static_map<T>::value;

}

#endif
