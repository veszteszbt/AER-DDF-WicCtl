#ifndef WICP_TYPES_OBJECT_RECORD
# define WICP_TYPES_OBJECT_RECORD
# include <set>
# include <net/ipv4_address.h>
# include <sched/listener.h>
# include <sched/lockable.h>
# include <types/meta.h>

namespace wicp {
namespace types {

	template <
		typename TwicClass,
		typename TobjectId, 
		typename Tvalue,
		typename... Tproperties
	>
	struct object_record
	{
		typedef TobjectId object_id_type;

		typedef Tvalue value_type;

		typedef static_map<Tproperties...> properties;

		std::mutex property_lock;

		object_id_type object_id;

	protected:
		object_record(object_id_type pobject_id) 
			: object_id(pobject_id)
		{}
	};

	template <
		typename TwicClass,
		typename TobjectId,
		typename Tvalue,
		typename... Tproperties
	>
	struct local_object_record 
		: public object_record<TwicClass, TobjectId, Tvalue, Tproperties...>
	{
		typedef TobjectId object_id_type;

		typedef sched::lockable<std::set<object_id_type>> remotes_type;

		remotes_type remotes;

		local_object_record(object_id_type object_id) 
			: object_record(object_id) 
		{}
	};

	template <
		typename TwicClass, 
		typename TobjectId, 
		typename Tvalue, 
		typename Taddress, 
		typename... Tproperties
	>
	struct remote_object_record 
		: public object_record<TwicClass, TobjectId, Tvalue, Tproperties...>
	{
		typedef TobjectId object_id_type;

		typedef Taddress address_type;

		address_type address;

		sched::listener on_destroy;

		sched::listener on_address_change;

		remote_object_record(
			object_id_type object_id, 
			const address_type &paddress
		)
			: object_record(object_id)
			, address(paddress)
		{}
	};
}}

#endif