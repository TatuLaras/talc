#include "calculate.h"
#include "symbol.h"

int calculate_value(SymbolQueue *postfix_expression, double *out_result) {
    DoubleStack holding_stack = {0};
    double_stack_init(&holding_stack);

    Symbol current_symbol = {0};
    while (!queue_dequeue(postfix_expression, &current_symbol)) {
        // If it's a numeric literal we push it as a double to the holding stack
        if (current_symbol.symbol_type == SYMBOL_LITERAL) {
            double_stack_push(&holding_stack, current_symbol.literal);
            continue;
        }

        // Otherwise it's an operator, so calculate
        switch (current_symbol.symbol_type) {
        case SYMBOL_OP_ADDITION: {
            if (holding_stack.__top < 2)
                return 1;

            // Pop operands
            double first = {0};
            double second = {0};
            double_stack_pop(&holding_stack, &first);
            double_stack_pop(&holding_stack, &second);

            // Push result
            double_stack_push(&holding_stack, first + second);
        } break;
        }
    }

    // If there's not exactly one item left in the holding stack it means the
    // input expression was invalid
    if (holding_stack.__top != 1)
        return 1;

    // Result
    if (double_stack_pop(&holding_stack, out_result))
        return 1;

    return 0;
}
