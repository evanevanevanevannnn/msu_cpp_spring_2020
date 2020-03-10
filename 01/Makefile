CC = g++

all: test

allocator.o: allocator.cpp allocator.h
	$(CC) -c allocator.cpp

test: test.cpp allocator.o
	$(CC) -o test test.cpp allocator.o && ./test

clean:
	rm -rf *.o test