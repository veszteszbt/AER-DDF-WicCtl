#ifndef WICP_DUMMYCLASS_HH
# define WICP_DUMMYCLASS_HH
# include <chrono>
# include <map>
# include <list>
# include <set>
# include <tuple>

namespace wicp {

	template <typename Tvalue>
	struct property_record
	{
		typedef Tvalue value_type;
	
		struct history_record
		{
			typename clock::time_point time;

			value_type                value;

			history_record() {}

			history_record(value_type v)
				: time(clock::now())
				, value(v)
			{}
		};

		typedef std::list<history_record> history_type;

		static history_type history;

		// sched::event<role_type&> on_bound;

		// sched::event<role_type&> on_unbound;

		// sched::event<role_type&> on_health_change;

	};





	template <typename TdummyClass, typename TobjectId, typename Tvalue>//, typename TmemberId, TmemberId tMemberId>
	struct object_record
	{
		typedef TobjectId object_id_type;

		typedef Tvalue value_type;

		// typedef smart_list<member_ids> = {property_records};

		object_id_type object_id;
	private:

		virtual ~object_record(){}
	};

	template <typename TdummyClass, typename TobjectId>
	class local_object_record : public object_record<TdummyClass, TobjectId>
	{
		typedef TobjectId object_id_type;

		typedef std::set<object_id_type> remotes_type;

		remotes_type remotes;
	};

	template <typename TdummyClass, typename TobjectId, typename TaddrProto>
	class remote_object_record : public object_record<TdummyClass, TobjectId>
	{
		typedef TobjectId object_id_type;

		typedef TaddrProto address_type;

		address_type address;
	};






	template <typename TclassID, typename TobjectId, typename TaddrProto, tClassId>
	class dummy_class
	{
		typedef TclassID class_id_type;

		typedef TobjectId object_id_type;

		typedef TaddrProto address_type;

		typedef std::map<object_id_type, local_object_record> local_objects_type;
		
		typedef std::map<object_id_type, remote_object_record> remote_objects_type;
		
		static const class_id_type = tClassId;

		local_objects_type local_objects;
		
		remote_objects_type remote_objects;

		// TODO getting this
		constexpr static const char* name;
		
		public:

		constexpr class end_iterator
		{
			bool operator==(local_objects_type::iterator i) const
			{ return local_object.end() == i; }

			bool operator==(remote_objects_type::iterator i) const
			{ return remote_object.end() == i; }

		} end;


		auto find_object(object_id_type object_id)
		{
			auto local_it = local_objects.find(object_id);
			if(local_it != local_objects.end())
				return local_it;

			return remote_objects.find(object_id);
		}
		
		auto end()
		{
			return MapTypeFromIterator()
		}

	};


	template <typename T, typename C1, typename C2, typename Tcond = void>
	struct MapTypeFromIterator
	{};

	template <typename T, typename C1, typename C2>
	struct MapTypeFromIterator<
		T, C1, C2,
		std::enable_if_t<
			std::is_same_v<T, decltype(std::declval<C1>().end())>
		>
	>
	{ typedef C1 type; };

	template <typename T, typename C1, typename C2>
	struct MapTypeFromIterator<
		T, C1, C2,
		std::enable_if_t<
			std::is_same_v<T, decltype(std::declval<C2>().end())>
		>
	>
	{ typedef C2 type; };
	
}
#endif
