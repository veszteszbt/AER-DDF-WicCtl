#ifndef OOSP_PROCESS_SYNC_REMOTE_H
# define OOSP_PROCESS_SYNC_REMOTE_H
# include <journal.h>
# include <oosp/types.h>
namespace oosp {
namespace process
{
	template<typename TEnv>
	class sync_remote
	{
		typedef typename TEnv::set_handle_type					set_handle_type;

		typedef typename TEnv::oosp_class						oosp_class;

		typedef typename TEnv::object_id_type					object_id_type;

		typedef typename TEnv::member_id						member_id;

		typedef typename oosp_class::remote_object_record_type	remote_object_record_type;

		static journal jrn(uint8_t level)
		{
			return journal(level,"oosp.sync.remote") << "property: " << std::hex <<
				TEnv::class_id << "::" << member_id::value << ' ';
		}

		static journal jrn(uint8_t level, object_id_type object)
		{
			return journal(level,"oosp.sync.remote") << std::hex <<
				"object:  " << object <<
				"; class: " << oosp_class::name <<
				"; property: " <<
				" (" << TEnv::class_id << "::" << member_id::value << "); ";
			;
		}

		static void call_finish(set_handle_type h)
		{
			const object_id_type arg_object_id = h.argument().object_id;
			oosp_class::lock_remote();

			auto remote_it = oosp_class::find_remote(arg_object_id);
			if(oosp_class::unknown_remote_object(remote_it, jrn))
				return;

			auto &remote = remote_it->second;
			remote.report_call(h);
			remote.property_lock.lock();

			auto &property = remote.properties.template get<member_id>();

			TEnv::finish_sync_remote(property.sync, h);

			if(call_failed(h, property.sync.failures, remote))
				return;

			const object_id_type ret_object_id = h.value();
			if(arg_and_ret_object_id_mismatched(remote, arg_object_id, ret_object_id, h))
				return;

			std::stringstream ss;
			ss << "remote: " << (std::string)h.ip <<
				"; object: " << std::hex << arg_object_id <<
				"; sync succeeded with call: " << std::hex << h.call_id;

			unlock_and_call_notify(remote, ss.str(), journal::trace);
		}

		static bool call_failed(const set_handle_type &h, uint32_t &failures, remote_object_record_type &remote)
		{
			if(h.reason)
			{
				++failures;
				std::stringstream ss;
				ss << "remote: " << (std::string)h.ip <<
					"; object: " << std::hex << remote.object_id <<
					"; sync failed";
				unlock_and_call_notify(remote, ss.str());
				return true;
			}
			return false;
		}

		static void unlock_and_call_notify(
			remote_object_record_type &remote, 
			const std::string &journal_msg,
			uint8_t journal_level = journal::error
		)
		{
			remote.property_lock.unlock();
			oosp_class::unlock_remote();

			if(!journal_msg.empty())
				jrn(journal_level, remote.object_id) << journal_msg << journal::end;
			
			notify(remote.object_id);
		}

		static bool arg_and_ret_object_id_mismatched(
			remote_object_record_type &remote,
			object_id_type arg_object_id, 
			object_id_type ret_object_id, 
			const set_handle_type &h
		)
		{
			if(arg_object_id != ret_object_id)
			{
				std::stringstream ss;
				ss << "remote: " << (std::string)h.ip <<
					"; sync succeeded with call " << std::hex << h.call_id <<
					"; but got invalid remote `" << oosp_class::name <<
					"' object reference " << std::hex << ret_object_id;
				unlock_and_call_notify(remote, ss.str(), journal::critical);
				return true;
			}
			return false;	
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
			oosp_class::lock_remote();

			auto remote_it = oosp_class::find_remote(object_id);
			if(oosp_class::unknown_remote_object(remote_it, jrn))
				return;
			
			auto &remote = remote_it->second;
			remote.property_lock.lock();

			auto &property = remote.properties.template get<member_id>();
			if(property.history.empty())
			{
				remote.property_lock.unlock();
				oosp_class::unlock_remote();
				jrn(journal::trace) <<
					"object: " << std::hex << object_id <<
					"; nothing to do; suspending until next notify" <<
					journal::end;
				return;
			}

			jrn(journal::trace) <<
				"remote: " << (std::string)remote.ip <<
				"; doing sync via object: " << std::hex << object_id <<
				journal::end;
			TEnv::sync_remote(
				property,
				object_id,
				remote.ip,
				types::function::set,
				call_finish
			);

			remote.property_lock.unlock();
			oosp_class::unlock_remote();
		}

		// TODO calling this
		static void cancel(object_id_type object_id)
		{
			oosp_class::lock_remote();
			auto remote_it = oosp_class::find_remote(object_id);
			if(oosp_class::unknown_remote_object(remote_it, jrn))
				return;

			remote_it->second.property_lock.lock();
			auto &property = remote_it->second.properties.template get<member_id>();
			if(property.call_id)
			{
				jrn(journal::debug) <<
					"object: " << std::hex << object_id <<
					"; cancelling sync" <<
					journal::end;
				TEnv::rpc::cancel(property.call_id);
				property.call_id = 0;
			}
			remote_it->second.property_lock.unlock();
			oosp_class::unlock_remote();
		}
	};
}}
#endif
