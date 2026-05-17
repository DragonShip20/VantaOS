#include <main/types.h>
#include <drivers/vesa.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();
    init_vesa();
    u16 white = make_color(255, 255, 255);
    for (int x=20; x<120; x++) {
        for (int y=20; y<120; y++) {
            put_pixel(white, x, y);
        }
    }
    flush();
        
    while (1) {
        asm volatile ("hlt");
    }
}
