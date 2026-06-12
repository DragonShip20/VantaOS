[org 0x7C00]
BITS 16

_start:
	;; Setup initital segments (flat memory model)
        cli
        xor ax, ax
        mov ds, ax
        mov es, ax
        mov ss, ax
        mov sp, 0xFFFF
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
	
	;; Load stage 2 into RAM
        mov ah, 0x42
        mov si, dap
        int 0x13
        jc disk_error
	
	;; Set A20 line
        in al, 0x92
        or al, 2
        out 0x92, al

    ;; Jump to stage 2
        jmp 0x500

vesa_fail:
        hlt
        jmp vesa_fail

disk_error:
        hlt
        jmp disk_error

;; Disk address packet
dap:
        db 0x10
        db 0x00
        dw 4 ;; Number of sectors to load
        dw 0x0500
        dw 0x0000
        dq 1

;; VBE struct localisation 
vbe_info equ 0x8000        

;; Boot signature 
times 510-($ - $$) db 0
dw 0xAA55
