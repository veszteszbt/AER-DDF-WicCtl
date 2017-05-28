#ifndef WICCTL_H
# define WICCTL_H
# include <iostream>
# include <cstring>
# include <string>
# include <cstdio>
# include <error.h>
# include <unistd.h>
# include <libusb-1.0/libusb.h>

class wicctl
{
	libusb_device_handle *devh;

	template<uint8_t tObj, uint16_t tFn>
	void invoke()
	{
		int size = libusb_control_transfer(
			devh,
			0x0,
			0x80+tObj,
			tFn,
			0,
			0,
			0,5000
		);

		if(size < 0)
			throw -size;
	}

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
			if(result < 0)
				throw -result;
			else
				throw EPROTO;

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

		if(size < 0)
			throw -size;
	}

	char buf[65536];

	template<uint8_t tObj, uint16_t tFn>
	std::string getstr(uint16_t index=0,uint16_t size=1024)
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

		if(size < 0)
			throw -size;

		return std::string(buf,s);
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

		if(size < 0)
			throw -size;
		else if(!size && value.size())
			throw ECOMM;
	}


	uint8_t app_state()
	{ return get<uint8_t,objs::app,0>(0); }

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
			throw EHOSTUNREACH;

		libusb_detach_kernel_driver(devh, 0);
		libusb_claim_interface(devh, 0);
	}

	wicctl()
	{
		libusb_init(0);
		devh = libusb_open_device_with_vid_pid(0, 0x1234, 0x5678);
		if(!devh)
			throw errno;

		libusb_detach_kernel_driver(devh, 0);
		libusb_claim_interface(devh, 0);
	}

	~wicctl()
	{
		libusb_close(devh);
		libusb_exit(0);
	}

	/*! Returns the version number of the host application installed on the WIC */
	uint32_t system_version()
	{ return get<uint32_t, objs::system, 0>(0); }

	/*! Returns the generally unique serial number of the processor in the WIC */
	uint64_t system_serial()
	{ return get<uint64_t, objs::system, 1>(0); }


	/*! Returns the hostname of the WIC */
	std::string network_hostname()
	{ return getstr<objs::network, 0>(0); }

	/*! Sets the hostname of the WIC */
	void network_hostname(const std::string &v)
	{ putstr<objs::network, 0>(0,v); }


	/*! Returns the SSID which the WIC connects to when available */
	std::string network_ssid()
	{ return getstr<objs::network, 1>(0); }

	/*! Sets the SSID which the WIC shall try to connect to */
	void network_ssid(const std::string &v)
	{ putstr<objs::network, 1>(0,v); }

	/*! Returns the security key which the WIC uses in order to connect to the specified network */
	std::string network_psk()
	{ return getstr<objs::network, 3>(0); }

	/*! Sets the security key which the WIC uses in order to connect to the specified network */
	void network_psk(const std::string &v)
	{ putstr<objs::network, 3>(0,v); }

	uint32_t network_own_ip()
	{ return get<uint32_t, objs::network, 4>(0); }

	void network_own_ip(uint32_t v)
	{ return put<uint32_t, objs::network, 4>(0,v); }

	uint32_t network_server_ip()
	{ return get<uint32_t, objs::network, 5>(0); }

	void network_server_ip(uint32_t v)
	{ return put<uint32_t, objs::network, 5>(0,v); }


	/*! Persists all the configuration modifications */
	void config_save()
	{ getstr<objs::system, 0x100>(0); }

	/*! Initiates uninstallation of currently installed WIC client app */
	uint8_t app_uninstall()
	{
		invoke<objs::app,0>();
		return app_wait_for_completion();
	}

	/*! Returns whether client application is currently running */
	bool app_running()
	{ return get<uint8_t,objs::app,1>(0); }

	/* Returns the number of 64-byte chunks the WIC application space contains. */
	uint16_t app_chunk_count()
	{ throw EOPNOTSUPP; }

	/*! Writes the specified chunk of data to the specified position WIC application space.
	 *  Chunk size must always be nonzero and less than or equal to 64 bytes, as this is the chunk size. Invocations with
	 *  chunk index greater or equal to chunk_count()'s return value will result in an invalid argument error.
	 */
	uint8_t app_install_chunk(uint16_t chunk, const std::string &s)
	{
		putstr<objs::app, 1>(chunk,s);
		return app_wait_for_completion();
	}

	/*! Begins the app installation process, which provides the ability to install application
	 *  chunks into the application space of the WIC.
	 */
	uint8_t app_install_begin()
	{
		invoke<objs::app,2>();
		return app_wait_for_completion();
	}

	/*! Ends the app installation process and returns a value indicating the outcome of the installation. */
	uint8_t app_install_end()
	{
		invoke<objs::app,3>();
		return app_wait_for_completion();
	}

	/*! Start the previously installed client application */
	uint8_t app_start()
	{
		invoke<objs::app,4>();
		return app_wait_for_completion();
	}

	/*! Stops the previously started client application */
	uint8_t app_stop()
	{
		invoke<objs::app,5>();
		return app_wait_for_completion();
	}

	std::string app_name()
	{ return getstr<objs::app, 3>(); }

	uint32_t app_version()
	{ return get<uint32_t, objs::app, 4>(0); }


	/*! Set the memory pointer to the specified value */
	void memory_seek(uint32_t p)
	{ put<uint32_t, objs::memory, 0>(0,p); }

	/*! Returns the value of the memory pointer */
	uint32_t memory_tell()
	{ return get<uint32_t, objs::memory, 0>(0); }

	/*! Reads the specified number of bytes into the specified target buffer, starting from the current value of memory
	 *  pointer, and increments it with the number of bytes eventually read. The number of bytes actually read is returned.
	 */
	uint32_t memory_read(void *target, uint32_t size)
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

	/*! Writes the specified number of bytes from the specified source buffer to the application space of the WIC, starting
	 *  from the current value of memory pointer, and increments it with the number of bytes eventually read. The number of
	 *  bytes actually read is returned.
	 */
	void memory_write(const void *source, uint32_t size)
	{
		char *const t = reinterpret_cast<char*>(const_cast<void*>(source));
		uint32_t s = 0;
		while(s < size)
		{
			putstr<objs::memory, 1>(0,std::string(&t[s],64));
			s += 64;
		}
	}

	void memory_exec()
	{ putstr<objs::memory,2>(0,std::string()); }

};
#endif
