all: test

parser.o: parser.cpp parser.h
	g++ parser.cpp -c

compileTest: safe_test.cpp parser.o
	g++ safe_test.cpp parser.o -o test

test: compileTest
	./test

clean:
	rm -rf test *.o