CC = g++
 
# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -Wall

all: randmst

randmst: randmst.o minheap.o
	g++ -o randmst randmst.o minheap.o

minheap.o: minheap.cc minheap.hh
	g++ -c minheap.cc

randmst.o: randmst.cc
	g++ -c randmst.cc