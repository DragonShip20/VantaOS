#include <main/types.h>
#include <drivers/vesa.h>
#include <drivers/text_mode.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();
    init_vesa();

    /* Dividing by 10 because cell dimensions are 10x10 */
    int screen_w = width / 10;
    int screen_h = height / 10;

    /* Dumps the font to the screen */
    for (int x=65; x<91; x++) {
        vesa_screen[x].fg = fg;
        vesa_screen[x].bg = bg;
        for (int i=0; i<8; i++) {
            vesa_screen[x].glyph[i] = font[x][i];
        }
        draw_cell(vesa_screen[x], x-65, 0);
    }
    flush();
        
    while (1) {
        asm volatile ("hlt");
    }
}
