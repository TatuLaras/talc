#include "symbol.h"

#define SYMBOL_FUNCTION_MAPPINGS_SIZE 3

struct FunctionNameMapping {
    const char *name;
    int type;
};

static struct FunctionNameMapping
    function_mappings[SYMBOL_FUNCTION_MAPPINGS_SIZE] = {
        {.name = "min", .type = SYMBOL_FUNC_MIN},
        {.name = "max", .type = SYMBOL_FUNC_MAX},
        {.name = "sin", .type = SYMBOL_FUNC_SIN},
};

// Tries to parse a multi-character function name into appropriate Symbol
//
// Symbol type will be SYMBOL_NULL if invalid
static Symbol parse_function(char *function_name) {
    int8_t operator_type = 0;

    for (int i = 0; i < SYMBOL_FUNCTION_MAPPINGS_SIZE; i++) {
        if (!strcmp(function_name, function_mappings[i].name))
            operator_type = function_mappings[i].type;
    }

    Symbol symbol = {.type = operator_type, .operator_precedence = 10};
    return symbol;
}

Symbol parse_operator(char op) {
    int8_t operator_type = 0;
    int8_t operator_precedence = 0;

    switch (op) {
    case '-': {
        operator_type = SYMBOL_OP_SUBTRACTION;
        operator_precedence = 1;
    } break;
    case '+': {
        operator_type = SYMBOL_OP_ADDITION;
        operator_precedence = 1;
    } break;
    case '*': {
        operator_type = SYMBOL_OP_MULTIPLICATION;
        operator_precedence = 2;
    } break;
    case '/': {
        operator_type = SYMBOL_OP_DIVISION;
        operator_precedence = 3;
    } break;
    case '^': {
        operator_type = SYMBOL_OP_EXPONENT;
        operator_precedence = 4;
    } break;
    case '(': {
        operator_type = SYMBOL_PARENTHESIS_OPEN;
    } break;
    case ')': {
        operator_type = SYMBOL_PARENTHESIS_CLOSE;
    } break;
    case ',': {
        operator_type = SYMBOL_OP_NO_OP;
    } break;
    default: {
        operator_type = SYMBOL_NULL;
    } break;
    }

    Symbol symbol = {.type = operator_type,
                     .operator_precedence = operator_precedence};
    return symbol;
}

Symbol parse_non_operator_symbol(char *str, int is_function) {
    int is_variable_name = !is_function && isalpha(str[0]);

    if (is_variable_name) {
        //  TODO:
        Symbol null = {0};
        return null;
    }

    if (is_function) {
        Symbol function_symbol = parse_function(str);
        return function_symbol;
    }

    //  TODO: Check validity of numeric literal
    Symbol numeric_literal = {.type = SYMBOL_LITERAL,
                              .literal = strtod(str, 0)};

    return numeric_literal;
}

int num_operands(Symbol *symbol) {
    switch (symbol->type) {
    case SYMBOL_OP_ADDITION:
        return 2;
    case SYMBOL_OP_SUBTRACTION:
        return 2;
    case SYMBOL_OP_MULTIPLICATION:
        return 2;
    case SYMBOL_OP_DIVISION:
        return 2;
    case SYMBOL_OP_EXPONENT:
        return 2;
    case SYMBOL_OP_NO_OP:
        return 2;
    case SYMBOL_FUNC_MIN:
        return 2;
    case SYMBOL_FUNC_MAX:
        return 2;
    case SYMBOL_FUNC_SIN:
        return 1;
    default:
        return 0;
    }
}
