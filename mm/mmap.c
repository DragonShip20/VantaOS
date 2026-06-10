#include <mm/mmap.h>

e820_entry mem_map[128]; /* For now we only support 128 entries */
u64 hi_addr = 0; /* The highest Physical Adress Space address for the PMM */
u8 *bitmap = (u8*)&_kernel_end;
u32 bitmap_len = 0;

u64 used_pages[5] = {0x0, 0x7000, 0x8000, 0x9000, 0xA000};

void init_mm(void) {
    handle_e820(E820_ADDR, E820_COUNT);
    init_pmm(mem_map, E820_COUNT);
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

void init_pmm(e820_entry *map, u16 count) {
    bitmap_len = hi_addr / 0x8000; /* Every bit maps 4kb */
    memset((void*)bitmap, bitmap_len, 0xFF); /* Setting everything first */

    for (u16 i=0; i<count; i++) {
        /* Clearing the type 1 memory regions */
        if (map[i].type == 1)
            bitmap_clear(map[i].address, map[i].len);
    }

    /* Setting the kernel as used */
    u64 kernel_start_diff = (u64)((u32)&_kernel_start % (u32)0x1000);
    u64 kernel_end_diff = (u64)((u32)&_kernel_end % (u32)0x1000);
    u64 kernel_page_start = (u64)((u32)&_kernel_start) - kernel_start_diff ;
    u64 kernel_page_end = (u64)((u32)&_kernel_end) - kernel_end_diff;
    bitmap_set(kernel_page_start, kernel_page_end - kernel_page_start);

    /* Setting used pages */
    for (int i=0; i<5; i++) {
        bitmap_set(used_pages[i], 0x1000);
    }
}

static inline void bitmap_set_bit(u64 page) {
    /* Dividing by 8 because we're operating on u8 */
    bitmap[page / 8] |= (1 << (page & 7));
}

static inline void bitmap_clear_bit(u64 page) {
    /* TODO: replace this unclear bit procedure with BIT() function */
    bitmap[page / 8] &= ~(1 << (page & 7));
}

void bitmap_set(u64 addr, u64 len) {
    u64 first = addr / 0x1000; /* TODO: replace magic number with definition */
    u64 last  = (addr + len - 1) / 0x1000;
    for (u64 p=first; p<=last; p++) {
        bitmap_set_bit(p);
    }
}

void bitmap_clear(u64 addr, u64 len) {
    u64 first = addr / 0x1000;
    u64 last  = (addr + len - 1) / 0x1000;
    for (u64 p=first; p<=last; p++) {
        bitmap_set_bit(p);
    }
}
