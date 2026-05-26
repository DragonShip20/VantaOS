#include <main/types.h>
#include <drivers/vesa.h>
#include <drivers/text_mode.h>
#include <arch/idt.h>
#include <kernel/stdout.h>

void kernel_main() {

    init_idt();
    init_vesa();

    print("The quick brown fox jumps over the lazy dog");
    
    while (1) {
        asm volatile ("hlt");
    }
}
