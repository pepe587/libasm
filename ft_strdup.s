global ft_strdup
extern malloc

ft_strdup:

mov rbx, rdi
call ft_strlen
mov rdi, rax
inc rdi
call malloc
mov rsi, rbx
call ft_strcpy