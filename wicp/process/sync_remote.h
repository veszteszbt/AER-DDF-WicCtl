#ifndef WICP_PROCESS_SYNC_REMOTE_H
# define WICP_PROCESS_SYNC_REMOTE_H
# include <wicp/types.h>
namespace wicp {
namespace process
{
	template<typename TEnv>
	class sync_remote
	{
		typedef typename TEnv::command_id_type command_id_type;

		typedef typename TEnv::value_type      value_type;

		typedef typename TEnv::remote_record   remote_record;

		typedef typename TEnv::history_type    history_type;

		constexpr static remote_record        &remote = TEnv::remote;

		constexpr static history_type         &history = TEnv::history;

		static void call_finish(net::ipv4_address ip, command_id_type cmd, const bool *v)
		{
			if(remote.ip == ip)
			{
				TEnv::finish_sync_remote(remote,v);
				if(v)
					std::cout << "\e[32;01m - \e[0mwicp sync remote: sync successful" << std::endl;
				else
					std::cout << "\e[31;01m - \e[0mwicp sync remote: sync failed" << std::endl;

				notify();
				return;
			}

			std::cout << "\e[33;01m - \e[0mwicp sync remote: ip address mismatch" << std::endl;
			notify();
		}

	public:
		static void init()
		{ std::cout << "\e[37;01m - \e[0mwicp sync remote: initialized" << std::endl; }

		static void uninit()
		{}

		static void notify()
		{
			if(history.empty())
			{
				std::cout << "\e[37;01m - \e[0mwicp sync remote: nothing to do; suspending until next notify" << std::endl;
				return;
			}

			TEnv::sync_remote(remote,types::function::set,call_finish);
		}
	};
}}
#endif
