#include "symbol.h"
#include <stdlib.h>
#include <strings.h>

#ifndef _STACK
#define _STACK

#define STACK_STARTING_SIZE 4

typedef struct {
    int __size;
    int __top;
    Symbol *__array;
} SymbolStack;

// Initialize a stack
void stack_init(SymbolStack *stack);

// Push a value into the stack
void stack_push(SymbolStack *stack, Symbol value);

// Free memory used by the stack
void stack_free(SymbolStack *stack);

// Pop element off the top of the stack
//
// Returns 1 if stack is empty
int stack_pop(SymbolStack *stack, Symbol *out_symbol);

// Get the element n elements down from the top of the stack
//
// Returns 1 if n is out of bounds
int stack_peek_from_top(SymbolStack *stack, int n, Symbol *out_symbol);

int stack_get(SymbolStack *stack, int i, Symbol *out_symbol);

#endif
