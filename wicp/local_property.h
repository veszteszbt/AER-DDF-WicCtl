#ifndef WICP_LOCAL_PROPERTY_H
# define WICP_LOCAL_PROPERTY_H
# include <wicp/types.h>
# include <wicp/property_env_base.h>
# include <wicp/process/sync_local.h>
# include <wicp/process/commit.h>
# include <wicp/process/log.h>
namespace wicp
{
	template<typename TConfig>
	class local_property
	{
	public:
		typedef void (*change_handler_type)();
	private:
		struct env : public property_env_base<TConfig>
		{
			typedef property_env_base<TConfig> base;

		/// Remote list ///

			typedef std::list<typename base::remote_record> remotes_type;

			static remotes_type remotes;

			static std::mutex   remotes_lock;
		};


		struct env_commit : public env
		{
			typedef typename process::sync_local<env> proc_sync;
			typedef typename process::log<env>         proc_log;
		};

		typedef typename process::commit<env_commit>  proc_commit;

		typedef typename env_commit::proc_sync        proc_sync;     

		typedef typename env::rpc                     rpc;

		typedef typename env::command_id_type         command_id_type;

		typedef typename env::value_type              value_type;

		typedef typename env::remotes_type            remotes_type;

		typedef typename env::remote_record           remote_record;

		typedef typename env::history_type            history_type;

		typedef typename rpc::template call_handle<value_type> get_handle_type;

		typedef typename rpc::template call_handle<bool>       set_handle_type;

		static const command_id_type                  command_id = env::command_id;

		constexpr static remotes_type                &remotes = env::remotes;

		constexpr static history_type                &history = env::history;

		constexpr static std::mutex                  &remotes_lock = env::remotes_lock;

		constexpr static std::mutex                  &history_lock = env::history_lock;


		static void get_handler(get_handle_type h,const uint8_t*)
		{
			history_lock.lock();
			value_type rv(history.empty() ? env::value : history.front().value);
			history_lock.unlock();
			h.respond(rv);
		}

		static void set_handler(set_handle_type h,const value_type *v)
		{
			history_lock.lock();
			env::value = *v;
			history_lock.unlock();
			proc_commit::notify();
			h.respond(true);
		}



	public:
		constexpr static listener_t &on_change = env::on_change;

		static void init()
		{
			remotes.clear();
			history.clear();
			proc_commit::init();
			proc_sync::init();
			rpc::set_command(
				command_id | types::function::get,
				get_handler
			);
			rpc::set_command(
				command_id | types::function::set,
				set_handler
			);
//			std::cout << "\e[32;01m - \e[0mwicp local property: initialized; command id is " << std::hex << command_id << std::endl;
		}

		static void uninit()
		{
			rpc::clear_command(command_id | types::function::get);
			rpc::clear_command(command_id | types::function::set);
			remotes.clear();
			history.clear();
			proc_commit::uninit();
			proc_sync::uninit();
		}

		static value_type value()
		{
			history_lock.lock();
			if(history.empty())
			{
				value_type rv = env::value;
				history_lock.unlock();
				return rv;
			}
			value_type rv = history.front().value;
			history_lock.unlock();
			return rv;
		}

		static value_type value(value_type v)
		{
			history_lock.lock();
			if(env::commit_change_only && env::value == v)
			{
				history_lock.unlock();
				return v;
			}
			env::value = v;
			history_lock.unlock();
			proc_commit::notify();
			return v;
		}

		static bool remote_add(net::ipv4_address ip)
		{
			remotes_lock.lock();
			remotes.push_back(remote_record(ip));
			remotes_lock.unlock();

			proc_sync::notify();
			return true;
		}

		static bool remote_del(net::ipv4_address ip)
		{
			remotes_lock.lock();
			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				if(i->ip == ip)
				{
				
					remotes.erase(i);
					remotes_lock.unlock();
					proc_sync::notify();
					return true;
				}
			remotes_lock.unlock();
			return false;
		}

	};

	template<typename c>
	typename local_property<c>::env::remotes_type local_property<c>::env::remotes;

	template<typename c>
	std::mutex local_property<c>::env::remotes_lock;
}
#endif
