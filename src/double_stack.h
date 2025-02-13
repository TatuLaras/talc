#include <stdlib.h>
#include <strings.h>

#ifndef _DOUBLE_STACK
#define _DOUBLE_STACK

#define DOUBLE_STACK_STARTING_SIZE 4

typedef struct {
    int _size;
    int top;
    double *_array;
} DoubleStack;

// Initialize a stack
void double_stack_init(DoubleStack *stack);

// Push a value into the stack
void double_stack_push(DoubleStack *stack, double value);

// Free memory used by the stack
void double_stack_free(DoubleStack *stack);

// Pop element off the top of the stack
//
// Returns 1 if stack is empty
int double_stack_pop(DoubleStack *stack, double *out_element);

// Get the element n elements down from the top of the stack
//
// Returns 1 if n is out of bounds
int double_stack_peek_from_top(DoubleStack *stack, int n, double *out_element);

int double_stack_get(DoubleStack *stack, int i, double *out_element);

#endif
