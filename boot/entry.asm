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

gdt_code64:
    ;; 64 bit kernel code segment
    dq 0x00AF9A000000FFFF

gdt_data64:
    ;; 64 bit kernel data segment
    dq 0x00AF92000000FFFF

gdt_end:

gdt_desc:
    dw gdt_end - gdt_start -1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10
CODE_SEG_LM equ 0x18
DATA_SEG_LM equ 0x20

;; -----------------------------------------------------------------------------------

BITS 32

PAE equ 1 << 5
PG equ 1 << 31
LME equ 1 << 8
IA_32e_EFER equ 0xC0000080

PML4_ADDR equ 0xB000
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
    call setup_pd
    call setup_pdpt

    jmp enable_paging_lm

hang:
    hlt
    jmp hang

enable_paging_lm:
    cli ;; We dont have a 64 bit IDT for now

    mov eax, PML4_ADDR
    mov cr3, eax ;; Giving the CPU PDPT for paging

    mov eax, cr4
    or eax, PAE
    mov cr4, eax ;; Enabling Physical Address Extention (PAE)

    mov ecx, IA_32e_EFER
    rdmsr
    or eax, LME
    wrmsr ;; Long mode enable

    mov eax, cr0
    or eax, PG
    mov cr0, eax ;; Enabling Paging
    
    jmp CODE_SEG_LM:lm_entry ;; Flush pipeline

setup_pd:
    ;; Map the first 4 GiB of Physical Address Space
    xor ebx, ebx
    mov edi, PD0_ADDR
    call .fill
    mov edi, PD1_ADDR
    call .fill
    mov edi, PD2_ADDR
    call .fill
    mov edi, PD3_ADDR
    call .fill
    ret
.fill:
    mov ecx, 512 ;; Each PAE struct has 512*8b=4096b
.loop:
    mov eax, ebx
    or eax, 0x83 ;; Flags: present, rw and page size (2mb)
    mov [edi], eax
    mov dword [edi+4], 0 ;; For now we map <4GiB so upper bits are all 0
    add ebx, 0x200000
    add edi, 8
    dec ecx
    jnz .loop
    jmp .done
.done:
    ret

setup_pdpt:
    ;; One entry in PDPT is PD_ADDR | FLAGS (0x03 here)
    mov dword [PDPT_ADDR+0], PD0_ADDR | 3 ;; 0x03 = PRESENT | RW
    mov dword [PDPT_ADDR+4], 0
    mov dword [PDPT_ADDR+8], PD1_ADDR | 3
    mov dword [PDPT_ADDR+12], 0
    mov dword [PDPT_ADDR+16], PD2_ADDR | 3
    mov dword [PDPT_ADDR+20], 0
    mov dword [PDPT_ADDR+24], PD3_ADDR | 3
    mov dword [PDPT_ADDR+28], 0
.setup_pml4:
    ;; We only have one entry in the PML4
    mov dword [PML4_ADDR+0], PDPT_ADDR | 3
    mov dword [PML4_ADDR+4], 0
    ret

reserve_pae:
    ;; We have to fill the structs with 0
    cld

    mov edi, PDPT_ADDR
    mov ecx, PD3_ADDR
    xor eax, eax
    shr ecx, 2
    rep stosd

    mov edi, PML4_ADDR
    mov ecx, 0x1000
    xor eax, eax
    shr ecx, 2
    rep stosd

    ret

;; -----------------------------------------------------------------------------------

BITS 64

lm_entry:
    mov ax, DATA_SEG_LM
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov rsp, 0xFFFF
    
    jmp 0x10000

halt:
    cli
    hlt
    jmp halt

times 2048-($ - $$) db 0
