
NAME = ft_ssl

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iinc -Ilibft

LIBFT = libft/libftprintf.a
SRC = $(wildcard src/*.c src/*/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re
.NOTPARALLEL: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C libft
	@$(CC) $(INC) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	@/bin/rm -f $(OBJ)
	@$(MAKE) clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -C libft

re: fclean all
