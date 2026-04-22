#include <main/types.h>
#include <drivers/vga.h>
#include <arch/idt.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();

    out_char('A');
    cursor_pos.x += 1;
    out_char('B');
    render();

    while (1);
}