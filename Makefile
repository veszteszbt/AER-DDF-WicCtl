ifeq ($(OS),Windows_NT)
   PLATFORM=WINDOWS
else
   _UNAME=$(shell uname -s)
   ifeq ($(_UNAME),Linux)
      PLATFORM=LINUX
   endif
   ifeq ($(_UNAME),Darwin)
      PLATFORM=OSX
   endif
endif


ifeq ($(PLATFORM),LINUX)

all: wicctl wic_host

wicctl: wicctl.cc wicctl.h
	g++ -I. -std=c++14 -lusb-1.0 -o wicctl wicctl.cc

%.o: %.cc %.h
	g++ -I. -g3 -std=c++14 -fdiagnostics-color -c $<

%.o: %.cc
	g++ -DLOG_SQL -I. -g3 -std=c++14 -fdiagnostics-color -c $<

wic_host: wic_host.o alsa_host.o
	g++ -g3 -std=c++14 -fdiagnostics-color -o wic_host wic_host.o alsa_host.o -lasound -lsndfile -pthread -lmysqlcppconn

clean:
	rm *.o wicctl wic_host 

else
ifeq ($(PLATFORM),WINDOWS)
	

all: wicctl wic_host


wicctl:
	$(error wicctl cannot be built for platform $(PLATFORM))

wic_host: wic_host.cc
	g++ -DLOG_SQL -I. \
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
	rm *.o *.exe
else
wicctl:
	$(error wicctl cannot be built for platform $(PLATFORM))

wic_host:
	$(error wic host cannot be built for platform $(PLATFORM))
endif
endif	
