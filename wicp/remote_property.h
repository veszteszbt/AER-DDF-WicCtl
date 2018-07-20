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
			
			typedef void (*change_handler_type)();

			static change_handler_type change_handler;

			typedef typename TConfig::cfg_wic_class			wic_class;

			typedef typename wic_class::remote_object_record_type	encap_object_type;

			typedef typename TConfig::cfg_property_data_type		property_data_type;

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

		typedef typename env::wic_class            wic_class;
		
		typedef typename env::call_id_type            call_id_type;

		typedef typename env::command_id_type         command_id_type;

		typedef typename env::object_id_type         object_id_type;

		typedef typename env::property_data_type	property_data_type;

		typedef typename env::history_record          history_record;

		typedef typename env::history_type            history_type;

		typedef typename env::get_handle_type         get_handle_type;

		typedef typename env::set_handle_type         set_handle_type;

		typedef typename env::notify_handle_type      notify_handle_type;

		typedef typename env::member_id      member_id;

	public:
		typedef TConfig config;

		typedef typename env::value_type			value_type;

		static const uint32_t history_size          = env::history_size;

	private:
		static const typename env::command_id_type   command_id = env::command_id;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.property.remote") <<
				"; property: " << std::hex << env::class_id << "::" << env::member_id::value <<
				"; ";

		}

		static void notify_handler(notify_handle_type h)
		{
			// TODO remote.role.report_call(h);
			if(h.reason != earpc::reason::process)
			{
				jrn(journal::error) << "notify with reason " << std::dec << (int)h.reason << journal::end;
				h.respond(object_id_type());
				return;
			}

			const property_data_type property_data = h.value();
			const object_id_type object_id = property_data.object_id;

			wic_class::lock_remote();
			auto it = wic_class::find_remote(object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				auto &property = it->second.properties.template get<member_id>();

				if(property.local_value == property_data.value)
				{
					jrn(journal::warning) << "notify with no change" << journal::end;
					h.respond(object_id);
					return;
				}
				jrn(journal::trace) << "notify with new value" << journal::end;

				if(it->second.initial_sync_pending)
				{
					it->second.initial_sync_pending = false;
					rpc::cancel(it->second.initial_sync_cid);
					it->second.initial_sync_cid = 0;
					jrn(journal::trace) << "initial sync completed" << journal::end;
				}
				// TODO unlock for a little time period, can it cause any problem?
				property.local_value = property_data.value;

				property.history.push_front(property_data.value);
				if(property.history.size() > history_size)
					property.history.pop_back();

				property.sync_timestamp = property.history.front().time;
				it->second.property_lock.unlock();
				wic_class::unlock_remote();
				h.respond(object_id);
				proc_log::notify(object_id);
				env::sync_local(object_id);
			}
			else
			{
				wic_class::unlock_remote();
				// TODO should we respond ? h.respond(property_data_type());
				jrn(journal::error) << "Invalid remote `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << journal::end;
			}
		}

		static void do_initial_sync(object_id_type object_id)
		{
			wic_class::lock_remote();
			auto it = wic_class::find_remote(object_id);
			if(it != wic_class::end())
			{
				if(!it->second.initial_sync_pending)
				{
					jrn(journal::trace) << "initial sync already completed" << journal::end;
					return;
				}				
				jrn(journal::trace) << "doing initial sync" << journal::end;
				it->second.initial_sync_cid = rpc::call(
					it->second.ip,
					command_id | types::function::get,
					object_id,
					get_handler
				);
				wic_class::unlock_remote();
			}
			else
			{
				wic_class::unlock_remote();
				jrn(journal::error) << "Invalid remote `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << journal::end;
			}
		}

		static void get_handler(get_handle_type h)
		{
			const property_data_type property_data = h.value();
			const object_id_type arg_object_id = h.argument();
			//TODO remote.role.report_call(h);
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
				do_initial_sync(arg_object_id);
				return;
			}
			if(arg_object_id != property_data.object_id)
			{
				jrn(journal::critical) << "; remote: " << (std::string)h.ip << " initial sync succeeded, but got invalid remote `" << 
					wic_class::name << "' object reference `" << std::hex << property_data.object_id << journal::end;
				return;
			}

			wic_class::lock_remote();
			auto it = wic_class::find_remote(arg_object_id);
			if(it != wic_class::end())
			{
				if(!it->second.initial_sync_pending)
				{
					jrn(journal::trace) << "initial sync succeeded, but already completed via notify" << journal::end;
					return;
				}
				jrn(journal::debug) << "initial sync succeeded" << journal::end;
				it->second.property_lock.lock();
				auto &property = it->second.properties.template get<member_id>();
				property.local_value = property_data.value;
				property.history.push_front(history_record(property_data.value));
				if(property.history.size() > history_size)
					property.history.pop_back();

				property.sync_timestamp = property.history.front().time;
				proc_log::notify(arg_object_id);
				env::sync_local(arg_object_id);

				it->second.property_lock.unlock();
				it->second.initial_sync_pending = false;
				wic_class::unlock_remote();
			}
			else
			{
				wic_class::unlock_remote();
				jrn(journal::error) << "Invalid remote `" << 
					wic_class::name << "' object reference `" << std::hex << arg_object_id << journal::end;
			}			
		}

		// static void bind_handler(role_type &role)
		// {
		// 	history_lock.lock();
		// 	if(initial_sync_cid)
		// 	{
		// 		rpc::cancel(initial_sync_cid);
		// 		initial_sync_cid = 0;
		// 	}
		// 	initial_sync_pending = true;
		// 	history_lock.unlock();
		// 	do_initial_sync();
		// }

		// static void unbind_handler(role_type &role)
		// {
		// 	history_lock.lock();
		// 	if(initial_sync_pending)
		// 	{
		// 		rpc::cancel(initial_sync_cid);
		// 		initial_sync_cid = 0;
		// 	}
		// 	history_lock.unlock();
		// 	proc_sync::cancel();
		// }

	public:
		static void init(object_id_type object_id, value_type v = value_type())
		{
			// new(&env::remote) remote_record(role);
			// env::value = env::default_value = v;
			// history.push_back(history_record(v));
			// env::local_timestamp = env::remote.sync_timestamp = history.back().time;
			// env::remote.pending_timestamp = clock::time_point::min();
			// initial_sync_pending = true;

			proc_log::init();
			proc_commit::init();
			proc_sync::init();

			// remote.role.on_bound += bind_handler;
			// remote.role.on_unbound += unbind_handler;

			rpc::set_command(
				command_id | types::function::notify,
				notify_handler
			);
			do_initial_sync(object_id);
			jrn(journal::debug) << "initialized" << journal::end;
		}

		static void uninit()
		{
			// remote.role.on_bound -= bind_handler;
			// remote.role.on_unbound -= unbind_handler;

			proc_commit::uninit();
			proc_sync::uninit();
			proc_log::uninit();
			rpc::clear_command(command_id | types::function::notify);
			jrn(journal::debug) << "uninitialized" << journal::end;
		}

		static value_type default_value()
		{ return env::default_value; }

		static value_type value(object_id_type object_id)
		{ 
			wic_class::lock_remote();
			auto it = wic_class::find_remote(object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				const value_type value = it->second.properties.template get<member_id>().local_value;
				it->second.property_lock.unlock();
				wic_class::unlock_remote();
				return value;
			}
			else
			{
				wic_class::unlock_remote();
				jrn(journal::error) << "Invalid remote `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << journal::end;
				return property_data_type(); 
			}
		}

		static uint32_t failures()
		{ return env::remote::failures; }

		static typename clock::duration latency()
		{ return env::remote::latency; }

		static value_type value(
			object_id_type object_id, 
			value_type pvalue
		)
		{
			wic_class::lock_remote();
			auto it = wic_class::find_remote(object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				auto &property = it->second.properties.template get<member_id>();
				if(pvalue == property.local_value)
					return pvalue;

				jrn(journal::trace) << "value set via API" << journal::end;
				const value_type value = property.local_value = pvalue;
				const call_id_type cid = it->second.initial_sync_cid;
				if(it->second.initial_sync_pending)
				{
					it->second.initial_sync_pending = false;
					it->second.initial_sync_cid = 0;
					rpc::cancel(cid);
				}
				proc_commit::notify(cid);
				it->second.property_lock.unlock();
				wic_class::unlock_remote();
				return value;
			}
			else
			{
				wic_class::unlock_remote();
				jrn(journal::error) << "Invalid remote `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << journal::end;
				return value_type();
			}
		}

		static void clear_history(object_id_type object_id)
		{
			wic_class::lock_remote();
			auto it = wic_class::find_remote(object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				auto &property = it->second.properties.template get<member_id>();
				property.history.clear();
				it->second.property_lock.unlock();
				wic_class::unlock_remote();
			}
			else
			{
				wic_class::unlock_remote();
				jrn(journal::error) << "Invalid remote `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << journal::end;
			}
		}
	};

}
#endif
