#ifndef OOSP_TYPES_PROPERTY_DATA_TYPE_H
# define OOSP_TYPES_PROPERTY_DATA_TYPE_H
# include <chrono>
namespace oosp {
namespace types
{
	template <typename TobjId, typename Tvalue>
	struct property_data_type
	{
		typedef TobjId object_id_type;
		typedef Tvalue value_type;

		object_id_type object_id;
		value_type value;

		property_data_type() = default;

		property_data_type(
			object_id_type pobject_id,
			const value_type &pvalue 
		) 
			: object_id(pobject_id)
			, value(pvalue)
		{}

		bool operator==(const property_data_type &that) const
		{ return std::tie(object_id, value) == std::tie(that.object_id, that.value); }
	};
}}
#endif
