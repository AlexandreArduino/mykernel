[BITS 64]

global float_to_int
output: resb 8

float_to_int:
	mov [output], byte 0
	mov rax, rdi
	mov rbx, [output]
	sub rbx, rax
	mov rdi, rax
	ret