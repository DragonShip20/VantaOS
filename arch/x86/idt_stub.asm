global isr_common
extern isr_dispatcher

;; Right now the function doesn't do anything special
isr_common:
    pusha
    call isr_dispatcher
    popa
    iret
