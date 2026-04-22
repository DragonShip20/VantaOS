#include <main/types.h>
#include <drivers/vga.h>
#include <arch/idt.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();

    upd_cursor(2, 1);
    out_char('a');
    render();
    
    while (1);
}