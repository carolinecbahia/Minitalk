# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 15:04:20 by ccavalca          #+#    #+#              #
#    Updated: 2025/10/29 18:00:37 by ccavalca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S = server
NAME_C = client
NAME_BONUS = $(NAME)_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I -I./Libft -I./ft_printf

LIBFT_DIR = Libft
PRINTF_DIR = ft_printf
BONUS_DIR = bonus

MANDATORY_SRCS = 	server.c \
					client.c \
					
BONUS_SRCS = 	$(wildcard $(BONUS_DIR)/*.c)

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT_A = $(LIBFT_DIR)/libft.a
PRINTF_A = $(PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(LIBFT_A) $(PRINTF_A) $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LIBFT_A) $(PRINTF_A) -o $(NAME)

$(LIBFT_A):
	make -C $(LIBFT_DIR)

$(PRINTF_A):
	make -C $(PRINTF_DIR)

bonus: $(NAME_BONUS)

$(NAME)_bonus: $(PRINTF_A) $(BONUS_OBJS) $(LIBFT_A) $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT_A) $(PRINTF_A) $(MANDATORY_OBJS) -o $(NAME_BONUS)

re: fclean all

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)

.PHONY: all clean fclean re bonus