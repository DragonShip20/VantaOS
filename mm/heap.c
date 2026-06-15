#include <mm/heap.h>

u64 heap_bottom = 0;
u64 heap_top = 0;
u64 heap_ptr = 0;

void init_heap(void) {
    heap_bottom = (u64)alloc_page(HEAP_SIZE);
    heap_top = heap_bottom + 0x1000 * HEAP_SIZE;
    heap_ptr = 0; /* Keep this, just in case */
}
