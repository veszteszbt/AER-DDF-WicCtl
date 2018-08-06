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
		typedef typename TEnv::set_handle_type		set_handle_type;

		typedef typename TEnv::oosp_class			oosp_class;

		typedef typename TEnv::object_id_type		object_id_type;

		typedef typename TEnv::member_id			member_id;

		static journal jrn(uint8_t level)
		{
			return journal(level,"oosp.sync.remote") << "property: " << std::hex <<
				TEnv::class_id << "::" << member_id::value << ' ';
		}

		static void call_finish(set_handle_type h)
		{
			const object_id_type arg_object_id = h.argument().object_id;

			oosp_class::lock_remote();
			auto it = oosp_class::find_remote(arg_object_id);
			if(it == oosp_class::end())
			{
				oosp_class::unlock_remote();
				jrn(journal::error) <<
					"Invalid remote `" << oosp_class::name <<
					"' object reference: " << std::hex << arg_object_id <<
					journal::end;
				return;
			}

			it->second.report_call(h);

			it->second.property_lock.lock();
			auto &property = it->second.properties.template get<member_id>();

			TEnv::finish_sync_remote(property.sync, h);

			if(h.reason)
			{
				++property.sync.failures;
				jrn(journal::error) <<
					"remote: " << (std::string)h.ip <<
					"; object: " << std::hex << arg_object_id <<
					"; sync failed" <<
					journal::end;
				it->second.property_lock.unlock();
				oosp_class::unlock_remote();
				notify(arg_object_id);
				return;
			}

			const object_id_type ret_object_id = h.value();
			if(arg_object_id != ret_object_id)
			{
				it->second.property_lock.unlock();
				oosp_class::unlock_remote();
				jrn(journal::critical) <<
					"remote: " << (std::string)h.ip <<
					"; sync succeeded with call " << std::hex << h.call_id <<
					"; but got invalid remote `" << oosp_class::name <<
					"' object reference " << std::hex << ret_object_id <<
					journal::end;

				notify(arg_object_id);
				return;
			}

			jrn(journal::trace) <<
				"remote: " << (std::string)h.ip <<
				"; object: " << std::hex << arg_object_id <<
				"; sync succeeded with call: " << std::hex << h.call_id <<
				journal::end;

			it->second.property_lock.unlock();
			oosp_class::unlock_remote();
			notify(arg_object_id);
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
			auto it = oosp_class::find_remote(object_id);
			if(it == oosp_class::end())
			{
				oosp_class::unlock_remote();
				jrn(journal::error) <<
					"Invalid remote `" << oosp_class::name <<
					"' object reference: " << std::hex << object_id <<
					journal::end;
				return;
			}

			it->second.property_lock.lock();
			auto &property = it->second.properties.template get<member_id>();
			if(property.history.empty())
			{
				it->second.property_lock.unlock();
				oosp_class::unlock_remote();
				jrn(journal::trace) <<
					"object: " << std::hex << object_id <<
					"; nothing to do; suspending until next notify" <<
					journal::end;
				return;
			}

			jrn(journal::trace) <<
				"remote: " << (std::string)it->second.ip <<
				"; doing sync via object: " << std::hex << object_id <<
				journal::end;

			TEnv::sync_remote(
				property,
				object_id,
				it->second.ip,
				types::function::set,
				call_finish
			);
			it->second.property_lock.unlock();
			oosp_class::unlock_remote();
		}

		// TODO calling this
		static void cancel(object_id_type object_id)
		{
			oosp_class::lock_remote();
			auto it = oosp_class::find_remote(object_id);
			if(it == oosp_class::end())
			{
				oosp_class::unlock_remote();
				jrn(journal::error) <<
					"Invalid remote `" << oosp_class::name <<
					"' object reference: " << std::hex << object_id <<
					journal::end;
				return;
			}

			it->second.property_lock.lock();
			auto &property = it->second.properties.template get<member_id>();
			if(property.call_id)
			{
				jrn(journal::debug) <<
					"object: " << std::hex << object_id <<
					"; cancelling sync" <<
					journal::end;
				TEnv::rpc::cancel(property.call_id);
				property.call_id = 0;
			}
			it->second.property_lock.unlock();
			oosp_class::unlock_remote();
		}
	};
}}
#endif
