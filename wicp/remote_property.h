#ifndef WICP_REMOTE_PROPERTY_H
# define WICP_REMOTE_PROPERTY_H
# include <wicp/property_env_base.h>
# include <wicp/process/sync_remote.h>
# include <wicp/process/commit.h>
# include <wicp/process/log.h>
# include <sched/listener.h>
namespace wicp
{
	template<typename TConfig>
	class remote_property
	{
		struct env : public property_env_base<TConfig>
		{
			typedef property_env_base<TConfig>  base;
			
			static typename base::remote_record remote;

			typedef void (*change_handler_type)();

			static change_handler_type change_handler;
		};

		struct env_commit : public env
		{
			typedef typename process::sync_remote<env> proc_sync;
			typedef typename process::log<env>         proc_log;
		};

		typedef typename process::commit<env_commit>  proc_commit;

		typedef typename env_commit::proc_sync        proc_sync;

		typedef typename env_commit::proc_log         proc_log;

		typedef typename env::clock                   clock;

		typedef typename env::rpc                     rpc;

		typedef typename env::command_id_type         command_id_type;

		typedef typename env::remote_record           remote_record;

		typedef typename env::history_record          history_record;

		typedef typename env::history_type            history_type;

	public:
		typedef TConfig config;

		typedef typename env::value_type              value_type;

		constexpr static sched::listener &on_change = env::on_change;

	private:
		typedef typename env::rpc::template incoming_call_handle<bool,value_type>  notify_call_handle_type;

		static const typename env::command_id_type   command_id = env::command_id;

		constexpr static history_type               &history = env::history;

		constexpr static std::mutex                 &history_lock = env::history_lock;

		constexpr static remote_record              &remote  = env::remote;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.property.remote") << "property: " << std::hex <<
				env::class_id << "::" << env::member_id << ' ';
		}

		static void notify_handler(notify_call_handle_type h)
		{
			if(h.reason != earpc::reason::process)
			{
				jrn(journal::error) << "notify from remote " << (std::string)h.ip << " with reason " << std::dec << (int)h.reason << journal::end;
				h.respond(false);
				return;
			}

			if(h.ip != remote.ip)
			{
				jrn(journal::debug) << "notify from remote with new address: " << (std::string)remote.ip << " -> " << (std::string) << h.ip << journal::end;
				history_lock.lock();
				remote.ip = h.ip;
				history_lock.unlock();
				role.notify_ip_change(h.ip);
			}

			const value_type v = h.value();
			if(env::value == v)
			{
				jrn(journal::warning) << "notify from remote " << (std::string)h.ip << " with no change" << journal::end;
				h.respond(true);
				return;
			}

			jrn(journal::trace) << "new value on remote " << (std::string)h.ip << journal::end;

			history_lock.lock();
			env::value = v;
			history.push_front(history_record(v));
			if(history.size() > 16)
				history.pop_back();
			remote.sync_timestamp = history.front().time;
			history_lock.unlock();
			h.respond(true);
			proc_log::notify();
			env::sync_local();
		}

	public:
		static void init(role_type &role, value_type v = value_type())
		{
			history.clear();
			new(&env::remote) remote_record(role);
			env::value = env::default_value = v;
			history.push_back(history_record(v));
			env::local_timestamp = env::remote.sync_timestamp = history.back().time;
			env::remote.pending_timestamp = clock::time_point::min();

			proc_log::init();
			proc_commit::init();
			proc_sync::init();

			role.on_bound += proc_sync::bind;
			role.on_unbound += proc_sync::unbind;

			rpc::set_command(
				command_id | types::function::notify,
				notify_handler
			);
			jrn(journal::debug) << "initialized" << journal::end;
		}

		static void uninit()
		{
			remote.role.on_bound -= proc_sync::bind;
			remote.role.on_unbound -= proc_sync::unbind;

			proc_commit::uninit();
			proc_sync::uninit();
			proc_log::uninit();
			rpc::clear_command(command_id | types::function::notify);
			jrn(journal::debug) << "uninitialized" << journal::end;
		}

		static value_type default_value()
		{ return env::default_value; }

		static value_type value()
		{ return env::value; }

		static uint32_t failures()
		{ return env::remote::failures; }

		static typename clock::duration latency()
		{ return env::remote::latency; }

		static value_type value(value_type v)
		{
			if(v == env::value)
				return v;
			jrn(journal::trace) << "value set via API" << journal::end;
			env::value = v;
			proc_commit::notify();
			return env::value;
		}
	};

	template<typename e>
	typename remote_property<e>::env::base::remote_record remote_property<e>::env::remote;
}
#endif
