#ifndef WICP_PROCESS_SYNC_REMOTE_H
# define WICP_PROCESS_SYNC_REMOTE_H
# include <journal.h>
# include <wicp/types.h>
namespace wicp {
namespace process
{
	template<typename TEnv>
	class sync_remote
	{
		typedef typename TEnv::clock				clock;

		typedef typename TEnv::command_id_type		command_id_type;

		typedef typename TEnv::value_type			value_type;

		typedef typename TEnv::history_type			history_type;

		typedef typename TEnv::set_handle_type		set_handle_type;

		typedef typename TEnv::wic_class			wic_class;

		typedef typename TEnv::object_id_type		object_id_type;

		typedef typename TEnv::member_id			member_id;

		typedef typename TEnv::property_data_type	property_data_type;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.sync.remote") << "property: " << std::hex <<
				TEnv::class_id << "::" << member_id::value << ' ';
		}

		static void call_finish(set_handle_type h)
		{
			const object_id_type arg_object_id = h.argument().object_id;
			const object_id_type ret_object_id = h.value();

			wic_class::lock_remote();
			auto it = wic_class::find_remote(arg_object_id);
			if(it != wic_class::end())
			{
				it->second.report_call(h);
				it->second.property_lock.lock();
				auto &property = it->second.properties.template get<member_id>();
				if(h.reason)
				{
					++property.sync.failures;
					jrn(journal::error) << "; remote: " << (std::string)h.ip << " sync failed" << journal::end;
				}
				else
				{
					if(arg_object_id != ret_object_id)
					{
						it->second.property_lock.unlock();
						wic_class::unlock_remote();
						jrn(journal::critical) << "; remote: " << (std::string)h.ip << " sync succeeded, but got invalid remote `" << 
							wic_class::name << "' object reference `" << std::hex << ret_object_id << journal::end;
						return;
					}
					jrn(journal::trace) << "; remote: " << (std::string)h.ip << " sync succeeded" << journal::end;
				}
				TEnv::finish_sync_remote(property.sync, h);
				it->second.property_lock.unlock();
				wic_class::unlock_remote();
				notify(arg_object_id);
			}
			else
			{
				wic_class::unlock_remote();
				jrn(journal::error) << "Invalid remote `" << 
					wic_class::name << "' object reference `" << std::hex << arg_object_id << journal::end;
			}
		}

	public:
		static void init()
		{
			jrn(journal::debug) << "initialized" << journal::end;
		}

		static void uninit()
		{
			jrn(journal::debug) << "uninitialized" << journal::end;
		}

		static void notify(object_id_type object_id)
		{
			wic_class::lock_remote();
			auto it = wic_class::find_remote(object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				auto &property = it->second.properties.template get<member_id>();
				if(property.history.empty())
				{
					it->second.property_lock.unlock();					
					wic_class::unlock_remote();
					jrn(journal::trace) << "nothing to do; suspending until next notify" << journal::end;
					return;
				}
				jrn(journal::trace) << "; remote: " << (std::string)it->second.ip << " doing sync" << journal::end;
				TEnv::sync_remote(property, object_id, it->second.ip, types::function::set, call_finish);
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

		// TODO calling this, i think the time is when we delete a remote at remote_del
		static void cancel(object_id_type object_id)
		{
			wic_class::lock_remote();
			auto it = wic_class::find_remote(object_id);
			if(it != wic_class::end())
			{
				it->second.property_lock.lock();
				auto &property = it->second.properties.template get<member_id>();
				if(property.call_id)
				{
					jrn(journal::debug) << "cancelling sync" << journal::end;
					TEnv::rpc::cancel(property.call_id);
					property.call_id = 0;
				}
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
}}
#endif
