global ft_strcpy

ft_strcpy:

.loop:
    mov al, byte [rsi]
    mov [rdi], al
    cmp al, 0
    je .end
    inc rdi
    inc rsi
    jmp .loop


.end:
    mov rax, rdi
    ret
