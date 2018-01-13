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

		typedef typename TEnv::set_handle_type  set_handle_type;

		constexpr static remotes_type          &remotes = TEnv::remotes;

		constexpr static std::mutex            &remotes_lock = TEnv::remotes_lock;

		static journal jrn(uint8_t level)
		{
			return journal(level,"wicp.sync.local") << "property: " << std::hex <<
				TEnv::class_id << "::" << TEnv::member_id << ' ';
		}

		static void call_finish(set_handle_type h)
		{
			TEnv::remotes_lock.lock();
			for(
				typename remotes_type::iterator i = remotes.begin();
				i != remotes.end();
				++i
			)
				if(i->call_id == h.call_id)
				{
					i->role.report_call(h);
					TEnv::finish_sync_remote(*i,h);
					TEnv::remotes_lock.unlock();
					notify();
					return;
				}

			jrn(journal::critical) << "; remote: " << (std::string)h.ip <<
				"could not find remote for finished change" << journal::end;

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

		static void notify(role_type &role)
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
				auto i = remotes.begin();
				i != remotes.end();
				++i
			)
				if(&i->role == &role)
				{
					if(i->role.is_bound())
					{
						jrn(journal::trace) << "remote: " << (std::string)i->role.get_ip() <<" doing sync via role `" <<
							i->role.name<< "'" << journal::end;
						TEnv::sync_remote(*i,types::function::notify,call_finish);
						TEnv::remotes_lock.unlock();
						return;
					}
					else
					{
						jrn(journal::debug) << "omitting sync via unbound role `" << i->role.name << "'" << journal::end;
						TEnv::remotes_lock.unlock();
						return;
					}
				}
			TEnv::remotes_lock.unlock();
			jrn(journal::warning) << "remote for notified role `" << role.name << "' not found" << journal::end;
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
				auto i = remotes.begin();
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

		static void cancel(typename remotes_type::iterator i)
		{
			if(i->call_id)
			{
				jrn(journal::trace) << "remote: " << (std::string)i->role.get_ip() <<" cancelling sync via role `" <<
					i->role.name<< "'" << journal::end;

				TEnv::rpc::cancel(i->call_id);
				i->call_id = 0;
			}
		}

		static void cancel(role_type &role)
		{
			TEnv::remotes_lock.lock();
			for(
				auto i = remotes.begin();
				i != remotes.end();
				++i
			)
				if(&i->role == &role)
				{
					cancel(i);
					TEnv::remotes_lock.unlock();
					return;
				}
			TEnv::remotes_lock.unlock();
			
		}
	};
}}
#endif
