#include "queue.h"
#include "symbol.h"

void queue_init(SymbolQueue *queue) {
    queue->_size = QUEUE_STARTING_SIZE;
    queue->_start = 0;
    queue->_used = 0;
    queue->_array = (Symbol *)malloc(sizeof(Symbol) * QUEUE_STARTING_SIZE);
}

void queue_enqueue(SymbolQueue *queue, Symbol value) {
    if (queue->_used == queue->_size) {
        // Grow array
        queue->_size *= 2;
        queue->_array =
            (Symbol *)realloc(queue->_array, sizeof(Symbol) * queue->_size);
    }

    queue->_array[queue->_used++] = value;
}

void queue_free(SymbolQueue *queue) {
    if (queue->_array)
        free(queue->_array);

    queue->_array = 0;
    queue->_used = 0;
    queue->_start = 0;
    queue->_size = 0;
}

int queue_peek_from_back(SymbolQueue *stack, int n, Symbol *out_symbol) {
    if (stack->_used - 1 < n || n < 0) {
        return 1;
    }

    *out_symbol = stack->_array[stack->_used - 1 - n];

    return 0;
}

int queue_dequeue(SymbolQueue *queue, Symbol *out_symbol) {
    if (queue->_used == 0 || queue->_start >= queue->_used) {
        return 1;
    }

    if (out_symbol)
        *out_symbol = queue->_array[queue->_start];

    queue->_start++;

    return 0;
}
