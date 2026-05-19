#include <main/types.h>
#include <drivers/vesa.h>
#include <drivers/text_mode.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();
    init_vesa();

    putc('H');
    vesa_set_cursor(1, 0);
    putc('E');
    vesa_set_cursor(2, 0);
    putc('L');
    vesa_set_cursor(3, 0);
    putc('L');
    vesa_set_cursor(4, 0);
    putc('O');
    vesa_set_cursor(0, 1);
    putc('W');
    vesa_set_cursor(1, 1);
    putc('O');
    vesa_set_cursor(2, 1);
    putc('R');
    vesa_set_cursor(3, 1);
    putc('L');
    vesa_set_cursor(4, 1);
    putc('D');
    vesa_set_cursor(5, 1);
    render_cells();
    
    while (1) {
        asm volatile ("hlt");
    }
}
