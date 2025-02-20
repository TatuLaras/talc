#include "variables.h"

void variables_init(VariableStorage *var) {
    var->_size = VARIABLES_STARTING_SIZE;
    var->top = 0;
    var->_array =
        (Variable *)malloc(sizeof(Variable) * VARIABLES_STARTING_SIZE);

    // Built-in variables
    variables_assign(var, "pi", 3.141592653589793);
    variables_assign(var, "e", 2.718281828459045);
}

void variables_free(VariableStorage *var) {
    if (var->_array)
        free(var->_array);

    var->_array = 0;
    var->top = 0;
    var->_size = 0;
}

void variables_assign(VariableStorage *var, char *name, double value) {
    Variable variable = {.value = value};
    strncpy(variable.name, name, VARIABLES_NAME_MAX_LENGTH);

    if (var->top == var->_size) {
        var->_size *= 2;
        var->_array =
            (Variable *)realloc(var->_array, sizeof(Variable) * var->_size);
    }

    var->_array[var->top++] = variable;
}

void variables_fullfill_assignment_request(VariableStorage *var,
                                           VariableAssignmentRequest *request,
                                           double value) {
    variables_assign(var, request->name, value);
}

int variables_retrieve(VariableStorage *var, char *name, double *out_value) {
    // We iterate in a reverse order so reassigned variables have the newer
    // value
    for (int i = var->top - 1; i >= 0; i--) {
        Variable variable = var->_array[i];

        if (strcmp(name, variable.name) == 0) {
            // Match!
            *out_value = variable.value;
            return 0;
        }
    }

    // Not defined
    return 1;
}

int variables_retrieve_suggestion(VariableStorage *var, char *incomplete_name,
                                  double *out_value, char *out_name,
                                  int out_name_length) {
    int incomplete_name_length = strlen(incomplete_name);
    if (incomplete_name_length == 0)
        return 1;

    for (int i = var->top - 1; i >= 0; i--) {
        Variable variable = var->_array[i];

        if (strncmp(incomplete_name, variable.name, incomplete_name_length) ==
            0) {
            // Match!
            *out_value = variable.value;
            strncpy(out_name, variable.name, out_name_length);
            return 0;
        }
    }

    // Not defined
    return 1;
}
