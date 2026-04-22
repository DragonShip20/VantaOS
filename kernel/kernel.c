#include <main/types.h>
#include <drivers/vga.h>
#include <arch/idt.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();

    out_char('W');
    upd_cursor(1, 0);
    out_char('o');
    upd_cursor(1, 0);
    out_char('r');
    upd_cursor(1, 0);
    out_char('k');
    upd_cursor(1, 0);
    out_char('s');
    upd_cursor(1, 0);

    render();
    
    while (1);
}