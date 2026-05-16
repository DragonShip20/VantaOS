#include <main/types.h>
#include <drivers/vesa.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

extern pos cursor_pos;

void kernel_main() {

    init_idt();
    init_vesa();
        
    while (1);
}
