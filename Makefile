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
	g++-7 -I. -std=c++17 -lusb-1.0 -o wicctl wicctl.cc

%.o: %.cc
	g++-7 -DLOG_SQL -I. -g3 -std=c++17 -fdiagnostics-color -o $@ -c $<

wic_host: wic_host.o alsa_host.o journal.o sched/process.o command_line/shell.o command_line/functions.o command_line/parser/parse.o command_line/parser/semantics.o command_line/parser/symbol_table.o command_line/scanner/lex.o command_line/types/type.o
	g++-7 -I. -g3 -std=c++17 -fdiagnostics-color -o wic_host $^ $(LIBS)

clean:
	rm *.o wicctl wic_host 

else
ifeq ($(PLATFORM),WINDOWS)
	

all: wicctl wic_host


wicctl:
	$(error wicctl cannot be built for platform $(PLATFORM))

wic_host: wic_host.cc
	g++-7 -DLOG_SQL -I. \
	-I"C:\Program Files\MySQL\MySQL Connector C++ 1.1.9\include" \
	-g3 \
	-std=c++17 \
	-fdiagnostics-color \
	-pthread \
	-o wic_host wic_host.cc journal.cc sched/process.cc \
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
