# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/17 14:56:05 by yinzhang          #+#    #+#              #
#    Updated: 2019/05/31 15:54:19 by yinzhang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FT_PRINTF_SRC = char.c conversions.c\
				ft_printf.c modifers.c\
				string.c auxilliary.c\
				pointer.c int.c\
				octal.c hex.c\
				udecimalint.c float.c\
				auxilliary2.c float2.c\
				cat.c binary.c\
				
LIBFT_PATH = libft/
LIBFT_SRC = ft_bzero.c ft_memalloc.c \
			ft_strlen.c ft_strdup.c ft_strcpy.c ft_strchr.c ft_strcmp.c \
			ft_atoi.c ft_isdigit.c ft_putchar.c ft_strjoin.c ft_strcat.c\

OBJ += $(FT_PRINTF_SRC:.c=.o)
OBJ += $(addprefix $(LIBFT_PATH),$(LIBFT_SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

CLEAR_LINE = \033[2K\c

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\nCreating $@"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@echo "$(CLEAR_LINE)"
	@echo "Compiling $<\r\c"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
