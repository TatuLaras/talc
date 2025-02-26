#include "double_stack.h"

void double_stack_init(DoubleStack *stack) {
    stack->_size = DOUBLE_STACK_STARTING_SIZE;
    stack->top = 0;
    stack->_array =
        (double *)malloc(sizeof(double) * DOUBLE_STACK_STARTING_SIZE);
}

void double_stack_push(DoubleStack *stack, double value) {
    if (stack->top == stack->_size) {
        // Grow stack
        stack->_size *= 2;
        stack->_array =
            (double *)realloc(stack->_array, sizeof(double) * stack->_size);
    }

    stack->_array[stack->top++] = value;
}

void double_stack_free(DoubleStack *stack) {
    if (stack->_array)
        free(stack->_array);

    stack->_array = 0;
    stack->top = 0;
    stack->_size = 0;
}

int double_stack_peek_from_top(DoubleStack *stack, int n, double *out_symbol) {
    if (stack->top - 1 < n || n < 0) {
        return 1;
    }

    *out_symbol = stack->_array[stack->top - 1 - n];

    return 0;
}

int double_stack_pop(DoubleStack *stack, double *out_symbol) {
    if (stack->top == 0) {
        return 1;
    }

    stack->top--;

    if (out_symbol)
        *out_symbol = stack->_array[stack->top];

    return 0;
}
