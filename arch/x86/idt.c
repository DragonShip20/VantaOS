#include <main/types.h>
#include <arch/idt.h>

struct idt_entry idt[256];

/* TODO: add register (and maybe stack) dumping on exception */
void dummy_func(void) {
    __asm__ volatile ("iret");
}

void init_idt(void) {
    /* TODO: replace dummy function with real IDT dispatcher */
    for (int i=0; i<256; i++) {
        set_idt_gate(i, dummy_func);
    }

    void *base = &idt;
    u16 limit = sizeof(idt) - 1;
    lidt((u32)base, limit);

    return;
}

static void set_idt_gate(int gate, void *func) {
    u32 addr = (u32)func;

    idt[gate].offset_1 = addr & 0xFFFF; /* Dummy function */
    idt[gate].selector = 0x08;          /* Code segment */
    idt[gate].zero = 0;                 /* Reserved */
    idt[gate].type_attributes = 0x8E;   /* Interrupt gate attribute */
    idt[gate].offset_2 = (addr >> 16) & 0xFFFF;
}

static void lidt(u32 base, u16 limit) {
    struct idt_desc descriptor;
    descriptor.limit = limit;
    descriptor.base = base;

    __asm__ volatile ("lidt %0" : : "m"(descriptor));
}
