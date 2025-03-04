#include "symbol.h"

//  TODO: Num operands into this table

FunctionNameMapping functions[SYMBOL_FUNCTION_MAPPINGS_SIZE] = {
    {.name = "min",
     .type = SYMBOL_FUNC_MIN,
     .summary = "min(x, y) - The smaller of x and y"},

    {.name = "max",
     .type = SYMBOL_FUNC_MAX,
     .summary = "max(x, y) - The larger of x and y"},

    {.name = "sin", .type = SYMBOL_FUNC_SIN, .summary = "sin(x) - Sine of x"},

    {.name = "cos", .type = SYMBOL_FUNC_COS, .summary = "cos(x) - Cosine of x"},

    {.name = "tan",
     .type = SYMBOL_FUNC_TAN,
     .summary = "tan(x) - Tangent of x"},

    {.name = "log",
     .type = SYMBOL_FUNC_LOG,
     .summary = "log(b, x) - Base b logarithm of x"},

    {.name = "ln",
     .type = SYMBOL_FUNC_LN,
     .summary = "ln(x) - Natural (base e) logarithm of x"},

    {.name = "lg",
     .type = SYMBOL_FUNC_LG,
     .summary = "lg(x) - Common (base-10) logarithm of x"},

    {.name = "asin",
     .type = SYMBOL_FUNC_ASIN,
     .summary = "asin(x) - Arc sine of x"},

    {.name = "acos",
     .type = SYMBOL_FUNC_ACOS,
     .summary = "acos(x) - Arc cosine of x"},

    {.name = "atan",
     .type = SYMBOL_FUNC_ATAN,
     .summary = "atan(x) - Arc tangent of x"},
};

// Tries to parse a multi-character function name into appropriate Symbol
//
// Symbol type will be SYMBOL_NULL if invalid
static Symbol parse_function(char *function_name) {
    int8_t operator_type = 0;

    for (int i = 0; i < SYMBOL_FUNCTION_MAPPINGS_SIZE; i++) {
        if (!strcmp(function_name, functions[i].name))
            operator_type = functions[i].type;
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

Symbol parse_non_operator_symbol(char *str, int is_function,
                                 VariableStorage *variables) {
    int is_variable_name = !is_function && isalpha(str[0]);

    if (is_variable_name) {
        Symbol symbol = {.type = SYMBOL_LITERAL, 0};

        if (!variables_retrieve(variables, str, &symbol.literal))
            return symbol;

        // Undefined variable, return null type symbol to indicate error
        symbol.type = SYMBOL_NULL;
        return symbol;
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
    case SYMBOL_FUNC_COS:
        return 1;
    case SYMBOL_FUNC_TAN:
        return 1;
    case SYMBOL_FUNC_LOG:
        return 2;
    case SYMBOL_FUNC_LN:
        return 1;
    case SYMBOL_FUNC_LG:
        return 1;
    case SYMBOL_FUNC_ASIN:
        return 1;
    case SYMBOL_FUNC_ACOS:
        return 1;
    case SYMBOL_FUNC_ATAN:
        return 1;
    default:
        return 0;
    }
}
