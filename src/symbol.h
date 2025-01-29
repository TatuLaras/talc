#ifndef _SYMBOL
#define _SYMBOL
#include <stdint.h>

// data: none
// used to catch errors
#define SYMBOL_NULL 0
// data: none
#define SYMBOL_PARENTHESIS_OPEN 1
// data: none
#define SYMBOL_PARENTHESIS_CLOSE 2

// data: floating
#define SYMBOL_LITERAL 3

#define SYMBOL_OP_ADDITION 4
#define SYMBOL_OP_SUBTRACTION 5
#define SYMBOL_OP_MULTIPLICATION 6
#define SYMBOL_OP_DIVISION 7
#define SYMBOL_OP_EXPONENT 8

typedef struct {
    int8_t symbol_type;
    int8_t operator_precedence;
    double literal;
} Symbol;

#endif
