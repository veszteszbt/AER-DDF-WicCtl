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
		typedef TConfig config;

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

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.property.local") << "property: " << std::hex <<
				env::class_id << "::" << env::member_id << ' ';
		}


		struct env_commit : public env
		{
			typedef typename process::sync_local<env> proc_sync;
			typedef typename process::log<env>         proc_log;
		};

		typedef typename process::commit<env_commit>  proc_commit;

		typedef typename env_commit::proc_sync        proc_sync;     

		typedef typename env::rpc                     rpc;

		typedef typename env::command_id_type         command_id_type;

	public:
		typedef typename env::value_type              value_type;

	private:
		typedef typename env::remotes_type            remotes_type;

		typedef typename env::remote_record           remote_record;

		typedef typename env::history_type            history_type;

		typedef typename rpc::template incoming_call_handle<value_type,bool> get_handle_type;

		typedef typename rpc::template incoming_call_handle<bool,value_type> set_handle_type;

		static const command_id_type                  command_id = env::command_id;

		constexpr static remotes_type                &remotes = env::remotes;

		constexpr static history_type                &history = env::history;

		constexpr static std::mutex                  &remotes_lock = env::remotes_lock;

		constexpr static std::mutex                  &history_lock = env::history_lock;


		static void get_handler(get_handle_type h)
		{
			// TODO: find corresponding role and report the call
			if(h.reason == earpc::reason::process)
			{
				jrn(journal::trace) << "get from remote " << (std::string)h.ip << journal::end;
				history_lock.lock();
				value_type rv(history.empty() ? env::value : history.front().value);
				history_lock.unlock();
				h.respond(rv);
			}
		}

		static void set_handler(set_handle_type h)
		{
			// TODO: find corresponding role and report the call
			if(h.reason == earpc::reason::process)
			{
				history_lock.lock();
				env::value = h.value();
				history_lock.unlock();
				jrn(journal::trace) << "set from remote " << (std::string)h.ip << journal::end;
				h.respond(true);
				proc_commit::notify();
			}
		}

	public:
		constexpr static sched::listener &on_change = env::on_change;

		static void init(value_type v = value_type())
		{
			remotes.clear();
			history.clear();
			env::default_value = env::value = v;
			history.push_back(typename env::history_record(v));
			env::local_timestamp = history.back().time;
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
			jrn(journal::debug) << "initialized" << journal::end;
		}

		static void uninit()
		{
			rpc::clear_command(command_id | types::function::get);
			rpc::clear_command(command_id | types::function::set);
			remotes.clear();
			history.clear();
			proc_commit::uninit();
			proc_sync::uninit();
			jrn(journal::debug) << "uninitialied" << journal::end;
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
			jrn(journal::trace) << "get from API" << journal::end;
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
			jrn(journal::trace) << "set from API" << journal::end;
			proc_commit::notify();
			return v;
		}

		static value_type default_value()
		{ return env::default_value; }

		static bool remote_add(role_type &role)
		{
			remotes_lock.lock();
			remotes.push_back(remote_record(role));
			remotes_lock.unlock();
			jrn(journal::trace) << "added remote `" << (std::string)role.name << "'" << journal::end;
			role.on_bound += proc_sync::notify;
			role.on_unbound += proc_sync::cancel;
			proc_sync::notify(role);
			return true;
		}

		static bool remote_del(role_type &role)
		{
			remotes_lock.lock();
			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				if(*i == role)
				{
					proc_sync::cancel(i);
					remotes.erase(i);
					remotes_lock.unlock();
					role.on_bound -= proc_sync::notify;
					role.on_unbound -= proc_sync::cancel;
					jrn(journal::trace) << "deleted remote `" << (std::string)role.name << "'" << journal::end;
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
