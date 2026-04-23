#ifndef STDOUT_H
#define STDOUT_H

#include <main/types.h>
#include <drivers/vga.h>

struct stdout {
    void (*stdout)(const u8* s);
    void (*scroll)(u32 lines);
};

extern struct stdout stdout;

void vga_print(const u8* s);
void init_stdout(void);
void scroll(u32 lines);

#endif