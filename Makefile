CC=gcc

all: main

main: main.o
	$(CC) main.o -o list_adder

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o
	rm list_adder 
