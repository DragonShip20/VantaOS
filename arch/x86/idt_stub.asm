global isr_common
extern isr_dispatcher

;; Right now the function doesn't do anything special
isr_common:
    pushad
    push esp
    call isr_dispatcher
    add esp, 4
    popad
    iret
