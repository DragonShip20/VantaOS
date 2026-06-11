#include <mm/pmm.h>

u8 *bitmap = (u8*)&_kernel_end;
u32 bitmap_len = 0;
u64 used_pages[5] = {0x0, 0x7000, 0x8000, 0x9000, 0xA000};

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

