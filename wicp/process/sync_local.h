#ifndef WICP_PROCESS_SYNC_LOCAL_H
# define WICP_PROCESS_SYNC_LOCAL_H
# include <journal.h>

namespace wicp {
namespace process
{
	template<typename TEnv>
	class sync_local
	{
		typedef typename TEnv::property_data_type	property_data_type;

		typedef typename TEnv::command_id_type		command_id_type;

		typedef typename TEnv::object_id_type		object_id_type;

		typedef typename TEnv::member_id			member_id;

		typedef typename TEnv::wic_class			wic_class;

		typedef typename wic_class::remote_iterator	remote_iterator;

		typedef typename TEnv::set_handle_type		set_handle_type;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.sync.local") << "property: " << std::hex <<
				TEnv::class_id << "::" << member_id::value << ' ';
		}

		static void call_finish(set_handle_type h)
		{
			const object_id_type arg_object_id = h.argument().object_id;
			const object_id_type ret_object_id = h.value();
			if(h.reason)
			{
				jrn(journal::error) << "; remote: " << (std::string)h.ip <<
					" error in call, restarting sync for object `" << arg_object_id << "'" << journal::end;
				notify(arg_object_id);
			}
			else
			{
				if(arg_object_id != ret_object_id)
				{
					jrn(journal::critical) << "; remote: " << (std::string)h.ip << " sync succeeded, but got invalid local `" << 
						wic_class::name << "' object reference `" << std::hex << ret_object_id << journal::end;
					return;
				}

				wic_class::lock_local();
				auto local_it = wic_class::find_local(arg_object_id);
				if(local_it != wic_class::end())
				{
					local_it->second.remotes.lock();
					wic_class::lock_remote();
					for(
						auto it = local_it->second.remotes.begin(); 
						it != local_it->second.remotes.end();
					)
					{
						auto remote_it = wic_class::find_remote(*it);
						if(remote_it != wic_class::end())
						{
							remote_it->second.property_lock.lock();
							auto &property = 
								remote_it->second.properties.template get<member_id>();
							if(property.call_id == h.call_id)
							{
								// TODO
								//i->role.report_call(h);
								jrn(journal::trace) << "; remote: " << (std::string)h.ip << " call_finished" << journal::end;
								TEnv::finish_sync_remote(property, h);
								remote_it->second.property_lock.unlock();
								wic_class::unlock_remote();
								local_it->second.remotes.unlock();
								wic_class::unlock_local();
								notify(arg_object_id);
								return;
							}
							remote_it->second.property_lock.unlock();
							++it;
						}
						else
						{
							it = local_it->second.remotes.erase(it);
							jrn(journal::debug) << "corrupted remote object `" << *it << "'" << journal::end;
						}
					}
					wic_class::unlock_remote();
					local_it->second.remotes.unlock();
					wic_class::unlock_local();
					jrn(journal::critical) << "; remote: " << (std::string)h.ip <<
						"could not find remote for finished change" << journal::end;
					notify(arg_object_id);
				}
				else
				{
					wic_class::unlock_local();			
					jrn(journal::error) << "Invalid local `" << 
						wic_class::name << "' object reference `" << std::hex << arg_object_id << journal::end;
				}
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

		static void notify(
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
					remote_it->second.property_lock.lock();
					auto &property = 
						remote_it->second.properties.template get<member_id>();
					if(property.history.empty())
					{
						jrn(journal::trace) << "nothing to do; suspending until next notify" << journal::end;
						remote_it->second.property_lock.unlock();
						wic_class::unlock_remote();
						wic_class::unlock_local();
						return;
					}
					jrn(journal::trace) << "remote: " << (std::string)remote_it->second.ip << " doing sync via object `" <<
						std::hex << remote_object_id << "'" << journal::end;

					TEnv::sync_remote(
						property, 
						local_object_id,
						remote_object_id,
						remote_it->second.ip, 
						types::function::notify, 
						call_finish
					);
					remote_it->second.property_lock.unlock();
					wic_class::unlock_remote();
					wic_class::unlock_local();
				}
				else
				{
					wic_class::unlock_remote();
					wic_class::unlock_local();
					jrn(journal::error) << "Invalid remote `" << wic_class::name << "' object reference `" << std::hex << remote_object_id << journal::end;
					return;
				}
			}
			else
			{
				wic_class::unlock_local();			
				jrn(journal::error) << "Invalid local `" << 
					wic_class::name << "' object reference `" << std::hex << local_object_id << journal::end;
			}	
		}

		static void notify(object_id_type object_id)
		{
			// TODO
			// wic_class::lock_local_and_process(
			// 	object_id, 
			// 	[](auto local_it)
			// 	{

			// 	}
			// );
			wic_class::lock_local();
			auto local_it = wic_class::find_local(object_id);
			if(local_it != wic_class::end())
			{
				local_it->second.property_lock.lock();
				auto &local_property = local_it->second.properties.template get<member_id>();
				if(local_property.history.empty())
				{
					local_it->second.property_lock.unlock();
					wic_class::unlock_local();
					jrn(journal::trace) << "nothing to do; suspending until next notify" << journal::end;
					return;
				}
				local_it->second.property_lock.unlock();
				local_it->second.remotes.lock();
				wic_class::lock_remote();
				for(
					auto it = local_it->second.remotes.begin(); 
					it != local_it->second.remotes.end();
				)
				{
					auto remote_it = wic_class::find_remote(*it);
					if(remote_it != wic_class::end())
					{
						jrn(journal::trace) << "; remote: " << (std::string)remote_it->second.ip << " doing sync via object `" <<
							std::hex << *it << "'" << journal::end;
						remote_it->second.property_lock.lock();
						auto &remote_property = 
							remote_it->second.properties.template get<member_id>();
						TEnv::sync_remote(
							remote_property, 
							local_property.history,
							*it,
							remote_it->second.ip, 
							types::function::notify, 
							call_finish
						); 
						remote_it->second.property_lock.unlock();
						++it;
					}
					else
					{
						it = local_it->second.remotes.erase(it);
						jrn(journal::debug) << "omitting sync via deleted object `" << std::hex << *it << "'" << journal::end;
					}
				}
				wic_class::unlock_remote();
				local_it->second.remotes.unlock();
				wic_class::unlock_local();
			}
			else
			{
				wic_class::unlock_local();
				jrn(journal::error) << "Invalid local `" << 
					wic_class::name << "' object reference `" << std::hex << object_id << journal::end;
			}
		}

		static void cancel(remote_iterator it)
		{
			if(it->second.remote.call_id)
			{
				jrn(journal::trace) << "remote: " << (std::string)it->second.ip << " cancelling sync via object `" <<
					std::hex << it->second.object_id << "'" << journal::end;

				TEnv::rpc::cancel(it->second.remote.call_id);
				it->second.remote.call_id = 0;
			}
		}

		static void cancel(
			object_id_type local_object_id, 
			object_id_type remote_object_id
		)
		{
			auto local_it = wic_class::find_local(local_object_id);
			if(local_it != wic_class::end())
			{
				wic_class::lock_remote();
				auto remote_it = wic_class::find_remote(remote_object_id);
				if(remote_it != wic_class::end())
				{
					cancel(remote_it);
					wic_class::unlock_remote();		
					return;
				}
				else
				{
					wic_class::unlock_remote();
					jrn(journal::error) << "Invalid remote `" << 
						wic_class::name << "' object reference `" << std::hex << remote_object_id << journal::end;
					return;
				}
			}
			else
				jrn(journal::error) << "Invalid local `" << 
					wic_class::name << "' object reference `" << std::hex << local_object_id << journal::end;
		}
	};
}}
#endif
