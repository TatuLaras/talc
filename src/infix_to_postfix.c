#include "infix_to_postfix.h"
#include <string.h>

static int push_symbol_with_shunting_yard(Symbol symbol,
                                          SymbolQueue *output_queue,
                                          SymbolStack *holding_stack) {
    // Numeric literals go straight to output
    if (symbol.type == SYMBOL_LITERAL) {
        queue_enqueue(output_queue, symbol);
        return 0;
    }

    // '(' goes straight to holding stack
    if (symbol.type == SYMBOL_PARENTHESIS_OPEN) {
        stack_push(holding_stack, symbol);
        return 0;
    }

    // Pop symbols from holding stack into output until open parenthesis has
    // been popped
    // Return 1 if no open parenthesis was found
    if (symbol.type == SYMBOL_PARENTHESIS_CLOSE) {
        Symbol top_symbol = {0};
        int open_parenthesis_found = 0;
        while (!stack_pop(holding_stack, &top_symbol)) {
            if (top_symbol.type == SYMBOL_PARENTHESIS_OPEN) {
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

static int drain_holding_stack_into_output(SymbolQueue *output_queue,
                                           SymbolStack *holding_stack) {
    Symbol out_symbol = {0};
    while (!stack_pop(holding_stack, &out_symbol)) {
        if (out_symbol.type == SYMBOL_PARENTHESIS_OPEN ||
            out_symbol.type == SYMBOL_PARENTHESIS_CLOSE)
            return INFIX_ERROR_MISMATCHED_PARENTHESIS;

        queue_enqueue(output_queue, out_symbol);
    }

    return 0;
}

int infix_to_postfix(char *src_str, VariableStorage *variables,
                     SymbolQueue *out_queue,
                     VariableAssignmentRequest *out_variable_request) {

    SymbolStack holding_stack = {0};
    stack_init(&holding_stack);

    // Initialize a buffer to the length of the source string for storing the
    // current symbol as we go (+ 1 to fit the null-terminator)
    int src_str_length = strlen(src_str) + 1;
    char current_symbol[src_str_length];
    memset(current_symbol, 0, src_str_length);

    int current_symbol_length = 0;

    int previous_was_close_parenthesis = 0;

    // Iterate over string
    for (size_t i = 0; src_str[i] != 0; i++) {

        if (src_str[i] == ' ')
            continue;

        // If the first character in the current symbol is a '-', interpret it
        // as part of a new numeric literal, as opposed to the operator '-'
        // which is preceded by some numeric literal.
        if (current_symbol_length == 0 && !previous_was_close_parenthesis &&
            src_str[i] == '-') {
            current_symbol[current_symbol_length++] = src_str[i];
            continue;
        }

        // Double minus just cancels them both out e.g. --2+2=4
        if (current_symbol_length == 1 && current_symbol[0] == '-' &&
            src_str[i] == '-') {
            current_symbol_length = 0;
            continue;
        }

        previous_was_close_parenthesis = 0;

        // Is a letter => push to current, unless current starts with a number
        // then something has gone wrong
        if (isalpha(src_str[i])) {
            int current_is_literal =
                current_symbol_length > 0 && isdigit(current_symbol[0]);

            if (current_is_literal)
                return INFIX_ERROR_MALFORMED_INPUT;

            current_symbol[current_symbol_length++] = src_str[i];
            continue;
        }

        // Digits we push in any case
        if (isdigit(src_str[i])) {
            current_symbol[current_symbol_length++] = src_str[i];
            continue;
        }

        if (src_str[i] == '.') {
            int current_is_variable_name =
                current_symbol_length > 0 && isalpha(current_symbol[0]);

            if (current_is_variable_name)
                return INFIX_ERROR_MALFORMED_INPUT;

            current_symbol[current_symbol_length++] = src_str[i];
            continue;
        }

        // Variable assignment
        if (src_str[i] == '=') {
            int invalid_assignment =
                current_symbol_length == 0 ||
                current_symbol_length >= VARIABLES_NAME_MAX_LENGTH ||
                !isalpha(current_symbol[0]) || out_queue->_used > 0 ||
                holding_stack.__top > 0 || out_variable_request->valid;

            if (invalid_assignment)
                return INFIX_ERROR_INVALID_VARIABLE_ASSIGNMENT;

            out_variable_request->valid = 1;

            current_symbol[current_symbol_length] = 0;

            strncpy(out_variable_request->name, current_symbol,
                    current_symbol_length);

            current_symbol_length = 0;
            continue;
        }

        // Try to parse a single character operator
        Symbol op = parse_operator(src_str[i]);

        // SYMBOL_NULL is returned to indicate error
        if (op.type == SYMBOL_NULL)
            return INFIX_ERROR_GENERAL;

        if (op.type == SYMBOL_PARENTHESIS_CLOSE)
            previous_was_close_parenthesis = 1;

        if (current_symbol_length > 0) {
            int is_function_name = op.type == SYMBOL_PARENTHESIS_OPEN;

            // Ensure null-termination
            current_symbol[current_symbol_length] = 0;

            Symbol symbol = parse_non_operator_symbol(
                current_symbol, is_function_name, variables);

            if (symbol.type == SYMBOL_NULL)
                return INFIX_ERROR_GENERAL;

            push_symbol_with_shunting_yard(symbol, out_queue, &holding_stack);

            current_symbol_length = 0;
        }

        if (op.type == SYMBOL_OP_NO_OP)
            continue;

        // Push operator
        if (push_symbol_with_shunting_yard(op, out_queue, &holding_stack))
            return INFIX_ERROR_MISMATCHED_PARENTHESIS;
    }

    if (current_symbol_length > 0) {
        current_symbol[current_symbol_length] = 0;

        Symbol symbol = parse_non_operator_symbol(current_symbol, 0, variables);

        if (symbol.type == SYMBOL_NULL)
            return INFIX_ERROR_GENERAL;

        push_symbol_with_shunting_yard(symbol, out_queue, &holding_stack);
    }

    // Returns possible error code
    return drain_holding_stack_into_output(out_queue, &holding_stack);
}
