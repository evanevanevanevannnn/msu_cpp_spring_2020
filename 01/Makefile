CC = g++

all: main

main.o: main.cpp main.h
	$(CC) -c main.cpp

main: main.o
	$(CC) -o main main.o

test: main
	python3 checker.py

run: main
	./main

clean:
	rm -rf *.o main