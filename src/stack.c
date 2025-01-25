#include "stack.h"
#include "symbol.h"

void stack_init(SymbolStack *stack) {
    stack->__size = STACK_STARTING_SIZE;
    stack->__top = 0;
    stack->__array = (Symbol *)malloc(sizeof(Symbol) * STACK_STARTING_SIZE);
}

void stack_push(SymbolStack *stack, Symbol value) {
    if (stack->__top == stack->__size) {
        // Grow stack
        stack->__size *= 2;
        stack->__array =
            (Symbol *)realloc(stack->__array, sizeof(Symbol) * stack->__size);
    }

    stack->__array[stack->__top++] = value;
}

void stack_free(SymbolStack *stack) {
    if (stack->__array)
        free(stack->__array);

    stack->__array = 0;
    stack->__top = 0;
    stack->__size = 0;
}

int stack_peek_from_top(SymbolStack *stack, int n, Symbol *out_symbol) {
    if (stack->__top - 1 < n || n < 0) {
        return 1;
    }

    *out_symbol = stack->__array[stack->__top - 1 - n];

    return 0;
}

int stack_pop(SymbolStack *stack, Symbol *out_symbol) {
    if (stack->__top == 0) {
        return 1;
    }

    stack->__top--;

    if (out_symbol)
        *out_symbol = stack->__array[stack->__top];

    return 0;
}
