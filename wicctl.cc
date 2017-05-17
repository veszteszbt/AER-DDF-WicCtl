#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <errno.h>
#include <error.h>
#include "wicctl.h"

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

int main(int argc, char **argv)
{

	if(argc < 3 || argc > 4)
	{
		std::cerr << "usage: wicctl <submodule> <property> [value]" << std::endl;
		return 0;
	}

	wicctl *ww;
	try {
		ww = new wicctl();
	} catch(int i)
	{
		std::cerr << "wicctl: \e[31;01merror:\e[0m could not connect to device" << std::endl; 
		return 1;
	}
	wicctl &w = *ww;

	
	const std::string submodule = argv[1];
	const std::string property = argv[2];
	
	if(submodule == "config")
		if(property == "save")
			w.save();
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
				std::cout << std::hex << w.serial() << std::endl;

		else if(property == "version")
			if(!assert_rdonly(property,argc))
				return 1;
			else
				std::cout << std::hex << w.version() << std::endl;
		else 
		{
			unknown_property(property);
			return 1;
		}
	
	else if(submodule == "network")
		if(property == "ssid")
			if(argc==4)
				w.ssid(argv[3]);
			else
				std::cout << w.ssid() << std::endl;
		else if(property == "hostname")
			if(argc==4)
				w.hostname(argv[3]);
			else
				std::cout << w.hostname() << std::endl;

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
						std::cerr << "wicctl: \e[31;01merror:\e[0m invalid character `"<<vs[i]<<"' in PSK" << std::endl;
						return 1;
					}
				}
				w.psk(v);
			}
			else
			{
				const std::string psk = w.psk();
				printf("%02x",(unsigned)psk[0]&0xff);
				for(int i = 1; i < psk.size(); ++i)
				{
					//if(!(i&0xf))
					//	std::cout << std::endl;
					printf("%02x",(unsigned)psk[i]&0xff);
				}
//				if((psk.size()-1)&0xf)
					std::cout << std::endl;
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
				const uint8_t s = w.app_start();
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
				const uint8_t s = w.app_stop();
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
				const uint8_t s = w.app_uninstall();
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

			uint8_t s = w.app_install_begin();
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
				s = w.app_install_chunk(idx,std::string(buf,64));
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
						s = w.app_install_chunk(idx,std::string(buf,64));
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
			
			s = w.app_install_end();	
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
			const uint8_t s = w.app_uninstall();
			if(s)	
			{
				std::cerr << "wicctl: \e[31;01merror:\e[0m " << strerror(s) << std::endl;
				return 1;
			}
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
				w.memseek(v);
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
				std::cout << "0x" << std::hex << w.memtell() << std::endl;
		else if(property == "read")
			if(argc==4)
			{
				const uint32_t s = atoi(argv[3]);
				char *x = new char[s];
				const uint32_t i = w.memread(x,s);
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
				w.memwrite(data.c_str(),data.size());
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
					w.memwrite(buf,i);
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
				w.memexec();


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

	return 0;
}
