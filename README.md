# VantaOS

A 64-bit x86 hobby operating system written from scratch in C and assembly for systems programming education and low-level architecture research.

## Overview

VantaOS is an operating system with VESA display, PAE paging and memory management developed to explore the fundamentals of computer systems software, including boot processes, CPU modes, memory layout, VESA-rendered text mode, and kernel-level execution.

It is intentionally built without external OS dependencies in the kernel layer, focusing on direct hardware interaction and a clean, understandable architecture.

---

## Features

- Custom 2 stage x86 bootloader
- Long mode architecture
- Physical Memory Management built entirely from scratch
- Full interrupt handling with custom stubs and stack handling
- Fully allocated heap and stack
- PAE paging with PDPT and PD
- E820 BIOS memory map
- VESA rendered text mode / VGA text mode output (fallback)
- Make-based build system

## Build & Run

Install all dependencies:

```
sudo apt install build-essential nasm gcc-multilib binutils qemu-system-x86
```

Build the system:

```
make
```

Run in QEMU:

```
make run
```

Debug mode (GDB supported):

```
make debug
```

## Requirements

```
GCC (recommended cross-compiler: i686-elf-gcc)
NASM assembler
GNU LD linker
QEMU (x86 / x86_64)
build-essential
binutils
```