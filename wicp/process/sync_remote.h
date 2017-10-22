#ifndef WICP_PROCESS_SYNC_REMOTE_H
# define WICP_PROCESS_SYNC_REMOTE_H
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
					std::cout << "\e[31;01m - \e[0mwicp sync remote: sync of " << std::hex << TEnv::class_id << "::" << TEnv::member_id << " with " <<
					(std::string)ip << " failed" << std::endl;
				}
				else
				{
//					std::cout << "\e[32;01m - \e[0mwicp sync remote: sync successful" << std::endl;
				}

				TEnv::finish_sync_remote(remote,v);
				notify();
				return;
			}

///			std::cout << "\e[33;01m - \e[0mwicp sync remote: ip address mismatch" << std::endl;
			notify();
		}

	public:
		static void init()
		{
//			std::cout << "\e[37;01m - \e[0mwicp sync remote: initialized" << std::endl;
		}

		static void uninit()
		{
//			std::cout << "\e[37;01m - \e[0mwicp sync remote: uninitialized" << std::endl;
		
		}

		static void notify()
		{
			history_lock.lock();
			if(history.empty())
			{
//				std::cout << "\e[37;01m - \e[0mwicp sync remote: nothing to do; suspending until next notify" << std::endl;
				history_lock.unlock();
				return;
			}

			history_lock.unlock();
			TEnv::sync_remote(remote,types::function::set,call_finish);
		}
	};
}}
#endif
