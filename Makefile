NAME = minishell

RL_DIR = lib/readline
RL = $(RL_DIR)/libreadline.a
SRC = src/main.c src/parser.c src/lexer.c src/builtin/env.c src/builtin/pwd.c \
	src/builtin/unset.c src/builtin/export.c src/builtin/cd.c src/builtin/echo.c \
	src/builtin/exit.c src/executor.c src/pipe.c src/signal.c src/r_direct.c \
	src/heredoc.c src/dollar.c src/utils.c

OBJ := $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g  -fsanitize=address
DIR = $(shell pwd)

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

DLINK_DIR = lib/dlist
DLINK = $(DLINK_DIR)/dlist.a

PRINTF_DIR = lib/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

RLFLAGS	= -L./lib/readline/lib -I./lib/readline/include/readline -lreadline
LDFLAGS = -L$(LIBFT_DIR) -L$(PRINTF_DIR)

all: $(RL) $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(DLINK) $(RL)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT) $(PRINTF) $(DLINK) $(RLFLAGS) -o $(NAME)

$(RL):
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
	@tar -xvf readline-8.2-rc1.tar.gz
	@rm -rf readline-8.2-rc1.tar.gz
	@mv readline-8.2-rc1 $(RL_DIR)
	@cd $(RL_DIR) && ./configure --prefix=$(DIR)/$(RL_DIR) && make && make install
	make -C $(RL_DIR)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

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
	make -C $(RL_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(DLINK_DIR) fclean
	make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: re fclean clean all