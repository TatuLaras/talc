#  TODO: Make dynamic with https://www.throwtheswitch.org/build/make
CC = gcc
CFLAGS = -Wall -ggdb

all: test_stack test_lexer

test_stack: test_stack.c
	$(CC) $(CFLAGS) -o build/test_stack test_stack.c  ../src/external/unity.c ../src/stack.c

test_lexer: test_lexer.c
	$(CC) $(CFLAGS) -o build/test_lexer test_lexer.c  ../src/external/unity.c ../src/lexer.c ../src/stack.c

run: all
	build/test_stack
	build/test_lexer
