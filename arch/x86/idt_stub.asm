global isr_common
extern isr_dispatcher

;; Every int has its own stub, and all lead to common stub
isr_common:
    pushad
    push esp ;; Giving the C dispatcher the stack 
    call isr_dispatcher
    add esp, 4
    popad
    ret

%macro ISR_NOERR 1
global isr%1
isr%1:
    ;; Setting up the stack frame
    push 0 ;; Fake error code
    push %1
    call isr_common
    add esp, 8
    iret
%endmacro

%macro ISR_ERR 1
global isr%1
isr%1:
    push %1
    call isr_common
    add esp, 4
    iret
%endmacro

;; There are some ints where the cpu pushes the error num
;; And there are some where we have to push a fake one
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR 8
ISR_NOERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_ERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_ERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_ERR 29
ISR_ERR 30
ISR_NOERR 31
%assign i 32
%rep 224
    ISR_NOERR i
%assign i i+1
%endrep

;; Giving C all the stubs
global isr_stubs
global isr_stubs_end

isr_stubs:
    %assign i 0
    %rep 256
        dd isr%+i
    %assign i i+1
    %endrep
isr_stubs_end:
