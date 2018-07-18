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

			typedef typename TConfig::cfg_wic_class			wic_class;

			typedef typename wic_class::local_object_record_type encap_object_type;
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

		typedef typename env::member_id member_id;		

		typedef typename process::commit<env_commit>	proc_commit;

		typedef typename env_commit::proc_sync			proc_sync;

		typedef typename env::rpc						rpc;

		typedef typename env::command_id_type			command_id_type;

	public:
		typedef typename env::value_type				value_type;

		typedef typename env::object_id_type			object_id_type;

	private:
		typedef typename env::remotes_type				remotes_type;

		typedef typename env::remote_record				remote_record;

		typedef typename env::history_type				history_type;

		typedef typename rpc::template incoming_call_handle<value_type,bool> get_handle_type;

		typedef typename rpc::template incoming_call_handle<bool,value_type> set_handle_type;

		static const command_id_type				command_id = env::command_id;

		constexpr static remotes_type				&remotes = env::remotes;

		constexpr static history_type				&history = env::history;

		constexpr static std::mutex					&remotes_lock = env::remotes_lock;

		constexpr static std::mutex					&history_lock = env::history_lock;


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
				// TODO Getting obj id for notify?
				proc_commit::notify(12);
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
				jrn(journal::trace) << "set from API" << journal::end;
				proc_commit::notify(object_id);
				return v;
			}
			jrn(journal::error) << "Invalid local `" << 
				wic_class::name << "' object reference `" << std::hex << object_id << journal::end;
			wic_class::unlock_local();
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
						wic_class::name << "' object reference" << std::hex << remote_object_id<< "'" << journal::end;
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
					wic_class::name << "' object reference" << std::hex << remote_object_id<< "'" << journal::end;
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

		// TODO clear all object history vs get object_id in arg
		static void clear_history()
		{
			history_lock.lock();
			history.clear();
			history_lock.unlock();
		}

	};

	template<typename c>
	typename local_property<c>::env::remotes_type local_property<c>::env::remotes;

	template<typename c>
	std::mutex local_property<c>::env::remotes_lock;
}
#endif
