#ifndef VGA_H
#define VGA_H

#include <main/types.h>

typedef struct {
    u32 x;
    u32 y;
} pos;

/* Memory layout of every field in VGA text mode */
typedef struct {
    u8 c;
    u8 color;
} vga_cell;

void render(void);
void out_char(u8 c);
void upd_cursor(u32 x, u32 y);
pos get_cursor(void);
int set_cursor(u32 x, u32 y);
void cell_move(u32 x1, u32 y1, u32 x2, u32 y2);
void cell_copy(u32 x1, u32 y1, u32 x2, u32 y2);

#endif
