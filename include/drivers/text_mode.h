#ifndef VESA_TEXT_MODE_H
#define VESA_TEXT_MODE_H

#include <main/types.h>
#include <main/font.h>
#include <drivers/vesa.h>

#define PIX(x) (1 << (7 - (x))) /* Set x bit of u8 value */

typedef struct vesa_cell {
    u16 fg;
    u16 bg;
    glyph_t glyph;
    u8 dirty;
} vesa_cell;

typedef struct vesa_cursor {
    u32 x;
    u32 y;
} vesa_cursor;

extern vesa_cell *vesa_screen;
extern int screen_w;
extern int screen_h;
extern vesa_cursor vcursor;

void draw_cell(vesa_cell c, u32 x, u32 y);
void render_cells(void);
void init_vesa_text_mode(void);
void putc(u8 c);
int vesa_set_cursor(u32 x, u32 y);
u8 parse_escape(u8 c);

#endif
