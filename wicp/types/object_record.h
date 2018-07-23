#ifndef WICP_TYPES_OBJECT_RECORD
# define WICP_TYPES_OBJECT_RECORD
# include <set>
# include <net/ipv4_address.h>
# include <sched/listener.h>
# include <sched/lockable.h>
# include <types/meta.h>

#define OBJECT_RECORD_CLASS object_record<TwicClass, TobjectId, Tproperties...>

namespace wicp {
namespace types 
{
	template <
		typename TwicClass,
		typename TobjectId, 
		typename... Tproperties
	>
	struct object_record
	{
		typedef TobjectId object_id_type;

		typedef ::types::static_keyed_map<Tproperties...> properties_type;

		properties_type properties;

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
		typename... Tproperties
	>
	struct local_object_record 
		: public OBJECT_RECORD_CLASS
	{
		typedef TobjectId object_id_type;

		typedef sched::lockable<std::set<object_id_type>> remotes_type;

		remotes_type remotes;

		local_object_record(object_id_type object_id) 
			: OBJECT_RECORD_CLASS(object_id) 
		{}
	};

	template <
		typename TwicClass, 
		typename TobjectId, 
		typename Taddress,
		typename... Tproperties
	>
	struct remote_object_record 
		: public OBJECT_RECORD_CLASS
	{
		// void report_call(call_report_type) = TwicClassReportCall;

		typedef TobjectId object_id_type;

		typedef Taddress address_type;

		address_type ip;

		sched::listener on_destroy;

		sched::listener on_ip_change;

		remote_object_record(
			object_id_type object_id, 
			const address_type &paddress
		)
			: OBJECT_RECORD_CLASS(object_id)
			, ip(paddress)
		{}
	};
}}

#undef OBJECT_RECORD_CLASS

#endif