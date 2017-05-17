all: wicctl

wicctl:
	g++ -I. -std=c++14 -lusb-1.0 -o wicctl wicctl.cc

