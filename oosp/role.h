#ifndef OOSP_ROLE_H
# define OOSP_ROLE_H
namespace oosp {

	struct call_report_type
	{
		bool    success;
		int32_t latency;
	};

	struct device_type
	{
		virtual ~device_type() {}

		virtual std::string get_name() = 0;

		virtual net::ipv4_address get_ip() = 0;

		virtual uint8_t get_health() = 0;

		virtual void report_call(call_report_type) = 0;
	};

	class role_type
	{
		std::mutex lock;


		template<typename T, typename U = decltype(T::finished), typename V = decltype(T::started)>
		int32_t calc_latency(const T &h)
		{ return ::types::time::msec(h.finished-h.started); }

		template<typename T, typename U = decltype(T::received)>
		int32_t calc_latency(const T &h)
		{ return -1; }

	public:
		const std::string name;

		sched::event<role_type&> on_bound;

		sched::event<role_type&> on_unbound;

		sched::event<role_type&> on_health_change;

		role_type(const std::string &pname)
			: name(pname)
		{}

		~role_type()
		{
			lock.lock();
			lock.unlock();
		}

		bool operator==(const role_type &t)
		{ return t.name == name; }

		net::ipv4_address get_ip()
		{
			net::ipv4_address r(127,0,0,1);

			return r;
		}

		uint8_t get_health()
		{
			return 255;
		}

		template<typename T>
		void report_call(const T &h)
		{
			if(h.reason == earpc::reason::cancelled)
				return;
			else if(h.reason == earpc::reason::success)
				journal(journal::info,"role.report_call") << "\e[32mcall succeeded\e[0m" << journal::end;

			call_report_type r;
			r.success = !h.reason;
			r.latency = calc_latency(h);
		}

		bool is_bound()
		{
			return true;
		}

		bool is_bound_to(device_type &dev)
		{
			return true;
		}

		bool unbind()
		{
			on_unbound(*this);
			return true;
		}

		bool bind(device_type &dev)
		{
			on_bound(*this);
			return true;
		}

		static role_type none;
	};

	role_type role_type::none("(none)");
}
#endif
