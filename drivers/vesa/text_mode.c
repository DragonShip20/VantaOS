#include <drivers/text_mode.h>

/* TODO: replace fixed address width memory allocation */
vcell *vscreen = (vcell*)0x900000;

void draw_cell(vcell c, u32 x, u32 y) {
    for (int row=0; row<10; row++) {
        for (int col=0; col<10; col++) {
            /* Check for cell edges (padding) */
            if ((col <= 1 || row <= 1) || (col > 9 && row > 9)) {
                put_pixel(c.bg, x*10+col, y*10+row);
                continue;
            }
            /* Check glyph bit by bit (-2 to adjust for laps) */
            if (c.glyph[row - 2] & PIX(col - 2)) {
                put_pixel(c.fg, x*10+col, y*10+row);
                continue;
            }
            put_pixel(c.bg, x*10+col, y*10+row);
        }
    }
}
