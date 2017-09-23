all: wicctl wic_host

wicctl: wicctl.cc wicctl.h
	g++ -I. -std=c++14 -lusb-1.0 -o wicctl wicctl.cc

wic_host: wic_host.cc
	g++ -I. \
	-I"C:\Program Files\MySQL\MySQL Connector C++ 1.1.9\include" \
	-g3 \
	-std=c++14 \
	-fdiagnostics-color \
	-pthread \
	-o wic_host wic_host.cc \
	-L"C:\Program Files\MySQL\MySQL Connector C++ 1.1.9\lib\opt" \
	-lmysqlcppconn \
	-lwsock32 \
	-lws2_32 \
	-lgdi32 \
	-ladvapi32 \
	-liphlpapi \
	-lpsapi \
	-lshell32
	

clean:
	rm *.o wicctl wic_host 
