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

			typedef typename TConfig::cfg_wic_class			wic_class;

			typedef typename wic_class::local_object_record_type	encap_object_type;

			typedef typename TConfig::cfg_property_data_type		property_data_type;
		};

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.property.local") << "property: " << std::hex <<
				env::class_id << "::" << env::member_id::value << ' ';
		}


		struct env_commit : public env
		{
			typedef typename process::sync_local<env>	proc_sync;
			typedef typename process::log<env>			proc_log;
		};

		typedef typename env::wic_class 	wic_class;

		typedef typename wic_class::local_iterator local_iterator;

		typedef typename env::member_id member_id;		

		typedef typename process::commit<env_commit>	proc_commit;

		typedef typename env_commit::proc_sync			proc_sync;

		typedef typename env::rpc						rpc;

		typedef typename env::command_id_type			command_id_type;

	public:
		typedef typename env::value_type				value_type;

		typedef typename env::object_id_type			object_id_type;

	private:

		typedef typename env::property_data_type 		property_data_type;

		typedef typename rpc::template incoming_call_handle<property_data_type, object_id_type> get_handle_type;

		typedef typename rpc::template incoming_call_handle<object_id_type, property_data_type> set_handle_type;

		static const command_id_type				command_id = env::command_id;

		static void get_handler(get_handle_type h)
		{
			// TODO: find corresponding role and report the call
			if(h.reason == earpc::reason::process)
			{
				const object_id_type object_id = h.value();
				wic_class::lock_local();			
				auto local_it = wic_class::find_local(object_id);
				if(local_it != wic_class::end())
				{
					local_it->second.property_lock.lock();
					auto &property = local_it->second.properties.template get<member_id>();
					property_data_type rv({object_id, property.history.empty() ? property.local_value : property.history.front().value});
					local_it->second.property_lock.unlock();
					wic_class::unlock_local();
					jrn(journal::trace) << "get from remote " << (std::string)h.ip << journal::end;
					h.respond(rv);
				}
				else
				{
					wic_class::unlock_local();			
					jrn(journal::critical) << "Invalid local `" << 
						wic_class::name << "' object reference `" << std::hex << object_id << "'" << journal::end;
				}	
			}
		}

		static void set_handler(set_handle_type h)
		{
			// TODO: find corresponding role and report the call
			if(h.reason == earpc::reason::process)
			{
				const property_data_type property_data = h.value();
				const object_id_type object_id = property_data.object_id;
				wic_class::lock_local();			
				auto local_it = wic_class::find_local(object_id);
				if(local_it != wic_class::end())
				{
					local_it->second.property_lock.lock();
					auto &property = local_it->second.properties.template get<member_id>();
					property.local_value = property_data.value;
					local_it->second.property_lock.unlock();
					wic_class::unlock_local();
					jrn(journal::trace) << "set from remote " << (std::string)h.ip << journal::end;
					h.respond(object_id);
					proc_commit::notify(object_id);
				}
				else
				{
					wic_class::unlock_local();			
					jrn(journal::critical) << "Invalid local `" << 
						wic_class::name << "' object reference `" << std::hex << object_id << "'" << journal::end;
				}	
			}
		}

	public:
		constexpr static sched::listener &on_change = env::on_change;

		static void init()
		{
// ///////////////
// 			auto local_it = wic_class::find_local(12);
// 			auto &property = local_it->second.properties.template get<member_id>();;
// 			property.history.push_back(typename env::history_record({12, 8}));
// 			property.local_value = {34, 8};
// ///////////////
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

		void init(
			object_id_type object_id,
			value_type value = value_type()
		)
		{
			wic_class::lock_local();			
			auto local_it = wic_class::find_local(object_id);
			if(local_it != wic_class::end())
			{
				local_it->second.remotes.clear();
				local_it->second.property_lock.lock();
				auto &property = local_it->second.properties.template get<member_id>();
				property.history.clear();

				property.history.push_back(typename env::history_record(value));
				env::default_value = property.local_value = value;

				property.local_timestamp = property.history.back().time;
				local_it->property_lock.unlock();
				wic_class::unlock_local();
			}
			else
			{
				wic_class::unlock_local();			
				jrn(journal::error) << "Invalid local `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << "'" << journal::end;
			}
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
			wic_class::lock_local();			
			auto local_it = wic_class::find_local(object_id);
			if(local_it != wic_class::end())
			{
				local_it->second.remotes.clear();
				local_it->second.property_lock.lock();
				auto &property = local_it->second.properties.template get<member_id>();
				property.history.clear();
				local_it->second.property_lock.unlock();
				wic_class::unlock_local();
			}
			else
			{
				wic_class::unlock_local();			
				jrn(journal::error) << "Invalid local `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << "'" << journal::end;
			}	
		}

		static value_type value(object_id_type object_id)
		{
			wic_class::lock_local();			
			auto local_it = wic_class::find_local(object_id);
			if(local_it != wic_class::end())
			{
				local_it->second.property_lock.lock();
				auto &property = local_it->second.properties.template get<member_id>();
				if(property.history.empty())
				{
					value_type rv = property.local_value;
					local_it->property_lock.unlock();
					wic_class::unlock_local();					
					return rv;
				}
				value_type rv = property.history.front().value;
				local_it->property_lock.unlock();
				wic_class::unlock_local();
				jrn(journal::trace) << "get from API" << journal::end;
				return rv;
			}
			else
			{
				wic_class::unlock_local();			
				jrn(journal::error) << "Invalid local `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << "'" << journal::end;

				return value_type();
			}	
		}

		static value_type value(object_id_type object_id, value_type v)
		{
			wic_class::lock_local();
			auto it = wic_class::find_local(object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				auto &property = it->second.properties.template get<member_id>();
				if(property.local_value == v)
				{
					it->second.property_lock.unlock();
					wic_class::unlock_local();
					return v;
				}
				property.local_value = v;
				it->second.property_lock.unlock();
				wic_class::unlock_local();
				jrn(journal::trace) << "set from API" << journal::end;
				proc_commit::notify(object_id);
				return v;
			}
			wic_class::unlock_local();
			jrn(journal::error) << "Invalid local `" << 
				wic_class::name << "' object reference `" << std::hex << object_id << "'" << journal::end;
		}

		static value_type default_value()
		{ return env::default_value; }

		static bool remote_add(
			object_id_type local_object_id,
			object_id_type remote_object_id
		)
		{
			wic_class::lock_local();
			auto local_it = wic_class::find_local(local_object_id);
			if(local_it != wic_class::end())
			{
				wic_class::lock_remote();
				auto remote_it = wic_class::find_remote(remote_object_id);
				if(remote_it != wic_class::end())
				{
					local_it->second.remotes.lock();
					local_it->second.remotes.emplace(remote_object_id);
					local_it->second.remotes.unlock();
					wic_class::unlock_remote();		
					wic_class::unlock_local();
					
					jrn(journal::trace) << "added remote `" << 
						wic_class::name << "' object reference `" << std::hex << remote_object_id<< "'" << journal::end;
					proc_sync::notify(local_object_id, remote_object_id);
					return true;
				}
				else
				{
					wic_class::unlock_remote();
					wic_class::unlock_local();
					jrn(journal::error) << "Invalid remote `" << 
						wic_class::name << "' object reference `" << std::hex << remote_object_id << journal::end;
					return false;
				}
			}
			else
			{
				wic_class::unlock_local();
				jrn(journal::error) << "Invalid local `" << 
					wic_class::name << "' object reference `" << std::hex << local_object_id << journal::end;
				return false;
			}
		}

		static bool remote_del(
			object_id_type local_object_id,
			object_id_type remote_object_id
		)
		{
			wic_class::lock_local();			
			auto local_it = wic_class::find_local(local_object_id);
			if(local_it != wic_class::end())
			{
				proc_sync::cancel(local_object_id, remote_object_id);
				local_it->remotes.lock();
				if(!local_it->remotes.erase(remote_object_id))
				{
					jrn(journal::error) << "Invalid remote `" << 
						wic_class::name << "' object reference `" << std::hex << remote_object_id << journal::end;
					local_it->remotes.unlock();
					wic_class::unlock_local();			

					return false;
				}
				local_it->remotes.unlock();
				wic_class::unlock_local();
				jrn(journal::trace) << "deleted remote `" << 
					wic_class::name << "' object reference `" << std::hex << remote_object_id<< "'" << journal::end;
				return true;
			}
			else
			{
				wic_class::unlock_local();			
				jrn(journal::error) << "Invalid local `" << 
					wic_class::name << "' object reference `" << std::hex << local_object_id << journal::end;
				return false;
			}
		}

		static void clear_history(object_id_type object_id)
		{
			wic_class::lock_local();			
			auto local_it = wic_class::find_local(object_id);
			if(local_it != wic_class::end())
			{
				local_it->second.property_lock.lock();
				auto &property = local_it->second.properties.template get<member_id>();
				property.history.clear();
				local_it->property_lock.unlock();
				wic_class::unlock_local();
			}
			else
			{
				wic_class::unlock_local();			
				jrn(journal::error) << "Invalid local `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << "'" << journal::end;
			}
		}
	};
}
#endif
