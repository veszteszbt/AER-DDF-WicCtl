#ifndef WICP_WIC_CLASS_HH
# define WICP_WIC_CLASS_HH
# include <map>
# include <mutex>
# include <sched/listener.h>
# include <sched/lockable.h>
# include <types/meta.h>
# include <wicp/local_property.h>
# include <wicp/remote_property.h>
# include <wicp/types/object_record.h>
# include <wicp/types/property_data_type.h>
# include <wicp/types/property_record.h>

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

		typedef WIC_CLASS									self;

		template <typename Tproperty>
		struct property_config
		{
			typedef typename Tproperty::value_type	cfg_value_type;

			typedef class_id_type					cfg_class_id_type;

			typedef member_id_type					cfg_member_id_type;

			typedef object_id_type					cfg_object_id_type;

			typedef earpc							cfg_earpc;

			typedef self							cfg_wic_class;

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
		struct object_record_transform 
			: std::pair<
				typename TpropertyConfig::cfg_member_id, 
					types::property_record<
						call_id_type,
						object_id_type,
						typename TpropertyConfig::cfg_value_type
					>
				>
		{};

		template <typename TpropertyConfig>
		struct property_transform 
			: std::pair<
				local_property<TpropertyConfig>, 
				remote_property<TpropertyConfig>
			>
		{};

		template <typename TpropertyConfig>
		struct local_property_transform 
			: std::pair<
				typename TpropertyConfig::cfg_member_id, 
				local_property<TpropertyConfig>
			>
		{};

		template <typename TpropertyConfig>
		struct remote_property_transform 
			: std::pair<
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

		typedef ::types::static_map<
			local_property_transform<
				property_config<Tproperties>
			>...
		>	local_property_holder;

		typedef ::types::static_map<
			remote_property_transform<
				property_config<Tproperties>
			>...
		>	remote_property_holder;

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

		template <member_id_type tMemberId>
		static auto get_local()
		{ return local_property_holder::template get<tMemberId>(); }

		template <member_id_type tMemberId>
		static auto get_remote()
		{ return remote_property_holder::template get<tMemberId>(); }

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
			auto it = local_object_lock_table.find(object_id);
			if(it == local_object_lock_table.end())
			{
				local_object_lock_table.unlock();
				return false;
			}

			const bool clred = local_object_lock_table.erase(it);
			property_initializer<
				local_property<
					property_config<Tproperties>
				>...
			>::uninit(object_id);

			local_object_lock_table.unlock();
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
			property_initializer<
				remote_property<
					property_config<Tproperties>
				>...
			>::uninit(object_id);
			remote_object_lock_table.unlock();
			return clred;
		}

		static bool clr_local(local_iterator it)
		{
			const object_id_type object_id = it->second.object_id;
			const bool clred = local_object_lock_table.erase(it);
			if(clred)
				property_initializer<
					local_property<
						property_config<Tproperties>
					>...
				>::uninit(object_id);

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

		static bool is_known_local_object(local_iterator local_it, journal (*jrn)(uint8_t, object_id_type))
		{
			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::error, local_it->first) <<
					"Invalid local `" << wic_class::name <<
					"' object reference" <<
					journal::end;
				return false;
			}
			return true;
		}

		template <typename Tfn>
		static void safe_local_process(object_id_type object_id, journal (*jrn)(uint8_t), Tfn &f)
		{
			wic_class::lock_local();
			auto local_it = wic_class::find_local(object_id);
			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::error) <<
					"Invalid local `" << wic_class::name <<
					"' object reference `" << std::hex << object_id <<
					journal::end;
				return;
			}

			f(local_it);
			wic_class::unlock_local();
		}

		template <typename Tfn>
		static void safe_remote_process(object_id_type object_id, journal (*jrn)(uint8_t), Tfn &f)
		{
			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(object_id);
			if(remote_it == wic_class::end())
			{
				wic_class::unlock_remote();
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference `" << std::hex << object_id <<
					journal::end;
				return;
			}

			f(remote_it);
			wic_class::unlock_remote();
		}

		template <typename T, typename Tfn>
		static std::enable_if_t<
			std::is_same_v<T, local_object_record_type>
		> safe_process(object_id_type object_id, journal (*jrn)(uint8_t), Tfn &f)
		{ safe_local_process(object_id); }

		template <typename T, typename Tfn>
		static std::enable_if_t<
			std::is_same_v<T, remote_object_record_type>
		> safe_process(object_id_type object_id, journal (*jrn)(uint8_t), Tfn &f)
		{ safe_remote_process(object_id); }

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
			Tproperty::first_type::init();
			Tproperty::second_type::init();
			WIC_CLASS::property_initializer<Tremaining...>::init();
		}

		static void uninit()
		{
			Tproperty::first_type::uninit();
			Tproperty::second_type::uninit();
			WIC_CLASS::property_initializer<Tremaining...>::uninit();
		}

		static void init(typename WIC_CLASS::object_id_type object_id)
		{
			Tproperty::init(object_id);
			WIC_CLASS::property_initializer<Tremaining...>::init(object_id);
		}

		static void uninit(typename WIC_CLASS::object_id_type object_id)
		{
			Tproperty::uninit(object_id);
			WIC_CLASS::property_initializer<Tremaining...>::uninit(object_id);
		}
	};

	WIC_CLASS_TEMPLATE
	template <typename Tproperty>
	struct WIC_CLASS::property_initializer<Tproperty>
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

		static void init(typename WIC_CLASS::object_id_type object_id)
		{ Tproperty::init(object_id); }

		static void uninit(typename WIC_CLASS::object_id_type object_id)
		{ Tproperty::uninit(object_id); }
	};
}

#undef WIC_CLASS_TEMPLATE
#undef WIC_CLASS

#endif
