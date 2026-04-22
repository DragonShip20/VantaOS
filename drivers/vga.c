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

    u16 index = (cursor_pos.y * 80 + cursor_pos.x);
    return;
}

void out_char(u8 c) {
    u32 index = (cursor_pos.y * 80) + cursor_pos.x;
    screen[index].c = c;
    screen[index].color = 0x0F;
    return;
}