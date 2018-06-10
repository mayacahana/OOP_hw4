#compiler and flags
COMP = g++-5.3.0
OBJS = main.o
EXEC = ex4
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

#the make execution
$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

#rules
main.o: main.cpp GameBoard.h unit_test_util.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

#clean rule	
clean:
	rm -f $(OBJS) $(EXEC)