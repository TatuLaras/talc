#include "ui_helpers.h"

#define SUGGESTION_ENTRIES_SIZE 3

static DocumentationEntry entries[SUGGESTION_ENTRIES_SIZE] = {
    {.name = "min", .summary = "min(x, y) - The smaller of x and y"},
    {.name = "max", .summary = "max(x, y) - The larger of x and y"},
    {.name = "asin", .summary = "asin(x) - Arc sine of x"},
};

// Gets an entry from the documentation table above
static int get_documentation_entry(char *incomplete_name,
                                   DocumentationEntry *out_entry) {
    int incomplete_name_length = strlen(incomplete_name);

    if (incomplete_name_length == 0)
        return 1;

    for (int i = 0; i < SUGGESTION_ENTRIES_SIZE; i++) {
        if (strncmp(incomplete_name, entries[i].name, incomplete_name_length) ==
            0) {
            // Match
            *out_entry = entries[i];
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

int ui_helper_get_summary(char *incomplete_name, char *out_summary,
                          int out_summary_length) {
    DocumentationEntry entry = {0};

    if (get_documentation_entry(incomplete_name, &entry))
        return 1;

    strncpy(out_summary, entry.summary, out_summary_length);
    return 0;
}

int ui_helper_get_completion(char *incomplete_name, char *out_completion,
                             int out_completion_length, int *out_is_function) {
    DocumentationEntry entry = {0};

    if (!get_documentation_entry(incomplete_name, &entry)) {
        strncpy(out_completion, entry.name, out_completion_length);

        if (out_is_function)
            *out_is_function = 1;

        return 0;
    }

    // TODO: Variables

    return 1;
}
