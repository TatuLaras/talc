#  TODO: Make dynamic with https://www.throwtheswitch.org/build/make
CC = gcc
CUSTOM_FLAGS = 
CFLAGS = -Wall -ggdb -lm -DUNITY_INCLUDE_DOUBLE $(CUSTOM_FLAGS)

all: setup test_stack test_infix_to_postfix test_queue test_double_stack test_calculate test_variables test_ui_helpers test_results_buffer

setup:
	@mkdir -p build

test_double_stack: test_double_stack.c
	$(CC) $(CFLAGS) -o build/test_double_stack test_double_stack.c  ../src/external/unity.c ../src/double_stack.c

test_stack: test_stack.c
	$(CC) $(CFLAGS) -o build/test_stack test_stack.c  ../src/external/unity.c ../src/symbol_stack.c 

test_infix_to_postfix: test_infix_to_postfix.c
	$(CC) $(CFLAGS) -o build/test_infix_to_postfix test_infix_to_postfix.c  ../src/external/unity.c ../src/infix_to_postfix.c ../src/symbol_stack.c ../src/queue.c ../src/symbol.c ../src/variables.c

test_queue: test_queue.c
	$(CC) $(CFLAGS) -o build/test_queue test_queue.c  ../src/external/unity.c ../src/queue.c ../src/symbol_stack.c

test_calculate: test_calculate.c
	$(CC) $(CFLAGS) -o build/test_calculate test_calculate.c  ../src/external/unity.c ../src/calculate.c ../src/symbol_stack.c ../src/double_stack.c ../src/queue.c ../src/infix_to_postfix.c ../src/symbol.c ../src/variables.c

test_variables: test_variables.c
	$(CC) $(CFLAGS) -o build/test_variables test_variables.c  ../src/external/unity.c ../src/variables.c
	
test_ui_helpers: test_ui_helpers.c
	$(CC) $(CFLAGS) -o build/test_ui_helpers test_ui_helpers.c  ../src/external/unity.c ../src/ui_helpers.c ../src/variables.c ../src/symbol.c

test_results_buffer: test_results_buffer.c
	$(CC) $(CFLAGS) -o build/test_results_buffer test_results_buffer.c  ../src/external/unity.c ../src/results_buffer.c

run: all
	build/test_stack
	build/test_double_stack
	build/test_infix_to_postfix
	build/test_queue
	build/test_calculate
	build/test_variables
	build/test_ui_helpers
	build/test_results_buffer
