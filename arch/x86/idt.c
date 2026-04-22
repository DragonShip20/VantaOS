#include <main/types.h>
#include <arch/idt.h>

struct idt_entry idt[256];
struct idt_desc idt_descriptor;

void dummy_func(void) {
    __asm__ volatile ("iret");
}

void init_idt(void) {
    u32 addr = (u32)dummy_func;

    for (int i=0; i<256; i++) {
        idt[i].offset_1 = addr & 0xFFFF;
        idt[i].selector = 0x08;
        idt[i].zero = 0;
        idt[i].type_attributes = 0x8E;
        idt[i].offset_2 = (addr >> 16) & 0xFFFF;
    }

    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base = (u32)&idt;

    __asm__ volatile ("lidt %0" : : "m"(idt_descriptor));
    
    return;
}