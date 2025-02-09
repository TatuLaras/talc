#include "variables.h"
#include <string.h>

void variables_init(VariableStorage *var) {
    var->__size = VARIABLES_STARTING_SIZE;
    var->__top = 0;
    var->__array =
        (Variable *)malloc(sizeof(Variable) * VARIABLES_STARTING_SIZE);

    // Built-in variables
    variables_assign(var, "pi", 3.141592653589793);
    variables_assign(var, "e", 2.718281828459045);
}

void variables_free(VariableStorage *var) {
    if (var->__array)
        free(var->__array);

    var->__array = 0;
    var->__top = 0;
    var->__size = 0;
}

void variables_assign(VariableStorage *var, char *name, double value) {
    Variable variable = {.name = name, .value = value};

    if (var->__top == var->__size) {
        var->__size *= 2;
        var->__array =
            (Variable *)realloc(var->__array, sizeof(Variable) * var->__size);
    }

    var->__array[var->__top++] = variable;
}

int variables_retrieve(VariableStorage *var, char *name, double *out_value) {
    // We iterate in a reverse order so reassigned variables have the newer
    // value
    for (int i = var->__top - 1; i >= 0; i--) {
        Variable variable = var->__array[i];

        if (strcmp(name, variable.name) == 0) {
            // Match!
            *out_value = variable.value;
            return 0;
        }
    }

    // Not defined
    return 1;
}
