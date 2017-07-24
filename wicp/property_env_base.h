#ifndef WICP_PROPERTY_ENV_BASE_H
# define WICP_PROPERTY_ENV_BASE_H
# include <mutex>
# include <list>
# include <net/ipv4_address.h>
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

	/// Remote endpoint ///
		struct remote_record
		{
			net::ipv4_address   ip;

			typename clock::time_point sync_timestamp;

			typename clock::time_point pending_timestamp;

			remote_record() {}

			remote_record(net::ipv4_address i)
				: ip(i)
				, sync_timestamp(clock::time_point::min())
				, pending_timestamp(clock::time_point::min())
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
		static value_type value;

		static void sync_remote(
			remote_record &r,
			uint8_t function,
			void(*callback)(net::ipv4_address,command_id_type,const bool*)
		)
		{
			history_lock.lock();
			if(
				r.pending_timestamp != clock::time_point::min() &&
				r.sync_timestamp < history.front().time
			)
			{
				typename history_type::reverse_iterator i = history.rbegin();
				for(
					;i != history.rend();
					++i
				)
					if(r.sync_timestamp >= i->time)
						break;

				if(i == history.rend())
					--i;
				else
					++i;
				
				r.pending_timestamp = i->time;
				history_lock.unlock();
				rpc::call(r.ip,command_id|function,i->value,callback);
			}
			else
				history_lock.unlock();
		}

		static void finish_sync_remote(remote_record &r, bool v)
		{
		
			history_lock.lock();
			if(v && (r.sync_timestamp < r.pending_timestamp))
				r.sync_timestamp = r.pending_timestamp;

			r.pending_timestamp = clock::time_point::min();

			history_lock.unlock();
		}
	};

	template<typename c>
	typename property_env_base<c>::history_type property_env_base<c>::history;

	template<typename c>
	std::mutex property_env_base<c>::history_lock;

	template<typename c>
	typename property_env_base<c>::value_type property_env_base<c>::value;

}
#endif
