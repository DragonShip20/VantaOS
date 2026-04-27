#include <main/types.h>
#include <arch/idt.h>

struct idt_entry idt[256];
struct idt_desc idt_descriptor;

void dummy_func(void) {
    __asm__ volatile ("iret");
}

void init_idt(void) {
    for (int i=0; i<256; i++) {
        set_idt_gate(i, dummy_func);
    }

    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base = (u32)&idt;

    __asm__ volatile ("lidt %0" : : "m"(idt_descriptor));
    
    return;
}

static void set_idt_gate(int gate, void *func) {
    u32 addr = (u32)func;

    idt[gate].offset_1 = addr & 0xFFFF;
    idt[gate].selector = 0x08;
    idt[gate].zero = 0;
    idt[gate].type_attributes = 0x8E;
    idt[gate].offset_2 = (addr >> 16) & 0xFFFF;
}