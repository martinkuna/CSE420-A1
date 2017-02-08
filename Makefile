# Basic makefile for ASU projects
# Martin Kuna
# ASUID: 1206459510

#Program Names	-- CHECK_CLOCKS is a seperate program used to test clock resolution
PROGRAM_NAME=prog
CHECK_CLOCKS=check_system_clocks

#Compiler & Flags & Libraries
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lrt

#Source files under src directory
SOURCES = ./src/main.c

#Object files from .c sources
OBJS = $(SOURCES:.c=.o)

.PHONY:all
all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(OBJS) $(LIBS)


clock: $(CHECK_CLOCKS)

$(CHECK_CLOCKS):
	$(CC) $(CFLAGS) -o $(CHECK_CLOCKS) ./src/test_progs/checkclocks.c

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM_NAME) $(CHECK_CLOCKS)
	@echo rm -f $(OBJS)
	@echo rm -f $(PROGRAM_NAME) $(CHECK_CLOCKS)
