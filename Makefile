# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsmith <zsmith@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/14 23:11:31 by zsmith            #+#    #+#              #
#    Updated: 2017/05/11 12:18:41 by zsmith           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	proxy

CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS =   -Wall -Wextra -Werror

CFLAGS	+=	-I $(HDIR)
LDFLAGS	+=	-Llib -lftprintf
		# -L<dirname> -l<libname without lib prefix>

CFILES	=	proxy_server.c			\
			external_communication.c\

LIBFILES=	libprintf.a

SRCDIR  =	src/
HDIR	=	includes/
LIBDIR  =	lib/
ODIR	=	obj/

OFILES	=	$(addprefix $(ODIR), $(CFILES:.c=.o))

ifdef DEBUG
	CFLAGS 	+=	-fsanitize=address -g
	LDFLAGS	+=	-fsanitize=address -g
endif

.PHONY: all $(NAME) clean flcean re

all: $(NAME)

$(ODIR)%.o: $(SRCDIR)%.c
	mkdir -p $(shell dirname $@)
	gcc $(CFLAGS) -c $^ -o $@

$(NAME): $(OFILES)
	gcc -o $@ $^ $(LDFLAGS)

clean:
	/bin/rm -f $(OFILES)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
