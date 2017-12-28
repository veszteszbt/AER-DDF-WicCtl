all: smoke_test heartbeat_test

smoke_test: smoke_test.cc
	g++ -g3 -std=c++17  -fdiagnostics-color -I../../ ../../journal.cc -pthread smoke_test.cc -o smoke_test

heartbeat_test: heartbeat_test.cc
	g++ -g3 -std=c++17  -fdiagnostics-color -I../../ ../../{journal,sched/process}.cc -pthread heartbeat_test.cc -o heartbeat_test

pair_test: pair_test_a pair_test_b

pair_test_a: pair_test_a.cc
	g++-7.2.0 -O3 -std=c++17  -fdiagnostics-color -I../../ ../../{journal,sched/process}.cc -pthread $@.cc -o $@

pair_test_b: pair_test_b.cc
	g++-7.2.0 -O3 -std=c++17  -fdiagnostics-color -I../../ ../../{journal,sched/process}.cc -pthread $@.cc -o $@

name_test: name_test.cc
	g++ -O3 -std=c++17  -fdiagnostics-color -I../../ ../../{journal,sched/process}.cc -pthread name_test.cc -o name_test

ts: ts.cc
	g++ -O3 -std=c++17  -fdiagnostics-color -I../../ ../../journal.cc -pthread ts.cc -o ts
