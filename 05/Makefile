all: test

bigint.o: bigint.cpp bigint.h
	g++ bigint.cpp -c

test_compile: test.cpp bigint.o
	g++ test.cpp bigint.o -o test

test: test_compile
	./test