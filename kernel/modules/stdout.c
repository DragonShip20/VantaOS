#include <main/types.h>
#include <drivers/vga.h>
#include <kernel/stdout.h>

void vga_print(const u8* s) {
    while (*s) {
        out_char(*s);
        upd_cursor(1, 0);
        s++;
    }
    render();
    return;
}