# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 00:04:28 by ccavalca          #+#    #+#              #
#    Updated: 2025/10/31 01:12:29 by ccavalca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S = server
NAME_C = client
NAME_S_BONUS = $(NAME_S)_bonus
NAME_C_BONUS = $(NAME_C)_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I./Libft -I./ft_printf

LIBFT_DIR = Libft/
PRINTF_DIR = ft_printf/

SERVER_SRC =	server.c \

CLIENT_SRC =	client.c \
					
SERVER_BONUS_SRCS =		server_bonus.c \

CLIENT_BONUS_SRCS =		client_bonus.c \

SERVER_OBJS = $(SERVER_SRC:.c=.o)
CLIENT_OBJS = $(CLIENT_SRC:.c=.o)
SERVER_BONUS_OBJS = $(SERVER_BONUS_SRCS:.c=.o)
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_SRCS:.c=.o)

LIBFT_A = $(LIBFT_DIR)/libft.a
PRINTF_A = $(PRINTF_DIR)/libftprintf.a

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(LIBFT_A) $(PRINTF_A) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT_A) $(PRINTF_A) -o $(NAME_S)

$(NAME_C): $(LIBFT_A) $(PRINTF_A) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT_A) $(PRINTF_A) -o $(NAME_C)

$(LIBFT_A):
	make -C $(LIBFT_DIR)

$(PRINTF_A):
	make -C $(PRINTF_DIR)

bonus: $(NAME_S_BONUS) $(NAME_C_BONUS)

$(NAME_S_BONUS): $(PRINTF_A) $(LIBFT_A) $(SERVER_BONUS_OBJS)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJS) $(LIBFT_A) $(PRINTF_A) -o $(NAME_S_BONUS)

$(NAME_C_BONUS): $(PRINTF_A) $(LIBFT_A) $(CLIENT_BONUS_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJS) $(LIBFT_A) $(PRINTF_A) -o $(NAME_C_BONUS)

re: fclean all

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER_BONUS_OBJS) $(CLIENT_BONUS_OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME_S) $(NAME_C) $(NAME_S_BONUS) $(NAME_C_BONUS)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)

.PHONY: all clean fclean re bonus