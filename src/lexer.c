#include "lexer.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int divide_into_symbols(char *src_str, SymbolStack *dst_array) {
    // Initialize a buffer to the length of the source string for storing the
    // current symbol as we go
    int src_str_length = strlen(src_str);
    char current_stack[src_str_length];
    memset(current_stack, 0, src_str_length);

    int current_stack_pointer = 0;

    for (size_t i = 0; src_str[i] != 0; i++) {
        // Is a letter => push to current, unless current starts with a number
        // then something has gone wrong
        if (isalpha(src_str[i])) {
            if (current_stack_pointer > 0 && isdigit(current_stack[0]))
                return 1;

            current_stack[current_stack_pointer++] = src_str[i];
        }

        // Digits we push in any case
        if (isdigit(src_str[i]))
            current_stack[current_stack_pointer++] = src_str[i];

        if (src_str[i] == '+') {
            char *expr = (char *)malloc(sizeof(char) * current_stack_pointer);
            strncpy(expr, current_stack, current_stack_pointer);
            // dparray_push(dst_array, expr);
            current_stack_pointer = 0;

            // Push operator to output
            char *operator=(char *) malloc(sizeof(char) * 2);
            strcpy(operator, "+");

            // dparray_push(dst_array, operator);
        }
    }

    if (current_stack_pointer > 0) {
        char *expr = (char *)malloc(sizeof(char) * current_stack_pointer);
        strncpy(expr, current_stack, current_stack_pointer);
        // dparray_push(dst_array, expr);
        current_stack_pointer = 0;
    }

    return 0;
}

// Operators
// Parentheses
// Variable names
// Values
