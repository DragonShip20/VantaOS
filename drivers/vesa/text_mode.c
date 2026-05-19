#include <drivers/text_mode.h>

/* TODO: replace fixed address width memory allocation */
vesa_cell *vesa_screen = (vesa_cell*)0x900000;

/* Dividing by 10 because cell dimensions are 10x10 */
int screen_w = 0;
int screen_h = 0;

vesa_cursor vcursor = {0};

void draw_cell(vesa_cell c, u32 x, u32 y) {
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

/* Stage 2 of init_vesa, keeping the compiler happy */
void init_vesa_text_mode(void) {
    /* Dividing by 10 because cell dimensions are 10x10 */
    screen_w = width / 10;
    screen_h = height / 10;
    vcursor.x = 0;
    vcursor.y = 0;
}

void render_cells(void) {
    for (int i=0; i<screen_h*screen_w; i++) {
        /* Checking for dirty cells (optimisation) */
        if (vesa_screen[i].dirty != 1)
            continue;

        draw_cell(vesa_screen[i], i % screen_w, i / screen_w);
    }
    flush();
}

void putc(u8 c) {
    int index = vcursor.y * screen_w + vcursor.x;
    vesa_screen[index].fg = fg;
    vesa_screen[index].bg = bg;
    vesa_screen[index].dirty = 1;
    for (int i=0; i<8; i++) {
        vesa_screen[index].glyph[i] = font[c][i];
    }
}
