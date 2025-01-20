#ifndef _LEXER
#define _LEXER

#include "stack.h"
#include <stddef.h>

// size_t *out_symbols_count
int divide_into_symbols(char *src_str, SymbolStack *dst_array);

#endif
