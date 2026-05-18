#include <main/types.h>
#include <drivers/vga.h>
#include <kernel/stdout.h>

#define HEIGHT 25
#define WIDTH 80

struct stdout stdout;

/* TODO: replace vga as stdout with dynamic stdout choosing */
void init_stdout(void) {
    stdout.stdout = (void*)vga_print;
    stdout.scroll = (void*)scroll;
    return;
}

/* TODO: move vga abstraction code to seperate file, keep stdout code here */
void vga_print(const u8* s) {
    /* TODO: check for buffer overflow */
    while (*s) {
        out_char(*s);
        upd_cursor(1, 0);
        s++;
    }
    render();
    return;
}

void scroll(u32 lines) {
    /* TODO: check for valid number of lines */
    for (int y=lines; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            cell_move(x, y, x, (y-lines));
        }
    }
    render();
    return;
}
