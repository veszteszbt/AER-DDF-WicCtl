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
		typedef typename TEnv::clock           clock;

		typedef typename TEnv::command_id_type command_id_type;

		typedef typename TEnv::value_type      value_type;

		typedef typename TEnv::remote_record   remote_record;

		typedef typename TEnv::history_type    history_type;

		constexpr static remote_record        &remote = TEnv::remote;

		constexpr static history_type         &history = TEnv::history;

		constexpr static std::mutex           &history_lock = TEnv::history_lock;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.sync.remote") << "role: " << remote.role.name << "; property: " << std::hex <<
				TEnv::class_id << "::" << TEnv::member_id << ' ';
		}

		static void call_finish(set_handle h)
		{

			std::string rsnstr;
			if(h.reason != earpc::reason::success)
			{
				++remote.failures;
				rsnstr = "failed";
			}
			else
				rsnstr = "succeeded";

			if(remote.role.get_ip() == h.ip)
				jrn(journal::error) << "; remote: " << (std::string)ip << " sync " << rsnstr << journal::end;

			else
			{
				jrn(journal::warning) <<
					"; orig ip: " << (std::string)remote.role.get_ip() <<
					"; final ip: " << (std::string)ip <<
					"; sync " << rsnstr << " with new address" <<
					journal::end;

				history_lock.lock();
				remote.ip = h.ip;
				history_lock.unlock();
				remote.role.notify_ip_change(h.ip);
			}
			TEnv::finish_sync_remote(remote,h);
			notify();
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

		static void notify()
		{
			history_lock.lock();
			if(history.empty())
			{
				jrn(journal::trace) << "nothing to do; suspending until next notify" << journal::end;
				history_lock.unlock();
				return;
			}

			history_lock.unlock();
			if(remote.role.is_bound())
			{
				jrn(journal::trace) << "; remote: " << (std::string)remote.role.get_ip() <<" doing sync" << journal::end;
				TEnv::sync_remote(remote,types::function::set,call_finish);
			}
			else
			{
				jrn(journal::debug) << "omitting sync via unbound role" << journal::end;
			}
		}
	};
}}
#endif
