#include <main/types.h>
#include <drivers/vesa.h>
#include <drivers/text_mode.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();
    init_vesa();

    /* Dump the font to the screen */
    for (int i=32; i<127; i++) {
        putc(i);
        vesa_set_cursor(vcursor.x + 1, vcursor.y);
        if (i==47 || i==64 || i==90 || i==96 || i==122)
            vesa_set_cursor(0, vcursor.y + 1);
    }
    render_cells();
    
    while (1) {
        asm volatile ("hlt");
    }
}
