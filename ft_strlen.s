section .text
global ft_strlen

ft_strlen:

xor rax, rax    ; rax = 0 
                ;   (lo logico seria mov rax, 0 pero es mas lento)

.loop:
    mov bl, byte [rdi]
    cmp bl, 0
    je  .end
    inc rax
    inc rdi
    jmp .loop

.end:
    ret
