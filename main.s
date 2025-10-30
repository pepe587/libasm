    .intel_syntax noprefix
    .section .data
teststr: 
    .ascii "Hola mundo"
    .byte 0
numbuf: 
    .space 20
newline:
    .byte 10,0

    .section .text
    .global _start
    .extern ft_strlen

# --------------------
# print_number: imprime rax como decimal
print_number:
    mov rcx, numbuf + 19
    mov rbx, 10
    cmp rax, 0
    jne .conv_loop
    mov byte ptr [rcx], '0'
    dec rcx
    jmp .done
.conv_loop:
    xor rdx, rdx
    div rbx
    add dl, '0'
    mov byte ptr [rcx], dl
    dec rcx
    cmp rax, 0
    jne .conv_loop
.done:
    inc rcx
    lea rdx, [numbuf + 20]
    sub rdx, rcx
    mov rsi, rcx
    mov rax, 1
    mov rdi, 1
    syscall
    ret
# --------------------

_start:
    lea rdi, [rel teststr]   # puntero al string
    call ft_strlen
    call print_number

    # imprimir newline
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel newline]
    mov rdx, 1
    syscall

    # exit
    mov rax, 60
    xor rdi, rdi
    syscall