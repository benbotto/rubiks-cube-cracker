EXE = rubiksCube
CC = g++
FLAGS = -Wall -pedantic -std=c++0x
CFLAGS = -O4
LIBS =
INCS =

# Find all the .cpp files.
SOURCES:=$(shell find . -name '*.cpp' -not -path './lib/*')

# Replace .cpp with .d in source files.
DEPFILES:=$(SOURCES:.cpp=.d)

# All the object files.
OBJS:=$(SOURCES:.cpp=.o)

# The main target.
$(EXE): $(OBJS)
	$(CC) $(FLAGS) $(CFLAGS) $(INCS) -o $@ $(OBJS) $(LIBS)

-include $(DEPFILES)

# Perform the actual compilation.
%.o: %.cpp
	$(CC) $(FLAGS) $(CFLAGS) -MT '$@ $(@:.o=.d)' \
	-MMD -MF $(@:.o=.d) \
	$(INCS) \
	$< -c -o $@ \

clean:
	find . -name '*.d' -exec rm -f {} +
	find . -name '*.o' -exec rm -f {} +
	rm -f $(EXE)

