CC=g++
CFLAGS= -g

PROCSRC=procA.cpp procB.cpp procC.cpp
PROCOBJS=$(patsubst %.cpp, %.o, $(PROCSRC))

_SRC=$(wildcard *.cpp)
SRC=$(filter-out $(PROCSRC), $(_SRC))
OBJS=$(patsubst %.cpp, %.o, $(SRC))

TARGET = procA procB procC

all: $(TARGET)

$(OBJS): %.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

$(PROCOBJS): %.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

procA: procA.o $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

procB: procB.o $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

procC: procC.o $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

clean:
	$(RM) lab *.o $(TARGET) /tmp/lab2.lock /tmp/procB.cache
