# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acollon <acollon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 13:22:58 by acollon           #+#    #+#              #
#    Updated: 2025/08/15 11:35:30 by acollon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

INC_DIR = includes
LIBFT_DIR = libft
SRCS	= \
		src/error_handler.c \
		src/execution.c \
		src/parsing.c

SRCS_BONUS	= \
		bonus/handle_close.c \
		bonus/main.c \
		bonus/pipeline_builder.c \
		bonus/parsing_bonus.c \
		bonus/pipex_bonus.c \
		bonus/split_argv_utils.c

OBJS	= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I $(INC_DIR) -o $(NAME)

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS_BONUS)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

rebonus : fclean bonus

.PHONY: all clean fclean re bonus rebonus