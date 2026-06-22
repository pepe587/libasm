extern __errno_location
global ft_write

ft_write:
    mov rax, 1
    syscall
    cmp rax, 0
    jge .done
    neg rax
    push rax
    call __errno_location wrt ..plt
    pop rdi
    mov [rax], edi
    mov rax, -1
.done:
    ret