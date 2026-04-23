#include <main/types.h>
#include <drivers/vga.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();
    init_stdout();

    stdout.stdout("Works!");
    set_cursor(0, 1);
    stdout.stdout("This message is a test");
    
    while (1);
}