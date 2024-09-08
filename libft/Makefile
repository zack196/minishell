# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 06:20:11 by zel-oirg          #+#    #+#              #
#    Updated: 2024/08/31 06:26:58 by zel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

AR = ar cr

CC = cc

CFLAG = -Wall -Wextra -Werror

RM = rm -f

INCLUDES = ./libft.h

SRC_PART1 = \
	./ft_memset.c	\
	./ft_bzero.c	\
	./ft_memcpy.c	\
	./ft_memmove.c	\
	./ft_memchr.c	\
	./ft_memcmp.c	\
	./ft_calloc.c	\
	./ft_strlen.c	\
	./ft_strlcpy.c	\
	./ft_strlcat.c	\
	./ft_strchr.c	\
	./ft_strrchr.c	\
	./ft_strncmp.c	\
	./ft_strcmp.c	\
	./ft_strnstr.c	\
	./ft_strdup.c	\
	./ft_isdigit.c	\
	./ft_atoi.c		\
	./ft_isalpha.c	\
	./ft_isalnum.c	\
	./ft_isempty.c \
	./ft_isascii.c	\
	./ft_isspace.c	\
	./ft_isprint.c	\
	./ft_toupper.c	\
	./ft_tolower.c
	
SRC_PART2 = \
	./ft_substr.c	\
	./ft_strjoin.c	\
	./ft_strtrim.c	\
	./ft_split.c	\
	./ft_itoa.c		\
	./ft_strmapi.c	\
	./ft_putchar_fd.c	\
	./ft_putstr_fd.c	\
	./ft_striteri.c		\
	./ft_putendl_fd.c	\
	./ft_putnbr_fd.c

SRCS = \
	$(SRC_PART1)	\
	$(SRC_PART2)
	
OBJS = $(SRCS:.c=.o)

SRC_BONUS = \
	./ft_lstnew.c	\
	./ft_lstadd_front.c	\
	./ft_lstsize.c	\
	./ft_lstlast.c	\
	./ft_lstadd_back.c	\
	./ft_lstdelone.c	\
	./ft_lstclear.c	\
	./ft_lstiter.c	\
	./ft_lstmap.c

OBJS_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

clean :
	$(RM)  $(OBJS) $(OBJS_BONUS)

fclean : clean
	$(RM)  $(NAME)

re : fclean all

%.o: %.c libft.h
	$(CC) $(CFLAG) -c $<

$(NAME) : $(OBJS)
	$(AR) $@ $^

bonus : $(OBJS) $(OBJS_BONUS)
	$(AR) $(NAME) $^

.PHONY : all bonus clean fclean re