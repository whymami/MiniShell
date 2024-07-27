NAME = minishell

SRC = src/main.c src/parser.c src/lexer.c src/builtin/env.c src/builtin/pwd.c \
	src/builtin/unset.c src/builtin/export.c src/builtin/cd.c src/builtin/echo.c \
	src/builtin/exit.c src/executor.c src/pipe.c src/signal.c src/r_direct.c \
	src/heredoc.c src/dollar.c src/utils.c

CFLAGS = -Wall -Wextra -Werror # -g -fsanitize=address
LIBFT = lib/libft/libft.a
PRINTF = lib/ft_printf/libftprintf.a
DLIST = lib/dlist/dlist.a
READLINE = lib/readline/lib/libreadline.a

RM = @rm -rf
CC = @cc

OBJS = $(SRC:.c=.o)

RESET = \033[0m
BOLD = \033[1m
YELLOW = \033[33m
GREEN = \033[32m
RED = \033[31m

all: $(READLINE) $(NAME) $(LIBFT) $(PRINTF) $(DLIST)

$(READLINE):
	@echo "$(BOLD)$(YELLOW)[DOWNLOADING READLINE...]$(RESET)"
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	@tar -xvf readline-8.2.tar.gz
	@$(RM) readline-8.2.tar.gz
	@cd readline-8.2 && ./configure --prefix=${PWD}/lib/readline
	@cd readline-8.2 && make install
	@$(RM) readline-8.2

$(NAME): $(LIBFT) $(PRINTF) $(DLIST) $(OBJS)
	@echo "$(BOLD)$(YELLOW)[COMPILING...]$(RESET)"
	@sleep 2
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBFT) $(PRINTF) $(DLIST) -I${PWD}/lib/readline/include/ -lreadline -L${PWD}/lib/readline/lib
	@clear
	@echo "$(BOLD)$(YELLOW)[COMPILATION COMPLETE]$(RESET)"

$(LIBFT):
	@echo "$(BOLD)$(GREEN)[BUILDING LIBFT...]$(RESET)"
	@sleep 1
	@make -C lib/libft

$(PRINTF):
	@echo "$(BOLD)$(GREEN)[BUILDING FT_PRINTF...]$(RESET)"
	@sleep 1
	@make -C lib/ft_printf

$(DLIST):
	@echo "$(BOLD)$(GREEN)[BUILDING DLIST...]$(RESET)"
	@sleep 1
	@make -C lib/dlist

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/lib/readline/include/

fclean: clean
	@echo "$(BOLD)$(RED)[DELETING...]$(RESET)"
	@sleep 1
	@$(RM) $(NAME)
	@make -C lib/libft/ fclean
	@make -C lib/ft_printf/ fclean
	@make -C lib/dlist/ fclean
	@echo "$(BOLD)$(RED)[ALL FİLE DELETED]$(RESET)"

clean:
	@echo "$(BOLD)$(YELLOW)[DELETING OBJECTS...]$(RESET)"
	@sleep 1
	@$(RM) $(OBJS)
	@make -C lib/libft/ clean
	@make -C lib/ft_printf/ clean
	@make -C lib/dlist/ clean
	@echo "$(BOLD)$(RED)[ALL OBJECTS DELETED]$(RESET)"

re: fclean all

.PHONY: all fclean clean re