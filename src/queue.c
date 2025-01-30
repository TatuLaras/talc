#include "queue.h"
#include "symbol.h"

void queue_init(SymbolQueue *queue) {
    queue->__size = QUEUE_STARTING_SIZE;
    queue->__start = 0;
    queue->__used = 0;
    queue->__array = (Symbol *)malloc(sizeof(Symbol) * QUEUE_STARTING_SIZE);
}

void queue_enqueue(SymbolQueue *queue, Symbol value) {
    if (queue->__used == queue->__size) {
        // Grow array
        queue->__size *= 2;
        queue->__array =
            (Symbol *)realloc(queue->__array, sizeof(Symbol) * queue->__size);
    }

    queue->__array[queue->__used++] = value;
}

void queue_free(SymbolQueue *queue) {
    if (queue->__array)
        free(queue->__array);

    queue->__array = 0;
    queue->__used = 0;
    queue->__start = 0;
    queue->__size = 0;
}

int queue_peek_from_back(SymbolQueue *stack, int n, Symbol *out_symbol) {
    if (stack->__used - 1 < n || n < 0) {
        return 1;
    }

    *out_symbol = stack->__array[stack->__used - 1 - n];

    return 0;
}

int queue_dequeue(SymbolQueue *queue, Symbol *out_symbol) {
    if (queue->__used == 0 || queue->__start >= queue->__used) {
        return 1;
    }

    if (out_symbol)
        *out_symbol = queue->__array[queue->__start];

    queue->__start++;

    return 0;
}
