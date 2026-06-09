#ifndef MEMUTILS_H
#define MEMUTILS_H

#include <main/types.h>

static inline void* memcpy(void* dst, const void* src, u64 n) {
    asm volatile(
        "cld\n\t"
        "rep movsb"
        : "+D"(dst), "+S"(src), "+c"(n)
        :
        : "memory"
    );
    return dst;
}

static inline void* memset(void* dst, int c, u64 n) {
    asm volatile(
        "cld\n\t"
        "rep stosb"
        : "+D"(dst), "+c"(n)
        : "a"(c)
        : "memory"
    );
    return dst;
}

static inline int memcmp(const void* a, const void* b, u64 n) {
    const u8* p1 = (const u8*)a;
    const u8* p2 = (const u8*)b;
    for (u64 i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return (int)p1[i] - (int)p2[i];
    }
    return 0;
}

static inline void* memmove(void* dst, const void* src, u64 n) {
    u8* d = (u8*)dst;
    const u8* s = (const u8*)src;
    if (d < s || d >= s + n) {
        return memcpy(dst, src, n);
    }
    d += n - 1;
    s += n - 1;

    asm volatile(
        "std\n\t"
        "rep movsb\n\t"
        "cld"
        : "+D"(d), "+S"(s), "+c"(n)
        :
        : "memory"
    );
    return dst;
}

#endif

