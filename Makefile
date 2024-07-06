NAME = minishell

SRC = src/main.c src/parser.c src/lexer.c
OBJ := $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = lib/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

RLFLAGS = -lreadline
LDFLAGS = -L$(LIBFT_DIR) -L$(PRINTF_DIR)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT) $(PRINTF) $(RLFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: re fclean clean all
