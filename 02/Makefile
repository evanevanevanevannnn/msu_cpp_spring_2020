all: test

parser.o: parser.cpp parser.h
	g++ parser.cpp parser.h -c -std=c++14

test: test.cpp parser.o
	g++ test.cpp parser.o -o test && ./test

clean:
	rm -rf test *.o