global ft_strcpy

ft_strcpy:

    mov rax, rdi

.loop:
    mov cl, byte [rsi]
    mov [rdi], cl
    cmp cl, 0
    je .end
    inc rdi
    inc rsi
    jmp .loop

.end:
    ret
