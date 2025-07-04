FLAGS = -Wall -pedantic -lSDL2

CC = gcc

all: *.c *.h
	$(CC) -o execSDL.out $? $(FLAGS)

memory-test:
	valgrind -s ./execSDL.out
