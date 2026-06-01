#include <main/types.h>
#include <drivers/vesa.h>
#include <drivers/text_mode.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

void kernel_main() {

    init_idt();
    init_vesa();

    print("Say my name\n");
    asm volatile ("int $42");
    print("Heisenberg");
    
    while (1) {
        asm volatile ("hlt");
    }
}
