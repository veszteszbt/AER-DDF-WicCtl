#ifndef WIC_ENTITY_H
# define WIC_ENTITY_H
# include <type_traits>
namespace wic {
	struct entity
	{
	protected:
		template<typename property, bool write = true>
		struct expose_property
		{
			static constexpr sched::listener &on_change = property::on_change;

			constexpr expose_property() {}
			template<typename T=void>
			constexpr expose_property(
				typename std::enable_if_t<
					std::is_same<T,void>::value && write,
					typename property::value_type
				> v
			)
			{ property::value(v); }

			operator typename property::value_type()
			{ return property::value(); }
		};
	};
}
#endif
