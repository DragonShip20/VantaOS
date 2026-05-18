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

    /* Floods the screen with A */
    for (int x=0; x<screen_w; x++) {
        for (int y=0; y<screen_h; y++) {
            vscreen[y * screen_w + x].fg = fg;
            vscreen[y * screen_w + x].bg = bg;
            for (int i=0; i<8; i++) {
                vscreen[y * screen_w + x].glyph[i] = font['A'][i];
            }
            draw_cell(vscreen[y * screen_w + x], x, y);
        }
    }
    flush();
        
    while (1) {
        asm volatile ("hlt");
    }
}
