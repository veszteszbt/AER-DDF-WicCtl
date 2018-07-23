#ifndef WICP_PROPERTY_ENV_BASE_H
# define WICP_PROPERTY_ENV_BASE_H
# include <mutex>
# include <list>
# include <net/ipv4_address.h>
# include <sched/listener.h>
# include <wicp/role.h>
# include <wicp/types/property_record.h>
# include <journal.h>
namespace wicp
{
	template<typename TConfig>
	struct property_env_base
	{
		typedef typename TConfig::cfg_clock          clock;

		typedef typename TConfig::cfg_earpc          rpc;

		typedef typename rpc::command_id_type        command_id_type;

		typedef typename rpc::call_id_type           call_id_type;

		typedef typename TConfig::cfg_class_id_type  class_id_type;

		typedef typename TConfig::cfg_member_id_type member_id_type;

		typedef typename TConfig::cfg_property_data_type property_data_type;

		typedef typename TConfig::cfg_object_id_type object_id_type;

		typedef typename TConfig::cfg_value_type     value_type;

		typedef typename rpc::template outgoing_call_handle<object_id_type, property_data_type> set_handle_type;

		typedef typename rpc::template outgoing_call_handle<property_data_type, object_id_type> get_handle_type;

		typedef typename rpc::template incoming_call_handle<object_id_type, property_data_type> notify_handle_type;

		typedef wicp::types::property_record_base<call_id_type, object_id_type, value_type> property_record_base;

		typedef typename property_record_base::history_type  history_type;

		typedef typename property_record_base::history_record  history_record;

		typedef typename TConfig::cfg_wic_class wic_class;

		typedef typename wic_class::local_object_record_type local_object_record_type;

		typedef typename wic_class::remote_object_record_type remote_object_record_type;

		typedef std::integral_constant<member_id_type, TConfig::cfg_member_id> member_id;

		static_assert(
			sizeof(command_id_type) >= sizeof(class_id_type) + sizeof(member_id_type),
			"class and member id types does not fit together in command id type"
		);

		static const uint32_t                        cooldown_time = TConfig::cfg_cooldown_time;

		static const uint32_t                        history_size  = TConfig::cfg_history_size;

		static const class_id_type                   class_id      = TConfig::cfg_class_id;

		static const command_id_type                 command_id    =
			(static_cast<command_id_type>(class_id) << (sizeof(member_id_type)*8)) |
			((member_id::value & (static_cast<member_id_type>(-1) >> 3)) << 3)
		;

		static value_type default_value;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.base") << "property: " << std::hex <<
				class_id << "::" << member_id::value << ' ';
		}

		template <typename Tproperty>
		static std::enable_if_t<
			std::is_base_of_v<
				property_record_base,
				Tproperty
			>, bool
		> sync_local(Tproperty &property)
		{
			if(property.history.empty())
			{
				jrn(journal::error) << "nothing to do history is empty" << journal::end;
				return false;				
			}
			if(property.local_timestamp < property.history.front().time)
			{
				property.local_timestamp = property.history.front().time;
				return true;
			}
			return false;
		}

		template <typename Tproperty>
		static std::enable_if_t<
			std::is_base_of_v<
				property_record_base, 
				Tproperty
			>
		> sync_remote(		
			Tproperty &property,
			const history_type &history,
			object_id_type object_id,
			net::ipv4_address ip,
			uint8_t function,
			void(*callback)(set_handle_type)
		)
		{
			if(history.empty())
			{
				jrn(journal::trace) << "history is empty; omitting sync" << journal::end;
				return;
			}
			if(property.sync_timestamp > history.front().time)
			{
				jrn(journal::critical) << "remote: " << (std::string)ip <<
					"; sync timestamp is newer than tip of history; recovering by synchronizing last item" << journal::end;
				property.sync_timestamp = history.front().time - std::chrono::nanoseconds(1);
			}
			else if(property.pending_timestamp != clock::time_point::min())
			{
				if(property.sync_start != clock::time_point::min())
				{
					uint32_t msecs = 
						std::chrono::duration_cast<std::chrono::milliseconds>(clock::now()-property.sync_start).count();
					if(msecs/(property.failures+1) < 3600)
					{
						jrn(journal::trace) << "remote: " << (std::string)ip << "; sync has been pending for " <<
							msecs << "msec" <<
							journal::end;
						return;
					}
				}
				property.pending_timestamp = clock::time_point::min();
				property.sync_start = clock::time_point::min();
			}
			else if(property.sync_timestamp == history.front().time)
			{
				jrn(journal::trace) << "remote: " << (std::string)ip << "; up-to-date" << journal::end;
				return;
			}			
			jrn(journal::trace) << "remote: " << (std::string)ip << "; sync needed" << journal::end;

			typename history_type::const_iterator i = history.begin();
			for(
				typename history_type::const_iterator j = history.begin();
				j != history.end();
				++j
			)
			{
				if(property.sync_timestamp >= j->time)
					break;
				i = j;
			}

			property.pending_timestamp = i->time;
			if(property.sync_start == clock::time_point::min())
			{
				property.sync_start = clock::now();
				property.failures = 0;
			}

			const property_data_type v = {object_id, i->value};
			jrn(journal::trace) << "remote: " << (std::string)ip << "; sync initiated" << journal::end;
			property.call_id = rpc::call(ip,command_id|function,v,callback);
		}

		template <typename Tproperty>
		static std::enable_if_t<
			std::is_base_of_v<
				property_record_base, 
				Tproperty
			>
		> sync_remote(
			Tproperty &property,
			object_id_type local_object_id,
			object_id_type remote_object_id,
			net::ipv4_address ip,
			uint8_t function,
			void(*callback)(set_handle_type)
		)
		{
			wic_class::lock_local();
			auto it = wic_class::find_local(local_object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				history_type history = it->second.properties.template get<member_id>().history;
				sync_remote(property, history, remote_object_id, ip,function, callback);
				wic_class::unlock_local();
				it->second.property_lock.unlock();
			}
			else
			{
				wic_class::unlock_local();
				jrn(journal::error) << "Invalid `" << 
					wic_class::name << "' object reference `" << std::hex << local_object_id << journal::end;
			}
		}

		template <typename Tproperty>
		static std::enable_if_t<
			std::is_base_of_v<
				property_record_base, 
				Tproperty
			>
		> sync_remote(
			Tproperty &property,
			object_id_type object_id,
			net::ipv4_address ip,
			uint8_t function,
			void(*callback)(set_handle_type)
		)
		{ sync_remote(property, property.history, object_id, ip, function, callback); }

		template <typename Tproperty>
		static std::enable_if_t<
			std::is_base_of_v<
				property_record_base, 
				Tproperty
			>
		> finish_sync_remote(Tproperty &property, set_handle_type h)
		{
			property.call_id = 0;
			if(property.sync_start != clock::time_point::min())
				property.latency = clock::now() - property.sync_start;

			if(
				h.reason == earpc::reason::success &&
				(property.sync_timestamp < property.pending_timestamp)
			)
			{
				property.sync_timestamp = property.pending_timestamp;
				property.sync_start = clock::time_point::min();
			}
			else
				++property.failures;

			property.pending_timestamp = clock::time_point::min();
		}
	};

	template<typename c>
	typename property_env_base<c>::value_type property_env_base<c>::default_value;
}
#endif
