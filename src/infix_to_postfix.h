#ifndef _SHUNTING
#define _SHUNTING

#include "queue.h"
#include "symbol.h"
#include "symbol_stack.h"

// Attempts to covert a string expression in src_str to postfix / RPN form,
// returns 1 on failure due to an invalid source expression.
int str_to_symbols_postfix(char *src_str, SymbolQueue *output_queue);

#endif
