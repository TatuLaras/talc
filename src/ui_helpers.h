#ifndef _UI_HELPERS
#define _UI_HELPERS

#include "symbol.h"
#include "user_interface.h"
#include "variables.h"
#include <stdio.h>
#include <string.h>

// Gets a function or variable name that is currently being written in the input
// buffer (for suggestions).
//
// For example in "5+mi" the name would be "mi" and we could use it to suggest
// the function "min" to the user.
//
// Returns 1 if no name was able to be parsed (e.g. the user is not currently
// writing a variable or function name).
//
// Not an internal static function for unit testing purposes.
int ui_helper_get_currently_typed_name(UserInterface *ui, char *out_name,
                                       int out_name_length,
                                       int *out_start_position);

// Returns a summary (if any) for an incomplete name (e.g. "mi" would return
// something like "max(x, y) - Returns the maximum of x and y").
//
// Returns 1 if no match is found
int ui_helper_get_summary(char *incomplete_name, VariableStorage *variables,
                          char *out_summary, int out_summary_length);

// Returns the completed name for an incomplete name (e.g. "mi" => "min")
//
// Returns 1 if no match is found
int ui_helper_get_completion(char *incomplete_name, VariableStorage *var,
                             char *out_completion, int out_completion_length,
                             int *out_is_function);

#endif
