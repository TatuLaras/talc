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

//  TODO: just make everything decimals, no need to have separate integers and
//  decimals in the symbol data structure

// data: floating
#define SYMBOL_LITERAL_DECIMAL 3
// data: int
#define SYMBOL_LITERAL_INTEGER 4

#define SYMBOL_OP_ADDITION 5
#define SYMBOL_OP_SUBTRACTION 6
#define SYMBOL_OP_MULTIPLICATION 7
#define SYMBOL_OP_DIVISION 8
#define SYMBOL_OP_EXPONENT 9

typedef struct {
    int8_t symbol_type;

    // symbol_type determines which of these fields gets used
    int8_t operator_precedence;
    int64_t literal_integer;
    double literal_floating;
} Symbol;

#endif
