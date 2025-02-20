#include "calculate.h"
#include "symbol.h"
#include <math.h>

static int do_operation(DoubleStack *holding_stack, Symbol *op) {
    int operands = num_operands(op);

    if (holding_stack->top < operands)
        return 1;

    // Not the most elegant, but avoids some code duplication

    // Pop operands
    double first = 0;
    double second = 0;

    if (operands == 0)
        return 1;

    if (operands == 1)
        double_stack_pop(holding_stack, &first);

    if (operands == 2) {
        double_stack_pop(holding_stack, &second);
        double_stack_pop(holding_stack, &first);
    }

    // Push result
    switch (op->type) {
    case SYMBOL_OP_ADDITION: {
        double_stack_push(holding_stack, first + second);
    } break;

    case SYMBOL_OP_SUBTRACTION: {
        double_stack_push(holding_stack, first - second);
    } break;

    case SYMBOL_OP_DIVISION: {
        if (second == 0)
            return 1;
        double_stack_push(holding_stack, first / second);
    } break;

    case SYMBOL_OP_MULTIPLICATION: {
        double_stack_push(holding_stack, first * second);
    } break;

    case SYMBOL_OP_EXPONENT: {
        double_stack_push(holding_stack, pow(first, second));
    } break;

    case SYMBOL_FUNC_MAX: {
        if (second > first)
            first = second;
        double_stack_push(holding_stack, first);
    } break;

    case SYMBOL_FUNC_MIN: {
        if (second < first)
            first = second;
        double_stack_push(holding_stack, first);
    } break;

    case SYMBOL_FUNC_SIN: {
        double_stack_push(holding_stack, sin(first));
    } break;

    case SYMBOL_FUNC_COS: {
        double_stack_push(holding_stack, cos(first));
    } break;

    case SYMBOL_FUNC_TAN: {
        double_stack_push(holding_stack, tan(first));
    } break;

    case SYMBOL_FUNC_LOG: {
        double_stack_push(holding_stack, log(second) / log(first));
    } break;

    case SYMBOL_FUNC_LN: {
        double_stack_push(holding_stack, log(first));
    } break;

    case SYMBOL_FUNC_LG: {
        double_stack_push(holding_stack, log10(first));
    } break;

    case SYMBOL_FUNC_ASIN: {
        double_stack_push(holding_stack, asin(first));
    } break;

    case SYMBOL_FUNC_ACOS: {
        double_stack_push(holding_stack, acos(first));
    } break;

    case SYMBOL_FUNC_ATAN: {
        double_stack_push(holding_stack, atan(first));
    } break;
    }

    return 0;
}

int calculate_value(SymbolQueue *postfix_expression, double *out_result) {
    DoubleStack holding_stack = {0};
    double_stack_init(&holding_stack);

    Symbol current_symbol = {0};
    while (!queue_dequeue(postfix_expression, &current_symbol)) {
        // If it's a numeric literal we push it as a double to the holding stack
        if (current_symbol.type == SYMBOL_LITERAL) {
            double_stack_push(&holding_stack, current_symbol.literal);
            continue;
        }

        // Otherwise it's an operator, so calculate
        if (do_operation(&holding_stack, &current_symbol)) {
            double_stack_free(&holding_stack);
            return 1;
        }
    }

    // If there's not exactly one item left in the holding stack it means
    // the input expression was invalid
    if (holding_stack.top != 1) {
        double_stack_free(&holding_stack);
        return 1;
    }

    // Result
    double_stack_pop(&holding_stack, out_result);

    double_stack_free(&holding_stack);
    return 0;
}
