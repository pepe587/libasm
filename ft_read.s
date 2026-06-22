extern __errno_location
global ft_read

ft_read:
    xor rax, rax
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