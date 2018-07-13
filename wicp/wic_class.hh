#ifndef WICP_WIC_CLASS_HH
# define WICP_WIC_CLASS_HH
# include <map>
# include <mutex>
# include <sched/listener.h>
# include <sched/lockable.h>
# include <wicp/types/object_record.h>


#define WIC_CLASS_TEMPLATE template < \
	typename Tconfig, \
	typename TobjectId, \
	typename Tvalue, \
	typename Taddress, \
	typename... Tproperties \
>

#define WIC_CLASS wic_class<Tconfig, TobjectId, Taddress, Tproperties...>

namespace wicp {

	WIC_CLASS_TEMPLATE
	class wic_class
	{
		typedef typename Tconfig::class_id_type	class_id_type;

		typedef TobjectId					 	object_id_type;

		typedef Tvalue							value_type;

		typedef Taddress					 	address_type;

		typedef wic_class<
			Tconfig, 
			object_id_type, 
			address_type, 
			Tproperties...
		> self;

		typedef local_object_record<
			self, 
			object_id_type, 
			value_type, 
			Tproperties...
		> local_object_record_type;

		typedef remote_object_record<
			self, 
			object_id_type, 
			value_type, 
			address_type, 
			Tproperties...
		> remote_object_record_type;

		typedef sched::lockable<
			std::map<
				object_id_type, 
				local_object_record_type
		>> local_object_lock_table_type;
		
		typedef sched::lockable<
			std::map<
				object_id_type, 
				remote_object_record_type
		>> remote_object_lock_table_type;

		typedef typename local_object_lock_table_type::iterator local_iterator;

		typedef typename remote_object_lock_table_type::iterator remote_iterator;
		
		static local_object_lock_table_type local_object_lock_table;

		static remote_object_lock_table_type remote_object_lock_table;

		static const class_id_type = Tconfig::class_id;

		constexpr static const char* name = Tconfig::name;


		friend bool operator==(local_iterator i, end_iterator);

		friend bool operator==(end_iterator, local_iterator i);

		friend bool operator==(remote_iterator i, end_iterator);

		friend bool operator==(end_iterator, remote_iterator i);

		friend bool operator!=(local_iterator i, end_iterator);

		friend bool operator!=(end_iterator, local_iterator i);

		friend bool operator!=(remote_iterator i, end_iterator);

		friend bool operator!=(end_iterator, remote_iterator i);
		public:

		constexpr class end_iterator {};


		// TODO
		// static auto find_object(object_id_type object_id)
		// {
		// 	auto local_it = local_object_lock_table.find(object_id);
		// 	if(local_it != local_object_lock_table.end())
		// 		return local_it;

		// 	return remote_object_lock_table.find(object_id);
		// }

		static void local_lock()
		{ local_object_lock_table.lock(); }

		static void local_unlock()
		{ local_object_lock_table.unlock(); }

		static void remote_lock()
		{ remote_object_lock_table.lock(); }

		static void remote_unlock()
		{ remote_object_lock_table.unlock(); }

		static local_iterator find_local(object_id_type object_id) 
		{ return local_object_lock_table.find(object_id); }
	
		static remote_iterator find_remote(object_id_type object_id) 
		{ return remote_object_lock_table.find(object_id); }
	
		static end_iterator end()
		{ return end_iterator(); }

		static bool push_local(object_id_type object_id)
		{
			auto it = remote_object_lock_table.find(object_id);
			if(it != remote_object_lock_table_type.end())
				return false;
			
			local_object_lock_table.emplace(object_id, object_id);
			return true; 
		}

		static bool push_remote(object_id_type object_id, const address_type address)
		{
			auto it = local_object_lock_table.find(object_id);
			if(it != local_object_lock_table.end())
				return false;

			remote_object_lock_table.try_emplace(object_id, object_id, address);
			return true;
		}

		static void erase_local(local_iterator it)
		{ local_object_lock_table.erase(it); }

		static void erase_remote(remote_iterator it)
		{ remote_object_lock_table.erase(it); }

		static bool remove_local(object_id_type object_id)
		{ return local_object_lock_table.erase(object_id); }

		static bool remove_remote(object_id_type object_id)
		{ return remote_object_lock_table.erase(object_id); }
	};

	WIC_CLASS_TEMPLATE
	bool operator==(typename WIC_CLASS::local_iterator it, typename WIC_CLASS::end_iterator end_it)
	{ return local_object_lock_table.end() == it; }

	WIC_CLASS_TEMPLATE
	bool operator==(typename WIC_CLASS::remote_iterator it, typename WIC_CLASS::end_iterator end_it)
	{ return remote_object_lock_table.end() == it; }

	WIC_CLASS_TEMPLATE
	bool operator==(typename WIC_CLASS::local_iterator it, typename WIC_CLASS::end_iterator end_it)
	{ return it == end_it; }

	WIC_CLASS_TEMPLATE
	bool operator==(typename WIC_CLASS::remote_iterator it, typename WIC_CLASS::end_iterator end_it)
	{ return it == end_it; }

	WIC_CLASS_TEMPLATE
	bool operator!=(typename WIC_CLASS::local_iterator it, typename WIC_CLASS::end_iterator end_it)
	{ return !(local_object_lock_table.end() == it); }

	WIC_CLASS_TEMPLATE
	bool operator!=(typename WIC_CLASS::remote_iterator it, typename WIC_CLASS::end_iterator end_it)
	{ return !(remote_object_lock_table.end() == it); }

	WIC_CLASS_TEMPLATE
	bool operator!=(typename WIC_CLASS::local_iterator it, typename WIC_CLASS::end_iterator end_it)
	{ return !(it == end_it); }

	WIC_CLASS_TEMPLATE
	bool operator!=(typename WIC_CLASS::remote_iterator it, typename WIC_CLASS::end_iterator end_it)
	{ return !(it == end_it); }
}

#undef WIC_CLASS_TEMPLATE

#undef WIC_CLASS

#endif
