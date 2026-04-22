ASM=nasm
CC=gcc
LD=ld
OBJCOPY=objcopy
QEMU=qemu-system-x86_64

IMG=disk.img

CFLAGS=-m32 -ffreestanding -nostdlib -fno-pie -Iinclude
LDFLAGS=-m elf_i386 -T linker.ld

C_SOURCES := $(shell find kernel arch drivers lib mm fs net -name "*.c")
C_OBJECTS := $(C_SOURCES:.c=.o)

ASM_SOURCES := $(shell find arch -name "*.asm")
ASM_OBJECTS := $(ASM_SOURCES:.asm=.o)

OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS)

all: $(IMG)

# Bootloader stage 1
boot.bin: boot/boot.asm
	@$(ASM) -f bin $< -o $@
	@truncate -s 512 boot.bin 

# ASM -> OBJ
%.o: %.asm
	@$(ASM) -f elf32 $< -o $@

# C -> OBJ
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking files
kernel.elf: $(OBJECTS)
	@$(LD) $(LDFLAGS) -o $@ $^

kernel.bin: kernel.elf
	@$(OBJCOPY) -O binary $< $@

# Disk image
$(IMG): boot.bin kernel.bin
	@dd if=/dev/zero of=$(IMG) bs=512 count=2048 2>/dev/null
	@dd if=boot.bin of=$(IMG) bs=512 count=1 conv=notrunc 2>/dev/null
	@dd if=kernel.bin of=$(IMG) bs=512 seek=1 conv=notrunc 2>/dev/null

run: $(IMG)
	@$(QEMU) $(IMG)

debug: $(IMG)
	@$(QEMU) $(IMG) -s -S

clean:
	@rm -rf $(C_OBJECTS) $(ASM_OBJECTS) *.bin *.img *.o *.elf