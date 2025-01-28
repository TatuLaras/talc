#ifndef _CALCULATE
#define _CALCULATE
#include "double_stack.h"
#include "infix_to_postfix.h"
#include "queue.h"
#include "symbol.h"

int calculate_value(SymbolQueue *postfix_expression, double *out_result);
#endif
