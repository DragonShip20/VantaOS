[org 0x7C00]
BITS 16

_start:
        cli
        xor ax, ax
        mov ds, ax
        mov es, ax
        mov ss, ax
        mov sp, 0x7c00
        sti

        cld

        xor ah, ah
        mov al, 0x03
        int 0x10

        mov dl, 0x80

        mov ah, 0x41
        mov bx, 0x55AA
        int 0x13
        jc disk_error

        mov ah, 0x42
        mov si, dap
        int 0x13
        jc disk_error

        in al, 0x92
        or al, 2
        out 0x92, al

        jmp enter_pm

enter_pm:
        cli
        lgdt [gdt_desc]
        mov eax, cr0
        or eax, 1
        mov cr0, eax

        jmp CODE_SEG:pm_entry

disk_error:
        hlt
        jmp disk_error

dap:
        db 0x10
        db 0x00
        dw 20
        dw 0x0000
        dw 0x1000
        dq 1

gdt_start:
        dq 0x0000000000000000

gdt_code:
        dq 0x00CF9A000000FFFF

gdt_data:
        dq 0x00CF92000000FFFF

gdt_end:

gdt_desc:
        dw gdt_end - gdt_start -1
        dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

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

        jmp 0x10000

times 510-($ - $$) db 0
dw 0xAA55