#ifndef _SYMBOL
#define _SYMBOL

#include "variables.h"

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_FUNCTION_MAPPINGS_SIZE 11

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
#define SYMBOL_OP_NO_OP 9

#define SYMBOL_FUNC_MIN 10
#define SYMBOL_FUNC_MAX 11
#define SYMBOL_FUNC_SIN 12
#define SYMBOL_FUNC_COS 13
#define SYMBOL_FUNC_TAN 14
#define SYMBOL_FUNC_LOG 15
#define SYMBOL_FUNC_LN 16
#define SYMBOL_FUNC_LG 17
#define SYMBOL_FUNC_ASIN 18
#define SYMBOL_FUNC_ACOS 19
#define SYMBOL_FUNC_ATAN 20

typedef struct {
    int8_t type;
    int8_t operator_precedence;
    double literal;
} Symbol;

typedef struct {
    const char *name;
    const char *summary;
    int type;

} FunctionNameMapping;

// Tries to parse a single-character operator into appropriate Symbol
//
// Symbol type will be SYMBOL_NULL if invalid
Symbol parse_operator(char op);

// Tries to parse a non-operator symbol from string
//
// Symbol type will be SYMBOL_NULL if invalid
Symbol parse_non_operator_symbol(char *str, int is_function,
                                 VariableStorage *variables);

//  NOTE: We use a function instead of a table for the number of operands so we
//  can use our defined constants above, and changing their integer values does
//  not affect this

// Returns the number of operands the operator operates on
//
// Returns 0 if not an operator
int num_operands(Symbol *symbol);

#endif
