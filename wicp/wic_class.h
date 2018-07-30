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
	typename... Tproperties \
>

#define WIC_CLASS wic_class<Tconfig, Tproperties...>

namespace wicp 
{
	WIC_CLASS_TEMPLATE
	struct wic_class
	{
		template <typename...>
		struct property_initializer;

		typedef typename Tconfig::cfg_class_id_type	   class_id_type;

		typedef typename Tconfig::cfg_member_id_type       member_id_type;

		typedef typename Tconfig::cfg_object_id_type       object_id_type;

		typedef typename Tconfig::cfg_earpc::call_id_type  call_id_type;

		typedef typename Tconfig::cfg_address_type         address_type;

		typedef typename Tconfig::cfg_clock                clock;

	private:
		typedef WIC_CLASS                                  self;
	
	public:
		typedef types::local_object_record<
			self, 
			Tproperties...
		> 										local_object_record_type;

		typedef types::remote_object_record<
			self, 
			Tproperties...
		> 										remote_object_record_type;
	private:
	
		typedef sched::lockable<
			std::map<
				object_id_type, 
				local_object_record_type
		>> 										local_object_lock_table_type;
		
		typedef sched::lockable<
			std::map<
				object_id_type, 
				remote_object_record_type
		>> 										remote_object_lock_table_type;

	public:
		typedef typename local_object_lock_table_type::iterator local_iterator;

		typedef typename remote_object_lock_table_type::iterator remote_iterator;
	private:
		
		static local_object_lock_table_type 	local_object_lock_table;

		static remote_object_lock_table_type 	remote_object_lock_table;

		static const class_id_type 	class_id = Tconfig::class_id;

	public:
		
		constexpr static const char* name = Tconfig::cfg_name;

		struct end_iterator
		{
			operator local_iterator()
			{ return local_object_lock_table.end(); }

			operator remote_iterator()
			{ return remote_object_lock_table.end(); }
		};

		static void init()
		{ property_initializer<Tproperties...>::init(); }

		static void uninit()
		{ property_initializer<Tproperties...>::uninit(); }

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
			std::is_same_v<T, local_object_record_type>
		> unlock()
		{ unlock_local(); }

		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, remote_object_record_type>
		> lock()
		{ lock_remote(); }

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
			remote_object_lock_table.lock();
			auto it = remote_object_lock_table.find(object_id);
			if(it != remote_object_lock_table.end())
			{
				remote_object_lock_table.unlock();
				return false;
			}
			remote_object_lock_table.unlock();
			local_object_lock_table.lock();
			local_object_lock_table.emplace(object_id, object_id);
			// TODO init inside the lock?
			property_initializer<Tproperties...>::init(object_id);
			local_object_lock_table.unlock();

			return true; 
		}

		static bool set_remote(
			object_id_type object_id,
			address_type address
		)
		{
			local_object_lock_table.lock();
			auto it = local_object_lock_table.find(object_id);
			if(it != local_object_lock_table.end())
			{
				local_object_lock_table.unlock();
				return false;
			}
			local_object_lock_table.unlock();
			remote_object_lock_table.lock();
			auto pair_it = remote_object_lock_table.try_emplace(object_id, object_id, address);
			if(!pair_it.second)
			{
				pair_it.first->second.ip = address;
				pair_it.first->second.on_ip_change();
			}

			property_initializer<Tproperties...>::init(object_id);
			remote_object_lock_table.unlock();

			return true;
		}

		static bool clr_local(object_id_type object_id)
		{
			local_object_lock_table.lock();
			auto it = local_object_lock_table.find(object_id);
			if(it == local_object_lock_table.end())
			{
				local_object_lock_table.unlock();
				return false;
			}

			const bool clred = local_object_lock_table.erase(it);
			local_object_lock_table.unlock();
			property_initializer<Tproperties...>::uninit(object_id);
			return clred;
		}

		static bool clr_remote(object_id_type object_id)
		{ 
			remote_object_lock_table.lock();
			auto it = remote_object_lock_table.find(object_id);
			if(it == remote_object_lock_table.end())
			{
				remote_object_lock_table.unlock();
				return false; 
			}

			it->second.on_destory();
			const bool clred = remote_object_lock_table.erase(it);
			remote_object_lock_table.unlock();
			property_initializer<Tproperties...>::uninit(object_id);
			return clred;
		}

		static bool clr_local(local_iterator it)
		{ 
			const object_id_type object_id = it->second.object_id;
			const bool clred = local_object_lock_table.erase(it);
			if(clred)
				property_initializer<Tproperties...>::uninit(object_id);
				
			return clred; 
		}

		static bool clr_remote(remote_iterator it)
		{
			const object_id_type object_id = it->second.object_id;
			const bool clred = remote_object_lock_table.erase(it);
			if(clred)
				property_initializer<Tproperties...>::uninit(object_id);
				
			return clred;  
		}

		// TODO
		// template <typename T>
		// static void lock_local_and_process(object_id_type object_id, T &fn)
		// {
		// 	wic_class::lock_local();			
		// 	auto local_it = wic_class::find_local(object_id);
		// 	if(local_it != wic_class::end())
		// 	{
		// 		fn(local_it);
		// 		wic_class::unlock_local();
		// 	}
		// 	else
		// 	{
		// 		wic_class::unlock_local();			
		// 		jrn(journal::error) << "Invalid local `" << 
		// 			wic_class::name << "' object reference `" << std::hex << object_id << journal::end;
		// 	}
		// }
	};

	WIC_CLASS_TEMPLATE
	typename WIC_CLASS::local_object_lock_table_type 
		WIC_CLASS::local_object_lock_table;
	
	WIC_CLASS_TEMPLATE
	typename WIC_CLASS::remote_object_lock_table_type 
		WIC_CLASS::remote_object_lock_table;

	WIC_CLASS_TEMPLATE
	template <typename Tproperty, typename... Tremaining>
	struct WIC_CLASS::property_initializer<Tproperty, Tremaining...>
	{
		static void init()
		{
			Tproperty::second_type::init();
			WIC_CLASS::property_initializer<Tremaining...>::init();
		}

		static void init(typename WIC_CLASS::object_id_type object_id)
		{
			Tproperty::second_type::init(object_id);
			WIC_CLASS::property_initializer<Tremaining...>::init(object_id);
		}

		static void uninit()
		{
			Tproperty::second_type::uninit();
			WIC_CLASS::property_initializer<Tremaining...>::uninit();
		}

		static void uninit(typename WIC_CLASS::object_id_type object_id)
		{
			Tproperty::second_type::uninit(object_id);
			WIC_CLASS::property_initializer<Tremaining...>::uninit(object_id);
		}
	};

	WIC_CLASS_TEMPLATE
	template <typename Tproperty>
	struct WIC_CLASS::property_initializer<Tproperty>
	{
		static void init()
		{ Tproperty::second_type::init(); }

		static void init(typename WIC_CLASS::object_id_type object_id)
		{ Tproperty::second_type::init(object_id); }

		static void uninit()
		{ Tproperty::second_type::uninit(); }

		static void uninit(typename WIC_CLASS::object_id_type object_id)
		{ Tproperty::second_type::uninit(object_id); }
	};

}

#undef WIC_CLASS_TEMPLATE
#undef WIC_CLASS

#endif
