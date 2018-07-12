SOURCES=../../journal.cc ../../sched/process.cc

LIBS=-pthread -lmysqlcppconn -lasound -lsndfile -lavformat -lavcodec -lswresample -lswscale -lavutil -lm

all: wicctl wic_host

wicctl: wicctl.cc wicctl.h
	g++-7.2.0 -I. -std=c++14 -lusb-1.0 -o wicctl wicctl.cc

%.o: %.cc
	g++ -DLOG_SQL -I. -g3 -std=c++14 -fdiagnostics-color -o $@ -c $<

pair_test_a: pair_test_a.o journal.o sched/process.o
	g++ -I. -g3 -std=c++14 -fdiagnostics-color -o pair_test_a pair_test_a.o journal.o sched/process.o $(LIBS)

pair_test_b: pair_test_b.o journal.o sched/process.o
	g++ -I. -g3 -std=c++14 -fdiagnostics-color -o pair_test_b pair_test_b.o journal.o sched/process.o $(LIBS)

clean:
	rm *.o wicctl wic_host 