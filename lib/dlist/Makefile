NAME = dlist.a

SRC = dlist_add_back.c \
	dlist_add_front.c \
	dlist_clear.c \
	dlist_delone.c \
	dlist_new.c \
	dlist_size.c

LIBC = ar rc
OBJ := $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(LIBC) $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all