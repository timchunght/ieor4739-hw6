

CC  = gcc
CXX = g++

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)


default: pnl

pnl: pnl.o

pnl.o: utilities.o

utilities.o: utilities.c

clean:
	rm -f *.o *~ a.out core utilities pnl

all: clean default
