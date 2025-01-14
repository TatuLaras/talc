// An automatically growing dynamic array

#include <stdlib.h>
#include <strings.h>
#define DARRAY_STARTING_SIZE 4

typedef struct {
    int __size;
    int __used;
    int *__array;
} DynamicArray;

typedef struct {
    int __size;
    int __used;
    void **__array;
} DynamicPointerArray;

// Initialize a dynamic array
void darray_init(DynamicArray *array);
// Initialize a dynamic pointer array
void dparray_init(DynamicPointerArray *array);

// Push a value into the dynamic array
void darray_push(DynamicArray *array, int value);
// Push a pointer into the dynamic pointer array
void dparray_push(DynamicPointerArray *array, void *value);

// Free memory used by dynamic array
void darray_free(DynamicArray *array);
// Free memory used by dynamic pointer array
//
//  NOTE: Make sure all data pointer to by the pointers is heap-allocated and
//  not freed
void dparray_free(DynamicPointerArray *array);

// Get element of array by index, returns 0 if index is out of bounds
int darray_get(DynamicArray *array, int i);
// Get element of array by index, returns a null pointer if index is out of
// bounds
void *dparray_get(DynamicPointerArray *array, int i);
