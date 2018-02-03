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

			static const uint32_t history_size = TConfig::cfg_history_size;
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

		typedef typename env::call_id_type            call_id_type;

		typedef typename env::command_id_type         command_id_type;

		typedef typename env::remote_record           remote_record;

		typedef typename env::history_record          history_record;

		typedef typename env::history_type            history_type;

		typedef typename env::get_handle_type         get_handle_type;

		typedef typename env::set_handle_type         set_handle_type;

		typedef typename env::notify_handle_type      notify_handle_type;

	public:
		typedef TConfig config;

		typedef typename env::value_type              value_type;

		constexpr static sched::listener &on_change = env::on_change;

		static const uint32_t history_size          = env::history_size;

	private:
		static const typename env::command_id_type   command_id = env::command_id;

		constexpr static history_type               &history = env::history;

		constexpr static std::mutex                 &history_lock = env::history_lock;

		constexpr static remote_record              &remote  = env::remote;

		static volatile bool initial_sync_pending;

		static volatile call_id_type  initial_sync_cid;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.property.remote") <<
				"remote: " << remote.role.name <<
				"; property: " << std::hex << env::class_id << "::" << env::member_id <<
				"; ";

		}

		static void notify_handler(notify_handle_type h)
		{
			remote.role.report_call(h);
			if(h.reason != earpc::reason::process)
			{
				jrn(journal::error) << "notify with reason " << std::dec << (int)h.reason << journal::end;
				h.respond(false);
				return;
			}

			const value_type v = h.value();
			if(env::value == v)
			{
				jrn(journal::warning) << "notify with no change" << journal::end;
				h.respond(true);
				return;
			}

			jrn(journal::trace) << "notify with new value" << journal::end;

			history_lock.lock();
			if(initial_sync_pending)
			{
				initial_sync_pending = false;
				rpc::cancel(initial_sync_cid);
				initial_sync_cid = 0;
				jrn(journal::trace) << "initial sync completed" << journal::end;
			}
			env::value = v;
			history.push_front(history_record(v));
			if(history.size() > history_size)
				history.pop_back();
			remote.sync_timestamp = history.front().time;
			history_lock.unlock();
			h.respond(true);
			proc_log::notify();
			env::sync_local();
		}

		static void do_initial_sync()
		{
			history_lock.lock();
			if(!initial_sync_pending)
			{
				history_lock.unlock();
				jrn(journal::trace) << "initial sync already completed" << journal::end;
				return;
				
			}

			if(!remote.role.is_bound())
			{
				history_lock.unlock();
				jrn(journal::trace) << "not doing initial sync via unbound role" << journal::end;
				return;
			}

			jrn(journal::trace) << "doing initial sync" << journal::end;

			initial_sync_cid = rpc::call(
				remote.role.get_ip(),
				command_id | types::function::get,
				true,
				get_handler
			);
			history_lock.unlock();
		
		}

		static void get_handler(get_handle_type h)
		{
			remote.role.report_call(h);
			if(h.reason != earpc::reason::success)
			{
				if(h.reason != earpc::reason::cancelled)
				{
					jrn(journal::error) << "initial sync failed with reason " <<
						std::dec << (int)h.reason << "; retrying" <<
						journal::end;
				}
				else
				{
					jrn(journal::warning) << "initial sync cancelled; retrying" <<
						journal::end;
				}

				do_initial_sync();
				return;
			}

			history_lock.lock();
			if(!initial_sync_pending)
			{
				history_lock.unlock();
				jrn(journal::trace) << "initial sync succeeded, but already completed via notify" << journal::end;
				return;
				
			}
			jrn(journal::debug) << "initial sync succeeded" <<
				journal::end;

			const value_type v = h.value();
			initial_sync_pending = false;
			env::value = v;

			history.push_front(history_record(v));

			if(history.size() > history_size)
				history.pop_back();

			remote.sync_timestamp = history.front().time;
			history_lock.unlock();
			proc_log::notify();
			env::sync_local();
		}

		static void bind_handler(role_type &role)
		{
			history_lock.lock();
			if(initial_sync_cid)
			{
				rpc::cancel(initial_sync_cid);
				initial_sync_cid = 0;
			}
			initial_sync_pending = true;
			history_lock.unlock();
			do_initial_sync();
		}

		static void unbind_handler(role_type &role)
		{
			history_lock.lock();
			if(initial_sync_pending)
			{
				rpc::cancel(initial_sync_cid);
				initial_sync_cid = 0;
			}
			history_lock.unlock();
			proc_sync::cancel();
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
			initial_sync_pending = true;

			proc_log::init();
			proc_commit::init();
			proc_sync::init();

			remote.role.on_bound += bind_handler;
			remote.role.on_unbound += unbind_handler;

			rpc::set_command(
				command_id | types::function::notify,
				notify_handler
			);
			do_initial_sync();
			jrn(journal::debug) << "initialized" << journal::end;
		}

		static void uninit()
		{
			remote.role.on_bound -= bind_handler;
			remote.role.on_unbound -= unbind_handler;

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
			if(initial_sync_pending)
			{
				initial_sync_pending = false;
				const auto cid = initial_sync_cid;
				initial_sync_cid = 0;
				rpc::cancel(cid);
			}
			proc_commit::notify();
			return env::value;
		}

		static void clear_history()
		{
			history_lock.lock();
			history.clear();
			history_lock.unlock();
		}
	};

	template<typename e>
	typename remote_property<e>::env::base::remote_record remote_property<e>::env::remote;

	template<typename e>
	volatile bool remote_property<e>::initial_sync_pending;

	template<typename e>
	volatile typename remote_property<e>::call_id_type remote_property<e>::initial_sync_cid;

}
#endif
