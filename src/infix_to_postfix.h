#ifndef _LEXER
#define _LEXER

#include "stack.h"
#include "symbol.h"
#include <stddef.h>

int str_to_symbols_postfix(char *src_str, SymbolStack *dst_stack);
static int push_symbol_with_shunting_yard(Symbol symbol,
                                          SymbolStack *output_stack,
                                          SymbolStack *holding_stack);
int drain_holding_stack_into_output(SymbolStack *output_stack,
                                    SymbolStack *holding_stack);

Symbol parse_operator(char op);

#endif
