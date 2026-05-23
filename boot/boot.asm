[org 0x7C00]
BITS 16

_start:
	;; Setup initital segments (flat memory model)
        cli
        xor ax, ax
        mov ds, ax
        mov es, ax
        mov ss, ax
        mov sp, 0x7c00
        sti

        cld

	;; Initialise vesa 0x117 mode with linear framebuffer
        mov ax, 0x4F02
        mov bx, 0x117 | 0x4000
        int 0x10
        
        cmp ax, 0x004F
        jne vesa_fail

	;; Get VBE info
        mov ax, 0x4F01
        mov cx, 0x117
        mov di, vbe_info
        int 0x10

	;; Check disk (0x80)
        mov dl, 0x80

        mov ah, 0x41
        mov bx, 0x55AA
        int 0x13	
        jc disk_error
	
	;; Load kernel into RAM
        mov ah, 0x42
        mov si, dap
        int 0x13
        jc disk_error
	
	;; Set A20 line
        in al, 0x92
        or al, 2
        out 0x92, al

        jmp enter_pm

vesa_fail:
        hlt
        jmp vesa_fail
    
enter_pm:
	;; Load GDT and set bit 1 (PM enable) in cr0
        cli
        lgdt [gdt_desc]
        mov eax, cr0
        or eax, 1
        mov cr0, eax
	
	;; Flush CS
        jmp CODE_SEG:pm_entry

disk_error:
        hlt
        jmp disk_error

;; Disk address packet
dap:
        db 0x10
        db 0x00
        dw 50
        dw 0x0000
        dw 0x1000
        dq 1

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

;; VBE struct localisation 
vbe_info equ 0x8000        

;-------------------------------------------------------------------------------------------------------------

BITS 32

pm_entry:
        mov ax, DATA_SEG
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        mov esp, 0x90000

	;; Kernel entry
        jmp 0x10000

;; Boot signature 
times 510-($ - $$) db 0
dw 0xAA55
