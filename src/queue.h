#include "symbol.h"
#include <stdlib.h>
#include <strings.h>

#ifndef _QUEUE
#define _QUEUE

#define QUEUE_STARTING_SIZE 4

typedef struct {
    int __size;
    int __used;
    int __start;
    Symbol *__array;
} SymbolQueue;

// Initialize a queue
void queue_init(SymbolQueue *queue);

// Enqueue a value into the queue
void queue_enqueue(SymbolQueue *queue, Symbol value);

// Free memory used by the queue
void queue_free(SymbolQueue *queue);

// Dequeues element off the start of the queue
//
// Returns 1 if queue is empty
int queue_dequeue(SymbolQueue *queue, Symbol *out_symbol);

// Get the element n elements down from the end of the queue
//
// Returns 1 if n is out of bounds
// int queue_peek_from_top(SymbolQueue *queue, int n, Symbol *out_symbol);

#endif
