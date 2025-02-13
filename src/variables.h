#ifndef _VARIABLES
#define _VARIABLES

#include <stdlib.h>

#define VARIABLES_STARTING_SIZE 8
#define VARIABLES_NAME_MAX_LENGTH 128

typedef struct {
    char name[VARIABLES_NAME_MAX_LENGTH];
    double value;
} Variable;

typedef struct {
    char name[VARIABLES_NAME_MAX_LENGTH];
    int valid;
} VariableAssignmentRequest;

//  NOTE: We could use a hash map but the number of variables is likely to be
//  very small (in the tens at max for most use cases) so it doesn't really make
//  sense to introduce a lot of implementational complexity and space complexity
//  for very little performace gain.

typedef struct {
    int _size;
    int top;
    Variable *_array;
} VariableStorage;

// Initializes the variable storage data structure
void variables_init(VariableStorage *var);

// De-initialies the variable storage data structure
void variables_free(VariableStorage *var);

// Assigns a variable of `name` to `value`
void variables_assign(VariableStorage *var, char *name, double value);

// Assigns a variable using the information of a VariableAssignmentRequest
void variables_fullfill_assignment_request(VariableStorage *var,
                                           VariableAssignmentRequest *request,
                                           double value);

// Retrieves a variable of a given `name` into `out_value`
//
// Returns 1 if variable is not defined
int variables_retrieve(VariableStorage *var, char *name, double *out_value);

#endif
