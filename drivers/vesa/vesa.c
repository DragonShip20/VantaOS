#include <drivers/vesa.h>

vbe_mode_info* vbe = 0;
u32* fb = 0;
int width = 0;
int height = 0;
int pitch = 0;

u16 bg = 0;
u16 fg = 0;

u16 make_color(u8 r, u8 g, u8 b) {
    return ((r >> 3) << 11) |
           ((g >> 2) << 5 ) |
           ((b >> 3));
}

void init_vesa(void) {
    vbe = (vbe_mode_info*)0x8000;
    fb = (u32*)vbe->framebuffer;
    width = vbe->width;
    height = vbe->height;
    pitch = vbe->pitch / 4;

    bg = make_color(50, 150, 0);
    fg = make_color(255, 255, 255);

    for (int y = 0; y < height; y++) {
        u16* row = (u16*)(fb + y * pitch);

        for (int x = 0; x < width; x++) {
            row[x] = bg;
        }
    }
}

