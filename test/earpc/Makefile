all: smoke_test heartbeat_test

smoke_test: smoke_test.cc
	g++ -g3 -std=c++17  -fdiagnostics-color -I../../ ../../journal.cc -pthread smoke_test.cc -o smoke_test

heartbeat_test: heartbeat_test.cc
	g++ -g3 -std=c++17  -fdiagnostics-color -I../../ ../../journal.cc -pthread heartbeat_test.cc -o heartbeat_test

name_test: name_test.cc
	g++ -O3 -std=c++17  -fdiagnostics-color -I../../ ../../journal.cc -pthread name_test.cc -o name_test
