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

		typedef typename env::command_id_type				command_id_type;

		typedef typename oosp_class::local_table_iterator	local_table_iterator;

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

			local_it->second.property_lock.lock();
			auto &property = local_it->second.properties.template get<member_id>();
			const property_data_type rv(
				object_id,
				property.history.empty() ?
				property.sync.local_value :
				property.history.front().value
			);
			jrn(journal::trace) <<
				"remote: " << (std::string)h.ip <<
				" cancelling sync via object " << std::hex << object_id <<
				journal::end;
			// TODO if statement wasn't here
			if(property.sync.call_id)
			{
				rpc::cancel(property.sync.call_id);
				property.sync.call_id = 0;
				property.sync.pending_timestamp = env::clock::time_point::min();
			}

			local_it->second.property_lock.unlock();
			oosp_class::unlock_local();
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

	public:

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
			auto local_it = oosp_class::find_local(object_id);
			if(local_it == oosp_class::end())
			{
				jrn(journal::error) <<
					"Invalid local `" << oosp_class::name <<
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
			oosp_class::lock_local();
			auto local_it = oosp_class::find_local(object_id);
			if(oosp_class::unknown_local_object(local_it))
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
			if(oosp_class::unknown_local_object(local_it))
				return value_type(0);

			local_it->second.property_lock.lock();

			auto &property = local_it->second.properties.template get<member_id>();
			if(local_value_match_given_value(property.sync.local_value, pvalue, local_it))
				return pvalue;

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

	private:
		static bool local_value_match_given_value(
			value_type local_value, 
			value_type value, 
			local_table_iterator &local_it
		)
		{
			if(local_value == value)
			{
				local_it->second.property_lock.unlock();
				oosp_class::unlock_local();
				jrn(journal::debug) <<
					"object: " << std::hex << local_it->first <<
					"; set from API with no change" <<
					journal::end;
				return true;
			}		
			return false;
		}
	public:

		static value_type default_value(object_id_type object_id)
		{
			oosp_class::lock_local();

			auto local_it = oosp_class::find_local(object_id);
			if(oosp_class::unknown_local_object(local_it))
				return value_type(0);

			local_it->second.property_lock.lock();
			
			auto &property = local_it->second.properties.template get<member_id>();
			const value_type default_value = property.sync.default_value;

			local_it->property_lock.unlock();
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
			if(oosp_class::unknown_local_object(local_it))
				return;

			local_it->second.property_lock.lock();
			
			auto &property = local_it->second.properties.template get<member_id>();
			property.history.clear();

			local_it->property_lock.unlock();
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
