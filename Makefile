NAME = minishell

RL_DIR = lib/readline
RL = $(RL_DIR)/libreadline.a
SRC = src/main.c src/parser.c src/lexer.c src/builtin/env.c src/builtin/pwd.c \
	src/builtin/unset.c src/builtin/export.c src/builtin/cd.c src/builtin/echo.c \
	src/builtin/exit.c src/executor.c src/pipe.c src/signal.c src/r_direct.c \
	src/heredoc.c src/dollar.c src/utils.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

DLINK_DIR = lib/dlist
DLINK = $(DLINK_DIR)/dlist.a

PRINTF_DIR = lib/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

READLINE = readline

all: $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	rm -rf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/lib/readline
	cd readline-8.2 && make install
	rm -rf readline-8.2

$(NAME): $(LIBFT) $(DLINK) $(PRINTF) $(OBJ) $(READLINE)
	@echo "[COMPILING...]"
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFT) $(DLINK) $(PRINTF) -I${PWD}/lib/readline/include/ -lreadline -L${PWD}/lib/readline/lib  

$(LIBFT):
	make -C $(LIBFT_DIR)
	make -C $(LIBFT_DIR) bonus

$(DLINK):
	make -C $(DLINK_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/lib/readline/include/

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(DLINK_DIR) fclean
	make -C $(PRINTF_DIR) fclean

clean:
	@echo "[DELETING...]"
	@$(RM) $(OBJ)
	@echo "[DELETED]"
	make -C $(LIBFT_DIR) clean
	make -C $(DLINK_DIR) clean
	make -C $(PRINTF_DIR) clean

re: fclean all

.PHONY: all fclean clean re
