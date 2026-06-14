#include <mm/mmap.h>

e820_entry mem_map[128]; /* For now we only support 128 entries */
u64 hi_addr = 0; /* The highest Physical Adress Space address for the PMM */

u64 stack_bottom = 0;
u64 stack_top = 0;

u64 heap_bottom = 0;
u64 heap_top = 0;
u64 heap_ptr = 0;

void init_mm(void) {
    handle_e820(E820_ADDR, E820_COUNT);
    init_pmm(mem_map, E820_COUNT);
    init_stack();
    init_heap();
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
    u64 kernel_page_start = ((u64)&_kernel_start) & ~0xFFFULL;
    u64 kernel_page_end = (((u64)&_kernel_end) + 0xFFFULL) & ~0xFFFULL;
    bitmap_set(kernel_page_start, kernel_page_end - kernel_page_start);

    /* Setting the bitmap as used */
    bitmap_set((u64)bitmap, (u64)bitmap_len);
    
    /* Setting used pages */
    for (int i=0; i<12; i++) {
        bitmap_set(used_pages[i], 0x1000);
    }
}

void init_stack(void) {
    stack_bottom = (u64)alloc_page(STACK_SIZE);
    stack_top = stack_bottom + 0x1000 * STACK_SIZE;
    asm volatile ("mov %0, %%esp"
                 :
                  : "r"((u32)stack_top)
                 );
}

void init_heap(void) {
    heap_bottom = (u64)alloc_page(HEAP_SIZE);
    heap_top = heap_bottom + 0x1000 * HEAP_SIZE;
    heap_ptr = 0; /* Keep this, just in case */
}
