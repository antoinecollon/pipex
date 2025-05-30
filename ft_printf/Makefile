# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acollon <acollon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 14:39:44 by acollon           #+#    #+#              #
#    Updated: 2025/04/28 09:38:40 by acollon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
SRC		=	$(SRC_DIR)/ft_printf.c \
			$(SRC_DIR)/ft_putchar.c \
			$(SRC_DIR)/ft_putstr.c \
			$(SRC_DIR)/ft_putnbr.c \
			$(SRC_DIR)/ft_putnbr_unsigned.c \
			$(SRC_DIR)/ft_puthex.c \
			$(SRC_DIR)/ft_putptr.c \
			$(SRC_DIR)/ft_dispatch.c

OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# TEST_SRC = test/main.c
# TEST_EXE = test_printf

all: $(LIBFT) $(NAME)

$(LIBFT):
	cd $(LIBFT_DIR) && $(MAKE)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	cd $(LIBFT_DIR) && $(MAKE) clean

fclean: clean
	$(RM) $(NAME)
#	$(RM) $(TEST_EXE)
	cd $(LIBFT_DIR) && $(MAKE) fclean

re: fclean all

# test: $(NAME)
#	cd $(LIBFT_DIR) && $(MAKE)
#	$(CC) $(CFLAGS) $(TEST_SRC) $(NAME) -L$(LIBFT_DIR) -lft -o $(TEST_EXE)

.PHONY: clean re fclean all test
