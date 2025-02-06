#define TB_IMPL
#include "external/termbox2.h"

#include "calculate.h"
#include "infix_to_postfix.h"
#include "results_buffer.h"
#include "user_interface.h"
#include <string.h>

int main() {

    UserInterface ui = {0};

    ui_init(&ui);

    char input_expression[UI_INPUT_BUFFER_SIZE] = {0};

    while (1) {
        int code = ui_main(&ui, input_expression);

        if (code == UI_CODE_QUIT)
            break;

        if (code == UI_CODE_INPUT_READY) {
            SymbolQueue rpn = {0};
            queue_init(&rpn);

            if (str_to_symbols_postfix(input_expression, &rpn)) {
                ui.is_error = 1;
                continue;
            }

            Result result = {0};

            if (calculate_value(&rpn, &result.result)) {
                ui.is_error = 1;
                continue;
            }

            result.expression = malloc(strlen(input_expression) * sizeof(char));
            strcpy(result.expression, input_expression);

            ui.is_error = 0;
            ui_append_result(&ui, result);
        }
    }

    ui_shutdown(&ui);

    return 0;
}
