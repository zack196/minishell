NAME = minishell


CFLAGS = -Wall -Wextra -Werror 
CC = cc

INCLUDE = minishell.h

SRC = ./main.c \
	  ./garbege_colector.c \
	  ./libft_utils.c \
	  ./utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)


$(OBJ): $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
