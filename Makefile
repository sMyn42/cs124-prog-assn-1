CC = g++
 
# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -Wall -std=c++20

all: randmst

randmst: randmst.o minheap.o
	g++ -std=c++17 -o randmst randmst.o minheap.o

minheap.o: minheap.cc minheap.hh
	g++ -std=c++17 -c minheap.cc

randmst.o: randmst.cc
	g++ -std=c++17 -c randmst.cc