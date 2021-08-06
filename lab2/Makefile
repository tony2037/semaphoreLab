CC=g++
CFLAGS= -g

SRC=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRC))

TARGET = main

all: $(TARGET)

$(OBJS): %.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) lab *.o $(TARGET) /tmp/lab2.lock /tmp/procB.cache log
