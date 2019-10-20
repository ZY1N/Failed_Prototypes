# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/14 16:26:00 by yinzhang          #+#    #+#              #
#    Updated: 2019/06/14 16:26:02 by yinzhang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME		= ft_ssl

CFLAGS		= -Wall -Werror -Wextra

INCLUDE		= ft_ssl.h\

FILES		= ft_ssl.c helper.c md5.c print.c sha256.c errors.c md5_2.c\
			sha256_2.c\

PRINTFSRC 	= ./ft_printf/libftprintf.a\

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME):
	@gcc $(CFLAGS) $(FILES) -o $(NAME) -I $(INCLUDE) $(PRINTFSRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all