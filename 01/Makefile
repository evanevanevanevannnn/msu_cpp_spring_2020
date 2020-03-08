all: main

main.o: main.cpp main.h
	g++ -c main.cpp

main: main.o
	g++ -o main main.o

test: main
	python3 checker.py

clean:
	rm -rf *.o main