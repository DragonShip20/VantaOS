#ifndef PMM_H
#define PMM_H

#include <main/types.h>

extern u8 *bitmap;
extern u32 bitmap_len;
extern u64 used_pages[];
extern u64 _kernel_start; 
extern u64 _kernel_end;

u64 alloc_page(u64 count);
void free(u64 addr);
static inline void bitmap_set_bit(u64 page);
static inline void bitmap_clear_bit(u64 page);
void bitmap_clear(u64 addr, u64 len);
void bitmap_set(u64 addr, u64 len);
static inline u8 bitmap_bit(u64 bit);

#endif
