#include <main/font.h>

/* 8x8 VGA style bitmap font */
glyph_t font[256] =
{
    ['A'] = {
       0b00000000,
       0b00011000,
       0b01100110,
       0b11000011,
       0b11000011,
       0b11111111,
       0b11000011,
       0b11000011
    }
};
