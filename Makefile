# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 05:57:11 by alex              #+#    #+#              #
#    Updated: 2026/02/08 09:28:08 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -O3
LINK_FLAGS = -L$(INCLUDE_FILE)/libft -lft -L$(INCLUDE_FILE)/minilibx-linux -lmlx_Linux \
			-lXext -lX11 -lm -lz
	
FILE_NAME = fractol
SRC_DIR = src
HEADERS = fractol.h
INCLUDE_FILE = libs
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/math_utils.c $(SRC_DIR)/utils.c \
		$(SRC_DIR)/set_definition.c $(SRC_DIR)/render.c \
		$(SRC_DIR)/create_cgi_env.c $(SRC_DIR)/events.c \
		$(SRC_DIR)/color_treatment.c

LIBFT = libft.a
MINI_LIBX = libmlx.a
PRINTF = libftprintf.a

OBJS = $(SRC:.c=.o)

all: $(LIBFT) $(MINI_LIBX) $(NAME) 

libft: $(LIBFT)

MiniLibx: $(MINI_LIBX)

message: 
	@echo "    _    _     ____    _    ____  ____  ___ _     "
	@echo "   / \\  | |   / ___|  / \\  |  _ \\|  _ \\|_ _| |    "
	@echo "  / _ \\ | |  | |     / _ \\ | |_) | |_) || || |    "
	@echo " / ___ \\| |__| |___ / ___ \\|  _ <|  _ < | || |___ "
	@echo "/_/   \\_\\_____\\____/_/   \\_\\_| \\_\\_| \\_\\___|_____|"
	@echo " La carpeta predefinida es: $(FILE_NAME). Si quieres cambiarla pon el nombre de la carpeta que contiene al proyecto EJ: make FILE_NAME="nombre de tu carpeta" "

$(LIBFT): 
	make all -C $(INCLUDE_FILE)/libft

$(MINI_LIBX):
	make all -C $(INCLUDE_FILE)/minilibx-linux

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LINK_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(INCLUDE_FILE)/libft
	make clean -C $(INCLUDE_FILE)/minilibx-linux
	rm -f $(OBJS) $(BONUS_OBJS)
	rm -f $(NAME)
	
fclean: clean
	make fclean -C $(INCLUDE_FILE)/libft
	rm -f $(NAME)

re: fclean all

PHONY: make clean fclean re bonus
	

