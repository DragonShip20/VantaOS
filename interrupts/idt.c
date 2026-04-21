#include "types.h"

typedef struct {
    u16 offset_1;
    u16 selector;
    u8 zero;
    u8 type_attributes;
    u16 offset_2;
} __attribute__((packed)) idt_entry;

typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_desc;

idt_entry idt[256];
idt_desc idt_descriptor;

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