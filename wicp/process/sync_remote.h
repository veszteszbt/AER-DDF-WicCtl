#ifndef WICP_PROCESS_SYNC_REMOTE_H
# define WICP_PROCESS_SYNC_REMOTE_H
# include <log.h>
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

		static void call_finish(net::ipv4_address ip, command_id_type cmd, const bool *v)
		{
			if(remote.ip == ip)
			{
				if(!v)
				{
					++remote.failures;
					::log(::log::error,"wicp.sync.remote") << "sync failed" << std::endl <<
						"  remote: " << (std::string)ip << std::endl <<
						"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
						::log::end;
				}
				else
				{
					::log(::log::trace,"wicp.sync.remote") << "sync succeeded" << std::endl <<
						"  remote: " << (std::string)ip << std::endl <<
						"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
						::log::end;
				}

				TEnv::finish_sync_remote(remote,v);
				notify();
				return;
			}

			::log(::log::warning,"wicp.sync.remote") << "ip address mismatch" << std::endl <<
				"expected: " << (std::string)remote.ip << std::endl <<
				"received: " << (std::string)ip << std::endl <<
				"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
				::log::end;
			notify();
		}

	public:
		static void init()
		{
			::log(::log::debug,"wicp.sync.remote") << "initialized" << std::endl <<
				"  remote: " << (std::string)remote.ip << std::endl <<
				"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
				::log::end;
		}

		static void uninit()
		{
			::log(::log::debug,"wicp.sync.remote") << "uninitialized" << std::endl <<
				"  remote: " << (std::string)remote.ip << std::endl <<
				"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<		
				::log::end;
		}

		static void notify()
		{
			history_lock.lock();
			if(history.empty())
			{
				::log(::log::trace,"wicp.sync.remote") << "nothing to do; suspending until next notify" << ::log::end;
				history_lock.unlock();
				return;
			}

			history_lock.unlock();
			TEnv::sync_remote(remote,types::function::set,call_finish);
		}
	};
}}
#endif
