# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alkozma <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 18:06:36 by alkozma           #+#    #+#              #
#    Updated: 2019/07/20 12:43:41 by alkozma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
	   input.c \
	   environ.c \
	   environ_helpers.c \
	   exec.c \
	   builtins.c \
	   display.c

OBJECTS = $(patsubst %.c,%.o,$(SRCS))

HEADERS = minishell.h \
		  includes/ftgnl.h \
		  includes/ft_printf.h \
		  includes/libft.h

FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME):
	make -C libft
	cp libft/libft.a ./
	gcc $(SRCS) libft.a -I includes $(FLAGS) -o $(NAME)

clean:
	make -C libft clean
	rm -rf $(OBJECTS)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME) libft.a

re: fclean all
