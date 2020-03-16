all: test

parser.o: parser.cpp parser.h
	g++ parser.cpp -c

test: test.cpp parser.o
	g++ test.cpp parser.o -o test && ./test

clean:
	rm -rf test *.o