#include "infix_to_postfix.h"
#include "queue.h"
#include "symbol.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static Symbol parse_operator(char op) {
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
    default: {
        operator_type = SYMBOL_NULL;
    } break;
    }

    Symbol symbol = {.symbol_type = operator_type,
                     .operator_precedence = operator_precedence};
    return symbol;
}

static int push_symbol_with_shunting_yard(Symbol symbol,
                                          SymbolQueue *output_queue,
                                          SymbolStack *holding_stack) {
    // Numeric literals go straight to output
    if (symbol.symbol_type == SYMBOL_LITERAL) {
        queue_enqueue(output_queue, symbol);
        return 0;
    }

    // '(' goes straight to holding stack
    if (symbol.symbol_type == SYMBOL_PARENTHESIS_OPEN) {
        stack_push(holding_stack, symbol);
        return 0;
    }

    // Pop symbols from holding stack into output until open parenthesis has
    // been popped
    // Return 1 if no open parenthesis was found
    if (symbol.symbol_type == SYMBOL_PARENTHESIS_CLOSE) {
        Symbol top_symbol = {0};
        int open_parenthesis_found = 0;
        while (!stack_pop(holding_stack, &top_symbol)) {
            if (top_symbol.symbol_type == SYMBOL_PARENTHESIS_OPEN) {
                open_parenthesis_found = 1;
                break;
            }

            queue_enqueue(output_queue, top_symbol);
        }

        return !open_parenthesis_found;
    }

    // Pop symbol from holding stack while the to be inserted symbol has lower
    // precedence

    Symbol top_symbol = {0};
    stack_peek_from_top(holding_stack, 0, &top_symbol);

    while (holding_stack->__top > 0 &&
           symbol.operator_precedence <= top_symbol.operator_precedence) {
        stack_pop(holding_stack, &top_symbol);
        queue_enqueue(output_queue, top_symbol);
        stack_peek_from_top(holding_stack, 0, &top_symbol);
    }

    stack_push(holding_stack, symbol);

    return 0;
}

int drain_holding_stack_into_output(SymbolQueue *output_queue,
                                    SymbolStack *holding_stack) {
    Symbol out_symbol = {0};
    while (!stack_pop(holding_stack, &out_symbol)) {
        if (out_symbol.symbol_type == SYMBOL_PARENTHESIS_OPEN ||
            out_symbol.symbol_type == SYMBOL_PARENTHESIS_CLOSE)
            return 1;

        queue_enqueue(output_queue, out_symbol);
    }

    return 0;
}

//  TODO: Error codes other than 1 for failure
int str_to_symbols_postfix(char *src_str, SymbolQueue *output_queue) {
    SymbolStack holding_stack = {0};
    stack_init(&holding_stack);

    // Initialize a buffer to the length of the source string for storing the
    // current symbol as we go (+ 1 to fit the null-terminator)
    int src_str_length = strlen(src_str) + 1;
    char current_symbol[src_str_length];
    memset(current_symbol, 0, src_str_length);

    int current_symbol_length = 0;

    int previous_symbol_was_closed_parenthesis = 0;

    // Iterate over string
    for (size_t i = 0; src_str[i] != 0; i++) {
        if (src_str[i] == ' ')
            continue;

        // If the first character in the current symbol is a '-', interpret it
        // as part of a new numeric literal, as opposed to the operator '-'
        // which is preceded by some numeric literal.
        if (current_symbol_length == 0 &&
            !previous_symbol_was_closed_parenthesis && src_str[i] == '-') {
            current_symbol[current_symbol_length++] = src_str[i];
            continue;
        }

        // Double minus just cancels them both out e.g. --2+2=4
        if (current_symbol_length == 1 && current_symbol[0] == '-' &&
            src_str[i] == '-') {
            current_symbol_length = 0;
            continue;
        }

        previous_symbol_was_closed_parenthesis = 0;

        // Is a letter => push to current, unless current starts with a number
        // then something has gone wrong
        if (isalpha(src_str[i])) {
            if (current_symbol_length > 0 && isdigit(current_symbol[0]))
                return 1;

            current_symbol[current_symbol_length++] = src_str[i];
            continue;
        }

        // Digits we push in any case
        if (isdigit(src_str[i])) {
            current_symbol[current_symbol_length++] = src_str[i];
            continue;
        }

        if (src_str[i] == '.') {
            if (current_symbol_length > 0 && isalpha(current_symbol[0]))
                return 1;
            current_symbol[current_symbol_length++] = src_str[i];
            continue;
        }

        // Try to parse a single character operator
        Symbol op = parse_operator(src_str[i]);
        if (op.symbol_type != SYMBOL_NULL) {
            if (op.symbol_type == SYMBOL_PARENTHESIS_CLOSE)
                previous_symbol_was_closed_parenthesis = 1;

            if (current_symbol_length > 0) {
                // Ensure null-termination
                current_symbol[current_symbol_length] = 0;
                // Push numeric literal to output
                //  TODO: Check validity of numeric literal
                Symbol numeric_literal = {.symbol_type = SYMBOL_LITERAL,
                                          .literal = strtod(current_symbol, 0)};
                if (push_symbol_with_shunting_yard(
                        numeric_literal, output_queue, &holding_stack))
                    return 1;

                current_symbol_length = 0;
            }

            // Push operator to output
            if (push_symbol_with_shunting_yard(op, output_queue,
                                               &holding_stack))
                return 1;
            continue;
        }

        // Invalid characters in input
        return 1;
    }

    if (current_symbol_length > 0) {
        // Ensure null-termination
        current_symbol[current_symbol_length] = 0;

        //  TODO: could be a variable

        // Push numeric symbol to output
        Symbol numeric_literal = {.symbol_type = SYMBOL_LITERAL,
                                  .literal = strtod(current_symbol, 0)};

        if (push_symbol_with_shunting_yard(numeric_literal, output_queue,
                                           &holding_stack))
            return 1;
    }

    // Returns possible error code
    return drain_holding_stack_into_output(output_queue, &holding_stack);
}
