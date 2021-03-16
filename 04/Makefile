all: test

test_compile: test.cpp serializer.h
	g++ test.cpp -o test

test: test_compile
	./test

clean:
	rm -rf *.o test