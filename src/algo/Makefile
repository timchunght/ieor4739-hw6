# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------

gccopt= gcc -O2 -funroll-loops
gccdeb= gcc -ggdb -Wall -pedantic
CCC = $(gccdeb)

#link
LIBS= -lm -lpthread 
CCCLNFLAGS = $(LIBS)

../bin/%.o: %.c
	@echo compiling $*.c with $(CCC) $(CCCFLAGS)
	@$(CCC) $(CCCFLAGS) -c $< -o $@

TIM = ../bin/tim_main.o ../bin/tim.o

tim: $(TIM)
	$(CCC) $(CCCFLAGS) -o ../bin/tim $(TIM) $(CCCLNFLAGS)

clean:
	rm ../bin/*

sweep:
	rm *~
	rm *#
