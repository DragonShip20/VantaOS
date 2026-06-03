#include <main/types.h>
#include <arch/idt.h>
#include <drivers/text_mode.h>

struct idt_entry idt[256];
extern void isr_common(void);
extern void *isr_stubs[256];
extern void *isr_stubs_end[];

/* This is the exact stack order, with edi being the youngest */
const char *regs[] =
    {"EDI", "ESI", "EBP", "ESP", "EBX",
     "EDX", "ECX", "EAX", "RET ADDRESS", "INT", "ERR CODE", "EIP", "CS", "EFLAGS"};

void init_idt(void) {
    /* TODO: add separate isr stubs for interrupts */
    for (int i=0; i<256; i++) {
        set_idt_gate(i, (void (*)())isr_stubs[i]);
    }
    
    void *base = &idt;
    u16 limit = sizeof(idt) - 1;
    lidt((u32)base, limit);

    return;
}

static void set_idt_gate(int gate, void *func) {
    u32 addr = (u32)func;

    idt[gate].offset_1 = addr & 0xFFFF; /* Given function */
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

void isr_dispatcher(u32* esp) {
    print("INTERRUPT\n");

    /* Stack dumping (which means all registers) */
    for (int i=0; i<14; i++) {
        /* Checking for ret address */
        if (i==8)
            continue;
        print(regs[i]);
        putc(' ');
        print_hex_u32(esp[i]);
        if (i>=3 && i%5==0) {
            print("\n");
            continue;
        }
        putc(' ');
    }
    print("\n\n");
    return;
}
