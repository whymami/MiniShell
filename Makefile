NAME = minishell


SRC = src/main.c src/parser.c src/lexer.c src/builtin/env.c src/builtin/pwd.c \
	src/builtin/unset.c src/builtin/export.c

OBJ := $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g  -fsanitize=address

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

DLINK_DIR = lib/dlist
DLINK = $(DLINK_DIR)/dlist.a

PRINTF_DIR = lib/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

RLFLAGS = -lreadline -g
LDFLAGS = -L$(LIBFT_DIR) -L$(PRINTF_DIR)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(DLINK)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT) $(PRINTF) $(DLINK) $(RLFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)
	make -C $(LIBFT_DIR) bonus

$(DLINK):
	make -C $(DLINK_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(DLINK_DIR) clean
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(DLINK_DIR) fclean
	make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: re fclean clean all
