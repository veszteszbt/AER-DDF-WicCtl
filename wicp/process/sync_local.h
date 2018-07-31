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

		typedef typename TEnv::call_id_type             call_id_type;

		typedef typename TEnv::object_id_type		object_id_type;

		typedef typename TEnv::member_id		member_id;

		typedef typename TEnv::wic_class		wic_class;

		typedef typename TEnv::wic_class		device_wic_class;

		typedef typename wic_class::remote_iterator	remote_iterator;

		typedef typename TEnv::set_handle_type		set_handle_type;

		typedef typename wic_class::local_object_record_type              local_object_record;

		typedef typename wic_class::remote_object_record_type             remote_object_record;

		typedef typename local_object_record::remote_property_sync_record sync_record;


		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.sync.local") << std::hex << 
				"class: " << wic_class::name <<
				"; property: " <<
				" (" << TEnv::class_id << "::" << member_id::value << "); ";
		}

		static journal jrn(uint8_t level, object_id_type object)
		{
			return journal(level,"wicp.sync.local") << std::hex <<
				"object:  " << object <<
				"; class: " << wic_class::name <<
				"; property: " <<
				" (" << TEnv::class_id << "::" << member_id::value << "); ";
			;
		}

		static std::pair<sync_record*,remote_object_record*>
		find_sync(
			local_object_record &local,
			call_id_type call_id
		)
		{
			for(auto i = local.remotes.begin(); i != local.remotes.end(); ++i)
			{
				auto &sync = i->second.template get<member_id>();
				if(sync.call_id == call_id)
				{
					auto device = wic_class::find_remote(i->first);

					if(device == wic_class::end())
					{
						jrn(journal::error,local.object_id) << 
							"Invalid remote `" << wic_class::name << 
							"' object reference; erasing endpoint" << 
							journal::end;

						i = local.remotes.erase(i);
						return std::make_pair<sync_record*,remote_object_record*>(nullptr,nullptr);
					}
					return std::make_pair(&sync,&device->second);
				}
			}
			return std::make_pair<sync_record*,remote_object_record*>(nullptr,nullptr);
		}

		static void call_finish(set_handle_type h)
		{
			const object_id_type arg_object_id = h.argument().object_id;

			wic_class::lock_local();

			auto local_it = wic_class::find_local(arg_object_id);

			if(local_it == wic_class::end())
			{
				wic_class::unlock_local();
				jrn(journal::error,arg_object_id) << 
					"Invalid local `" << wic_class::name << 
					"' object reference" << 
					journal::end;
				return;
			}

			auto &local = local_it->second;

			local.remotes.lock();
			wic_class::lock_remote();

			auto sync_it = find_sync(local,h.call_id);
			if(!sync_it.first || !sync_it.second)
			{
				wic_class::unlock_remote();
				local.remotes.unlock();
				wic_class::unlock_local();
				jrn(journal::critical,arg_object_id) <<
					"remote: " << (std::string)h.ip << std::hex <<
					"; could not find a valid remote for finished sync call " << h.call_id <<
					journal::end;

				notify(arg_object_id);
				return;
			}

			TEnv::finish_sync_remote(*sync_it.first, h);
			sync_it.second->report_call(h);

			if(h.reason)
			{
				wic_class::unlock_remote();
				local.remotes.unlock();
				wic_class::unlock_local();

				jrn(journal::error,arg_object_id) << 
					"remote: " << (std::string)h.ip <<
					"; error in call, restarting sync for object " << std::hex << arg_object_id << 
					journal::end;
				notify(arg_object_id);
				return;
			}
			
			const object_id_type ret_object_id = h.value();
			if(arg_object_id != ret_object_id)
			{
				wic_class::unlock_remote();
				local.remotes.unlock();
				wic_class::unlock_local();

				jrn(journal::error,arg_object_id) << 
					"; remote: " << (std::string)h.ip << 
					"; sync returned mismatching `" << 
					wic_class::name << "' object reference " << std::hex << ret_object_id <<
					"; considering failed" <<
					journal::end;
				notify(arg_object_id);
				return;
			}


			jrn(journal::trace,arg_object_id) <<
				"remote: " << std::hex << sync_it.second->object_id << " (" << (std::string)h.ip << ")"
				"; sync call finished" << 
				journal::end;

			wic_class::unlock_remote();
			local.remotes.unlock();
			wic_class::unlock_local();

			notify(arg_object_id);
		}
	public:
		static void init()
		{ jrn(journal::debug) << "initialized" << journal::end; }

		static void uninit()
		{ jrn(journal::debug) << "uninitialized" << journal::end; }

		static void notify(
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
				return;
			}

			auto &local = local_it->second;

			local.property_lock.lock();

			auto &local_property = 
				local.properties.template get<member_id>();
			if(local_property.history.empty())
			{
				jrn(journal::trace) << 
					"object: " << std::hex << local_object_id << 
					"; nothing to do; suspending until next notify" << 
					journal::end;
				local.property_lock.unlock();
				wic_class::unlock_local();
				return;
			}
			
			local.property_lock.unlock();

			local.remotes.lock();
			auto device = local.remotes.find(remote_object_id);
			if(device == local.remotes.end())
			{
				local.remotes.unlock();
				wic_class::unlock_local();
				jrn(journal::error) <<
					"local object " << std::hex << local_object_id <<
					" has no remote object with id " << remote_object_id <<
					journal::end;
				return;
			}
			
			wic_class::lock_remote();
			auto remote_it = wic_class::find_remote(remote_object_id);
			if(remote_it == wic_class::end())
			{
				wic_class::unlock_remote();
				local.remotes.unlock();
				wic_class::unlock_local();
				jrn(journal::error) << 
					"Invalid remote `" << wic_class::name << 
					"' object reference " << std::hex << remote_object_id << 
					journal::end;
				return;
			}
			
			auto &sync = device->second.template get<member_id>();
			jrn(journal::trace) << 
				"object: " << std::hex << local_object_id <<
				"; remote: " << (std::string)remote_it->second.ip <<
				" doing sync via device " << remote_object_id << 
				journal::end;

			TEnv::sync_remote(
				sync, 
				local_property.history,
				local_object_id,
				remote_it->second.ip, 
				::wicp::types::function::notify, 
				call_finish
			);
			local.remotes.unlock();
			wic_class::unlock_remote();
			wic_class::unlock_local();
		}

		static void notify(object_id_type object_id)
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
			auto &local_property = local_it->second.properties.template get<member_id>();
			if(local_property.history.empty())
			{
				local_it->second.property_lock.unlock();
				wic_class::unlock_local();
				jrn(journal::trace) << 
					"object: " << std::hex << object_id << 
					"; nothing to do suspending until next notify" << 
					journal::end;
				return;
			}

			local_it->second.remotes.lock();
			wic_class::lock_remote();
			for(
				auto device = local_it->second.remotes.begin(); 
				device != local_it->second.remotes.end();
			)
			{
				auto remote_it = wic_class::find_remote(device->first);
				if(remote_it != wic_class::end())
				{
					remote_it->second.property_lock.lock();
					auto &remote_property = remote_it->second.properties.template get<member_id>();
					// TODO
					if(local_property.local_value == remote_property.local_value)
					{
						remote_it->second.property_lock.unlock();
						jrn(journal::trace,object_id) << 
							"remote: " << (std::string)remote_it->second.ip << 
							"; skipping sync for the source of the data, device: " << 
							std::hex << device->first << 
							journal::end;

						continue;
					}
					remote_it->second.property_lock.unlock();

					jrn(journal::trace,object_id) << 
						"remote: " << (std::string)remote_it->second.ip << 
						"; doing sync via device: " << std::hex << device->first << 
						journal::end;

					TEnv::sync_remote(
						device->second.template get<member_id>(),
						local_property.history,
						object_id,
						remote_it->second.ip, 
						::wicp::types::function::notify, 
						call_finish
					); 
					++device;
				}
				else
				{
					device = local_it->second.remotes.erase(device);
					jrn(journal::debug, object_id) << 
						"omitting sync via deleted device " << std::hex << device->first << 
						journal::end;
				}
			}
			wic_class::unlock_remote();
			local_it->second.remotes.unlock();
			local_it->second.property_lock.unlock();
			wic_class::unlock_local();
		}

		static void cancel(remote_iterator it)
		{
			if(it->second.remote.call_id)
			{
				jrn(journal::trace) << 
					"remote: " << (std::string)it->second.ip << 
					" cancelling sync via object " << std::hex << it->second.object_id << 
					journal::end;

				TEnv::rpc::cancel(it->second.remote.call_id);
				it->second.remote.call_id = 0;
			}
		}

		static void cancel(
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
						"' object reference " << std::hex 
						<< local_object_id << 
					journal::end;
				return;
			}

			local_it->second.remotes.lock();
			auto device = local_it->second.remotes.find(remote_object_id);
			if(device == local_it->second.remotes.end())
			{
				local_it->second.remotes.unlock();
				wic_class::unlock_local();
				jrn(journal::error) <<
					"local object: " << std::hex << local_object_id <<
					"; has no remote object: " << remote_object_id <<
					journal::end;
				return;
			}
			local_it->second.remotes.unlock();
			
			// TODO when to unlock remotes
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
				return;
			}

			cancel(remote_it);
			// TODO journal
			wic_class::unlock_remote();		
			wic_class::unlock_local();
		}
	};
}}
#endif
