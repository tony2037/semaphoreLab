CC=gcc
CFLAGS= -g

SRC=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRC))

all: lab

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^
lab: $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

clean:
	$(RM) lab $(OBJS)
