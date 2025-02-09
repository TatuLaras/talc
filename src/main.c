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
        int code = ui_main(&ui, input_expression);

        if (code == UI_CODE_QUIT)
            break;

        if (code == UI_CODE_INPUT_READY) {
            SymbolQueue rpn = {0};
            queue_init(&rpn);

            // Initialize a Result object to store the result in
            Result result = {0};
            result.expression = malloc(strlen(input_expression) * sizeof(char));
            strcpy(result.expression, input_expression);

            // Convert to reverse polish notation
            if (infix_to_postfix(input_expression, &rpn, &variables)) {
                result.erroneous = 1;
                ui.erroneus = 1;
                ui_append_result(&ui, result);
                continue;
            }

            // Calculate result from reverse polish notation
            if (calculate_value(&rpn, &result.result)) {
                result.erroneous = 1;
                ui.erroneus = 1;
            } else
                ui.erroneus = 0;

            ui_append_result(&ui, result);
        }
    }

    ui_shutdown(&ui);

    return 0;
}
