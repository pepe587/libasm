section .text
global ft_strlen

ft_strlen:

xor rax, rax

.loop:
    mov cl, byte [rdi]
    cmp cl, 0
    je  .end
    inc rax
    inc rdi
    jmp .loop

.end:
    ret
