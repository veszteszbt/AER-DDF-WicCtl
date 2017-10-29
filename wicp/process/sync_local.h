#ifndef WICP_PROCESS_SYNC_LOCAL_H
# define WICP_PROCESS_SYNC_LOCAL_H
# include <log.h>
namespace wicp {
namespace process
{
	template<typename TEnv>
	class sync_local
	{
		typedef typename TEnv::value_type       value_type;

		typedef typename TEnv::remotes_type     remotes_type;

		typedef typename TEnv::command_id_type  command_id_type;

		constexpr static remotes_type          &remotes = TEnv::remotes;

		constexpr static std::mutex            &remotes_lock = TEnv::remotes_lock;

		static void call_finish(net::ipv4_address ip, command_id_type cmd, const bool *v)
		{
			TEnv::remotes_lock.lock();
			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				if(i->ip == ip)
				{
					TEnv::finish_sync_remote(*i,v);
					TEnv::remotes_lock.unlock();
					notify();
					return;
				}

			TEnv::remotes_lock.unlock();
			log(log::warning,"wicp.sync.local") << "could not find remote for finished change" << std::endl << 
				"remote: " << (std::string)ip << std::endl <<
				"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
				log::end;
			notify();
		}

	public:
		static void init()
		{
			log(log::debug,"wicp.sync.local") << "initialized" << std::endl <<
				"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
				log::end;
		}

		static void uninit()
		{
			log(log::debug,"wicp.sync.local") << "uninitialized" << std::endl <<
				"property: " << std::hex << TEnv::class_id << "::" << TEnv::member_id <<
				log::end;
		}

		static void notify()
		{
			TEnv::history_lock.lock();
			if(TEnv::history.empty())
			{
				TEnv::history_lock.unlock();
				log(log::trace,"wicp.sync.local") << "nothing to do; suspending until next notify" << log::end;
				return;
			}
			TEnv::history_lock.unlock();
			TEnv::remotes_lock.lock();
			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				TEnv::sync_remote(*i,types::function::notify,call_finish);

			TEnv::remotes_lock.unlock();
		}
	};
}}
#endif
