#ifndef WICP_ROLE_H
# define WICP_ROLE_H
namespace wicp {

	struct device_type
	{
		virtual ~device_type() {}

		virtual std::string get_name() = 0;

		virtual net::ipv4_address get_ip() = 0;
	};

	class role_type
	{
		device_type *volatile device;

		std::mutex lock;

	public:
		const std::string name;

		sched::event<role_type&> on_bound;

		sched::event<role_type&> on_unbound;

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

		template<typename T>
		void report_call(const T &handle)
		{
			std::cout << "report call" << std::endl;
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
