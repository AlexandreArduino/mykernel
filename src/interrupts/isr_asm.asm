[BITS 64]

%macro push_all 0

    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

%endmacro

%macro pop_all 0

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

%endmacro

division_by_zero_interrupt:
    push_all
    call DivisionByZero
    pop_all
page_fault_interrupt:
    push_all
    call PageFaultHandler
    pop_all
    iretq
double_fault_interrupt:
    push_all
    call DoubleFaultHandler
    pop_all
    iretq
general_protection_fault_interrupt:
    push_all
    call GeneralProtectionHandler
    pop_all
    iretq
keyboard_interrupt:
    push_all
    call KeyboardInterruptHandler
    pop_all
    iretq
mouse_interrupt:
    push_all
    call MouseInterruptHandler
    pop_all
    iretq
pit_interrupt:
    push_all
    call PITHandler
    pop_all
    iretq
default_interrupt:
    iretq
invalid_opcode_interrupt:
    push_all
    call InvalidOpCode
    pop_all
    iretq

GLOBAL division_by_zero_interrupt
GLOBAL page_fault_interrupt
GLOBAL double_fault_interrupt
GLOBAL general_protection_fault_interrupt
GLOBAL keyboard_interrupt
GLOBAL mouse_interrupt
GLOBAL pit_interrupt
GLOBAL default_interrupt
GLOBAL invalid_opcode_interrupt
EXTERN DivisionByZero
EXTERN PageFaultHandler
EXTERN DoubleFaultHandler
EXTERN GeneralProtectionHandler
EXTERN KeyboardInterruptHandler
EXTERN MouseInterruptHandler
EXTERN PITHandler
EXTERN InvalidOpCode