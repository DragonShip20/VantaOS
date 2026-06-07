#ifndef MMAP_H
#define MMAP_H

/* E820 info location */
#define E820_ADDR 0x9000
#define E820_COUNT *(u16*)0xA000

void init_mm(void);

#endif
