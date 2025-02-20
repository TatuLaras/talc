#define TB_IMPL
#include "external/termbox2.h"

#include "calculate.h"
#include "infix_to_postfix.h"
#include "results_buffer.h"
#include "user_interface.h"
#include "variables.h"
#include <string.h>

int main() {

    UserInterface ui = {0};
    ui_init(&ui);

    VariableStorage variables = {0};
    variables_init(&variables);

    char input_expression[UI_INPUT_BUFFER_SIZE] = {0};

    while (1) {
        int code = ui_main(&ui, &variables, input_expression);

        if (code == UI_CODE_QUIT)
            break;

        if (code == UI_CODE_INPUT_READY) {
            SymbolQueue rpn = {0};
            queue_init(&rpn);

            VariableAssignmentRequest variable_assignment_request = {0};

            // Initialize a Result object to store the result in
            Result result = {0};
            int limit = UI_INPUT_BUFFER_SIZE;
            if (RESULTS_EXPRESSION_SIZE < UI_INPUT_BUFFER_SIZE)
                limit = RESULTS_EXPRESSION_SIZE;

            strncpy(result.expression, input_expression, limit);

            // Convert to reverse polish notation
            if (infix_to_postfix(input_expression, &variables, &rpn,
                                 &variable_assignment_request)) {
                result.erroneous = 1;
                ui.erroneus = 1;
                ui_append_result(&ui, result);
                queue_free(&rpn);
                continue;
            }

            // Calculate result from reverse polish notation
            if (calculate_value(&rpn, &result.result)) {
                result.erroneous = 1;
                ui.erroneus = 1;
            } else {
                ui.erroneus = 0;
                variables_fullfill_assignment_request(
                    &variables, &variable_assignment_request, result.result);

                // Also store result into 'ans' variable
                variables_assign(&variables, "ans", result.result);
            }

            // We append the result whether or not it was erroneus, for
            // bash style edit previous functionality (to be implemented later)
            ui_append_result(&ui, result);
            queue_free(&rpn);
        }
    }

    ui_shutdown(&ui);
    variables_free(&variables);

    return 0;
}
