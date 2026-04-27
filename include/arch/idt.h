#ifndef IDT_H
#define IDT_H

#include <main/types.h>

struct idt_entry {
    u16 offset_1;
    u16 selector;
    u8 zero;
    u8 type_attributes;
    u16 offset_2;
} __attribute__((packed));

struct idt_desc {
    u16 limit;
    u32 base;
} __attribute__((packed));

void dummy_func(void);
void init_idt(void);
static void set_idt_gate(int gate, void *func);
static void lidt(u32 base, u16 limit);

#endif