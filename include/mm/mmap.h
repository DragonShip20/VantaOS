#ifndef MMAP_H
#define MMAP_H

#include <main/types.h>

/* E820 info location */
#define E820_ADDR 0x9000
#define E820_COUNT *(u16*)0xA000

typedef struct e820_entry {
    u64 address;
    u64 len;
    u32 type;
    u32 attrs;
} __attribute__((packed)) e820_entry;

extern e820_entry mem_map[];
extern u64 hi_addr;

void init_mm(void);
void handle_e820(u32 addr, u16 count);

#endif
