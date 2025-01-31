#ifndef _SHUNTING
#define _SHUNTING

#include "queue.h"
#include "symbol.h"
#include "symbol_stack.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define INFIX_ERROR_GENERAL 1
#define INFIX_ERROR_MISMATCHED_PARENTHESIS 2
#define INFIX_ERROR_MALFORMED_INPUT 3

// Attempts to covert a string expression in src_str to postfix / RPN form,
// returns 1 on failure due to an invalid source expression.
int str_to_symbols_postfix(char *src_str, SymbolQueue *output_queue);

#endif
