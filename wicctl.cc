#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <errno.h>
#include <error.h>
#include "wicctl.h"
namespace
{
	bool assert_rdonly(const std::string &property, int argc)
	{
		if(argc == 4)
		{
			std::cerr << "wicctl: \e[31;01merror:\e[0m property `" << property << "' is read-only" << std::endl;
			return false;;
		}
		return true;
	}

	void unknown_property(const std::string &property)
	{ std::cerr << "wicctl: \e[31;01merror:\e[0m unknown property `" << property << "'" << std::endl; }

	void unknown_function(const std::string &property)
	{ std::cerr << "wicctl: \e[31;01merror:\e[0m unknown function `" << property << "'" << std::endl; }

	void print_version(uint32_t v)
	{
		union
		{
			uint32_t value;
			uint8_t bits[4];
		} ver;
		ver.value = v;
		std::cout << std::dec <<
			(int)ver.bits[3] << '.' <<
			(int)ver.bits[2] << '.' <<
			(int)ver.bits[1] << std::endl
		;
	
	}
}



int main(int argc, char **argv)
{

	if(argc < 3 || argc > 4)
	{
		std::cerr << "usage: wicctl <submodule> <property> [value]" << std::endl;
		return 0;
	}

	wicctl *w;

	try { w = new wicctl(); }
	catch(int i)
	{
		std::cerr << "wicctl: \e[31;01merror:\e[0m could not connect to device: ";
		switch(i)
		{
			case 0:
				std::cerr << strerror(ENODEV) << std::endl;
				break;

			default:
				std::cerr << strerror(i) << std::endl; 
				break;
		}
		return 1;
	}
	
	const std::string submodule = argv[1];

	const std::string property = argv[2];

	try
	{
		
		if(submodule == "config")
			if(property == "save")
				w->config_save();
			else 
			{
				unknown_property(property);
				return 1;
			}
				

		else if(submodule == "system")
			if(property == "serial")
				if(!assert_rdonly(property,argc))
					return 1;
				else
					std::cout << std::hex << w->system_serial() << std::endl;

			else if(property == "version")
				if(!assert_rdonly(property,argc))
					return 1;
				else
					print_version(w->system_version());
			else 
			{
				unknown_property(property);
				return 1;
			}
		
		else if(submodule == "network")
			if(property == "ssid")
				if(argc==4)
					w->network_ssid(argv[3]);
				else
					std::cout << w->network_ssid() << std::endl;
			else if(property == "hostname")
				if(argc==4)
					w->network_hostname(argv[3]);
				else
					std::cout << w->network_hostname() << std::endl;

			else if(property == "psk")
				if(argc==4)
				{
					const std::string vs = argv[3];
					std::string v(vs.size()/2+(vs.size()%2),'\000');
					for(int i = 0; i < vs.size(); ++i)
					{
						const int j = i>>1;
						v[j]<<=4;
						if(vs[i] >= '0' && vs[i] <= '9')
							v[j] += vs[i]-'0';
						else if(vs[i] >= 'A' && vs[i] <='F')
							v[j] += (uint8_t)vs[i]-'A'+10;
						else if(vs[i] >= 'a' && vs[i] <='f')
							v[j] += (uint8_t)vs[i]-'a'+10;
						else
						{
							std::cerr << "wicctl: \e[31;01merror:\e[0m invalid character `" <<
								vs[i] << "' in PSK" << std::endl;
							return 1;
						}
					}
					w->network_psk(v);
				}
				else
				{
					const std::string psk = w->network_psk();
					printf("%02x",(unsigned)psk[0]&0xff);
					for(int i = 1; i < psk.size(); ++i)
						printf("%02x",(unsigned)psk[i]&0xff);
					std::cout << std::endl;
				}

			else if(property == "own_ip" || property == "server_ip")
			{
				if(argc==4)
				{
					uint32_t ip = 0;
					uint32_t cur = 0;
					uint8_t cnt = 0;
					const std::string vs = argv[3];
					for(int i = 0; i < vs.size(); ++i)
					{
						if(vs[i] >= '0' && vs[i] <= '9')
						{
							cur *= 10;
							cur += vs[i]-'0';
						}
						else if(vs[i]=='.')
						{
							if(cur > 255)
							{
								std::cerr << "wicctl: \e[31;01merror:\e[0m invalid value `" <<
									cur << "' in IP address" << std::endl;
								return 1;
							
							}
							ip += cur<<(cnt*8);
							if(cnt++ > 3)
							{
								std::cerr << "wicctl: \e[31;01merror:\e[0m too many segments"
									" in IP address" << std::endl;
								return 1;
							
							}

							cur = 0;
						}
						else
						{
							std::cerr << "wicctl: \e[31;01merror:\e[0m invalid character `" <<
								vs[i] << "' in IP address" << std::endl;
							return 1;
						}
					}
					if(cur > 255)
					{
						std::cerr << "wicctl: \e[31;01merror:\e[0m invalid value `" <<
							cur << "' in IP address" << std::endl;
						return 1;
					
					}
					if(cnt> 3)
					{
						std::cerr << "wicctl: \e[31;01merror:\e[0m too many segments"
							" in IP address" << std::endl;
						return 1;
					
					}
					ip += cur<<24;

					if(property == "own_ip")
						w->network_own_ip(ip);
					else if(property == "server_ip")
						w->network_server_ip(ip);
				}
				
				else
				{
					uint32_t ip;
					if(property == "own_ip")
						ip = w->network_own_ip();
					else if(property == "server_ip")
						ip = w->network_server_ip();

					std::cout << std::dec;
					for(int i = 0; i < 3; ++i)
						std::cout << ((ip >> (i*8)) & 0xff) << '.';

					std::cout << ((ip>>24)&0xff) << std::endl;
				}
			}
			else 
			{
				unknown_property(property);
				return 1;
			}
		
		else if(submodule == "app")
		{
			if(property == "start")
				if(argc > 3)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m too many arguments" << std::endl;
					return 1;
				}
				else
				{
					const uint8_t s = w->app_start();
					if(s)
					{
						std::cerr
							<< "wicctl: \e[31;01merror:\e[0m "
							<< strerror(s) << std::endl;
						return 1;
					}
				}

			else if(property == "stop")
				if(argc > 3)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m too many arguments" << std::endl;
					return 1;
				}
				else
				{
					const uint8_t s = w->app_stop();
					if(s)
					{
						std::cerr
							<< "wicctl: \e[31;01merror:\e[0m "
							<< strerror(s) << std::endl;
						return 1;
					}
				
				}

			else if(property == "uninstall")
				if(argc > 3)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m too many arguments" << std::endl;
					return 1;
				}

				else
				{
					const uint8_t s = w->app_uninstall();
					if(s)
					{
						std::cerr
							<< "wicctl: \e[31;01merror:\e[0m "
							<< strerror(s) << std::endl;
						return 1;
					}
				}


			else if(property == "install")
			{
				if(argc < 4)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m file argument expected" << std::endl;
					return 1;
				}

				std::ifstream fin;
				fin.open(argv[3]);
				if(!fin)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m unable to open file: " << strerror(errno) << std::endl;
					return 1;
				}

				uint8_t s = w->app_install_begin();
				if(s && s != EALREADY)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m " << strerror(s) << std::endl;
					return 1;
				}

				int idx = 0;

				fin.seekg(0,fin.end);
				const size_t app_size = fin.tellg();
				fin.seekg(0,fin.beg);
				std::cout << "\e[s";
				std::cout.flush();

				while(!fin.eof() && fin.good())
				{
					char buf[64];
					fin.read(buf,64);
					int l = fin.gcount();
					if(l<=0)
					{
						if(fin.eof())
							break;
						std::cerr << "wicctl: \e[31;01merror:\e[0m error reading file: " << strerror(errno) << std::endl;
						return 1;
					}

					uint8_t retry = 0;
					s = w->app_install_chunk(idx,std::string(buf,64));
					while(s)
					{
						if(s == EIO)
						{
							if(retry++ > 10)
							{
								std::cerr << "wicctl: \e[31;01merror:\e[0m too many chunk errors; giving up" << std::endl;
								return 1;
							}
							std::cerr << "\e[31;01m - \e[0mchunk error" << std::endl;
							usleep(20000);
							s = w->app_install_chunk(idx,std::string(buf,64));
							continue;
						}
						
						else
						{
							std::cerr << "wicctl: \e[31;01merror:\e[0m " << strerror(s) << std::endl;
							return 1;
						}
					}
					++idx;
					std::cout << "\e[u" << 6400*idx/app_size << "%\e[K";
					std::cout.flush();
				}
				
				s = w->app_install_end();	
				if(s)
				{
					std::cerr << "\e[uwicctl: \e[31;01merror:\e[0m " << strerror(s) << std::endl;
					return 1;
				}
				else
					std::cout << "\e[u100%\e[32;01m - \e[0mdone\e[K" << std::endl;
				return 0;
			}
			else if(property == "uninstall")
			{
				if(argc > 3)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m too many arguments" << std::endl;
					return 1;
				}

				const uint8_t s = w->app_uninstall();
				if(s)	
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m " << strerror(s) << std::endl;
					return 1;
				}
			}
			else if(property == "name")
			{
				if(argc > 3)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m too many arguments" << std::endl;
					return 1;
				}

				const std::string v = w->app_name();
				if(!v.size())
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m " << strerror(ENOENT) << std::endl;
					return 1;
				}
					
				std::cout << v << std::endl;
			}
			else if(property == "version")
			{
				if(argc > 3)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m too many arguments" << std::endl;
					return 1;
				}

				const uint32_t v = w->app_version();
				if(!v)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m " << strerror(ENOENT) << std::endl;
					return 1;
				}

				print_version(v);
			}

			else
			{
				unknown_function(property);
				return 1;
			}

		}

		else if(submodule == "memory")
			if(property == "seek")
				if(argc==4)
				{
					std::stringstream ss;
					const std::string address(argv[3]);
					if(address.size() >= 2 && address[0] == '0' && address[1] == 'x')
					{
						ss << std::hex;
						ss << &argv[3][2];
					}
					else
					{
						ss << std::dec;
						ss << argv[3];
					}
					uint32_t v;
					ss >> v;
					w->memory_seek(v);
				}

				else
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m memory address argument expected" << std::endl;
					return 1;
				}
			else if(property == "tell")
				if(argc==4)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m excess number of arguments" << std::endl;
					return 1;
				}
				else
					std::cout << "0x" << std::hex << w->memory_tell() << std::endl;
			else if(property == "read")
				if(argc==4)
				{
					const uint32_t s = atoi(argv[3]);
					char *x = new char[s];
					const uint32_t i = w->memory_read(x,s);
					std::cout.write(x,i);
					std::cout.flush();
					delete x;
				}

				else
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m size argument expected" << std::endl;
					return 1;
				}
			else if(property == "write")
				if(argc==4)
				{
					const std::string data(argv[3]);
					w->memory_write(data.c_str(),data.size());
				}
				else
				{
					char buf[64];
					while(std::cin.good() && !std::cin.eof() && !std::cin.fail())
					{
						std::cin.read(buf,64);
						const int i = std::cin.gcount();
						if(!i)
							break;
						w->memory_write(buf,i);
					}
					return 0;
				}
			else if(property == "exec")
				if(argc==4)
				{
					std::cerr << "wicctl: \e[31;01merror:\e[0m excess number of arguments" << std::endl;
					return 1;
				}
				else
					w->memory_exec();
			else 
			{
				unknown_function(property);
				return 1;
			}
		

		else
		{
			std::cerr << "wicctl: \e[31;01merror:\e[0m unknown submodule `" << submodule << "'" << std::endl;
			return 1;
		}
	}
	catch(int e)
	{
		std::cerr << "wicctl: \e[31;01mfatal error:\e[0m ";
		switch(e)
		{
			case E2BIG:
				std::cerr << "IO error" << std::endl;
				break; 
			default:
				std::cerr << strerror(e) << std::endl;
				break;
		}
	}
	return 0;
}
