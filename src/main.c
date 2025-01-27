#define TB_IMPL
#include "external/termbox2.h"
#include "infix_to_postfix.h"
#include "user_interface.h"

int main() {

    UserInterface ui = {0};

    ui_init(&ui);

    char input_expression[UI_INPUT_BUFFER_SIZE] = {0};

    while (1) {
        int code = ui_main(&ui, input_expression);
        if (code == UI_CODE_QUIT)
            break;
        if (code == UI_CODE_INPUT_READY)
            str_to_symbols_postfix(input_expression, &ui.results);
    }

    ui_shutdown(&ui);

    return 0;
}
