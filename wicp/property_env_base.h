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

		typedef typename TConfig::cfg_class_id_type  class_id_type;

		typedef typename TConfig::cfg_member_id_type member_id_type;

		typedef typename TConfig::cfg_value_type     value_type;

		static typename clock::time_point            local_timestamp;

		static sched::listener on_change;

		static_assert(
			sizeof(command_id_type) >= sizeof(class_id_type) + sizeof(member_id_type),
			"class and member id types does not fit together in command id type"
		);

		static const uint32_t                        cooldown_time = TConfig::cfg_cooldown_time;

		constexpr static const bool                  commit_change_only   = TConfig::cfg_commit_change_only;

		static const class_id_type                   class_id      = TConfig::cfg_class_id;

		static const member_id_type                  member_id     = TConfig::cfg_member_id;

		static const command_id_type                 command_id    =
			(static_cast<command_id_type>(class_id) << (sizeof(member_id_type)*8)) |
			((member_id & (static_cast<member_id_type>(-1) >> 3)) << 3)
		;

		static int64_t tp2nsec(typename clock::time_point p)
		{ return std::chrono::time_point_cast<std::chrono::nanoseconds>(p).time_since_epoch().count(); }

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.base") << "property: " << std::hex <<
				class_id << "::" << member_id << ' ';
		}

	/// Remote endpoint ///
		struct remote_record
		{
			role_type &role;

			typename clock::time_point sync_timestamp;

			typename clock::time_point pending_timestamp;

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
			{}

			remote_record(role_type &prole)
				: role(prole)
				, sync_timestamp(clock::time_point::min())
				, pending_timestamp(clock::time_point::min())
				, failures(0)
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

		static void sync_local()
		{
			history_lock.lock();
			if(history.empty())
			{
				history_lock.unlock();
				return;
			
			}
			if(local_timestamp < history.front().time)
			{
				local_timestamp = history.front().time;
				history_lock.unlock();
				on_change();
				return;
			}
			history_lock.unlock();
		}

		static void sync_remote(
			remote_record &r,
			uint8_t function,
			void(*callback)(net::ipv4_address,command_id_type,const bool*)
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
			history_lock.unlock();
			rpc::call(r.role.get_ip(),command_id|function,v,callback);
		}

		static void finish_sync_remote(remote_record &r, bool v)
		{
		
			history_lock.lock();
			if(r.sync_start != clock::time_point::min())
				r.latency = clock::now() - r.sync_start;

			if(v && (r.sync_timestamp < r.pending_timestamp))
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
