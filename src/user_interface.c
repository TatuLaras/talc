#include "user_interface.h"
#include "external/termbox2.h"
#include "results_buffer.h"

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
static void ui_render_status_line(UserInterface *ui) {
    int row = tb_height() - 2;

    if (ui->erroneus)
        tb_printf(0, row, TB_WHITE, TB_RED, " ERROR ");
}

// Renders the contents of the results buffer onto the TUI
static void ui_render_results(UserInterface *ui) {
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
static void ui_render_help_message(UserInterface *ui) {
    int line = 1;

    tb_printf(2, line++, TB_CYAN, 0, "ctrl+c to quit");
    tb_printf(2, line++, TB_CYAN, 0, "ctrl+l to clear");
}

// Renders the TUI according to the state in the struct UserInterface
static void ui_render(UserInterface *ui) {
    tb_clear();

    tb_set_cursor(ui->input_buffer_cursor, tb_height());

    if (ui->results.count == 0)
        ui_render_help_message(ui);

    ui_render_input_line(ui);
    ui_render_status_line(ui);
    ui_render_results(ui);

    tb_present();
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

    if (event.key == TB_KEY_CTRL_C)
        return UI_CODE_QUIT;

    if (event.key == TB_KEY_ENTER) {
        strncpy(out_expression, ui->input_buffer, ui->input_buffer_used);
        out_expression[ui->input_buffer_cursor] = 0;
        ui_reset_input(ui);
        return UI_CODE_INPUT_READY;
    }

    if (event.key == TB_KEY_BACKSPACE2 || event.key == TB_KEY_BACKSPACE) {
        ui_erase_character(ui);
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

    ui_input_character(ui, event.ch);
    return 0;
}

void ui_init(UserInterface *ui) { tb_init(); }

void ui_shutdown(UserInterface *ui) { tb_shutdown(); }

void ui_append_result(UserInterface *ui, Result result) {
    results_buffer_push(&ui->results, result);
}

int ui_main(UserInterface *ui, char *out_expression) {
    ui_render(ui);
    return ui_handle_keyboard_input(ui, out_expression);
}
