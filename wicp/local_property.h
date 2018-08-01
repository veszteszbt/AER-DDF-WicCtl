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
	struct local_property
	{
		typedef TConfig config;

		typedef void (*change_handler_type)();
	private:

		struct env : public property_env_base<TConfig>
		{
			typedef property_env_base<TConfig> base;

			typedef typename TConfig::cfg_wic_class					wic_class;

			typedef typename wic_class::local_object_record_type	encap_object_type;

			typedef typename TConfig::cfg_property_data_type		property_data_type;
		};

		struct env_commit : public env
		{
			typedef typename process::sync_local<env>	proc_sync;
			typedef typename process::log<env>			proc_log;
		};

		typedef typename env::wic_class					wic_class;

		typedef typename env::member_id 				member_id;

		typedef typename env_commit::proc_sync			proc_sync;

		typedef typename env::rpc						rpc;

		typedef typename env::command_id_type			command_id_type;

		typedef typename wic_class::clock				clock;

		typedef typename wic_class::local_iterator		local_iterator;

		typedef typename process::commit<env_commit>	proc_commit;

	public:
		typedef typename env::value_type				value_type;

		typedef typename env::object_id_type			object_id_type;

	private:

		typedef typename env::property_data_type 		property_data_type;

		typedef typename rpc::template incoming_call_handle<
			property_data_type,
			object_id_type
		> 												get_handle_type;

		typedef typename rpc::template incoming_call_handle<
			object_id_type,
			property_data_type
		> 												set_handle_type;

		static const command_id_type command_id 		= env::command_id;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.property.local") << "property: " << std::hex <<
				env::class_id << "::" << env::member_id::value << ' ';
		}

		static void get_handler(get_handle_type h)
		{
			// TODO: find corresponding role and report the call
			if(h.reason != earpc::reason::process)
				return;

			const object_id_type object_id = h.value();
			wic_class::lock_local();
			auto local_it = wic_class::find_local(object_id);
			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::critical) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				h.respond(property_data_type(0,0));
				return;
			}

			local_it->second.property_lock.lock();
			auto &property = local_it->second.properties.template get<member_id>();
			property_data_type rv(
				object_id,
				property.history.empty() ?
				property.sync.local_value :
				property.history.front().value
			);
			jrn(journal::trace) <<
				"remote: " << (std::string)h.ip <<
				" cancelling sync via object " << std::hex << object_id <<
				journal::end;

			rpc::cancel(property.sync.call_id);
			property.sync.call_id = 0;
			property.sync.pending_timestamp = env::clock::time_point::min();

			local_it->second.property_lock.unlock();
			wic_class::unlock_local();
			jrn(journal::trace) <<
				"get from remote: " << (std::string)h.ip <<
				"; object: " << std::hex << object_id <<
				journal::end;
			h.respond(rv);
		}

		static void set_handler(set_handle_type h)
		{
			// TODO: find corresponding role and report the call
			if(h.reason != earpc::reason::process)
				return;

			const property_data_type property_data = h.value();
			const object_id_type object_id = property_data.object_id;
			wic_class::lock_local();
			auto local_it = wic_class::find_local(object_id);
			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::critical) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				h.respond(object_id_type(0));
				return;
			}

			local_it->second.property_lock.lock();
			auto &property = local_it->second.properties.template get<member_id>();
			property.sync.local_value = property_data.value;

			local_it->second.property_lock.unlock();
			wic_class::unlock_local();
			jrn(journal::trace) <<
				"set from remote: " << (std::string)h.ip <<
				"; object: " << std::hex << object_id <<
				journal::end;
			h.respond(object_id);
			proc_commit::notify(object_id);
		}
	public:

		static void init()
		{
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

		static void init(
			object_id_type object_id,
			value_type value = value_type()
		)
		{
			auto local_it = wic_class::find_local(object_id);
			if(local_it == wic_class::end())
			{
				jrn(journal::error) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return;
			}

			local_it->second.remotes.clear();
			local_it->second.property_lock.lock();
			auto &property = local_it->second.properties.template get<member_id>();
			property.history.clear();

			property.history.push_back(typename env::history_record(value));
			property.sync.default_value = property.sync.local_value = value;

			property.local_timestamp = property.history.back().time;
			local_it->second.property_lock.unlock();
			jrn(journal::debug) <<
				"local object: " << std::hex << object_id <<
				"; initialized" <<
				journal::end;
		}

		static void uninit()
		{
			rpc::clear_command(command_id | types::function::get);
			rpc::clear_command(command_id | types::function::set);
			proc_commit::uninit();
			proc_sync::uninit();
			jrn(journal::debug) << "uninitialied" << journal::end;
		}

		void uninit(object_id_type object_id)
		{
			auto local_it = wic_class::find_local(object_id);
			if(local_it == wic_class::end())
			{
				jrn(journal::error) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return;
			}

			local_it->second.remotes.clear();
			local_it->second.property_lock.lock();
			auto &property = local_it->second.properties.template get<member_id>();
			property.history.clear();
			local_it->second.property_lock.unlock();
		}

		static value_type value(object_id_type object_id)
		{
			wic_class::lock_local();
			auto local_it = wic_class::find_local(object_id);
			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::error) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;

				return value_type(0);
			}

			local_it->second.property_lock.lock();
			auto &property = local_it->second.properties.template get<member_id>();
			if(property.history.empty())
			{
				const value_type rv = property.sync.local_value;
				local_it->second.property_lock.unlock();
				wic_class::unlock_local();
				jrn(journal::trace) <<
					"object: " << std::hex << object_id <<
					"; get from API history is empty; returning local value" <<
					journal::end;
				return rv;
			}

			const value_type rv = property.history.front().value;
			local_it->second.property_lock.unlock();
			wic_class::unlock_local();
			jrn(journal::trace) <<
				"object: " << std::hex << object_id <<
				"; get from API" <<
				journal::end;
			return rv;
		}

		static value_type value(object_id_type object_id, value_type pvalue)
		{
			wic_class::lock_local();
			auto it = wic_class::find_local(object_id);
			if(it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::error) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return value_type(0);
			}

			it->second.property_lock.lock();
			auto &property = it->second.properties.template get<member_id>();
			if(property.sync.local_value == pvalue)
			{
				it->second.property_lock.unlock();
				wic_class::unlock_local();
				jrn(journal::debug) <<
					"object: " << std::hex << object_id <<
					"; set from API with no change" <<
					journal::end;
				return pvalue;
			}

			property.sync.local_value = pvalue;
			it->second.property_lock.unlock();
			wic_class::unlock_local();
			jrn(journal::trace) <<
				"object: " << std::hex << object_id <<
				"; set from API" <<
				journal::end;

			proc_commit::notify(object_id);
			return pvalue;
		}

		static value_type default_value(object_id_type object_id)
		{
			wic_class::lock_local();
			auto local_it = wic_class::find_local(object_id);
			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::error) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return value_type(0);
			}

			local_it->second.property_lock.lock();
			auto &property = local_it->second.properties.template get<member_id>();
			const value_type default_value = property.sync.default_value;
			local_it->property_lock.unlock();
			wic_class::unlock_local();
			jrn(journal::trace, object_id) <<
				"default value get from API" <<
				journal::end;
			return default_value;
		}

		static bool remote_add(
			object_id_type local_object_id,
			object_id_type remote_object_id
		)
		{
			wic_class::lock_local();
			auto local_it = wic_class::find_local(local_object_id);
			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::error) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << local_object_id <<
					journal::end;
				return false;
			}

			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(remote_object_id);
			if(remote_it == wic_class::end())
			{
				wic_class::unlock_remote();
				wic_class::unlock_local();
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference " << std::hex << remote_object_id <<
					journal::end;
				return false;
			}

			local_it->second.remotes.lock();
			local_it->second.remotes.try_emplace(remote_object_id);
			local_it->second.remotes.unlock();

			wic_class::unlock_remote();
			wic_class::unlock_local();

			jrn(journal::trace) <<
				"object: " << std::hex << local_object_id << "; added remote `" << wic_class::name <<
				"' object reference " << remote_object_id <<
				journal::end;

			proc_sync::notify(local_object_id, remote_object_id);
			return true;
		}

		static bool remote_del(
			object_id_type local_object_id,
			object_id_type remote_object_id
		)
		{
			wic_class::lock_local();
			auto local_it = wic_class::find_local(local_object_id);
			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::error) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << local_object_id <<
					journal::end;
				return false;
			}

			proc_sync::cancel(local_object_id, remote_object_id);
			local_it->remotes.lock();
			if(!local_it->remotes.erase(remote_object_id))
			{
				local_it->remotes.unlock();
				wic_class::unlock_local();
				jrn(journal::error) <<
					"Invalid remote `" << wic_class::name <<
					"' object reference " << std::hex << remote_object_id <<
					journal::end;

				return false;
			}

			local_it->remotes.unlock();
			wic_class::unlock_local();
			jrn(journal::trace) <<
				"object: " << std::hex << local_object_id << "; deleted remote `" << wic_class::name <<
				"' object reference " << std::hex << remote_object_id <<
				journal::end;
			return true;
		}

		static void clear_history(object_id_type object_id)
		{
			wic_class::lock_local();
			auto local_it = wic_class::find_local(object_id);
			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::error) <<
					"Invalid local `" << wic_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return;
			}

			local_it->second.property_lock.lock();
			auto &property = local_it->second.properties.template get<member_id>();
			property.history.clear();
			local_it->property_lock.unlock();
			jrn(journal::trace, object_id) <<
				"history cleared" <<
				journal::end;

			wic_class::unlock_local();
		}

		static void subscribe_to_change(object_id_type object_id, void (*change_handler)(object_id_type object_id))
		{
			wic_class::lock_local();
			auto it = wic_class::find_local(object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				it->second.properties.template get<member_id>().on_change += change_handler;
				it->second.property_lock.unlock();
			}
			wic_class::unlock_local();
		}
	};
}
#endif
