NAME = minishell


CFLAGS = -Wall -Wextra -Werror 
CC = cc

INCLUDE = minishell.h

SRC = ./main.c \
	  ./garbage_collector.c \
	  ./libft_utils.c \
	  ./utils.c \
	  ./envirenement.c

OBJ = $(SRC:.c=.o)

all: $(NAME)


$(OBJ): $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -lreadline -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all



.PHONY: all clean fclean re 

