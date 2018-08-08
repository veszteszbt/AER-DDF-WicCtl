#ifndef OOSP_PROCESS_SYNC_LOCAL_H
# define OOSP_PROCESS_SYNC_LOCAL_H
# include <journal.h>

namespace oosp {
namespace process
{
	template<typename TEnv>
	class sync_local
	{
		typedef typename TEnv::call_id_type							call_id_type;

		typedef typename TEnv::object_id_type						object_id_type;

		typedef typename TEnv::member_id							member_id;

		typedef typename TEnv::oosp_class							oosp_class;

		typedef typename TEnv::sync_record 							sync_record;

		typedef typename TEnv::set_handle_type						set_handle_type;

		typedef typename TEnv::history_type							history_type;

		typedef typename oosp_class::local_table_iterator			local_table_iterator;

		typedef typename oosp_class::remote_table_iterator			remote_table_iterator;

		typedef typename oosp_class::local_object_record_type		local_object_record_type;

		typedef typename oosp_class::remote_object_record_type		remote_object_record_type;

		typedef typename local_object_record_type::remotes_iterator	remotes_iterator;

		typedef std::pair<sync_record*,remote_object_record_type*>	sync_remote_pair_record;

		typedef typename sync_record::value_type					value_type;

		typedef net::ipv4_address 									address_type;

		friend oosp_class;

		static journal jrn(uint8_t level)
		{
			return journal(level,"oosp.sync.local") << std::hex <<
				"class: " << oosp_class::name <<
				"; property: " <<
				" (" << TEnv::class_id << "::" << member_id::value << "); ";
		}

		static journal jrn(uint8_t level, object_id_type object)
		{
			return journal(level,"oosp.sync.local") << std::hex <<
				"object:  " << object <<
				"; class: " << oosp_class::name <<
				"; property: " <<
				" (" << TEnv::class_id << "::" << member_id::value << "); ";
			;
		}

		static void call_finish(set_handle_type h)
		{
			const object_id_type arg_object_id = h.argument().object_id;
			oosp_class::lock_local();

			auto local_it = oosp_class::find_local(arg_object_id);
			if(oosp_class::unknown_local_object(local_it, jrn))
				return;

			auto &local = local_it->second;
			local.remotes.lock();
			oosp_class::lock_remote();

			auto sync_pair = find_sync(local,h.call_id);
			if(there_is_no_valid_remote_for_finished_sync(local, sync_pair, h.ip, h.call_id))
				return;

			TEnv::finish_sync_remote(*sync_pair.first, h);
			sync_pair.second->report_call(h);
			if(call_failed(local, h.reason, h.ip, arg_object_id))
				return;

			const object_id_type ret_object_id = h.value();
			if(arg_and_ret_object_id_mismatched(local, arg_object_id, ret_object_id, h.ip))
				return;

			std::stringstream ss;
			ss << "remote: " << std::hex << sync_pair.second->object_id << 
				" (" << (std::string)h.ip << "); sync call finished";
			unlock_and_call_notify(local, ss.str(), journal::trace);
		}

		static sync_remote_pair_record find_sync(
			local_object_record_type &local,
			call_id_type call_id
		)
		{
			for(auto i = local.remotes.begin(); i != local.remotes.end(); ++i)
			{
				auto &sync = i->second.template get<member_id>();
				if(sync.call_id == call_id)
				{
					auto device = oosp_class::find_remote(i->first);

					if(device == oosp_class::end())
					{
						jrn(journal::error,local.object_id) <<
							"Invalid remote `" << oosp_class::name <<
							"' object reference; erasing endpoint" <<
							journal::end;

						i = local.remotes.erase(i);
						return std::make_pair<sync_record*,remote_object_record_type*>(nullptr,nullptr);
					}
					return std::make_pair(&sync,&device->second);
				}
			}
			return std::make_pair<sync_record*,remote_object_record_type*>(nullptr,nullptr);
		}

		static bool there_is_no_valid_remote_for_finished_sync(
			local_object_record_type &local, 
			const sync_remote_pair_record &sync_pair, 
			address_type ip, 
			call_id_type call_id
		)
		{
			if(!sync_pair.first || !sync_pair.second)
			{
				std::stringstream ss;
				ss << "remote: " << (std::string)ip << std::hex <<
					"; could not find a valid remote for finished sync call " << call_id;
				unlock_and_call_notify(local, ss.str(), journal::critical);
				return true;
			}
			return false;
		}

		static void unlock_and_call_notify(
			local_object_record_type &local, 
			const std::string &journal_msg,
			uint8_t journal_level = journal::error
		)
		{
			oosp_class::unlock_remote();
			local.remotes.unlock();
			oosp_class::unlock_local();
			if(!journal_msg.empty())
				jrn(journal_level, local.object_id) << journal_msg << journal::end;

			notify(local.object_id);
		}

		static bool call_failed(
			local_object_record_type &local,
			uint8_t reason, 
			address_type ip, 
			object_id_type object_id
		)
		{
			if(reason != ::earpc::reason::success)
			{
				std::stringstream ss;
				ss << "remote: " << (std::string)ip <<
					"; error in call, restarting sync for object " << std::hex << object_id;
				unlock_and_call_notify(local, ss.str());
				return true;
			}
			return false;
		}

		static bool arg_and_ret_object_id_mismatched(
			local_object_record_type &local,
			object_id_type arg_object_id, 
			object_id_type ret_object_id, 
			address_type ip
		)
		{
			if(arg_object_id != ret_object_id)
			{
				std::stringstream ss;
				ss << "; remote: " << (std::string)ip <<
					"; sync returned mismatching `" <<
					oosp_class::name << "' object reference " << std::hex << ret_object_id <<
					"; considering failed";
				unlock_and_call_notify(local, ss.str(), journal::critical);
				return true;
			}
			return false;
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
			oosp_class::lock_local();

			auto local_it = oosp_class::find_local(local_object_id);
			if(oosp_class::unknown_local_object(local_it, jrn))
				return;

			auto &local = local_it->second;
			local.property_lock.lock();

			auto &local_property =
				local.properties.template get<member_id>();
			if(history_empty_of(local_property.history, local_it))
				return;

			local.property_lock.unlock();
			local.remotes.lock();

			auto device = local.remotes.find(remote_object_id);
			if(oosp_class::local_has_no_remote(device, remote_object_id, local))
				return;

			oosp_class::lock_remote();

			auto remote_it = oosp_class::find_remote(remote_object_id);
			if(oosp_class::unknown_device_object(local, remote_it, jrn))
				return;

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
				::oosp::types::function::notify,
				call_finish
			);

			oosp_class::unlock_remote();
			local.remotes.unlock();
			oosp_class::unlock_local();
		}

	private:
		static bool history_empty_of(
			const history_type &history, 
			local_table_iterator &local_it
		)
		{
			if(history.empty())
			{
				local_it->second.property_lock.unlock();
				oosp_class::unlock_local();
				jrn(journal::trace) <<
					"object: " << std::hex << local_it->first <<
					"; nothing to do suspending until next notify" <<
					journal::end;
				return true;
			}
			return false;
		}

	public:
		static void notify(object_id_type object_id)
		{
			oosp_class::lock_local();

			auto local_it = oosp_class::find_local(object_id);
			if(oosp_class::unknown_local_object(local_it, jrn))
				return;

			local_it->second.property_lock.lock();
			
			auto &local_property = local_it->second.properties.template get<member_id>();
			if(history_empty_of(local_property.history, local_it))
				return;

			local_it->second.remotes.lock();
			oosp_class::lock_remote();

			sync_remotes_of_local_object(local_it, local_property);

			oosp_class::unlock_remote();
			local_it->second.remotes.unlock();
			local_it->second.property_lock.unlock();
			oosp_class::unlock_local();
		}

	private:

		template <typename Tproperty>
		static void sync_remotes_of_local_object(
			local_table_iterator local_it, 
			Tproperty &local_property
		)
		{
			for(
				auto device = local_it->second.remotes.begin();
				device != local_it->second.remotes.end();
			)
			{
				auto remote_it = oosp_class::find_remote(device->first);
				if(remote_it != oosp_class::end())
				{
					auto &device_sync = device->second.template get<member_id>();
					if(
						sync_necessary(
							device, 
							device_sync.local_value, 
							local_property.sync.local_value, 
							remote_it->first,
							remote_it->second.ip
						)
					)
						sync_remote(
							remote_it, 
							device, 
							device_sync, 
							local_property.history, 
							local_it->first
						);
					else
						continue;
				}
				else
				{
					device = local_it->second.remotes.erase(device);
					jrn(journal::debug, local_it->first) <<
						"omitting sync via deleted device " << std::hex << device->first <<
						journal::end;
				}
			}
		}

		static bool sync_necessary(
			remotes_iterator &device, 
			value_type device_value, 
			value_type local_value,
			object_id_type object_id,
			address_type ip
		)
		{
			if(local_value == device_value)
			{
				jrn(journal::trace,object_id) <<
					"remote: " << (std::string)ip <<
					"; skipping sync for the source of the data, device: " <<
					std::hex << device->first <<
					journal::end;
				++device;
				return false;
			}
			return true;
		}

		template <typename TdeviceSyncRecord>
		static bool sync_remote(
			remote_table_iterator remote_it, 
			remotes_iterator &device,
			TdeviceSyncRecord &device_sync,
			const history_type &history,
			object_id_type object_id
		)
		{
			jrn(journal::trace,remote_it->first) <<
				"remote: " << (std::string)remote_it->second.ip <<
				"; doing sync via device: " << std::hex << device->first <<
				journal::end;

			TEnv::sync_remote(
				device_sync,
				history,
				object_id,
				remote_it->second.ip,
				::oosp::types::function::notify,
				call_finish
			);
			++device;
			return false;
		}
	};
}}
#endif
