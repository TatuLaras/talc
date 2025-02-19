#include "user_interface.h"
#include "external/termbox2.h"
#include "results_buffer.h"
#include "ui_helpers.h"
#include "variables.h"

static void input_character(UserInterface *ui, char character) {
    if (ui->input_buffer_used >= UI_INPUT_BUFFER_SIZE ||
        ui->input_buffer_used >= tb_width() - 1)
        return;

    ui->input_buffer[ui->input_buffer_used++] = character;
    ui->input_buffer_cursor++;
}

static void reset_input(UserInterface *ui) {
    ui->input_buffer_used = 0;
    ui->input_buffer_cursor = 0;
}

// Renders the current input buffer as an input line in the bottom of the TUI
static void render_input_line(UserInterface *ui) {
    int row = tb_height() - 1;

    // Input buffer
    for (int i = 0; i < ui->input_buffer_used; i++) {
        tb_set_cell(i, row, ui->input_buffer[i], TB_BLACK, TB_WHITE);
    }

    // Rest of the line (to get background color for the whole line)
    for (int i = ui->input_buffer_used; i < tb_width(); i++) {
        tb_set_cell(i, row, ' ', TB_BLACK, TB_WHITE);
    }
}

// Renders a "status line" above the input line
static void render_status_line(UserInterface *ui, VariableStorage *var) {
    int row = tb_height() - 2;

    if (ui->erroneus && ui->input_buffer_cursor == 0) {
        tb_printf(0, row, TB_WHITE, TB_RED, " ERROR ");
        return;
    }

    // Summary of the currently typed function or variable
    char out_name[100] = {0};
    if (ui_helper_get_currently_typed_name(ui, out_name, 99, 0))
        return;

    char out_suggestion[100] = {0};
    if (ui_helper_get_summary(out_name, var, out_suggestion, 99))
        return;

    tb_printf(0, row, TB_BLACK, TB_BLUE, out_suggestion);
}

// Renders the contents of the results buffer onto the TUI
static void render_results(UserInterface *ui) {
    int line = tb_height() - 3;
    int i = 0;

    Result result = {0};
    while (!results_buffer_get_latest(&ui->results, i, &result)) {
        i++;

        if (result.erroneous)
            continue;

        tb_printf(1, line--, TB_DEFAULT, TB_DEFAULT, " = %lg", result.result);
        tb_printf(1, line--, TB_DEFAULT, TB_DEFAULT, result.expression);
        line--;
    }
}

// Shows some keyboard shortcuts in the top part of the screen
static void render_help_message(UserInterface *ui) {
    int line = 1;

    tb_printf(2, line++, TB_CYAN, 0, "Ctrl+C to quit");
    tb_printf(2, line++, TB_CYAN, 0, "Ctrl+L to clear");
    tb_printf(2, line++, TB_CYAN, 0, "Tab to autocomplete suggestion");
}

// Renders the TUI according to the state in the struct UserInterface
static void render(UserInterface *ui, VariableStorage *var) {
    tb_clear();

    tb_set_cursor(ui->input_buffer_cursor, tb_height());

    if (ui->results.count == 0)
        render_help_message(ui);

    render_input_line(ui);
    render_status_line(ui, var);
    render_results(ui);

    tb_present();
}

static void erase_character(UserInterface *ui) {
    if (ui->input_buffer_used <= 0 || ui->input_buffer_cursor <= 0)
        return;
    ui->input_buffer_used--;
    ui->input_buffer_cursor--;
}

static void autocomplete_input(UserInterface *ui, VariableStorage *var) {
    char name[100] = {0};
    int start_position = 0;
    if (ui_helper_get_currently_typed_name(ui, name, 99, &start_position))
        return;

    char completion[100] = {0};
    int is_function = 0;
    if (ui_helper_get_completion(name, var, completion, 99, &is_function))
        return;

    ui->input_buffer_used = start_position;
    ui->input_buffer_cursor = start_position;

    for (int i = 0; completion[i]; i++) {
        input_character(ui, completion[i]);
    }

    if (is_function)
        input_character(ui, '(');
}

// Handles special hotkeys and inserts other keys into the input buffer
//
// Returns with event codes described by the UI_CODE... contants in the header
// file, meant to be passed straight to the caller of ui_main
static int ui_handle_keyboard_input(UserInterface *ui, VariableStorage *var,
                                    char *out_expression) {
    struct tb_event event;

    tb_poll_event(&event);

    if (event.key == TB_KEY_CTRL_C)
        return UI_CODE_QUIT;

    if (event.key == TB_KEY_ENTER) {
        strncpy(out_expression, ui->input_buffer, ui->input_buffer_used);
        out_expression[ui->input_buffer_cursor] = 0;
        reset_input(ui);
        return UI_CODE_INPUT_READY;
    }

    if (event.key == TB_KEY_TAB) {
        autocomplete_input(ui, var);
        return 0;
    }

    if (event.key == TB_KEY_BACKSPACE2 || event.key == TB_KEY_BACKSPACE) {
        erase_character(ui);
        return 0;
    }

    if (event.key == TB_KEY_CTRL_P || event.key == TB_KEY_ARROW_UP) {
        //  TODO: previous result into buffer
        return 0;
    }

    if (event.key == TB_KEY_CTRL_N || event.key == TB_KEY_ARROW_DOWN) {
        //  TODO: next result into buffer
        return 0;
    }

    if (event.key == TB_KEY_CTRL_L) {
        results_buffer_clear(&ui->results);
        return 0;
    }

    input_character(ui, event.ch);
    return 0;
}

void ui_init(UserInterface *ui) { tb_init(); }

void ui_shutdown(UserInterface *ui) { tb_shutdown(); }

void ui_append_result(UserInterface *ui, Result result) {
    results_buffer_push(&ui->results, result);
}

int ui_main(UserInterface *ui, VariableStorage *var, char *out_expression) {
    render(ui, var);
    return ui_handle_keyboard_input(ui, var, out_expression);
}
