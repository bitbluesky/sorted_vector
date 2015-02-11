################################################################################
#
# Build script for project
#
################################################################################
#
# Makefile
#

# Define macros for name of compiler
CC	= cc

CFLAGS  = -g

PRGS 	= set_sorted_vector
SRCS 	= $(wildcard *.cpp) #$(wildcard formula/*.c) $(wildcard IS/*.cpp)\

OBJS	:= $(SRCS:.c=.o)  
OBJS    := $(OBJS:.cpp=.o) 

all:	$(PRGS)

set_sorted_vector:	$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS) $(LIBS) -lm -lstdc++ -static

clean:
	rm -f $(OBJS)
	rm -f $(PRGS)

# DO NOT DELETE
