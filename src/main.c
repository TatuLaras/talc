#define TB_IMPL
#include "external/termbox2.h"
#include "lexer.h"

int main() {
    struct tb_event ev;
    int cursor_x = 0;
    int cursor_y = 0;

    tb_init();

    char *str = "Hello this is me!";
    while (1) {
        tb_printf(2, 2, TB_CYAN, 0, "width=%d height=%d", tb_width(),
                  tb_height());

        Symbol symbols[1024] = {0};
        // divide_into_symbols(str, symbols, 1024);

        tb_printf(2, 3, TB_RED, 0, "str: %s", symbols);

        tb_set_cursor(cursor_x, cursor_y);
        tb_present();

        tb_poll_event(&ev);

        if (ev.ch == 'q')
            break;

        if (ev.ch == 'h')
            cursor_x--;
        if (ev.ch == 'j')
            cursor_y++;
        if (ev.ch == 'k')
            cursor_y--;
        if (ev.ch == 'l')
            cursor_x++;
    }

    tb_shutdown();

    return 0;
}
