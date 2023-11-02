# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotavare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 00:45:13 by jotavare          #+#    #+#              #
#    Updated: 2023/11/02 04:21:27 by jotavare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS		=	-Wall -Wextra -Werror -g
CC			=	cc

NAME		=	cub3d

HEADERS		=	include/cub3d.h
INCLUDE		=	-I ./include -I $(MLX_DIR) -I $(LIBFT_DIR)


SRCS		=	source/algorithm/check_walls.c \
				source/algorithm/initialize_player.c \
				source/algorithm/raycasting.c \
				source/algorithm/render_3d_view.c \
				source/cub3d/cub3d_utilities.c \
				source/cub3d/cub3d.c \
				source/cub3d/key_events.c \
				source/cub3d/player_movement.c \
				source/parsing/file_validation.c \
				source/parsing/map_dimensions.c \
				source/parsing/map_inicialize.c \
				source/parsing/map_populate.c \
				source/parsing/map_validation.c \
				source/parsing/process_data.c \
				source/parsing/validation_handling.c \
				source/parsing/validation_utilities.c \
				source/rendering/2d_minimap.c \
				source/rendering/ceiling_floor.c \
				source/rendering/frame_utilities.c \
				source/rendering/texture_loading.c \

OBJS		=	$(patsubst %.c,%.o,$(SRCS))

MLX_DIR		=	./extras/minilibx
MLX			=	$(MLX_DIR)/libmlx_Linux.a

LIBFT_DIR	=	./extras/libft
LIBFT		=	$(LIBFT_DIR)/libft.a

LIBS_DIR	=	-L $(MLX_DIR) -L $(LIBFT_DIR)
LIBS		=	-lft -lmlx -lX11 -lXext -lm

all :
	make -C $(LIBFT_DIR)
	make $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS_DIR) $(LIBS)

%.o : %.c $(HEADERS) Makefile $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean :
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

norm:
	@printf "$(CURSIVE)$(GRAY)"
	@norminette | grep -v OK!
	@printf "$(RESET)"

.PHONY : all clean fclean re
