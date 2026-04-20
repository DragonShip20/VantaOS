# VantaOS

A 32-bit x86 hobby operating system written from scratch in C and assembly for systems programming education and low-level architecture research.

## Overview

VantaOS is a minimal, bootable operating system developed to explore the fundamentals of computer systems software, including boot processes, CPU modes, memory layout, and kernel-level execution.

It is intentionally built without external OS dependencies in the kernel layer, focusing on direct hardware interaction and a clean, understandable architecture.

---

## Features

Custom x86 Bootloader (boot sector 0)
C-based kernel entry point (kernel_main)
ASM -> C transition layer (entry.asm)
Raw disk image boot pipeline
VGA text mode output
Custom linker script
Make-based build system

## Build & Run

Build the system

make

Run in QEMU

make run

Debug mode (GDB supported)

make debug

## Requirements

GCC (recommended cross-compiler: i686-elf-gcc)
NASM assembler
GNU LD linker
QEMU (x86 / x86_64)
Make
objcopy