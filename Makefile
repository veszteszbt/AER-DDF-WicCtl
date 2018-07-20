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

LIBS=-pthread -lmysqlcppconn -lasound -lsndfile -lavformat -lavcodec -lswresample -lswscale -lavutil -lm

all: wicctl wic_host

wicctl: wicctl.cc wicctl.h
	g++-7.2.0 -I. -std=c++17 -lusb-1.0 -o wicctl wicctl.cc

%.o: %.cc
	g++ -DLOG_SQL -I. -g3 -std=c++17 -fdiagnostics-color -o $@ -c $<

wic_host: wic_host.o alsa_host.o journal.o sched/process.o
	g++ -I. -g3 -std=c++17 -fdiagnostics-color -o wic_host wic_host.o alsa_host.o journal.o sched/process.o $(LIBS)

pair_test: pair_test_l pair_test_r

pair_test_l: pair_test_l.o journal.o sched/process.o
	g++ -I. -g3 -std=c++17 -fdiagnostics-color -o pair_test_l pair_test_l.o journal.o sched/process.o $(LIBS)

pair_test_r: pair_test_r.o journal.o sched/process.o
	g++ -I. -g3 -std=c++17 -fdiagnostics-color -o pair_test_r pair_test_r.o journal.o sched/process.o $(LIBS)

clean:
	rm *.o wicctl wic_host 

else
ifeq ($(PLATFORM),WINDOWS)
	

all: wicctl wic_host


wicctl:
	$(error wicctl cannot be built for platform $(PLATFORM))

wic_host: wic_host.cc
	g++ -DLOG_SQL -I. \
	-g3 \
	-std=c++17 \
	-fdiagnostics-color \
	-pthread \
	-o wic_host wic_host.cc journal.cc sched/process.cc \
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
