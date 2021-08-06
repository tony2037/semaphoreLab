CC=gcc
CFLAGS= -g

all: proc1 proc2
proc1: proc1.c semaphore.c
	$(CC) $(CFLAGS) -o $@ $^
proc2: proc2.c semaphore.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) proc1 proc2
