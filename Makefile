# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonny <jonny@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 12:04:03 by josaykos          #+#    #+#              #
#    Updated: 2020/07/30 18:43:37 by jonny            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname)

# Colors
GREEN = `tput setaf 2`
RED = `tput setaf 1`
END = `tput sgr0`

NAME	= cub3D
LIBFT	= libft/libft.a
MLX 	= mlx/
CC 		= gcc -D MACOS

INCLUDES = -Iincludes -Ilibft -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

SRC_NAME	= 	main.c \
				cub3d_parsing_1.c \
				cub3d_parsing_2.c \
				cub3d_parsing_3.c \
				cub3d_utils_1.c \
				cub3d_utils_2.c \
				cub3d_events.c \
				cub3d_moves.c \
				cub3d_textures.c \
				cub3d_graphics.c \
				cub3d_graphics2.c \
				cub3d_debug.c \
				cub3d_screenshot.c \
				cub3d_errors.c \
				cub3d_sprites.c \
				cub3d_sprites2.c \
				cub3d_raycasting.c \
				cub3d_interface.c \
				cub3d_interface2.c \
				cub3d_memory.c \
				cub3d_macos.c \

ifeq ($(OS), Linux)
INCLUDES = -Iincludes -Ilibft -Iminilibx_linux -Lminilibx_linux -lmlx -lXext -lX11 -lpthread -lm -lbsd
MLX 	= minilibx_linux/
CC 		= clang -D LINUX
SRC_NAME	= 	main.c \
				cub3d_parsing_1.c \
				cub3d_parsing_2.c \
				cub3d_parsing_3.c \
				cub3d_utils_1.c \
				cub3d_utils_2.c \
				cub3d_events.c \
				cub3d_moves.c \
				cub3d_textures.c \
				cub3d_graphics.c \
				cub3d_graphics2.c \
				cub3d_debug.c \
				cub3d_screenshot.c \
				cub3d_errors.c \
				cub3d_sprites.c \
				cub3d_sprites2.c \
				cub3d_raycasting.c \
				cub3d_interface.c \
				cub3d_interface2.c \
				cub3d_memory.c \
				cub3d_linux.c
endif

OBJ	= $(SRC:.c=.o)

SRC_PATH = src

SRC 		= $(addprefix $(SRC_PATH)/,$(SRC_NAME))

RM		= rm -rf

all:	$(NAME)

$(NAME): $(OBJ)
	make -C libft/ 1>/dev/null
	@echo "$(GREEN)$(LIBFT) done...$(END)"
	make -C $(MLX) 1>/dev/null 2>/dev/null
	@echo "$(GREEN)mlx/libmlx.a done...$(END)"
	$(CC) $(OBJ) $(LIBFT) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)$(NAME) binary compilation completed !$(END)"

%.o: %.c
	@echo "$(GREEN)Compiling $<$ ...$(END)"
	$(CC) -Wall -Wextra -Werror -Iincludes -I$(MLX) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)
	make fclean -C libft/ 1>/dev/null
	make clean -C $(MLX) 1>/dev/null
	@echo "$(RED)$(LIBFT) removed$(END)"
	@echo "$(RED)mlx/libmlx.a removed$(END)"
	@echo "$(RED)$(NAME) removed$(END)"

re: clean fclean all
