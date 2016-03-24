CCC = gcc -O2 -funroll-loops
CCCFLAGS = # -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-label

OBJ = utilities.o pnl.o helpers.o

pnl: $(OBJ)
	$(CCC) $(CCCFLAGS) -o pnl $(OBJ) $(CCCLNFLAGS)

clean:
	rm -f *.o *~ a.out core utilities pnl helpers

