#ifndef TYPES_META_HH
# define TYPES_META_HH
# include <cstring>
# include <type_traits>
# include <tuple>

namespace types{
namespace meta
{
namespace _detail
{
	template<typename T, typename E = void>
	struct is_container : std::false_type {};

	template<typename T>
	struct is_container<
		T,
		std::conditional_t<
			false,
			std::void_t<
				typename T::value_type,
				typename T::size_type,
				typename T::iterator,
				typename T::const_iterator,
				decltype(std::declval<T>().size()),
				decltype(std::declval<T>().begin()),
				decltype(std::declval<T>().end())
			>,
			void
		>
	> : std::true_type {};


	template<typename T, typename E = void>
	struct is_nullary_callable : std::false_type {};

	template<typename T>
	struct is_nullary_callable<
		T,
		std::conditional_t<
			false,
			decltype(std::declval<T>()()),
			void
		>
	> : std::true_type {};

	template <typename Tuple, typename F, std::size_t... Indices>
	void for_each_impl(Tuple&& tuple, F&& f, std::index_sequence<Indices...>) {
		using swallow = int[];
		(void)swallow{ 1,
			(f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...
		};
	}
}

template<typename T1, typename T2, typename... Tn>
struct is_one_of : std::bool_constant
<
	std::is_same_v<T1,T2> ||
	is_one_of<T1,Tn...>::value
> {};

template<typename T1, typename T2>
struct is_one_of<T1,T2> : std::is_same<T1,T2> {};

template<typename T>
struct is_container : _detail::is_container<T> {};

template<typename T>
struct is_nullary_callable: _detail::is_nullary_callable<T> {};

template<typename... Targs>
constexpr bool is_one_of_v = is_one_of<Targs...>::value;

template<typename T>
constexpr bool is_container_v = is_container<T>::value;

template<typename T>
constexpr bool is_nullary_callable_v = is_nullary_callable<T>::value;

template <typename Tuple, typename F>
void for_each(Tuple&& tuple, F&& f)
{
	constexpr std::size_t N = std::tuple_size_v<std::remove_reference_t<Tuple>>;
	_detail::for_each_impl(
		std::forward<Tuple>(tuple), std::forward<F>(f), 
		std::make_index_sequence<N>{}
	);
}

template<template<typename...> typename T, typename... TBindArgs>
struct bind
{
	// TODO: placeholder handling
	template<typename... TResultArgs>
	using type = T<TBindArgs..., TResultArgs...>;
};

}}
#endif
