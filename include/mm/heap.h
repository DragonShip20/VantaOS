#ifndef HEAP_H
#define HEAP_H

#include <main/types.h>
#include <mm/pmm.h>

#define HEAP_SIZE 512

extern u64 heap_bottom;
extern u64 heap_top;
extern u64 heap_ptr;

void init_heap(void);
void* kmalloc(u64 bytes);

#endif
