#ifndef _CALCULATE
#define _CALCULATE
#include "double_stack.h"
#include "infix_to_postfix.h"
#include "queue.h"
#include "symbol.h"
#include <math.h>
#include <stdint.h>

// Calculates numeric value from a RPN / postfix queue of symbols
//
// Returns 1 on failure
int calculate_value(SymbolQueue *postfix_expression, double *out_result);

#endif
