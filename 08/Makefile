CC=g++
FLAG=-std=c++17

test: pool
	./pool

pool: main.o
	$(CC) $(FLAG) -pthread -o pool main.o

main.o: main.cpp threadpool.h
	$(CC) $(FLAG) -c main.cpp

clean:
	rm -rf *.o pool