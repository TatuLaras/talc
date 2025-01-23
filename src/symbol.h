#ifndef _SYMBOL
#define _SYMBOL

// data: none
// used to catch errors
#include <stdint.h>
#define SYMBOL_NULL 0
// data: none
#define SYMBOL_PARENTHESIS_OPEN 1
// data: none
#define SYMBOL_PARENTHESIS_CLOSE 2
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
    //  TODO: Safer alternative
    int8_t operator_precedence;
    int64_t literal_integer;
    double literal_floating;
} Symbol;

#endif
