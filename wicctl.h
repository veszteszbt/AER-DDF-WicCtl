#ifndef WICCTL_H
# define WICCTL_H
# include <iostream>
# include <cstring>
# include <string>
# include <stdio.h>
# include <unistd.h>
# include <libusb-1.0/libusb.h>

class wicctl
{
	libusb_device_handle *devh;

	template<typename Tresult, uint8_t tObj, uint16_t tFn>
	Tresult get(uint16_t index)
	{
		Tresult rv;
		int result = libusb_control_transfer(
			devh,
			0x80,
			0x80+tObj,
			tFn,
			index,
			(unsigned char*)&rv,
			sizeof(Tresult),5000
		);

		if(result != sizeof(Tresult))
			throw 1;

		return rv;
	}

	template<typename Tdata, uint8_t tObj, uint16_t tFn>
	void put(uint16_t index, Tdata value)
	{
		int size = libusb_control_transfer(
			devh,
			0x0,
			0x80+tObj,
			tFn,
			index,
			(unsigned char*)&value,
			sizeof(Tdata),5000
		);


		if(size <= 0 || size != sizeof(Tdata))
			throw 1;
	}

	char buf[65536];

	template<uint8_t tObj, uint16_t tFn>
	std::string getstr(uint16_t index,uint16_t size=1024)
	{
		int s = libusb_control_transfer(
			devh,
			0x80,
			0x80+tObj,
			tFn,
			index,
			(unsigned char*)&buf,
			size,5000
		);

		if(s<0)
			std::cerr << "getstr error " << std::dec << s << std::endl;

		return std::string(buf,size);
	}

	template<uint8_t tObj, uint16_t tFn>
	void putstr(uint16_t index,const std::string &value)
	{
		int size = libusb_control_transfer(
			devh,
			0x0,
			0x80+tObj,
			tFn,
			index,
			(unsigned char*)value.c_str(),
			value.size(),5000
		);

		if(size<=0 && value.size())
			throw size;
	}

	uint8_t app_wait_for_completion()
	{
		uint8_t r;
		while((r = app_state()) == EINPROGRESS)
			usleep(10000);
		return r;
	}


	struct objs
	{
		static const uint8_t system = 0;
		static const uint8_t network = 1;
		static const uint8_t app = 2;

		static const uint8_t memory = 8;
	};

public:

	void reopen()
	{
		libusb_close(devh);
		libusb_exit(0);
		libusb_init(0);
		devh = libusb_open_device_with_vid_pid(0, 0x1234, 0x5678);
		if(!devh)
			throw static_cast<int>((int64_t)devh);

		libusb_detach_kernel_driver(devh, 0);
		libusb_claim_interface(devh, 0);
	}

	wicctl()
	{
		libusb_init(0);
		devh = libusb_open_device_with_vid_pid(0, 0x1234, 0x5678);
		if(!devh)
			throw 1;

		libusb_detach_kernel_driver(devh, 0);
		libusb_claim_interface(devh, 0);
	}

	~wicctl()
	{
		libusb_close(devh);
		libusb_exit(0);
	}

	
	uint32_t version()
	{ return get<uint32_t, objs::system, 0>(0); }

	uint64_t serial()
	{ return get<uint64_t, objs::system, 1>(0); }


	std::string hostname()
	{ return getstr<objs::network, 0>(0); }

	void hostname(const std::string &v)
	{ putstr<objs::network, 0>(0,v); }


	std::string ssid()
	{ return getstr<objs::network, 1>(0); }

	void ssid(const std::string &v)
	{ putstr<objs::network, 1>(0,v); }

	std::string psk()
	{ return getstr<objs::network, 3>(0); }

	void psk(const std::string &v)
	{ putstr<objs::network, 3>(0,v); }

	void save()
	{ getstr<objs::system, 0x100>(0); }


	uint8_t app_state()
	{ return get<uint8_t,objs::app,0>(0); }

	uint8_t app_uninstall()
	{
		putstr<objs::app,0>(0,"");
		return app_wait_for_completion();
	}

	uint8_t app_install_chunk(uint16_t chunk, const std::string &s)
	{
		putstr<objs::app, 1>(chunk,s);
		return app_wait_for_completion();
	}

	uint8_t app_install_begin()
	{
		putstr<objs::app,2>(0,"");
		return app_wait_for_completion();
	}

	uint8_t app_install_end()
	{
		putstr<objs::app,3>(0,"");
		return app_wait_for_completion();
	}

	uint8_t app_start()
	{
		putstr<objs::app,4>(0,"");
		return app_wait_for_completion();
	}

	uint8_t app_stop()
	{
		putstr<objs::app,5>(0,"");
		return app_wait_for_completion();
	}


	void memseek(uint32_t p)
	{ put<uint32_t, objs::memory, 0>(0,p); }

	uint32_t memtell()
	{ return get<uint32_t, objs::memory, 0>(0); }

	uint32_t memread(void *target, uint32_t size)
	{ 
		char *const t = reinterpret_cast<char*>(target);
		uint32_t s = 0;
		while(s < size)
		{
			const std::string x = getstr<objs::memory, 1>(0,size-s);
			if(x.size() == 0)
				return s;

			memcpy(&t[s],x.c_str(),x.size());
			s += x.size();
		}
		return s;
	}

	void memwrite(const void *source, uint32_t size)
	{
		char *const t = reinterpret_cast<char*>(const_cast<void*>(source));
		uint32_t s = 0;
		while(s < size)
		{
			putstr<objs::memory, 1>(0,std::string(&t[s],64));
			s += 64;
		}
	}

	void memexec()
	{ putstr<objs::memory,2>(0,std::string()); }

};
#endif
