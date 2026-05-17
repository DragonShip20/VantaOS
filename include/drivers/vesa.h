#ifndef VESA_H
#define VESA_H

#include <main/types.h>

/* 512 byte struct, BIOS given vesa mode info */
typedef struct __attribute__((packed)) vbe_mode_info_t {
    u16 attributes;
    u8  window_a;
    u8  window_b;
    u16 granularity;
    u16 window_size;
    u16 segment_a;
    u16 segment_b;
    u32 win_func_ptr;
    u16 pitch;
    u16 width;
    u16 height;
    u8  w_char;
    u8  y_char;
    u8  planes;
    u8  bpp;
    u8  banks;
    u8  memory_model;
    u8  bank_size;
    u8  image_pages;
    u8  reserved0;

    u8  red_mask;
    u8  red_position;
    u8  green_mask;
    u8  green_position;
    u8  blue_mask;
    u8  blue_position;
    u8  reserved_mask;
    u8  reserved_position;
    u8  directcolor_info;

    u32 framebuffer;
    u32 offscreen_mem;
    u16 offscreen_size;

    u8  reserved[206];
} vbe_mode_info;

extern vbe_mode_info* vbe;
extern u16 *fb;
extern u16 *backbuffer;
extern u16 width;
extern u16 height;
extern u16 pitch;
extern u8 bpp;

extern u16 bg;
extern u16 fg;

u16 make_color(u8 r, u8 g, u8 b);
void init_vesa(void);
void flush(void);
void put_pixel(u16 color, int x, int y);

#endif
