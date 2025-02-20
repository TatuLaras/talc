#include "ui_helpers.h"
#include "symbol.h"
#include <stdio.h>
#include <string.h>

extern FunctionNameMapping functions[SYMBOL_FUNCTION_MAPPINGS_SIZE];

// Gets an entry from the documentation table above
static int get_documentation_entry(char *incomplete_name,
                                   FunctionNameMapping *out_entry) {
    int incomplete_name_length = strlen(incomplete_name);

    if (incomplete_name_length == 0)
        return 1;

    for (int i = 0; i < SYMBOL_FUNCTION_MAPPINGS_SIZE; i++) {
        if (strncmp(incomplete_name, functions[i].name,
                    incomplete_name_length) == 0) {
            // Match
            *out_entry = functions[i];
            return 0;
        }
    }

    return 1;
}

int ui_helper_get_currently_typed_name(UserInterface *ui, char *out_name,
                                       int out_name_length,
                                       int *out_start_position) {
    int start = ui->input_buffer_cursor - 1;

    while (start > 0 && isalnum(ui->input_buffer[start]))
        start--;

    if (start > 0)
        start++;

    if (out_start_position)
        *out_start_position = start;

    // The user is not typing a variable or a function
    if (isdigit(ui->input_buffer[start]) ||
        ui->input_buffer_cursor - start == 0)
        return 1;

    for (int i = 0; i < ui->input_buffer_cursor - start; i++) {
        if (i >= out_name_length)
            break;

        out_name[i] = ui->input_buffer[start + i];
    }

    return 0;
}

int ui_helper_get_summary(char *incomplete_name, VariableStorage *var,
                          char *out_summary, int out_summary_length) {
    FunctionNameMapping entry = {0};

    // Function
    if (!get_documentation_entry(incomplete_name, &entry)) {
        strncpy(out_summary, entry.summary, out_summary_length);
        return 0;
    }

    // Variable
    double value = 0;
    char name[100] = {0};
    if (!variables_retrieve_suggestion(var, incomplete_name, &value, name,
                                       99)) {
        snprintf(out_summary, out_summary_length, "%s - %lg", name, value);
        return 0;
    }

    return 1;
}

int ui_helper_get_completion(char *incomplete_name, VariableStorage *var,
                             char *out_completion, int out_completion_length) {
    int incomplete_name_length = strlen(incomplete_name);
    // Function
    FunctionNameMapping entry = {0};

    if (!get_documentation_entry(incomplete_name, &entry)) {
        snprintf(out_completion, out_completion_length, "%s(",
                 entry.name + incomplete_name_length);

        return 0;
    }

    // Variable
    double _value;
    char name[100] = {0};
    if (!variables_retrieve_suggestion(var, incomplete_name, &_value, name,
                                       99)) {
        strncpy(out_completion, name + incomplete_name_length,
                out_completion_length);
        return 0;
    }

    return 1;
}
