[org 0x500]
BITS 16

_start:
   	;; Load kernel into RAM
    mov ah, 0x42
    mov si, dap
    int 0x13
    jc disk_error

    call memory_map

    jmp enter_pm

memory_map:
    xor ebx, ebx
    xor bp, bp ;; bp is the counter
    xor ax, ax
    mov es, ax
    mov di, 0x9000 ;; The mmap is saved to 0x9000
.loop:  
    mov eax, 0x0000E820
    mov edx, 0x534D4150 ;; 'SMAP'
    mov ecx, 24
    int 0x15
    jc .error
    
    inc bp

    cmp eax, 0x534D4150
    jne .error

    add di, 24 ;; Next entry
    test ebx, ebx
    jne .loop
.done:
    mov word [0xA000], bp
    ret
.error:
    hlt
    jmp .error

disk_error:
    hlt
    jmp disk_error

;; Disk address packet
dap:
        db 0x10
        db 0x00
        dw 50 ;; Number of sectors to load
        dw 0x0000
        dw 0x1000 ;; Segment 1000:0000
        dq 5

enter_pm:
	;; Load GDT and set bit 1 (PM enable) in cr0
    cli
    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
	
	;; Flush CS
    jmp CODE_SEG:pm_entry

gdt_start:
	;; GDT null entry
    dq 0x0000000000000000

gdt_code:
	;; Kernel code segment 
    dq 0x00CF9A000000FFFF

gdt_data:
	;; Kernel data segment
    dq 0x00CF92000000FFFF

gdt_end:

gdt_desc:
    dw gdt_end - gdt_start -1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

;; -----------------------------------------------------------------------------------

BITS 32

PDPT_ADDR equ 0x1000
PD0_ADDR equ 0x2000
PD1_ADDR equ 0x3000
PD2_ADDR equ 0x4000
PD3_ADDR equ 0x5000

pm_entry:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0xFFFF

    call reserve_pae

	;; Kernel entry
    jmp 0x10000

hang:
    hlt
    jmp hang


reserve_pae:
    ;; We have to fill the structs with 0
    mov di, PDPT_ADDR
    mov cx, PD3_ADDR
    sub cx, di
    cld
    xor al, al
.loop:
    test cx, cx
    jz .done
    stosb ;; [ES:DI] = AL (0)
    dec cx
    jmp .loop
.done:
    ret
times 2048-($ - $$) db 0
