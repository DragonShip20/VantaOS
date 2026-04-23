#include <main/types.h>
#include <drivers/vga.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();
    init_stdout();

    stdout.stdout("Working!");
    
    while (1);
}