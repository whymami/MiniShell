NAME = minishell

SRC = src/main.c src/parser.c
OBJ = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -lreadline

all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(RLFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all