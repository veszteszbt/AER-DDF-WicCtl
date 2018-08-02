#ifndef WICP_TYPES_OBJECT_RECORD
# define WICP_TYPES_OBJECT_RECORD
# include <set>
# include <net/ipv4_address.h>
# include <sched/listener.h>
# include <sched/lockable.h>
# include <types/meta.h>
# include <wicp/types/sync_record.h>

#define OBJECT_RECORD_CLASS object_record<TwicClass, Tproperties...>

namespace wicp {
namespace types
{
	template <
		typename TwicClass,
		typename... Tproperties
	>
	struct object_record
	{
		typedef typename TwicClass::object_id_type        object_id_type;

		typedef ::types::static_keyed_map<Tproperties...> properties_type;

		properties_type properties;

		std::mutex 		property_lock;

		object_id_type	object_id;

	protected:
		object_record(object_id_type pobject_id)
			: object_id(pobject_id)
		{}
	};

	template <
		typename TwicClass,
		typename... Tproperties
	>
	class local_object_record
		: public OBJECT_RECORD_CLASS
	{
		template<typename Tpair, typename T>
		struct change_second_to : std::pair<typename Tpair::first_type,T> {};

	public:
		typedef typename TwicClass::clock           clock;

		typedef typename TwicClass::call_id_type    call_id_type;

		typedef typename TwicClass::object_id_type  object_id_type;

		template <typename Tvalue>
		using remote_property_sync_record = sync_record<call_id_type, Tvalue, clock>;

		/*! Type to hold sync status for each property of a remote endpoint */
		typedef ::types::static_keyed_map<
			change_second_to<
				Tproperties,
				remote_property_sync_record<
					typename Tproperties::second_type::value_type
				>
			>...
		>											remote_object_sync_record;

		/*! Type to map remote object ids to sync records */
		typedef sched::lockable<
			std::map<
				object_id_type,
				remote_object_sync_record
			>
		>											remotes_type;

		/*! Store of remote endpoints */
		remotes_type								remotes;

		local_object_record(object_id_type object_id)
			: OBJECT_RECORD_CLASS(object_id)
		{}
	};

	template <
		typename TwicClass,
		typename... Tproperties
	>
	struct remote_object_record
		: public OBJECT_RECORD_CLASS
	{
		typedef typename TwicClass::address_type   address_type;

		struct call_report_type
		{
			bool    success;
			int32_t latency;
			address_type address;
		};

		typedef typename TwicClass::object_id_type object_id_type;

		address_type 	ip;

		sched::listener on_destroy;

		sched::listener on_ip_change;

		remote_object_record(
			object_id_type object_id,
			const address_type &paddress
		)
			: OBJECT_RECORD_CLASS(object_id)
			, ip(paddress)
		{}

		template <typename T>
		void report_call(const T &h)
		{
			if(h.reason == earpc::reason::cancelled)
				return;
			if(h.ip == ip)
				return;

			ip = h.ip;
			on_ip_change();

			call_report_type r;
			r.success = !h.reason;
			r.latency = calc_latency(h);
		}

	private:
		template<typename T, typename U = decltype(T::finished), typename V = decltype(T::started)>
		int32_t calc_latency(const T &h)
		{ return ::types::time::msec(h.finished-h.started); }

		template<typename T, typename U = decltype(T::received)>
		int32_t calc_latency(const T &h)
		{ return -1; }
	};
}}

#undef OBJECT_RECORD_CLASS

#endif
