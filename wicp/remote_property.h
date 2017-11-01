#ifndef WICP_REMOTE_PROPERTY_H
# define WICP_REMOTE_PROPERTY_H
# include <wicp/property_env_base.h>
# include <wicp/process/sync_remote.h>
# include <wicp/process/commit.h>
# include <wicp/process/log.h>
# include <sched/listener.h>
namespace wicp
{
	template<typename TConfig>
	class remote_property
	{
		struct env : public property_env_base<TConfig>
		{
			typedef property_env_base<TConfig>  base;
			
			static typename base::remote_record remote;

			typedef void (*change_handler_type)();

			static change_handler_type change_handler;
		};

		struct env_commit : public env
		{
			typedef typename process::sync_remote<env> proc_sync;
			typedef typename process::log<env>         proc_log;
		};

		typedef typename process::commit<env_commit>  proc_commit;

		typedef typename env_commit::proc_sync        proc_sync;

		typedef typename env_commit::proc_log         proc_log;

		typedef typename env::clock                   clock;

		typedef typename env::rpc                     rpc;

		typedef typename env::command_id_type         command_id_type;

		typedef typename env::remote_record           remote_record;

		typedef typename env::history_record          history_record;

		typedef typename env::history_type            history_type;

		typedef typename env::rpc::template call_handle<bool>  notify_call_handle_type;

	public:
		typedef typename env::value_type              value_type;

		constexpr static sched::listener &on_change = env::on_change;

	private:

		static const typename env::command_id_type   command_id = env::command_id;

		constexpr static history_type               &history = env::history;

		constexpr static std::mutex                 &history_lock = env::history_lock;

		constexpr static remote_record              &remote  = env::remote;

		static void notify_handler(notify_call_handle_type  h, const value_type *v)
		{
			if(v)
			{
				if(env::value != *v)
				{
					log(log::trace,"wicp.property.remote") << "new value on remote" << std::endl <<
						"  remote: " << (std::string)h.ip << std::endl <<
						"property: " << std::hex << env::class_id << "::" << env::member_id <<
						log::end;

					history_lock.lock();
					env::value = *v;
					history.push_front(history_record(*v));
					if(history.size() > 16)
						history.pop_back();
					remote.sync_timestamp = history.front().time;
					history_lock.unlock();
					h.respond(true);
					proc_log::notify();
					env::sync_local();
				}
				else
				{
					log(log::warning,"wicp.property.remote") << "notify from remote with no change" << std::endl <<
						"  remote: " << (std::string)h.ip << std::endl <<
						"property: " << std::hex << env::class_id << "::" << env::member_id <<
						log::end;
					h.respond(false);
				}
			}
			else
			{
				log(log::error,"wicp.property.remote") << "notify from remote with no value" << std::endl <<
					"  remote: " << (std::string)h.ip << std::endl <<
					"property: " << std::hex << env::class_id << "::" << env::member_id <<
					log::end;
				h.respond(false);
			}
		}

	public:
		static void init(net::ipv4_address ip)
		{
			history.clear();
			env::remote.ip = ip;
			env::remote.sync_timestamp = clock::time_point::min();
			env::remote.pending_timestamp = clock::time_point::min();
			proc_log::init();
			proc_commit::init();
			proc_sync::init();
			rpc::set_command(
				command_id | types::function::notify,
				notify_handler
			);
			log(log::debug,"wicp.property.remote") << "initialized" << std::endl <<
				"  remote: " << (std::string)ip << std::endl <<
				"property: " << std::hex << env::class_id << "::" << env::member_id <<
				log::end;
		}

		static void uninit()
		{
			proc_commit::uninit();
			proc_sync::uninit();
			proc_log::uninit();
			rpc::clear_command(command_id | types::function::notify);
			log(log::debug,"wicp.property.remote") << "uninitialized" << std::endl <<
				"  remote: " << (std::string)env::remote.ip << std::endl <<
				"property: " << std::hex << env::class_id << "::" << env::member_id <<
				log::end;
		}

		static value_type value()
		{ return env::value; }

		static uint32_t failures()
		{ return env::remote::failures; }

		static typename clock::duration latency()
		{ return env::remote::latency; }

		static value_type value(value_type v)
		{
			if(v == env::value)
				return v;
			log(log::trace,"wicp.property.remote") << "new local value" << std::endl <<
				"property: " << std::hex << env::class_id << "::" << env::member_id <<
				log::end;
			env::value = v;
			proc_commit::notify();
			return env::value;
		}
	};

	template<typename e>
	typename remote_property<e>::env::base::remote_record remote_property<e>::env::remote;
}
#endif
