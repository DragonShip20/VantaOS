#include <main/types.h>
#include <drivers/vesa.h>
#include <drivers/text_mode.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();
    init_vesa();

    /* Dumps the font to the screen */
    for (int x=65; x<91; x++) {
        vesa_screen[x - 65].fg = fg;
        vesa_screen[x - 65].bg = bg;
        vesa_screen[x - 65].dirty = 1;
        for (int i=0; i<8; i++) {
            vesa_screen[x - 65].glyph[i] = font[x][i];
        }
    }
    render_cells();
    
    while (1) {
        asm volatile ("hlt");
    }
}
