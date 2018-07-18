#ifndef WICP_WIC_CLASS_HH
# define WICP_WIC_CLASS_HH
# include <map>
# include <mutex>
# include <sched/listener.h>
# include <sched/lockable.h>
# include <wicp/types/object_record.h>
# include <types/meta.h>


#define WIC_CLASS_TEMPLATE template < \
	typename Tconfig, \
	typename TobjectId, \
	typename Tvalue, \
	typename Taddress, \
	typename... Tproperties \
>

#define WIC_CLASS wic_class<Tconfig, TobjectId, Tvalue, Taddress, Tproperties...>

namespace wicp 
{
	WIC_CLASS_TEMPLATE
	class wic_class
	{
		typedef typename Tconfig::class_id_type	class_id_type;

		typedef TobjectId					 	object_id_type;

		typedef Tvalue							value_type;

		typedef Taddress					 	address_type;

		typedef WIC_CLASS 						self;
	
	// TODO populate these to other processes
	public:
		typedef types::local_object_record<
			self, 
			object_id_type, 
			value_type, 
			Tproperties...
		> local_object_record_type;

		typedef types::remote_object_record<
			self, 
			object_id_type, 
			value_type, 
			address_type, 
			Tproperties...
		> remote_object_record_type;
	private:
	
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

	// TODO 
	public:
		typedef typename local_object_lock_table_type::iterator local_iterator;

		typedef typename remote_object_lock_table_type::iterator remote_iterator;
	private:
		
		static local_object_lock_table_type local_object_lock_table;

		static remote_object_lock_table_type remote_object_lock_table;

		static const class_id_type class_id = Tconfig::class_id;
		public:
		
		constexpr static const char* name = Tconfig::cfg_name;

		struct end_iterator
		{
			operator local_iterator()
			{ return local_object_lock_table.end(); }

			operator remote_iterator()
			{ return remote_object_lock_table.end(); }
		};


		// TODO
		// static auto find_object(object_id_type object_id)
		// {
		// 	auto local_it = local_object_lock_table.find(object_id);
		// 	if(local_it != local_object_lock_table.end())
		// 		return local_it;

		// 	return remote_object_lock_table.find(object_id);
		// }

		// TODO lock_local vs lock_lockal
		static void lock_local()
		{ local_object_lock_table.lock(); }

		static void unlock_local()
		{ local_object_lock_table.unlock(); }

		static void lock_remote()
		{ remote_object_lock_table.lock(); }

		static void unlock_remote()
		{ remote_object_lock_table.unlock(); }

		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, local_object_record_type>
		> lock()
		{ lock_local(); }

		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, remote_object_record_type>
		> lock()
		{ lock_remote(); }

		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, local_object_record_type>
		> unlock()
		{ unlock_local(); }

		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, remote_object_record_type>
		> unlock()
		{ unlock_remote(); }

		static local_iterator find_local(object_id_type object_id) 
		{ return local_object_lock_table.find(object_id); }
	
		static remote_iterator find_remote(object_id_type object_id) 
		{ return remote_object_lock_table.find(object_id); }
	
		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, local_object_record_type>,
			local_iterator
		> find(object_id_type pobject_id)
		{ return find_local(pobject_id); }

		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, remote_object_record_type>,
			remote_iterator
		> find(object_id_type pobject_id)
		{ return find_remote(pobject_id); }

		static end_iterator end()
		{ return end_iterator(); }

		static bool set_local(object_id_type object_id)
		{
			auto it = remote_object_lock_table.find(object_id);
			if(it != remote_object_lock_table.end())
				return false;
			
			local_object_lock_table.emplace(object_id, object_id);
			return true; 
		}

		static bool set_remote(
			object_id_type object_id, 
			const address_type address
		)
		{
			auto it = local_object_lock_table.find(object_id);
			if(it != local_object_lock_table.end())
				return false;

			auto pair_it = remote_object_lock_table.try_emplace(object_id, object_id, address);
			if(!pair_it.second)
				pair_it.first->second.address = address;
				
			return true;
		}

		static bool clr_local(object_id_type object_id)
		{ return local_object_lock_table.erase(object_id); }

		static bool clr_local(local_iterator it)
		{ return local_object_lock_table.erase(it); }

		static bool clr_remote(object_id_type object_id)
		{ return remote_object_lock_table.erase(object_id); }

		static bool clr_remote(remote_iterator it)
		{ return remote_object_lock_table.erase(it); }
	};

	WIC_CLASS_TEMPLATE
	typename WIC_CLASS::local_object_lock_table_type 
		WIC_CLASS::local_object_lock_table;
	
	WIC_CLASS_TEMPLATE
	typename WIC_CLASS::remote_object_lock_table_type 
		WIC_CLASS::remote_object_lock_table;
}

#undef WIC_CLASS_TEMPLATE
#undef WIC_CLASS

#endif
