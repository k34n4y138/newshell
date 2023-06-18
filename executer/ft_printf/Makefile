# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 17:28:16 by yowazga           #+#    #+#              #
#    Updated: 2023/05/18 17:14:16 by yowazga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#include variables

NAME = libftprintf.a

SRC = ft_printf.c ft_putadd.c ft_putchar.c ft_puthex.c ft_putnbr.c ft_putstr.c

OBG = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBG)
	@ar -rsc $(NAME) $(OBG)

%.o:%.c ft_pritf.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -f $(OBG)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all makes clean fclean re
