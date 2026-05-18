#ifndef VESA_TEXT_MODE_H
#define VESA_TEXT_MODE_H

#include <main/types.h>
#include <main/font.h>
#include <drivers/vesa.h>

#define PIX(x) (1 << (7 - (x))) /* Set x bit of u8 value */

typedef struct vcell {
    u16 fg;
    u16 bg;
    glyph_t glyph;
} vcell;

extern vcell *vscreen;

void draw_cell(vcell c, u32 x, u32 y);

#endif
