#ifndef WICP_PROCESS_SYNC_LOCAL_H
# define WICP_PROCESS_SYNC_LOCAL_H
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

		static void call_finish(net::ipv4_address ip, command_id_type cmd, const bool *v)
		{
			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				if(i->ip == ip)
				{
					TEnv::finish_sync_remote(*i,v);
					idle::yield(notify);
					return;
				}

			log::println("\e[33;01m - \e[0mwicp sync local: could not find remote for finished change notify");
			notify();
		}

	public:
		static void init()
		{ log::println("\e[37;01m - \e[0mwicp sync local: initialized"); }

		static void uninit()
		{}

		static void notify()
		{
			if(TEnv::history.empty())
			{
				log::println("\e[37;01m - \e[0mwicp sync local: nothing to do; suspending until next notify");
				return;
			}

			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				TEnv::sync_remote(*i,types::function::notify,call_finish);
		}
	};
}}
#endif
