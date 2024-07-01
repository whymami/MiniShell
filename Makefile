CC = gcc
CFLAGS = 
RLFLAGS = -lreadline
NAME = minishell
SRCS = main.c \
		pipe.c
READLINE_DIR = lib/readline
READLINE = $(READLINE_DIR)/lib/libreadline.a

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJS = $(SRCS:.c=.o)

all: $(READLINE) $(LIBFT) $(NAME) 

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(READLINE):
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
	@tar -xvf readline-8.2-rc1.tar.gz
	@rm -rf readline-8.2-rc1.tar.gz
	@cd readline-8.2-rc1 && ./configure --prefix=$(shell pwd)/$(READLINE_DIR)/ && make && make install
	@rm -rf readline-8.2-rc1

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -I$(shell pwd)/$(READLINE_DIR)/include $(RLFLAGS) -L$(shell pwd)/$(READLINE_DIR)/lib

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(shell pwd)/$(READLINE_DIR)/include/

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(READLINE_DIR)
	make -C $(LIBFT_DIR) fclean

re: fclean all
