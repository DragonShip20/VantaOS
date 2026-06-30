global _start
extern kernel_main
section .start	

_start:
    jmp kernel_main

section .text
.halt:
    hlt
    jmp .halt
