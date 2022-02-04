[BITS 64]

global save_current_stack_state

save_current_stack_state:
    ; Data are stored in the current stack
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    push rsp
    push rbp