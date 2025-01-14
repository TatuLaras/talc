# TODO: Make dynamic with https://www.throwtheswitch.org/build/make
CC = gcc
CFLAGS = -Wall -ggdb

test:
	$(CC) $(CFLAGS) -o build/test_dynamic_array test_dynamic_array.c ../src/external/unity.c ../src/dynamic_array.c

run: test
	build/test_dynamic_array
