#ifndef ARCTL_HOST_H
# define ARCTL_HOST_H
# include <sched/process.h>
namespace wic{

template<typename TConfig>
class arctl_host
{
	typedef typename TConfig::cfg_earpc rpc;

#pragma pack(push,1)
	struct
	heartbeat_payload_type
	{
		uint64_t serial;
		uint32_t counter;
	};
#pragma pack(pop)

	static heartbeat_payload_type heartbeat_payload;

	static net::ipv4_address server;

	static volatile bool heartbeat_pending;

	struct heartbeat_process_type : public sched::process
	{
		virtual ~heartbeat_process_type() {}

		virtual const std::string &name()
		{
			static const std::string n = "wic heartbeat";
			return n;
		}

		virtual void init()
		{
			heartbeat_payload.counter = 0;
			heartbeat_pending = false;
		}

		virtual void uninit()
		{}

		virtual void exec()
		{
			using namespace std::literals::chrono_literals;

			++heartbeat_payload.counter;
			if(!heartbeat_pending)
			{
				heartbeat_pending = true;
				rpc::call(server,0xffffffff0ffff000,heartbeat_payload,heartbeat_callback);
			}
			suspend(1s);
		}

	};
	static heartbeat_process_type *heartbeat_process;

	static void heartbeat_callback(net::ipv4_address ip, typename rpc::command_id_type cmd, const bool *v)
	{
		heartbeat_pending = false;
		if(!v)
			heartbeat_process->notify();
	}

	static void get_app_running(typename rpc::template call_handle<bool> h, const bool*)
	{ h.respond(true); }

	static void get_app_name(typename rpc::template call_handle<std::string> h, const bool*)
	{
		static std::string n = "(unimplemented)";
		h.respond(n);
	}

	static void get_app_version(typename rpc::template call_handle<uint32_t> h, const bool*)
	{ h.respond(0x10000000); }

public:
	static void init(uint64_t pserial, net::ipv4_address pserver)
	{

		rpc::set_command(
			0xffffffff00004001,
			get_app_running
		);

		rpc::set_command(
			0xffffffff00004003,
			get_app_name
		);
		
		rpc::set_command(
			0xffffffff00004004,
			get_app_version
		);


		const_cast<volatile uint64_t&>(heartbeat_payload.serial) = pserial;
		server = pserver;
		heartbeat_process = new heartbeat_process_type();
		heartbeat_process->start();
	}

	static void uninit()
	{
		heartbeat_process->stop();
		delete heartbeat_process;
		rpc::clear_command(0xffffffff00004001);
		rpc::clear_command(0xffffffff00004003);
		rpc::clear_command(0xffffffff00004004);
	}
};

template<typename c>
typename arctl_host<c>::heartbeat_process_type *arctl_host<c>::heartbeat_process;

template<typename c>
typename arctl_host<c>::heartbeat_payload_type arctl_host<c>::heartbeat_payload;

template<typename c>
net::ipv4_address arctl_host<c>::server;

template<typename c>
volatile bool arctl_host<c>::heartbeat_pending;

}
#endif
