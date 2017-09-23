all: wicctl wic_host

wicctl: wicctl.cc wicctl.h
	g++ -I. -std=c++14 -lusb-1.0 -o wicctl wicctl.cc

%.o: %.cc %.h
	g++ -I. -g3 -std=c++14 -fdiagnostics-color -c $<

%.o: %.cc
	g++ -I. -g3 -std=c++14 -fdiagnostics-color -c $<

wic_host: wic_host.o alsa_host.o
	g++ -I. -g3 -std=c++14 -fdiagnostics-color -pthread -lmysqlcppconn -o wic_host wic_host.o alsa_host.o -lasound

clean:
	rm *.o wicctl wic_host 
	
