#ifndef WIC_ENTITY_H
# define WIC_ENTITY_H
namespace wic {
	struct entity
	{
		template<typename property>
		struct expose_property
		{
			static constexpr sched::listener &on_change = property::on_change;

			constexpr expose_property(){}

			constexpr expose_property(typename property::value_type v)
			{ property::value(v); }

			operator typename property::value_type()
			{ return property::value(); }
		};
	};
}
#endif
