# specify the compiler
CC=gcc

# specify options for the compiler
CFLAGS=-c -Wall

all: pa

pa: noparallel.o thread.o

noparallel.o: noparallel.c
	$(CC) -g -o noparallel noparallel.c -lm

thread.o: thread.c
	$(CC) -g -pthread -o thread thread.c -lm

clean:
	rm -rf *o noparallel thread
