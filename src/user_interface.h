// Wraps the termbox2 TUI library and provides easier handling of user input and
// printing of calculation results

#ifndef _UI
#define _UI

#include "results_buffer.h"
#include "symbol.h"
#include "symbol_stack.h"

#define UI_INPUT_BUFFER_SIZE 1024

#define UI_CODE_QUIT 1
#define UI_CODE_INPUT_READY 2

typedef struct {
    char input_buffer[UI_INPUT_BUFFER_SIZE];
    int input_buffer_used;
    int input_buffer_cursor;
    ResultsBuffer results;
    int erroneus;
} UserInterface;

// Initializes the necessary internal buffers.
//
// Call this before using any of the other ui functions.
void ui_init(UserInterface *ui);

// Appends a result to the list of results that can be rendered via the
// ui_render_results function
void ui_append_result(UserInterface *ui, Result result);

// Renders the TUI according to state in UserInterface struct and responds to
// keyboard input
//
// Returns with a code described by the UI_CODE ... constants in this header
// file
int ui_main(UserInterface *ui, VariableStorage *var, char *out_expression);

// De-initializes the internal buffers (of the termbox2 library mainly).
void ui_shutdown(UserInterface *ui);

#endif
