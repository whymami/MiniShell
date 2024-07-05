NAME = libftprintf.a
SRC = \
	ft_func1.c \
	ft_printf.c \
	ft_func2.c
CFLAGS = -Wall -Wextra -Werror
LIBC = ar rc
OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(LIBC) $(NAME) $(OBJ)
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY : all clean fclean re
