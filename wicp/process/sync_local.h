#ifndef WICP_PROCESS_SYNC_LOCAL_H
# define WICP_PROCESS_SYNC_LOCAL_H
# include <journal.h>
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

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.sync.local") << "property: " << std::hex <<
				TEnv::class_id << "::" << TEnv::member_id << ' ';
		}

		static void call_finish(net::ipv4_address ip, command_id_type cmd, const bool *v)
		{
			TEnv::remotes_lock.lock();
			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				if(i->role.get_ip() == ip)
				{
					TEnv::finish_sync_remote(*i,v);
					TEnv::remotes_lock.unlock();
					notify();
					return;
				}

			jrn(journal::warning) << "; remote: " << (std::string)ip <<
				"could not find remote for finished change" << journal::end;
			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				TEnv::finish_sync_remote(*i,0);

			TEnv::remotes_lock.unlock();
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
			TEnv::history_lock.lock();
			if(TEnv::history.empty())
			{
				TEnv::history_lock.unlock();
				jrn(journal::trace) << "nothing to do; suspending until next notify" << journal::end;
				return;
			}
			TEnv::history_lock.unlock();
			TEnv::remotes_lock.lock();
			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				if(i->role.is_bound())
				{
					jrn(journal::trace) << "; remote: " << (std::string)i->role.get_ip() <<" doing sync via role `" <<
						i->role.name<< "'" << journal::end;
					TEnv::sync_remote(*i,types::function::notify,call_finish);
				}
				else
				{
					jrn(journal::debug) << "omitting sync via unbound role `" << i->role.name << "'" << journal::end;
				}

			TEnv::remotes_lock.unlock();
		}
	};
}}
#endif
