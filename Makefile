NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LDFLAGS     = -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS    = -I/Users/$(USER)/.brew/opt/readline/include

CFLAGS = -Wall -Wextra -Werror 
CC = cc

F_LFT = -L$(LIBFT_DIR) -lft
INC = -I$(LIBFT_DIR)

INCLUDE = includes/parse.h

SRC = main.c signals.c src/lexer/tokenizer_line.c src/tools/lst_addback_m.c \
	 src/tools/lst_env.c src/envir/environment.c src/expand/expansion.c src/tools/free_envi.c \
	 src/expand/expansion2.c src/expand/expansion3.c  \
	 src/lexer/checks.c src/parse/parsing.c src/parse/parsing2.c src/tools/lst_redir.c \
	 src/tools/lst_cmd.c \
	 src/exec/exe_cmd.c src/exec/exec.c src/exec/handel_pipe.c src/exec/handel_redi.c src/exec/build_in_exec.c src/exec/handel_heredoc.c src/exec/expand_helper.c \
	 src/build_in/echo.c src/build_in/unset.c src/build_in/env.c src/build_in/export.c src/build_in/cd.c src/build_in/pwd.c src/build_in/exit.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT): 
	$(MAKE) -C $(LIBFT_DIR)


$(OBJ): $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(F_LFT) -lreadline $(CPPFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJ) $(OBJ_B)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re $(LIBFT)
