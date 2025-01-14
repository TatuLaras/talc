# TODO: Make dynamic w/ https://www.throwtheswitch.org/build/make
CC = gcc
CFLAGS = -Wall

test:
	$(CC) $(CFLAGS) -o build/test1 test1.c ../src/testable.c ../src/external/unity.c

run: test
	build/test1
