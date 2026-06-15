#include <mm/heap.h>

u64 heap_bottom = (u64)NULL;
u64 heap_top = (u64)NULL;
u64 heap_ptr = (u64)NULL;

void init_heap(void) {
    heap_bottom = (u64)alloc_page(HEAP_SIZE);
    heap_top = heap_bottom + 0x1000 * HEAP_SIZE;
    heap_ptr = 0; /* Keep this, just in case */
}

void* kmalloc(u64 bytes) {
    /* TODO: add NULL type and add it here */
    if (heap_bottom+heap_ptr >= heap_top) return NULL;
    u64 address = heap_bottom+heap_ptr;
    heap_ptr += bytes;
    return (void*)address;
}
