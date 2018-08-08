#ifndef OOSP_WIC_CLASS_HH
# define OOSP_WIC_CLASS_HH
# include <map>
# include <mutex>
# include <sched/listener.h>
# include <sched/lockable.h>
# include <types/meta.h>
# include <oosp/local_property.h>
# include <oosp/remote_property.h>
# include <oosp/types/object_record.h>
# include <oosp/types/property_data_type.h>
# include <oosp/types/property_record.h>

#define OOSP_CLASS_TEMPLATE template < \
	typename Tconfig, \
	typename... Tproperties \
>

#define OOSP_CLASS oosp_class<Tconfig, Tproperties...>

namespace oosp
{
	OOSP_CLASS_TEMPLATE
	struct oosp_class
	{
		typedef typename std::chrono::high_resolution_clock	clock;

		typedef typename Tconfig::cfg_class_id_type			class_id_type;

		typedef typename Tconfig::cfg_member_id_type		member_id_type;

		typedef typename Tconfig::cfg_object_id_type		object_id_type;

		typedef typename Tconfig::cfg_earpc					earpc;

		typedef typename Tconfig::cfg_earpc::call_id_type	call_id_type;

		typedef net::ipv4_address							address_type;

	private:
		template <typename...>
		struct property_initializer;

		typedef OOSP_CLASS									self;

		template <typename Tproperty>
		struct property_config
		{
			typedef typename Tproperty::value_type	cfg_value_type;

			typedef class_id_type					cfg_class_id_type;

			typedef member_id_type					cfg_member_id_type;

			typedef object_id_type					cfg_object_id_type;

			typedef earpc							cfg_earpc;

			typedef self							cfg_oosp_class;

			typedef types::property_data_type<
				object_id_type,
				cfg_value_type
			> 										cfg_property_data_type;

			typedef std::integral_constant<
				member_id_type,
				static_cast<member_id_type>(Tproperty::member_id)
			> 										cfg_member_id;

			static const class_id_type cfg_class_id = Tconfig::cfg_class_id;

			static const uintmax_t cfg_cooldown_time = Tproperty::cooldown_time;

			constexpr static const size_t cfg_history_size = Tproperty::history_size;
		};

		template <typename TpropertyConfig>
		struct object_record_transform : std::pair<
			typename TpropertyConfig::cfg_member_id, 
				types::property_record<
					call_id_type,
					object_id_type,
					typename TpropertyConfig::cfg_value_type
				>
			>
		{};

		template <typename TpropertyConfig>
		struct property_transform : std::pair<
				local_property<TpropertyConfig>, 
				remote_property<TpropertyConfig>
			>
		{};

		template <typename TpropertyConfig>
		struct local_property_transform : std::pair<
				typename TpropertyConfig::cfg_member_id, 
				local_property<TpropertyConfig>
			>
		{};

		template <typename TpropertyConfig>
		struct remote_property_transform : std::pair<
				typename TpropertyConfig::cfg_member_id, 
				remote_property<TpropertyConfig>
			>
		{};

	public:
		typedef types::local_object_record<
			self,
			object_record_transform<
				property_config<Tproperties>
			>...
		> 										local_object_record_type;

		typedef types::remote_object_record<
			self,
			object_record_transform<
				property_config<Tproperties>
			>...
		> 										remote_object_record_type;
	private:

		typedef ::types::type_map<
			local_property_transform<
				property_config<Tproperties>
			>...
		>										local_property_holder; // TODO should this be handler instead of holder?

		typedef ::types::type_map<
			remote_property_transform<
				property_config<Tproperties>
			>...
		>										remote_property_holder;

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
		typedef typename local_object_lock_table_type::iterator local_table_iterator;

		typedef typename remote_object_lock_table_type::iterator remote_table_iterator;
	private:

		static local_object_lock_table_type 	local_object_lock_table;

		static remote_object_lock_table_type 	remote_object_lock_table;

		static const class_id_type 	class_id = Tconfig::cfg_class_id;

	public:

		constexpr static const char* name = Tconfig::cfg_name;

		struct end_iterator
		{
			operator local_table_iterator()
			{ return local_object_lock_table.end(); }

			operator remote_table_iterator()
			{ return remote_object_lock_table.end(); }
		};

		static journal jrn(uint8_t level)
		{
			return journal(level,"oosp.oosp_class") << "property: " << std::hex <<
				class_id << ' ';
		}

		static journal jrn(uint8_t level, object_id_type object)
		{
			return journal(level,"oosp.class") << std::hex <<
				"object:  " << object <<
				"; class: " << oosp_class::name <<
				"; property: " <<
				" (" << class_id << ")";
			;
		}
		static void init()
		{ 
			property_initializer<
				property_transform<
					property_config<Tproperties>
				>...
			>::init(); 
		}

		static void uninit()
		{ 
			property_initializer<
				property_transform<
					property_config<Tproperties>
				>...
			>::uninit(); 
		}

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

		static local_table_iterator find_local(object_id_type object_id)
		{ return local_object_lock_table.find(object_id); }

		static remote_table_iterator find_remote(object_id_type object_id)
		{ return remote_object_lock_table.find(object_id); }

		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, local_object_record_type>,
			local_table_iterator
		> find(object_id_type pobject_id)
		{ return find_local(pobject_id); }

		template <typename T>
		static std::enable_if_t<
			std::is_same_v<T, remote_object_record_type>,
			remote_table_iterator
		> find(object_id_type pobject_id)
		{ return find_remote(pobject_id); }

		static end_iterator end()
		{ return end_iterator(); }

		template <typename tMemberId>
		using get_local = typename local_property_holder::template get<tMemberId>;
		
		template <typename tMemberId>
		using get_remote = typename remote_property_holder::template get<tMemberId>;

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
			property_initializer<
				local_property<
					property_config<Tproperties>
				>...
			>::init(object_id);

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

			property_initializer<
				remote_property<
					property_config<Tproperties>
				>...
			>::init(object_id);
			remote_object_lock_table.unlock();

			return true;
		}

		static bool clr_local(object_id_type object_id)
		{
			local_object_lock_table.lock();

			if(!local_object_lock_table.erase(object_id))
			{
				local_object_lock_table.unlock();
				return false;
			}

			property_initializer<
				local_property<
					property_config<Tproperties>
				>...
			>::uninit(object_id);

			local_object_lock_table.unlock();
			return true;
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

			it->second.on_destroy();
			remote_object_lock_table.erase(it);
			property_initializer<
				remote_property<
					property_config<Tproperties>
				>...
			>::uninit(object_id);
			remote_object_lock_table.unlock();
			return true;
		}

		// TODO
		// static bool clr_local(local_table_iterator it)
		// {
		// 	const object_id_type object_id = it->second.object_id;
		// 	const bool clred = local_object_lock_table.erase(it);
		// 	if(clred)
		// 		property_initializer<
		// 			local_property<
		// 				property_config<Tproperties>
		// 			>...
		// 		>::uninit(object_id);

		// 	return clred;
		// }

		// static bool clr_remote(remote_table_iterator it)
		// {
		// 	const object_id_type object_id = it->second.object_id;
		// 	const bool clred = remote_object_lock_table.erase(it);
		// 	if(clred)
		// 		property_initializer<
		// 			remote_property<
		// 				property_config<Tproperties>
		// 			>...
		// 		>::uninit(object_id);

		// 	return clred;
		// }

		static bool remote_add(
			object_id_type local_object_id,
			object_id_type remote_object_id
		)
		{
			lock_local();

			auto local_it = find_local(local_object_id);
			if(unknown_local_object(local_it, jrn))
				return false;

			lock_remote();

			auto remote_it = find_remote(remote_object_id);
			if(remote_it == end())
			{
				unlock_remote();
				unlock_local();
				jrn(journal::error) <<
					"Invalid remote `" << name <<
					"' object reference " << std::hex << remote_object_id <<
					journal::end;
				return false;
			}

			local_it->second.remotes.lock();
			local_it->second.remotes.try_emplace(remote_object_id);
			local_it->second.remotes.unlock();

			unlock_remote();
			unlock_local();
			jrn(journal::trace) <<
				"object: " << std::hex << local_object_id << "; added remote `" << name <<
				"' object reference " << remote_object_id <<
				journal::end;

			property_initializer<
				local_property<
					property_config<Tproperties>
				>...
			>::proc_sync_notify(local_object_id, remote_object_id);
			return true;
		}

		static bool remote_del(
			object_id_type local_object_id,
			object_id_type remote_object_id
		)
		{
			lock_local();

			auto local_it = find_local(local_object_id);
			if(unknown_local_object(local_it, jrn))
				return false;

			auto &local = local_it->second;
			property_initializer<
				local_property<
					property_config<Tproperties>
				>...
			>::cancel(local_it, remote_object_id);

			local.remotes.lock();

			if(!local.remotes.erase(remote_object_id))
			{
				local.remotes.unlock();
				unlock_local();
				jrn(journal::error) <<
					"Invalid remote `" << name <<
					"' object reference " << std::hex << remote_object_id <<
					journal::end;

				return false;
			}

			local.remotes.unlock();
			unlock_local();
			jrn(journal::trace) <<
				"object: " << std::hex << local_object_id << "; deleted remote `" << name <<
				"' object reference " << std::hex << remote_object_id <<
				journal::end;
			return true;
		}

		static bool local_has_no_remote(
			const typename local_object_record_type::remotes_iterator &device, 
			object_id_type remote_object_id, 
			local_object_record_type &local
		)
		{
			if(device == local.remotes.end())
			{
				local.remotes.unlock();
				oosp_class::unlock_local();
				jrn(journal::error) <<
					"local object " << std::hex << local.object_id <<
					" has no remote object: " << remote_object_id <<
					journal::end;
				return true;
			}
			return false;
		}

		static bool unknown_local_object(local_table_iterator local_it, journal (*jrnal)(uint8_t, object_id_type))
		{
			if(local_it == end())
			{
				unlock_local();
				jrnal(journal::error, local_it->first) <<
					"Invalid local `" << name <<
					"' object reference" <<
					journal::end;
				return true;
			}
			return false;
		}

		static bool unknown_remote_object(remote_table_iterator remote_it, journal (*jrnal)(uint8_t, object_id_type))
		{
			if(remote_it == end())
			{
				unlock_remote();
				jrnal(journal::error, remote_it->first) <<
					"Invalid remote `" << name <<
					"' object reference" <<
					journal::end;
				return true;
			}
			return false;
		}
	
		static bool unknown_object(local_table_iterator local_it, journal (*jrnal)(uint8_t, object_id_type))
		{ return unknown_local_object(local_it, jrnal); }

		static bool unknown_object(remote_table_iterator remote_it, journal (*jrnal)(uint8_t, object_id_type))
		{ return unknown_remote_object(remote_it, jrnal); }

		static bool unknown_device_object(
			local_object_record_type &local, 
			remote_table_iterator remote_it, 
			journal (*jrnal)(uint8_t, object_id_type)
		)
		{
			if(remote_it == end())
			{
				unlock_remote();
				local.remotes.unlock();
				unlock_local();
				jrnal(journal::error, remote_it->first) <<
					"Invalid remote `" << name <<
					"' object reference" <<
					journal::end;
				return true;
			}
			return false;
		}

		// TODO
		// template <typename Tfn>
		// static void safe_local_process(object_id_type object_id, journal (*jrnal)(uint8_t), Tfn &f)
		// {
		// 	lock_local();
		// 	auto local_it = find_local(object_id);
		// 	if(local_it == end())
		// 	{
		// 		unlock_local();
		// 		jrnal(journal::error) <<
		// 			"Invalid local `" << name <<
		// 			"' object reference `" << std::hex << object_id <<
		// 			journal::end;
		// 		return;
		// 	}

		// 	f(local_it);
		// 	unlock_local();
		// }

		// template <typename Tfn>
		// static void safe_remote_process(object_id_type object_id, journal (*jrnal)(uint8_t), Tfn &f)
		// {
		// 	lock_remote();
		// 	auto remote_it = find_remote(object_id);
		// 	if(remote_it == end())
		// 	{
		// 		unlock_remote();
		// 		jrnal(journal::error) <<
		// 			"Invalid remote `" << name <<
		// 			"' object reference `" << std::hex << object_id <<
		// 			journal::end;
		// 		return;
		// 	}

		// 	f(remote_it);
		// 	unlock_remote();
		// }

		// template <typename T, typename Tfn>
		// static std::enable_if_t<
		// 	std::is_same_v<T, local_object_record_type>
		// > safe_process(object_id_type object_id, journal (*jrnal)(uint8_t), Tfn &f)
		// { safe_local_process(object_id); }

		// template <typename T, typename Tfn>
		// static std::enable_if_t<
		// 	std::is_same_v<T, remote_object_record_type>
		// > safe_process(object_id_type object_id, journal (*jrnal)(uint8_t), Tfn &f)
		// { safe_remote_process(object_id); }

	};

	OOSP_CLASS_TEMPLATE
	typename OOSP_CLASS::local_object_lock_table_type
		OOSP_CLASS::local_object_lock_table;

	OOSP_CLASS_TEMPLATE
	typename OOSP_CLASS::remote_object_lock_table_type
		OOSP_CLASS::remote_object_lock_table;

	OOSP_CLASS_TEMPLATE
	template <typename Tproperty, typename... Tremaining>
	struct OOSP_CLASS::property_initializer<Tproperty, Tremaining...>
	{
		static void init()
		{
			Tproperty::first_type::init();
			Tproperty::second_type::init();
			OOSP_CLASS::property_initializer<Tremaining...>::init();
		}

		static void uninit()
		{
			Tproperty::first_type::uninit();
			Tproperty::second_type::uninit();
			OOSP_CLASS::property_initializer<Tremaining...>::uninit();
		}

		static void init(typename OOSP_CLASS::object_id_type object_id)
		{
			Tproperty::init(object_id);
			OOSP_CLASS::property_initializer<Tremaining...>::init(object_id);
		}

		static void uninit(typename OOSP_CLASS::object_id_type object_id)
		{
			Tproperty::uninit(object_id);
			OOSP_CLASS::property_initializer<Tremaining...>::uninit(object_id);
		}

		static void proc_sync_notify(
			typename OOSP_CLASS::object_id_type local_object_id, 
			typename OOSP_CLASS::object_id_type remote_object_id
		)
		{
			Tproperty::proc_sync::notify(local_object_id, remote_object_id);
			OOSP_CLASS::property_initializer<Tremaining...>::proc_sync_notify(local_object_id, remote_object_id);
		}

		static void cancel(
			typename OOSP_CLASS::local_table_iterator &local_it, 
			typename OOSP_CLASS::object_id_type remote_object_id
		)
		{
			Tproperty::cancel(local_it, remote_object_id);
			OOSP_CLASS::property_initializer<Tremaining...>::cancel(local_it, remote_object_id);
		}
	};

	OOSP_CLASS_TEMPLATE
	template <typename Tproperty>
	struct OOSP_CLASS::property_initializer<Tproperty>
	{
		static void init()
		{ 
			Tproperty::first_type::init(); 
			Tproperty::second_type::init();
		}

		static void uninit()
		{ 
			Tproperty::first_type::uninit(); 
			Tproperty::second_type::uninit();
		}

		static void init(typename OOSP_CLASS::object_id_type object_id)
		{ Tproperty::init(object_id); }

		static void uninit(typename OOSP_CLASS::object_id_type object_id)
		{ Tproperty::uninit(object_id); }

		static void proc_sync_notify(
			typename OOSP_CLASS::object_id_type local_object_id, 
			typename OOSP_CLASS::object_id_type remote_object_id
		)
		{ Tproperty::proc_sync::notify(local_object_id, remote_object_id); }

		static void cancel(
			typename OOSP_CLASS::local_table_iterator &local_it, 
			typename OOSP_CLASS::object_id_type remote_object_id
		)
		{ Tproperty::cancel(local_it, remote_object_id); }
	};
}

#undef OOSP_CLASS_TEMPLATE
#undef OOSP_CLASS

#endif
