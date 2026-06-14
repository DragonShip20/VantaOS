#include <mm/pmm.h>

u8 *bitmap = (u8*)&_kernel_end;
u32 bitmap_len = 0;
u64 used_pages[12] = {0x0, 0x7000, 0x8000, 0x9000, 0xA000, 0x10000, 0x11000, 0x12000, 0x13000, 0x14000, 0x15000, 0x16000};

/* For now the addresses are 32 bits but we will switch to long mode */
u32 alloc_page(u64 count) {
    for (u64 i=0; i<=bitmap_len; i++) {
        if (bitmap_bit(i)) {
            continue;
        }
        for (u64 j=0; j<count; j++) {
            if (bitmap_bit(i+j))
                break;
            if (!bitmap_bit(i+j) && j==(count-1)) {
                bitmap_set(i*0x1000, count*0x1000);
                return i*0x1000;
            }
        }
    }
    /* For now we return 1 if there is an error */
    return 1; /* A normal call will NEVER return 1 */
}

void free(u32 addr) {
    for (int i=addr; bitmap_bit(i/0x1000); i+=0x1000) {
        bitmap_clear_bit((u64)i);
    }
}

static inline u8 bitmap_bit(u64 bit) {
    return (bitmap[bit >> 3] >> (bit & 7)) & 1;
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
        bitmap_clear_bit(p);
    }
}

