#include <main/types.h>
#include <drivers/vesa.h>
#include <drivers/text_mode.h>
#include <arch/idt.h>
#include <kernel/stdout.h>
#include <mm/mmap.h>

void kernel_main() {

    init_vesa();
    print("VESA display and framebuffer initialised and loaded.\n");
    init_idt();
    print("Interrupt Descriptor Table initialised and loaded.\n");
    init_mm();
    print("E820 ram map initialised and loaded.\n");

    while (1) {
        asm volatile ("hlt");
    }
}
