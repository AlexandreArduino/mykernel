[BITS 64]

GLOBAL cpuid_result
GLOBAL cpuid_command

cpuid_result:
    resb 8
cpuid_command:
    mov rax, rdi
    cpuid
    mov [cpuid_result], rbx
    mov [cpuid_result + 4], rdx
    mov [cpuid_result + 8], rcx
    mov rax, cpuid_result
    ret