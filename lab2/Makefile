CC=g++
CFLAGS= -g

SRC=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRC))

all: lab

$(OBJS): %.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
lab: $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

clean:
	$(RM) lab $(OBJS)
