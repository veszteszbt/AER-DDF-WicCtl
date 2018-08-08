#ifndef OOSP_LOCAL_PROPERTY_H
# define OOSP_LOCAL_PROPERTY_H
# include <oosp/types.h>
# include <oosp/property_env_base.h>
# include <oosp/process/sync_local.h>
# include <oosp/process/commit.h>
# include <oosp/process/log.h>
namespace oosp
{
	template<typename TConfig>
	class local_property
	{
		struct env : public property_env_base<TConfig>
		{
			typedef property_env_base<TConfig> base;

			typedef typename TConfig::cfg_oosp_class				oosp_class;

			typedef typename oosp_class::local_object_record_type	encap_object_type;

			typedef typename TConfig::cfg_property_data_type		property_data_type;
		};

		struct env_commit : public env
		{
			typedef typename process::sync_local<env>		proc_sync;

			typedef typename process::log<env>				proc_log;
		};

		typedef typename env::oosp_class					oosp_class;

		typedef typename env::member_id 					member_id;

		typedef typename env_commit::proc_sync				proc_sync;

		typedef typename env::rpc							rpc;
		
		typedef typename env::sync_record					sync_record;

		typedef typename env::command_id_type				command_id_type;

		typedef typename oosp_class::local_table_iterator	local_table_iterator;

		typedef typename oosp_class::remote_table_iterator	remote_table_iterator;

		typedef typename oosp_class::clock					clock;

		typedef typename process::commit<env_commit>		proc_commit;

		friend oosp_class;

	public:
		typedef typename env::value_type					value_type;

		typedef typename env::object_id_type				object_id_type;

	private:

		typedef typename env::property_data_type 			property_data_type;

		typedef typename rpc::template incoming_call_handle<
			property_data_type,
			object_id_type
		> 													get_handle_type;

		typedef typename rpc::template incoming_call_handle<
			object_id_type,
			property_data_type
		> 													set_handle_type;

		friend oosp_class;

		static const command_id_type 			command_id 	= env::command_id;

		static journal jrn(uint8_t level)
		{
			return journal(level,"oosp.property.local") << "property: " << std::hex <<
				env::class_id << "::" << env::member_id::value << ' ';
		}

		static journal jrn(uint8_t level, object_id_type object)
		{
			return journal(level,"oosp.property.local") << std::hex <<
				"object:  " << object <<
				"; class: " << oosp_class::name <<
				"; property: " <<
				" (" << env::class_id << "::" << env::member_id::value << "); ";
			;
		}

		static void get_handler(get_handle_type h)
		{
			// TODO: find corresponding role and report the call
			if(h.reason != earpc::reason::process)
			{
				jrn(journal::error) <<
					"`" << oosp_class::name << "' get called with other reason than process " <<
					journal::end;
				h.respond(property_data_type(0,0));
				return;
			}

			const object_id_type object_id = h.value();
			oosp_class::lock_local();
			auto local_it = oosp_class::find_local(object_id);
			if(oosp_class::unknown_local_object(local_it, jrn))
			{
				h.respond(property_data_type(0,0));
				return;
			}

			const property_data_type rv = safe_create_response_value_and_cancel_call(local_it, h.ip);

			oosp_class::unlock_local();
			jrn(journal::trace) <<
				"get from remote: " << (std::string)h.ip <<
				"; object: " << std::hex << object_id <<
				journal::end;
			h.respond(rv);
		}

		static property_data_type safe_create_response_value_and_cancel_call(
			local_table_iterator &local_it, 
			net::ipv4_address ip
		)
		{
			local_it->second.property_lock.lock();

			auto &property = local_it->second.properties.template get<member_id>();
			const property_data_type rv(
				local_it->first,
				property.history.empty() ?
				property.sync.local_value :
				property.history.front().value
			);

			cancel_call(property.sync, local_it->first, ip);

			local_it->second.property_lock.unlock();
			return rv;
		}

		static void cancel_call(sync_record &sync, object_id_type object_id, net::ipv4_address ip)
		{
			if(sync.call_id)
			{
				jrn(journal::trace) <<
					"remote: " << (std::string)ip <<
					" cancelling sync via object " << std::hex << object_id <<
					journal::end;
				rpc::cancel(sync.call_id);
				sync.call_id = 0;
				sync.pending_timestamp = env::clock::time_point::min();
			}
		}

		static void set_handler(set_handle_type h)
		{
			// TODO: find corresponding role and report the call
			if(h.reason != earpc::reason::process)
			{
				jrn(journal::error) <<
					"`" << oosp_class::name << "' Set called with other reason than process " <<
					journal::end;
				h.respond(object_id_type(0));
				return;
			}

			const property_data_type property_data = h.value();
			const object_id_type object_id = property_data.object_id;
			oosp_class::lock_local();
			auto local_it = oosp_class::find_local(object_id);
			if(oosp_class::unknown_local_object(local_it, jrn))
			{
				h.respond(object_id_type(0));
				return;
			}
			
			safe_set_property_local_value(local_it, property_data.value);

			oosp_class::unlock_local();
			jrn(journal::trace) <<
				"set from remote: " << (std::string)h.ip <<
				"; object: " << std::hex << object_id <<
				journal::end;
			h.respond(object_id);
			proc_commit::notify(object_id);
		}

		static void safe_set_property_local_value(local_table_iterator &local_it, value_type value)
		{
			local_it->second.property_lock.lock();
			auto &property = local_it->second.properties.template get<member_id>();
			property.sync.local_value = value;
			local_it->second.property_lock.unlock();
		}

		static void cancel(
			local_table_iterator &local_it,
			object_id_type remote_object_id
		)
		{
			auto &local = local_it->second;
			local.remotes.lock();

			auto device = local.remotes.find(remote_object_id);
			if(oosp_class::local_has_no_remote(device, remote_object_id, local))
				return;

			local.remotes.unlock();
			oosp_class::lock_remote();

			auto remote_it = oosp_class::find_remote(remote_object_id);
			if(oosp_class::unknown_remote_object(remote_it, jrn))
				return;

			cancel(remote_it);

			oosp_class::unlock_remote();
		}

		static void cancel(remote_table_iterator &it)
		{
			it->second.property_lock.lock();

			auto &property = it->second.properties.template get<member_id>();
			if(property.sync.call_id)
			{
				it->second.property_lock.unlock();
				jrn(journal::trace) <<
					"remote: " << (std::string)it->second.ip <<
					" cancelling sync via object " << std::hex << it->second.object_id <<
					journal::end;

				rpc::cancel(property.sync.call_id);
				property.sync.call_id = 0;
				property.sync.pending_timestamp = clock::time_point::min();
			}
			else
			{
				it->second.property_lock.unlock();
				jrn(journal::error, it->second.object_id) <<
					"ommiting cancel; call has not been made" <<
					journal::end;
			}
		}

		static void init(
			object_id_type object_id,
			value_type value = value_type()
		)
		{
			auto local_it = oosp_class::find_local(object_id);
			if(local_it == oosp_class::end())
			{
				jrn(journal::error) <<
					"Invalid local `" << oosp_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return;
			}

			local_it->second.remotes.lock();
			local_it->second.remotes.clear();
			local_it->second.remotes.unlock();

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

		static void uninit(object_id_type object_id)
		{
			auto local_it = oosp_class::find_local(object_id);
			if(local_it == oosp_class::end())
			{
				jrn(journal::error) <<
					"Invalid local `" << oosp_class::name <<
					"' object reference " << std::hex << object_id <<
					journal::end;
				return;
			}

			local_it->second.remotes.lock();
			local_it->second.remotes.clear();
			local_it->second.remotes.unlock();
			local_it->second.property_lock.lock();
			
			auto &property = local_it->second.properties.template get<member_id>();
			property.history.clear();

			local_it->second.property_lock.unlock();
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

		static void uninit()
		{
			rpc::clear_command(command_id | types::function::get);
			rpc::clear_command(command_id | types::function::set);
			proc_commit::uninit();
			proc_sync::uninit();
			jrn(journal::debug) << "uninitialied" << journal::end;
		}

		static value_type value(object_id_type object_id)
		{
			oosp_class::lock_local();
			auto local_it = oosp_class::find_local(object_id);
			if(oosp_class::unknown_local_object(local_it, jrn))
				return value_type(0);

			local_it->second.property_lock.lock();

			auto &property = local_it->second.properties.template get<member_id>();
			if(property.history.empty())
			{
				const value_type rv = property.sync.local_value;
				local_it->second.property_lock.unlock();
				oosp_class::unlock_local();
				jrn(journal::trace) <<
					"object: " << std::hex << object_id <<
					"; get from API history is empty; returning local value" <<
					journal::end;
				return rv;
			}

			const value_type rv = property.history.front().value;

			local_it->second.property_lock.unlock();
			oosp_class::unlock_local();
			jrn(journal::trace) <<
				"object: " << std::hex << object_id <<
				"; get from API" <<
				journal::end;
			return rv;
		}

		static value_type value(object_id_type object_id, value_type pvalue)
		{
			oosp_class::lock_local();
			auto local_it = oosp_class::find_local(object_id);
			if(oosp_class::unknown_local_object(local_it, jrn))
				return value_type(0);

			local_it->second.property_lock.lock();

			auto &property = local_it->second.properties.template get<member_id>();
			if(env::local_value_match_given_value(property.sync.local_value, pvalue, local_it))
			{
				jrn(journal::debug) <<
					"object: " << std::hex << object_id <<
					"; set from API with no change" <<
					journal::end;
				return pvalue;
			}

			property.sync.local_value = pvalue;
			
			local_it->second.property_lock.unlock();
			oosp_class::unlock_local();
			jrn(journal::trace) <<
				"object: " << std::hex << object_id <<
				"; set from API" <<
				journal::end;

			proc_commit::notify(object_id);
			return pvalue;
		}

		static value_type default_value(object_id_type object_id)
		{
			oosp_class::lock_local();

			auto local_it = oosp_class::find_local(object_id);
			if(oosp_class::unknown_local_object(local_it, jrn))
				return value_type(0);

			local_it->second.property_lock.lock();
			
			auto &property = local_it->second.properties.template get<member_id>();
			const value_type default_value = property.sync.default_value;

			local_it->second.property_lock.unlock();
			oosp_class::unlock_local();
			jrn(journal::trace, object_id) <<
				"default value get from API" <<
				journal::end;
			return default_value;
		}

		static void clear_history(object_id_type object_id)
		{
			oosp_class::lock_local();

			auto local_it = oosp_class::find_local(object_id);
			if(oosp_class::unknown_local_object(local_it, jrn))
				return;

			local_it->second.property_lock.lock();
			
			auto &property = local_it->second.properties.template get<member_id>();
			property.history.clear();

			local_it->second.property_lock.unlock();
			oosp_class::unlock_local();
			jrn(journal::trace, object_id) <<
				"history cleared" <<
				journal::end;
		}

		static bool is_sync_pending(object_id_type object_id)
		{ return env::template is_sync_pending<typename env::encap_object_type>(object_id); }

		// TODO delete this
		static void subscribe_to_change(object_id_type object_id, void (*change_handler)(object_id_type object_id))
		{
			oosp_class::lock_local();
			auto it = oosp_class::find_local(object_id);
			if(it != oosp_class::end())
			{
				it->second.property_lock.lock();
				it->second.properties.template get<member_id>().on_change += change_handler;
				it->second.property_lock.unlock();
			}
			oosp_class::unlock_local();
		}
	};
}
#endif
