#ifndef _SYMBOL
#define _SYMBOL

// data: none
// used to catch errors
#define SYMBOL_NULL 0
// data: none
#define SYMBOL_PARENTHESIS_OPEN 1
// data: none
#define SYMBOL_PARENTHESIS_CLOSE 2
// data: floating
#define SYMBOL_VALUE_DECIMAL 3
// data: int
#define SYMBOL_VALUE_INTEGER 4

typedef struct {
    int symbol_type;
    int numeric_integer;
    float numeric_floating;
} Symbol;

#endif
