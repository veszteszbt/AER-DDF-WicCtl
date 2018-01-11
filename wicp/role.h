#ifndef WICP_ROLE_H
# define WICP_ROLE_H
namespace wicp {

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
		device_type *volatile device;

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
			, device(0)
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
			lock.lock();
			net::ipv4_address r;
			if(device)
				r = device->get_ip();
			else
				r = net::ipv4_address(0,0,0,0);
			lock.unlock();

			return r;
		}

		uint8_t get_health()
		{
			lock.lock();
			uint8_t r;
			if(device)
				r = device->get_health();
			else
				r = 0;
			lock.unlock();

			return r;
		}

		template<typename T>
		void report_call(const T &h)
		{
			if(h.reason == earpc::reason::cancelled)
				return;
			call_report_type r;
			r.success = !h.reason;
			r.latency = calc_latency(h);

			lock.lock();
			if(device)
				device->report_call(r);
			lock.unlock();
		}

		bool is_bound()
		{
			lock.lock();
			const bool r = device;
			lock.unlock();
			return r;
		}

		bool is_bound_to(device_type &dev)
		{
			if(!&dev)
				return false;
			lock.lock();
			const bool r = (device == &dev);
			lock.unlock();
			return r;
		}

		bool unbind()
		{
			lock.lock();
			if(!device)
			{
				lock.unlock();
				return false;
			}
			device = 0;
			lock.unlock();
			on_unbound(*this);
			return true;
		}


		bool bind(device_type &dev)
		{
			if(!&dev)
				return false;
			lock.lock();
			if(device)
			{
				lock.unlock();
				return false;
			}
			device = &dev;
			lock.unlock();
			on_bound(*this);
			return true;
		}

		static role_type none;
	};

	role_type role_type::none("(none)");
}
#endif
