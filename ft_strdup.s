global ft_strdup
extern malloc
extern __errno_location
extern ft_strlen
extern ft_strcpy

ft_strdup:

    push rbx
    push r12
    mov rbx, rdi
    call ft_strlen
    inc rax
    mov rdi, rax
    call malloc wrt ..plt
    test rax, rax
    jz .fail
    mov r12, rax
    mov rdi, rax
    mov rsi, rbx
    call ft_strcpy wrt ..plt
    mov rax, r12
    pop r12
    pop rbx
    ret

.fail:
    call __errno_location wrt ..plt
    mov dword [rax], 12
    xor rax, rax
    pop r12
    pop rbx
    ret
