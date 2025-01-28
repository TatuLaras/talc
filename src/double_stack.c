#include "double_stack.h"

void double_stack_init(DoubleStack *stack) {
    stack->__size = DOUBLE_STACK_STARTING_SIZE;
    stack->__top = 0;
    stack->__array =
        (double *)malloc(sizeof(double) * DOUBLE_STACK_STARTING_SIZE);
}

void double_stack_push(DoubleStack *stack, double value) {
    if (stack->__top == stack->__size) {
        // Grow stack
        stack->__size *= 2;
        stack->__array =
            (double *)realloc(stack->__array, sizeof(double) * stack->__size);
    }

    stack->__array[stack->__top++] = value;
}

void double_stack_free(DoubleStack *stack) {
    if (stack->__array)
        free(stack->__array);

    stack->__array = 0;
    stack->__top = 0;
    stack->__size = 0;
}

int double_stack_peek_from_top(DoubleStack *stack, int n, double *out_symbol) {
    if (stack->__top - 1 < n || n < 0) {
        return 1;
    }

    *out_symbol = stack->__array[stack->__top - 1 - n];

    return 0;
}

int double_stack_get(DoubleStack *stack, int i, double *out_symbol) {
    if (i >= stack->__top || i < 0)
        return 1;

    *out_symbol = stack->__array[i];

    return 0;
}

int double_stack_pop(DoubleStack *stack, double *out_symbol) {
    if (stack->__top == 0) {
        return 1;
    }

    stack->__top--;

    if (out_symbol)
        *out_symbol = stack->__array[stack->__top];

    return 0;
}
