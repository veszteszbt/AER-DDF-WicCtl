all: wicctl wic_host

wicctl: wicctl.cc wicctl.h
	g++ -I. -std=c++14 -lusb-1.0 -o wicctl wicctl.cc

wic_host: wic_host.cc
	g++ -I. -g3 -std=c++14 -fdiagnostics-color -pthread -lmysqlcppconn -o wic_host wic_host.cc

clean:
	rm *.o wicctl wic_host 
	
