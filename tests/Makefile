#  TODO: Make dynamic with https://www.throwtheswitch.org/build/make
CC = gcc
CFLAGS = -Wall -ggdb

all: test_stack test_infix_to_postfix test_queue

test_stack: test_stack.c
	$(CC) $(CFLAGS) -o build/test_stack test_stack.c  ../src/external/unity.c ../src/stack.c

test_infix_to_postfix: test_infix_to_postfix.c
	$(CC) $(CFLAGS) -o build/test_infix_to_postfix test_infix_to_postfix.c  ../src/external/unity.c ../src/infix_to_postfix.c ../src/stack.c

test_queue: test_queue.c
	$(CC) $(CFLAGS) -o build/test_queue test_queue.c  ../src/external/unity.c ../src/queue.c ../src/stack.c

run: all
	build/test_stack
	build/test_infix_to_postfix
	build/test_queue
