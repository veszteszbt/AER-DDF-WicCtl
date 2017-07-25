#ifndef WICP_REMOTE_PROPERTY_H
# define WICP_REMOTE_PROPERTY_H
# include <wicp/property_env_base.h>
# include <wicp/process/sync_remote.h>
# include <wicp/process/commit.h>
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
		{ typedef typename process::sync_remote<env> proc_sync; };

		typedef typename process::commit<env_commit>  proc_commit;

		typedef typename env_commit::proc_sync        proc_sync;

		typedef typename env::clock                   clock;

		typedef typename env::rpc                     rpc;

		typedef typename env::command_id_type         command_id_type;

		typedef typename env::value_type              value_type;

		typedef typename env::remote_record           remote_record;

		typedef typename env::history_record          history_record;

		typedef typename env::history_type            history_type;

		typedef typename env::rpc::template call_handle<bool>  notify_call_handle_type;

	public:
		typedef typename env::change_handler_type change_handler_type;

		constexpr static change_handler_type &change_handler = env::change_handler;

	private:

		static const typename env::command_id_type   command_id = env::command_id;

		constexpr static history_type               &history = env::history;

		constexpr static std::mutex                 &history_lock = env::history_lock;

		constexpr static remote_record              &remote  = env::remote;

		static void notify_handler(notify_call_handle_type  h, const value_type *v)
		{
			if(v && env::value != *v)
			{
				std::cout << "\e[32;01m - \e[0mwicp remote property: new value on remote" << std::endl;

				history_lock.lock();
				env::value = *v;
				history.push_front(history_record(*v));
				if(history.size() > 16)
					history.pop_back();
				remote.sync_timestamp = history.front().time;
				history_lock.unlock();

				h.respond(true);
				if(change_handler)
					change_handler();
			}
			else
			{
				std::cout << "\e[32;01m - \e[0mwicp remote property: notify from remote" << std::endl;
				h.respond(false);
			}
		}

	public:
		static void init(net::ipv4_address ip)
		{
			history.clear();
			proc_commit::init();
			proc_sync::init();
			change_handler = 0;
			env::remote.ip = ip;
			env::remote.sync_timestamp = clock::time_point::min();
			env::remote.pending_timestamp = clock::time_point::min();
			rpc::set_command(
				command_id | types::function::notify,
				notify_handler
			);
			std::cout << "\e[32;01m - \e[0mwicp remote property: initialized; command id is " << std::hex << command_id << std::endl;
		}

		static void uninit()
		{
			proc_commit::uninit();
			proc_sync::uninit();
			rpc::clear_command(command_id | types::function::notify);
			std::cout << "\e[32;01m - \e[0mwicp remote property: uninitialized; command id is " << command_id << std::endl;
		}

		static value_type value()
		{ return env::value; }

		static value_type value(value_type v)
		{
			if(v == env::value)
				return v;
			env::value = v;
			proc_commit::notify();
			return env::value;
		}

		static change_handler_type on_change()
		{ return change_handler; }

		static change_handler_type on_change(change_handler_type c)
		{ change_handler = c; }
	};

	template<typename e>
	typename remote_property<e>::env::base::remote_record remote_property<e>::env::remote;

	template<typename e>
	typename remote_property<e>::env::change_handler_type remote_property<e>::env::change_handler;
}
#endif
