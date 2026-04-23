#include <main/types.h>
#include <drivers/vga.h>

#define HEIGHT 25
#define WIDTH 80

cell screen[WIDTH * HEIGHT];
pos cursor_pos = {0, 0};

void render(void) {
    u16* vga = (u16*)0xB8000;

    for (int i=0; i< (WIDTH * HEIGHT); i++) {
            vga[i] = screen[i].c | (screen[i].color << 8);
    }
    return;
}

void out_char(u8 c) {
    u32 index = (cursor_pos.y * WIDTH) + cursor_pos.x;
    screen[index].c = c;
    screen[index].color = 0x0F;
    return;
}

void upd_cursor(u32 x, u32 y) {
    cursor_pos.x += x;
    if (cursor_pos.x >= WIDTH) {
        cursor_pos.y += (cursor_pos.x / WIDTH);
        cursor_pos.x %= WIDTH;
    }
    cursor_pos.y += y;
    return;
}

int set_cursor(u32 x, u32 y) {
    if (x >= WIDTH || y >= HEIGHT)
        return -1;
    cursor_pos.x = x;
    cursor_pos.y = y;
    return 0;
}

pos get_cursor(void) {
    return cursor_pos;
}