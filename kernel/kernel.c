#include <main/types.h>
#include <drivers/vga.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();
    init_stdout();

    stdout.stdout("Not Working!");
    set_cursor(0, 1);
    stdout.stdout("Working!");
    stdout.scroll(1);
    
    while (1);
}