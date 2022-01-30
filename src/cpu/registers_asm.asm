[BITS 64]

GLOBAL dump_registers_asm
GLOBAL registers_saved
GLOBAL number_registers

REGISTERS_COUNT equ 13

number_registers:
    dw REGISTERS_COUNT

registers_saved:
    resb 8 * REGISTERS_COUNT

dump_registers_asm:
    mov [registers_saved], rax
    mov [registers_saved + 8], rbx
    mov [registers_saved + 16], rcx
    mov [registers_saved + 24], rdx
    mov [registers_saved + 32], rsi
    mov [registers_saved + 40], rdi
    mov [registers_saved + 48], r8
    mov [registers_saved + 56], r9
    mov [registers_saved + 64], r10
    mov [registers_saved + 72], r11
    mov [registers_saved + 80], r12
    mov [registers_saved + 88], r13
    mov [registers_saved + 96], r14
    mov [registers_saved + 104], r15
    ret