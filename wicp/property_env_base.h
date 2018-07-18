#ifndef WICP_PROPERTY_ENV_BASE_H
# define WICP_PROPERTY_ENV_BASE_H
# include <mutex>
# include <list>
# include <net/ipv4_address.h>
# include <sched/listener.h>
# include <wicp/role.h>
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


		typedef typename TConfig::cfg_object_id_type object_id_type;

		typedef typename TConfig::cfg_value_type     value_type;

		typedef typename rpc::template outgoing_call_handle<bool,value_type> set_handle_type;

		typedef typename rpc::template outgoing_call_handle<value_type,bool> get_handle_type;

		typedef typename rpc::template incoming_call_handle<bool,value_type> notify_handle_type;

		typedef typename TConfig::cfg_wic_class wic_class;

		typedef typename wic_class::local_object_record_type local_object_record_type;

		typedef typename wic_class::remote_object_record_type remote_object_record_type;

		typedef std::integral_constant<member_id_type, TConfig::cfg_member_id> member_id;

		static typename clock::time_point            local_timestamp;

		static sched::listener on_change;

		static_assert(
			sizeof(command_id_type) >= sizeof(class_id_type) + sizeof(member_id_type),
			"class and member id types does not fit together in command id type"
		);

		static const uint32_t                        cooldown_time = TConfig::cfg_cooldown_time;

		static const uint32_t                        history_size  = TConfig::cfg_history_size;

		constexpr static const bool                  commit_change_only   = TConfig::cfg_commit_change_only;

		static const class_id_type                   class_id      = TConfig::cfg_class_id;

		static const command_id_type                 command_id    =
			(static_cast<command_id_type>(class_id) << (sizeof(member_id_type)*8)) |
			((member_id::value & (static_cast<member_id_type>(-1) >> 3)) << 3)
		;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.base") << "property: " << std::hex <<
				class_id << "::" << member_id::value << ' ';
		}

	/// Remote endpoint ///
		struct remote_record
		{
			role_type &role;

			typename clock::time_point sync_timestamp;

			typename clock::time_point pending_timestamp;

			call_id_type call_id;

			typename clock::time_point sync_start;

			typename clock::duration latency;

			uint32_t failures;

			remote_record() 
				: role(role_type::none)
			{}

			remote_record(const remote_record &t)
				: role(t.role)
				, sync_timestamp(t.sync_timestamp)
				, pending_timestamp(t.pending_timestamp)
				, sync_start(t.sync_start)
				, latency(t.latency)
				, failures(t.failures)
				, call_id(t.call_id)
			{}

			remote_record(role_type &prole)
				: role(prole)
				, sync_timestamp(clock::time_point::min())
				, pending_timestamp(clock::time_point::min())
				, failures(0)
				, call_id(0)
			{}
		};

	/// History /// 
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

		static std::mutex   history_lock;

	/// Local value ///
		static value_type default_value;

		static value_type value;

		static void sync_local(object_id_type object_id)
		{
			wic_class::lock_local();
			auto it = wic_class::find_local(object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				auto &property = it->second.properties.template get<member_id>();
				if(property.history.empty())
				{
					it->second.property_lock.unlock();
					wic_class::unlock_local();
					return;				
				}
				if(local_timestamp < property.history.front().time)
				{
					local_timestamp = property.history.front().time;
					property.on_change();
					it->second.property_lock.unlock();
					wic_class::unlock_local();
					return;
				}
				it->second.property_lock.unlock();
			}
			wic_class::unlock_local();
		}

		static void sync_remote(
			remote_record &r,
			uint8_t function,
			void(*callback)(set_handle_type)
		)
		{
			history_lock.lock();
			if(history.empty())
			{
				history_lock.unlock();
				jrn(journal::trace) << "history is empty; omitting sync" << journal::end;
				return;
			}
			if(r.sync_timestamp > history.front().time)
			{
				jrn(journal::critical) << "remote: " << (std::string)r.role.get_ip() <<
					"; sync timestamp is newer than tip of history; recovering by synchronizing last item" << journal::end;
				r.sync_timestamp = history.front().time - std::chrono::nanoseconds(1);
			}
			else if(r.pending_timestamp != clock::time_point::min())
			{
				if(r.sync_start != clock::time_point::min())
				{
					uint32_t msecs = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now()-r.sync_start).count();
					if(msecs/(r.failures+1) < 3600)
					{
						jrn(journal::trace) << "remote: " << (std::string)r.role.get_ip() << "; sync has been pending for " <<
							msecs << "msec" <<
							journal::end;
						history_lock.unlock();
						return;
					}
				}
				r.pending_timestamp = clock::time_point::min();
				r.sync_start = clock::time_point::min();
			}
			else if(r.sync_timestamp == history.front().time)
			{
				jrn(journal::trace) << "remote: " << (std::string)r.role.get_ip() << "; up-to-date" << journal::end;
				history_lock.unlock();
				return;
			}


			
			jrn(journal::trace) << "remote: " << (std::string)r.role.get_ip() << "; sync needed" << journal::end;
			typename history_type::iterator i = history.begin();
			for(
				typename history_type::iterator j = history.begin();
				j != history.end();
				++j
			)
			{

				if(r.sync_timestamp >= j->time)
					break;
				i = j;
			}

			r.pending_timestamp = i->time;
			if(r.sync_start == clock::time_point::min())
			{
				r.sync_start = clock::now();
				r.failures = 0;
			}

			const value_type v = i->value;
			jrn(journal::trace) << "remote: " << (std::string)r.role.get_ip() << "; sync initiated" << journal::end;
			r.call_id = rpc::call(r.role.get_ip(),command_id|function,v,callback);
			history_lock.unlock();
		}

		static void sync_remote(
			remote_object_record_type &r,
			uint8_t function,
			void(*callback)(set_handle_type)
		)
		{
			auto &property = r.properties.template get<member_id>();

			// TODO we already check this in sync_local/123 and our lock is still on			
			// history_lock.lock();
			// if(history.empty())
			// {
			// 	history_lock.unlock();
			// 	jrn(journal::trace) << "history is empty; omitting sync" << journal::end;
			// 	return;
			// }
			if(property.remote.sync_timestamp > property.history.front().time)
			{
				jrn(journal::critical) << "remote: " << (std::string)r.address <<
					"; sync timestamp is newer than tip of history; recovering by synchronizing last item" << journal::end;
				property.remote.sync_timestamp = property.history.front().time - std::chrono::nanoseconds(1);
			}
			else if(property.remote.pending_timestamp != clock::time_point::min())
			{
				if(property.remote.sync_start != clock::time_point::min())
				{
					uint32_t msecs = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now()-property.remote.sync_start).count();
					if(msecs/(property.remote.failures+1) < 3600)
					{
						jrn(journal::trace) << "remote: " << (std::string)r.address << "; sync has been pending for " <<
							msecs << "msec" <<
							journal::end;
						return;
					}
				}
				property.remote.pending_timestamp = clock::time_point::min();
				property.remote.sync_start = clock::time_point::min();
			}
			else if(property.remote.sync_timestamp == property.history.front().time)
			{
				jrn(journal::trace) << "remote: " << (std::string)r.address << "; up-to-date" << journal::end;
				return;
			}
			
			jrn(journal::trace) << "remote: " << (std::string)r.address << "; sync needed" << journal::end;

			// TODO [eliminate loop]
			typename std::remove_reference_t<decltype(property)>::history_type::iterator i = property.history.begin();
			for(
				typename std::remove_reference_t<decltype(property)>::history_type::iterator j = property.history.begin();
				j != property.history.end();
				++j
			)
			{
				if(property.remote.sync_timestamp >= j->time)
					break;
				i = j;
			}

			property.remote.pending_timestamp = i->time;
			if(property.remote.sync_start == clock::time_point::min())
			{
				property.remote.sync_start = clock::now();
				property.remote.failures = 0;
			}

			const value_type v = i->value;
			jrn(journal::trace) << "remote: " << (std::string)r.address << "; sync initiated" << journal::end;
			property.remote.call_id = rpc::call(r.address,command_id|function,v,callback);
		}

		static void finish_sync_remote(remote_record &r, set_handle_type h)
		{
			history_lock.lock();
			r.call_id = 0;
			if(r.sync_start != clock::time_point::min())
				r.latency = clock::now() - r.sync_start;

			if(
				h.reason == earpc::reason::success &&
				(r.sync_timestamp < r.pending_timestamp)
			)
			{
				r.sync_timestamp = r.pending_timestamp;
				r.sync_start = clock::time_point::min();
			}

			else
			{
				++r.failures;
			}

			r.pending_timestamp = clock::time_point::min();

			history_lock.unlock();
		}
	};

	template<typename c>
	typename property_env_base<c>::history_type property_env_base<c>::history;

	template<typename c>
	std::mutex property_env_base<c>::history_lock;

	template<typename c>
	sched::listener property_env_base<c>::on_change;

	template<typename c>
	typename property_env_base<c>::value_type property_env_base<c>::value;

	template<typename c>
	typename property_env_base<c>::value_type property_env_base<c>::default_value;

	template<typename c>
	typename property_env_base<c>::clock::time_point property_env_base<c>::local_timestamp =
		property_env_base<c>::clock::time_point::min();
}
#endif
