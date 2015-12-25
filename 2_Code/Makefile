# Makefile for compiling and creating the executable app
# Author: Archit Gupta, Nehal Bhandari
# Date December 24, 2015

# Definitions (Compiler, flags, optimizations etc.)

CC	= g++

LIBFLAGS = -lncurses
LDFLAGS += $(LIBFLAGS)

# Library flags required for compilation. In this
# case, the ncurses library is required

CCFLAGS =

C_SRCS = $(wildcard *.cc)

# The wildcard function picks up all the files that end with the .cc extension
# and puts them together in a data structure. We are using this to tell the
# makefile that out final executable depends on all the .o files. These files
# will, in turn, be generated from the .cc files. Gathering the .cc files
# together here

OBJS = $(patsubst %.cc, %.o, $(C_SRCS))

# The patsubst function substitutes the .cc pattern with .o in the $(C_SRCS)
# that we had previously generated. We can now say that the final executable
# depends on $(OBJS) variable

todo-list: $(OBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $+

%.o:%.cc
	$(CC) $(CCFLAGS) -c -o $@ $<
									# The -c option prevents the linker from
									# linking the code. As a result of this,
									# we don't have to provide the ncurses
									# library at compile time

pristine:
	rm -f todo-list
	rm -f *.o

clean:
	rm -f *.o
