# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 15:17:07 by jyao              #+#    #+#              #
#    Updated: 2022/02/15 19:30:53 by jyao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME := libftprintf.a

CC := gcc

CFLAGS := -Wall -Wextra -Werror

SRCS = ft_printf.c hft_parsef.c hft_putchar.c hft_putstr.c \
	hft_putdeci.c hft_putudeci.c hft_putlhex.c hft_writehexpfix.c

OBJS = $(SRCS:.c=.o)

# make rules

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $^

.c.o: libftprintf.h
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

bonus: all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all