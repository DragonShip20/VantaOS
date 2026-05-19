#include <drivers/vesa.h>

/* Necessary vesa variables, operating on 16 bpp and 16 bit color */
vbe_mode_info* vbe = 0;
u16 *fb = 0;
u16 *backbuffer = (u16*)0x1000000; /* TODO: replace fixed address with allocated memory */
u16 width = 0;
u16 height = 0;
u16 pitch = 0;
u8 bpp = 0;

u16 bg = 0;
u16 fg = 0;

/* This vesa mode uses RGB565 */
u16 make_color(u8 r, u8 g, u8 b) {
    return ((r >> 3) << 11) |
           ((g >> 2) << 5 ) |
           ((b >> 3));
}

/* TODO: replace manual memory copying with memcpy */
void flush(void) {
    for (int y=0; y<height; y++) {
        /* Addressing by rows */
        /* Framebuffer needs to be converted to u8 because pitch */
        /* is a u8 value (byte) */
        
        u16 *row = (u16*)((u8*)fb + y * pitch);
        for (int x=0; x<width; x++) {
            
            /* backbuffer[y*width+x] = fb[y*pitch+x] */
            row[x] = backbuffer[y * width + x];
        }
    }
}

void init_vesa(void) {
    /* Setup global VBE variables */
    vbe = (vbe_mode_info*)0x8000;
    fb = (u16*)vbe->framebuffer;
    width = vbe->width;
    height = vbe->height;
    pitch = vbe->pitch;
    bpp = vbe->bpp;

    bg = make_color(0, 0, 255);
    fg = make_color(255, 255, 255);

    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            backbuffer[y * width + x] = bg;
        }
    }
}

void put_pixel(u16 color, int x, int y) {
    backbuffer[y * width + x] = color;
}
