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
    /* TODO: add custom bg and fg instead of fixed ones */
    vesa_screen[index].fg = fg;
    vesa_screen[index].bg = bg;
    vesa_screen[index].dirty = 1;
    for (int i=0; i<8; i++) {
        /* Setting each row separately is necesary */
        vesa_screen[index].glyph[i] = font[c][i]; 
    }
    vesa_upd_cursor(1, 0);
}

int vesa_set_cursor(u32 x, u32 y) {
    /* Checking for screen boundries */
    if (x > screen_w || y > screen_h)
        return 1;
    vcursor.x = x;
    vcursor.y = y;
}

u8 parse_escape(u8 c) {
    /* Function takes the next char after the \ */
    switch (c) {
    case 'n':
        vesa_set_cursor(0, vcursor.y+1);
        return 0; /* Return 0 if this function handles it */
    case 't':
        vesa_set_cursor(vcursor.x+4, vcursor.y);
        return 0;
    case 'b':
        vesa_set_cursor(vcursor.x-1, vcursor.y);
        return 0;
    case 'r':
        vesa_set_cursor(0, vcursor.y);
        return 0;
    case 'a':
        /* TODO: add actual bell ringing here */
        return 0;
    case '\'':
        return '\''; /* Return normal char if this just needs printing */
    case '"':
        return '"';
    case '?':
        return '?';
    case '\\':
        return '\\';
    case 'f':
        /* We do not support form feed, print space */
        return ' ';
    case 'v':
        vesa_set_cursor(0, vcursor.y+4);
        return 0;
    case '0':
        return 1; /* Return 1 if the char is the null terminator */
    default:
        return 2; /* Return 2 if the char is unexpected */
    }
    /* We do not yet support printing octal and hex with this function */
}

void vesa_upd_cursor(u32 x, u32 y) {
    if (vcursor.x + x > screen_w) {
        vcursor.x += x % screen_w;
        vcursor.y += y / screen_w;
    } else {
        vcursor.x += x;
    }
    if (vcursor.y + y > screen_h) {
        vcursor.x = screen_w - 1;
        vcursor.y = screen_h;
    } else {
        vcursor.y += y;
    }
}

void print_hex_u32(u32 v) {
    static char hex[] = {
    '0','1','2','3',
    '4','5','6','7',
    '8','9','A','B',
    'C','D','E','F'
    };

    putc('0');
    putc('x');

    for (int i = 7; i >= 0; i--) {
        u8 nibble = (v >> (i * 4)) & 0xF;
        putc(hex[nibble]);
    }
}

