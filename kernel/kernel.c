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
    vcursor.x += 1;
    putc('E');
    vcursor.x += 1;
    putc('L');
    vcursor.x += 1;
    putc('L');
    vcursor.x += 1;
    putc('O');
    vcursor.x += 2;
    putc('W');
    vcursor.x += 1;
    putc('O');
    vcursor.x += 1;
    putc('R');
    vcursor.x += 1;
    putc('L');
    vcursor.x += 1;
    putc('D');
    vcursor.x += 1;
    render_cells();
    
    while (1) {
        asm volatile ("hlt");
    }
}
