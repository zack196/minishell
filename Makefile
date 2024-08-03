NAME = minishell

CC = cc 
CFLAG = #-Wall -Wextra -Werror  -g

SRC = ./main.c	\
	  ./my_malloc.c

SRC_LIBFT = ./libft/ft_strcmp.c	\
			./libft/ft_strncmp.c	\
			./libft/ft_strdup.c	\
			./libft/ft_atoi.c	\
			./libft/ft_split.c	\
			./libft/ft_memcpy.c	\
			./libft/ft_putstr_fd.c	\
			./libft/ft_strlcpy.c	\
			./libft/ft_substr.c	\
			./libft/ft_isdigit.c	\
			./libft/ft_strjoin.c	\
			./libft/ft_strlen.c	\
			./libft/ft_isalpha.c	\
			./libft/ft_isalnum.c	\
			./libft/ft_strrchr.c

SRC_EXEC = ./exec/init_env.c \
		   ./exec/build_in/export.c	\
		   ./exec/cmd/exec_one_cmd.c	\
		   ./exec/build_in/pwd.c	\
		   ./exec/build_in/exit.c	\
		   ./exec/build_in/echo.c	\
		   ./exec/build_in/cd.c	\
		   ./exec/build_in/env.c \
		   ./exec/build_in/unset.c

SRC_PARS = ./parse/aide.c \
		   ./parse/checksyntaxe.c \
		   ./parse/clear.c \
		   ./parse/list.c \
		   ./parse/remove.c \
		   ./parse/parse.c \
		   ./parse/token.c 

OBJ = $(SRC:.c=.o) \
	  $(SRC_EXEC:.c=.o) \
	  $(SRC_PARS:.c=.o) \
	  $(SRC_LIBFT:.c=.o)

all:$(NAME)

%.o:%.c minishell.h
	$(CC) $(CFLAG) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $(CFLAG) $(OBJ) -lreadline -lncurses -o $(NAME)

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all
