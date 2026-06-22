NAME = libasm.a
SRCS = ft_strlen.s ft_strcmp.s ft_strcpy.s ft_write.s ft_read.s ft_strdup.s
OBJS = $(SRCS:.s=.o)
FLAGS = -f elf64

all: $(NAME) test

%.o: %.s
	nasm $(FLAGS) $< -o $@

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

test: $(NAME) main.c
	gcc main.c $(NAME) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) test

re: fclean all

.PHONY: all clean fclean re test