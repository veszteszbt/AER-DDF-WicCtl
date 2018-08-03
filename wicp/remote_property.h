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

			static change_handler_type 								change_handler;

			typedef typename TConfig::cfg_wic_class					wic_class;

			typedef typename wic_class::remote_object_record_type	encap_object_type;

			typedef typename TConfig::cfg_property_data_type		property_data_type;

			static const uint32_t history_size = TConfig::cfg_history_size;
		};

		struct env_commit : public env
		{
			typedef typename process::sync_remote<env> proc_sync;
			typedef typename process::log<env>         proc_log;
		};

		typedef typename process::commit<env_commit>	proc_commit;

		typedef typename env_commit::proc_sync			proc_sync;

		typedef typename env_commit::proc_log			proc_log;

		typedef typename env::clock						clock;

		typedef typename env::rpc						rpc;

		typedef typename env::wic_class					wic_class;

		typedef typename env::call_id_type				call_id_type;

		typedef typename env::command_id_type			command_id_type;

		typedef typename env::object_id_type			object_id_type;

		typedef typename env::property_data_type		property_data_type;

		typedef typename env::history_record			history_record;

		typedef typename env::history_type				history_type;

		typedef typename env::get_handle_type			get_handle_type;

		typedef typename env::set_handle_type			set_handle_type;

		typedef typename env::notify_handle_type		notify_handle_type;

		typedef typename env::member_id					member_id;

		typedef typename wic_class::remote_iterator		remote_iterator;

	public:
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

		static journal jrn(uint8_t level, object_id_type object)
		{
			return journal(level,"wicp.property.remote") << std::hex <<
				"object:  " << object <<
				"; class: " << wic_class::name <<
				"; property: " <<
				" (" << env::class_id << "::" << member_id::value << "); ";
			;
		}

		static void notify_handler(notify_handle_type h)
		{
			const property_data_type property_data = h.value();
			const object_id_type object_id = property_data.object_id;
			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(object_id);
			if(remote_it == wic_class::end())
			{
				wic_class::unlock_remote();
				h.respond(object_id_type(0));
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference `" << std::hex << object_id <<
					journal::end;
				return;
			}

			remote_it->second.report_call(h);
			if(h.reason != earpc::reason::process)
			{
				wic_class::unlock_remote();
				jrn(journal::error) <<
					"object: " << std::hex << object_id <<
					"; notify with reason " << std::dec << (int)h.reason <<
					journal::end;
				h.respond(object_id_type(0));
				return;
			}

			remote_it->second.property_lock.lock();
			auto &property = remote_it->second.properties.template get<member_id>();
			if(property.sync.local_value == property_data.value)
			{
				remote_it->second.property_lock.unlock();
				wic_class::unlock_remote();
				jrn(journal::warning) <<
					"object: " << std::hex << object_id <<
					"; notify with no change" <<
					journal::end;
				h.respond(object_id);
				return;
			}

			jrn(journal::trace) <<
				"object: " << std::hex << object_id <<
				"; notify with new value " << std::dec << int(property_data.value) <<
				journal::end;

			if(property.initial_sync_pending)
			{
				property.initial_sync_pending = false;
				rpc::cancel(property.initial_sync_cid);
				property.initial_sync_cid = 0;
				jrn(journal::trace) <<
					"object: " << std::hex << object_id <<
					"; initial sync completed with call: " << std::hex << h.call_id <<
					journal::end;
			}

			property.sync.local_value = property_data.value;
			property.history.emplace_front(property_data.value);
			if(property.history.size() > history_size)
				property.history.pop_back();

			property.sync.timestamp = property.history.front().time;
			h.respond(object_id);
			if(env::sync_local(property))
			{
				remote_it->second.property_lock.unlock();
				wic_class::unlock_remote();
				property.on_change(object_id);
			}
			else
			{
				remote_it->second.property_lock.unlock();
				wic_class::unlock_remote();
			}
			proc_log::notify(object_id);
		}

		static void get_handler(get_handle_type h)
		{
			const object_id_type arg_object_id = h.argument();
			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(arg_object_id);
			if(remote_it == wic_class::end())
			{
				wic_class::unlock_remote();
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference `" << std::hex << arg_object_id <<
					journal::end;
				return;
			}

			remote_it->second.report_call(h);
			if(h.reason != earpc::reason::success)
			{
				if(h.reason != earpc::reason::cancelled)
				{
					jrn(journal::error) <<
						"object: " << std::hex << arg_object_id <<
						"; initial sync failed with reason " << std::dec << (int)h.reason <<
						"; retrying" <<
						journal::end;
				}
				else
				{
					jrn(journal::warning) <<
						"object: " << std::hex << arg_object_id <<
						"; initial sync cancelled with call: " << std::hex << h.call_id << " retrying" <<
						journal::end;
				}
				do_initial_sync(remote_it);
				wic_class::unlock_remote();
				return;
			}

			const property_data_type property_data = h.value();
			if(arg_object_id != property_data.object_id)
			{
				jrn(journal::critical) <<
					"remote: " << (std::string)h.ip <<
					"; initial sync succeeded with call: " << std::hex << h.call_id <<
					"; but got invalid remote `" << wic_class::name <<
					"' object reference `" << std::hex << property_data.object_id <<
					journal::end;
				return;
			}

			remote_it->second.property_lock.lock();
			auto &property = remote_it->second.properties.template get<member_id>();
			if(!property.initial_sync_pending)
			{
				remote_it->second.property_lock.unlock();
				wic_class::unlock_remote();
				jrn(journal::trace) <<
					"initial sync succeeded with call: " << std::hex << h.call_id <<
					"; but already completed via notify" <<
					journal::end;
				return;
			}

			jrn(journal::debug) <<
				"object: " << std::hex << arg_object_id <<
				"; initial sync succeeded with call: " << std::hex << h.call_id <<
				journal::end;

			property.initial_sync_pending = false;
			property.sync.local_value = property_data.value;

			property.history.emplace_front(property_data.value);
			if(property.history.size() > history_size)
				property.history.pop_back();

			property.sync.timestamp = property.history.front().time;
			if(env::sync_local(property))
			{
				remote_it->second.property_lock.unlock();
				wic_class::unlock_remote();
				property.on_change(arg_object_id);
			}
			else
			{
				remote_it->second.property_lock.unlock();
				wic_class::unlock_remote();
			}
			proc_log::notify(arg_object_id);
		}

		static void do_initial_sync(remote_iterator remote_it)
		{
			remote_it->second.property_lock.lock();
			auto &property = remote_it->second.properties.template get<member_id>();
			if(!property.initial_sync_pending)
			{
				remote_it->second.property_lock.unlock();
				jrn(journal::trace) <<
					"object: " << std::hex << remote_it->first <<
					"; initial sync already completed" <<
					journal::end;
				return;
			}

			jrn(journal::trace) <<
				"object: " << std::hex << remote_it->first <<
				"; doing initial sync" <<
				journal::end;

			property.initial_sync_cid = rpc::call(
				remote_it->second.ip,
				command_id | types::function::get,
				remote_it->first,
				get_handler
			);
			remote_it->second.property_lock.unlock();
		}
	public:

		static void init()
		{
			proc_log::init();
			proc_commit::init();
			proc_sync::init();

			rpc::set_command(
				command_id | types::function::notify,
				notify_handler
			);
			jrn(journal::debug) << "initialized" << journal::end;
		}

		static void init(object_id_type object_id, value_type pvalue = value_type())
		{
			// TODO tell me what is this new(&env::remote) remote_record(role);
			auto remote_it = wic_class::find_remote(object_id);
			if(remote_it == wic_class::end())
			{
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return;
			}

			remote_it->second.property_lock.lock();
			auto &property = remote_it->second.properties.template get<member_id>();

			property.sync.local_value = property.sync.default_value = pvalue;
			property.history.emplace_back(pvalue);
			property.local_timestamp = property.sync.timestamp = property.history.back().time;
			property.sync.pending_timestamp = clock::time_point::min();
			property.initial_sync_pending = true;

			remote_it->second.property_lock.unlock();

			// remote.role.on_bound += bind_handler;
			// remote.role.on_unbound += unbind_handler;
			do_initial_sync(remote_it);
			jrn(journal::debug) <<
				"remote object: " << std::hex << object_id <<
				"; initialized" <<
				journal::end;
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

		static void uninit(object_id_type object_id)
		{
			// remote.role.on_bound -= bind_handler;
			// remote.role.on_unbound -= unbind_handler;

			jrn(journal::debug) << "uninitialized" << journal::end;
		}

		static value_type value(object_id_type object_id)
		{
			auto remote_it = wic_class::find_remote(object_id);
			if(remote_it == wic_class::end())
			{
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return value_type(0);
			}

			remote_it->second.property_lock.lock();
			const value_type value = remote_it->second.properties.template get<member_id>().sync.local_value;
			remote_it->second.property_lock.unlock();
			jrn(journal::trace, object_id) <<
				"get from API " <<
				journal::end;
			return value;
		}

		static value_type value(
			object_id_type object_id,
			value_type pvalue
		)
		{
			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(object_id);
			if(remote_it == wic_class::end())
			{
				wic_class::unlock_remote();
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return value_type(0);
			}

			remote_it->second.property_lock.lock();
			auto &property = remote_it->second.properties.template get<member_id>();
			if(pvalue == property.sync.local_value)
			{
				remote_it->second.property_lock.unlock();
				wic_class::unlock_remote();
				jrn(journal::debug, object_id) <<
					"set from API with no change " <<
					journal::end;

				return pvalue;
			}

			jrn(journal::trace) <<
				"object: " << std::hex << object_id <<
				"; value set via API" <<
				journal::end;
			const value_type value = property.sync.local_value = pvalue;
			if(property.initial_sync_pending)
			{
				property.initial_sync_pending = false;
				const call_id_type cid = property.initial_sync_cid;
				property.initial_sync_cid = 0;
				rpc::cancel(cid);
			}

			remote_it->second.property_lock.unlock();
			wic_class::unlock_remote();
			proc_commit::notify(object_id);
			return value;
		}

		static value_type default_value(object_id_type object_id)
		{
			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(object_id);
			if(remote_it == wic_class::end())
			{
				wic_class::unlock_remote();
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return value_type(0);
			}

			remote_it->second.property_lock.lock();
			auto &property = remote_it->second.properties.template get<member_id>();
			const value_type default_value = property.sync.default_value;
			remote_it->property_lock.unlock();
			wic_class::unlock_remote();
			jrn(journal::trace, object_id) <<
				"default value get from API" <<
				journal::end;

			return default_value;
		}

		static uint32_t failures(object_id_type object_id)
		{
			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(object_id);
			if(remote_it == wic_class::end())
			{
				wic_class::unlock_remote();
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return uint32_t(0);
			}

			remote_it->second.property_lock.lock();
			const uint32_t failures = remote_it->second.properties.template get<member_id>().failures;
			remote_it->second.property_lock.unlock();
			wic_class::unlock_remote();
			jrn(journal::trace, object_id) <<
				"failures get from API" <<
				journal::end;

			return failures;
		}

		static typename clock::duration latency(object_id_type object_id)
		{
			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(object_id);
			if(remote_it == wic_class::end())
			{
				wic_class::unlock_remote();
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return clock::duration(0);
			}

			remote_it->second.property_lock.lock();
			const auto latency = remote_it->second.properties.template get<member_id>().latency;
			remote_it->second.property_lock.unlock();
			wic_class::unlock_remote();
			jrn(journal::trace, object_id) <<
				"latency get from API" <<
				journal::end;


			return latency;
		}

		static void clear_history(object_id_type object_id)
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

			remote_it->second.property_lock.lock();
			auto &property = remote_it->second.properties.template get<member_id>();
			property.history.clear();
			remote_it->second.property_lock.unlock();
			wic_class::unlock_remote();
		}

		static void subscribe_to_change(
			object_id_type object_id,
			void (*change_handler)(object_id_type object_id)
		)
		{
			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(object_id);
			if(remote_it != wic_class::end())
			{
				remote_it->second.property_lock.lock();
				remote_it->second.properties.template get<member_id>().on_change += change_handler;
				remote_it->second.property_lock.unlock();
			}
			wic_class::unlock_remote();
		}
	};
}
#endif
