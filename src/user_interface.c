#include "user_interface.h"
#include "external/termbox2.h"
#include "stack.h"
#include "symbol.h"

static void ui_input_character(UserInterface *ui, char character) {
    if (ui->input_buffer_used >= UI_INPUT_BUFFER_SIZE ||
        ui->input_buffer_used >= tb_width() - 1)
        return;

    ui->input_buffer[ui->input_buffer_used++] = character;
    ui->input_buffer_cursor++;
}

static void ui_reset_input(UserInterface *ui) {
    ui->input_buffer_used = 0;
    ui->input_buffer_cursor = 0;
}

// Renders the current input buffer as an input line in the bottom of the TUI
static void ui_render_input_line(UserInterface *ui) {
    int input_line_row = tb_height() - 1;

    // Input buffer
    for (int i = 0; i < ui->input_buffer_used; i++) {
        tb_set_cell(i, input_line_row, ui->input_buffer[i], TB_DEFAULT,
                    TB_BLACK);
    }

    // Rest of the line (to get background color for the whole line)
    for (int i = ui->input_buffer_used; i < tb_width(); i++) {
        tb_set_cell(i, input_line_row, ' ', TB_DEFAULT, TB_BLACK);
    }
}

static void ui_render_results(UserInterface *ui) {
    int line = tb_height() - 3;
    int i = 0;

    Symbol symbol = {0};
    while (!stack_peek_from_top(&ui->results, i, &symbol)) {
        i++;

        if (symbol.symbol_type != SYMBOL_LITERAL_DECIMAL &&
            symbol.symbol_type != SYMBOL_LITERAL_INTEGER)
            continue;

        if (symbol.symbol_type == SYMBOL_LITERAL_DECIMAL)
            tb_printf(2, line--, TB_DEFAULT, TB_DEFAULT, "$%d  %f", i,
                      symbol.literal_floating);

        if (symbol.symbol_type == SYMBOL_LITERAL_INTEGER)
            tb_printf(2, line--, TB_DEFAULT, TB_DEFAULT, "$%d  %d", i,
                      symbol.literal_integer);
    }
}

static void ui_erase_character(UserInterface *ui) {
    if (ui->input_buffer_used <= 0 || ui->input_buffer_cursor <= 0)
        return;
    ui->input_buffer_used--;
    ui->input_buffer_cursor--;
}

// Handles special hotkeys and inserts other keys into the input buffer
//
// Returns with event codes described by the UI_CODE... contants in the header
// file, meant to be passed straight to the caller of ui_main
static int ui_handle_keyboard_input(UserInterface *ui, char *out_expression) {
    struct tb_event event;

    tb_poll_event(&event);

    if (event.key == TB_KEY_CTRL_Q)
        return UI_CODE_QUIT;

    if (event.key == TB_KEY_ENTER) {
        strncpy(out_expression, ui->input_buffer, ui->input_buffer_used);
        out_expression[ui->input_buffer_cursor] = 0;
        ui_reset_input(ui);
        return UI_CODE_INPUT_READY;
    }

    if (event.key == TB_KEY_BACKSPACE2) {
        ui_erase_character(ui);
        return 0;
    }

    ui_input_character(ui, event.ch);
    return 0;
}

// Renders the TUI according to the state in the struct UserInterface
static void ui_render(UserInterface *ui) {
    tb_clear();

    tb_set_cursor(ui->input_buffer_cursor, tb_height());
    tb_printf(2, 1, TB_CYAN, 0, "width=%d height=%d", tb_width(), tb_height());

    ui_render_input_line(ui);
    ui_render_results(ui);

    tb_present();
}

void ui_init(UserInterface *ui) {
    tb_init();
    stack_init(&ui->results);
}

void ui_shutdown(UserInterface *ui) { tb_shutdown(); }

void ui_append_result(UserInterface *ui, Symbol result) {
    stack_push(&ui->results, result);
}

int ui_main(UserInterface *ui, char *out_expression) {
    ui_render(ui);
    return ui_handle_keyboard_input(ui, out_expression);
}
