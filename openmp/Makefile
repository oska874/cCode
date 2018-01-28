
CC = gcc
CXX = g++

CFLAGS = -fopenmp 
CFLAG_BACK = -lm

LIB_FILE = opmp0.o
EXE_FILE = opmptest

all:OPENMP_TEST
	$(CC) $(CFLAGS) -o $(EXE_FILE) $(LIB_FILE) $(CFLAG_BACK)

OPENMP_TEST: $(LIB_FILE)

clean:
	rm *.[oa]
	rm opmptest


%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<
