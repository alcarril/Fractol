# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 05:57:11 by alex              #+#    #+#              #
#    Updated: 2025/12/27 11:14:58 by alejandro        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -O3
LINK_FLAGS = -L$(INCLUDE_FILE)/libft -lft -L$(INCLUDE_FILE)/minilibx-linux -lmlx_Linux \
			-lXext -lX11 -lm -lz
	
FILE_NAME = fractol
HEADERS = $(SRC_FILE)/fractol.h
INCLUDE_FILE = include
SRC = main.c math_utils.c utils.c set_definition.c render.c \
		create_cgi_env.c events.c color_treatment.c

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
	

