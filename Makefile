NAME = minishell

CC = cc 
CFLAG = -Wall -Wextra -Werror -g

SRC = ./main.c	\
	  ./my_malloc.c

SRC_LIBFT = ./libft/ft_strcmp.c	\
			./libft/ft_strncmp.c	\
			./libft/ft_strdup.c	\
			./libft/ft_split.c	\
			./libft/ft_substr.c	\
			./libft/ft_strjoin.c	\
			./libft/ft_strlen.c	\
			./libft/ft_isalpha.c	\
			./libft/ft_isalnum.c	\
			./libft/ft_strrchr.c

SRC_EXEC = ./env/init_env.c \
		   ./env/export.c	\
		   ./env/env.c \
		   ./env/unset.c


OBJ = $(SRC:.c=.o) \
	  $(SRC_EXEC:.c=.o) \
	  $(SRC_LIBFT:.c=.o)

all:$(NAME)

%.o:%.c philo.h
	$(CC) $(CFLAG) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all
