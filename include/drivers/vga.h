#ifndef VGA_H
#define VGA_H

#include <main/types.h>

typedef struct {
    u32 x;
    u32 y;
} pos;

typedef struct {
    u8 c;
    u8 color;
} cell;

void render(void);
void out_char(u8 c);
void upd_cursor(u32 x, u32 y);
pos get_cursor(void);
int set_cursor(u32 x, u32 y);

#endif