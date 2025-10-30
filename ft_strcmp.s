global ft_strcmp

ft_strcmp:

.loop:
    mov al, byte [rdi]
    mov dl, byte [rsi]

    cmp al, dl
    jne .notequal
    
    cmp al, 0
    je .equal
    cmp dl, 0
    je .equal
    
    inc rdi
    inc rsi
    jmp .loop

.equal:
    cmp al, dl
    jne .notequal
    xor rax, rax
    ret

.notequal:
    sub al, dl
    movsx eax, al
    ret