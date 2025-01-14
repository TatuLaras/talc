#include "dynamic_array.h"

void darray_init(DynamicArray *array) {
    array->__size = DARRAY_STARTING_SIZE;
    array->__used = 0;
    array->__array = (int *)malloc(sizeof(int) * DARRAY_STARTING_SIZE);
}

void dparray_init(DynamicPointerArray *array) {
    array->__size = DARRAY_STARTING_SIZE;
    array->__used = 0;
    array->__array = (void **)malloc(sizeof(void *) * DARRAY_STARTING_SIZE);
}

void darray_push(DynamicArray *array, int value) {
    if (array->__used == array->__size) {
        // Grow array
        array->__size *= 2;
        array->__array =
            (int *)realloc(array->__array, sizeof(int) * array->__size);
    }

    array->__array[array->__used++] = value;
}

void dparray_push(DynamicPointerArray *array, void *value) {
    if (array->__used == array->__size) {
        // Grow array
        array->__size *= 2;
        array->__array =
            (void **)realloc(array->__array, sizeof(void *) * array->__size);
    }

    array->__array[array->__used++] = value;
}

void darray_free(DynamicArray *array) {
    if (array->__array)
        free(array->__array);

    array->__array = 0;
    array->__used = 0;
    array->__size = 0;
}

void dparray_free(DynamicPointerArray *array) {
    // Free all pointers in array
    for (int i = 0; i < array->__used; i++) {
        if (array->__array[i])
            free((void *)array->__array[i]);

        array->__array[i] = 0;
    }

    if (array->__array)
        free(array->__array);

    array->__array = 0;
    array->__used = 0;
    array->__size = 0;
}

void *dparray_get(DynamicPointerArray *array, int i) {
    if (i >= array->__used || i < 0)
        return 0;

    return array->__array[i];
}

int darray_get(DynamicArray *array, int i) {
    if (i >= array->__used || i < 0)
        return 0;

    return array->__array[i];
}
