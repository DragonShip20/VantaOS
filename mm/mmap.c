#include <mm/mmap.h>

e820_entry mem_map[128]; /* For now we only support 128 entries */

void init_mm(void) {
    e820_entry* mmap = (e820_entry*)E820_ADDR;

    for (u16 i=0; i<E820_COUNT; i++) {
        mem_map[i] = mmap[i];
    }
}
