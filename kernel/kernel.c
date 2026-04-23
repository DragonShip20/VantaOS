#include <main/types.h>
#include <drivers/vga.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();

    vga_print("The stdout system works!");
    
    while (1);
}