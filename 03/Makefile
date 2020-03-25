all: test

matrix.o: matrix.cpp matrix.h
	g++ matrix.cpp -c

test_compile: matrix.o test.cpp
	g++ test.cpp matrix.o -o test

test: test_compile
	./test

clean:
	rm -rf test *.o