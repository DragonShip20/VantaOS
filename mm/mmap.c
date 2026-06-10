#include <mm/mmap.h>

e820_entry mem_map[128]; /* For now we only support 128 entries */
u64 hi_addr = 0; /* The highest Physical Adress Space address for the PMM */
u8 *bitmap = (u8*)&_kernel_end;
u32 bitmap_len = 0;

void init_mm(void) {
    handle_e820(E820_ADDR, E820_COUNT);
    init_pmm();
}

void handle_e820(u32 addr, u16 count) {
    e820_entry *mmap = (e820_entry*)addr;
    /* Map the temporary E820 map in ram to a known array */
    for (u16 i=0; i<count; i++) {
        mem_map[i] = mmap[i];
        /* Count the highest address of Physical Address Space */
        u64 end = mem_map[i].address + mem_map[i].len;
        if (end > hi_addr)
            hi_addr = end;
    }
}

void init_pmm(void) {
    bitmap_len = hi_addr / 0x8000; /* Every bit maps 4kb */
    memset((void*)bitmap, bitmap_len, 0xFF); /* For now everything is set */
}
