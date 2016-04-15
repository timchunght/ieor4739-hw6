gccopt= gcc -O2 -funroll-loops
gccdeb= gcc -ggdb -Wall -pedantic
CCC = $(gccdeb)

OS := $(shell uname)
ifeq ($(OS),Darwin)
  # Run MacOS commands
  GRB = /Library/gurobi651/mac64
else
	GRB = /opt/gurobi/gurobi650/linux64
  # check for Linux and run other commands
endif

#include
LPINCDIR = $(GRB)/include

#link
LIBS= -lm -lpthread 
GRBLNFLAGS = -L$(GRB)/lib -lgurobi65
CCCLNFLAGS = $(GRBLNFLAGS) $(LIBS)

#compilation flags: just the include libraries
CCCFLAGS = -I$(LPINCDIR) 

%.o: %.c
	@echo compiling $*.c with $(CCC) $(CCCFLAGS)
	@$(CCC) $(CCCFLAGS) -c $< -o $@

OBJ = utilities.o pnl.o helpers.o rebengine.o

pnl: $(OBJ)
	$(CCC) $(CCCFLAGS) -o pnl $(OBJ) $(CCCLNFLAGS)



clean:
	rm *.o pnl
