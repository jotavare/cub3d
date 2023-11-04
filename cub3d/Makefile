# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotavare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/04 17:45:51 by jotavare          #+#    #+#              #
#    Updated: 2023/11/04 18:29:17 by jotavare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags (enables warnings and debugging information).
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Executable name, header files, and flags to include header files.
NAME = cub3D
HEADERS = include/cub3d.h
INCLUDE = -I ./include -I $(MLX_DIR) -I $(LIBFT_DIR)

# Path to source files.
SRCS = source/algorithm/check_walls.c \
       source/algorithm/initialize_player.c \
       source/algorithm/raycasting.c \
       source/algorithm/render_3d_view.c \
       source/cub3d/cub3d_utilities.c \
       source/cub3d/cub3d.c \
       source/cub3d/key_events.c \
       source/cub3d/player_movement.c \
       source/parsing/file_validation.c \
       source/parsing/map_dimensions.c \
       source/parsing/map_initialize.c \
       source/parsing/map_populate.c \
       source/parsing/map_validation.c \
       source/parsing/process_data.c \
       source/parsing/validation_handling.c \
       source/parsing/validation_utilities.c \
       source/rendering/2d_minimap.c \
       source/rendering/ceiling_floor.c \
       source/rendering/frame_utilities.c \
       source/rendering/texture_loading.c

# Generate object file names (.c -> .o) from source files.
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Location of the MiniLibx and Libft directories.
# Also includes the library files (.a) of each one.
MLX_DIR = ./extras/minilibx
MLX = $(MLX_DIR)/libmlx_Linux.a
LIBFT_DIR = ./extras/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Flags to specify and link MiniLibx and Libft directories.
LIBS_DIR = -L $(MLX_DIR) -L $(LIBFT_DIR)
LIBS = -lft -lmlx -lX11 -lXext -lm

# Makefile rules.
# Build the project.
all: make_libft make_cub3D

# Build the cub3D executable.
make_cub3D: $(OBJS) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS_DIR) $(LIBS)

# Build object files from source files.
%.o : %.c $(HEADERS) Makefile $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Build the Libft library.
make_libft:
	make -C $(LIBFT_DIR)

# Clean up object files.
clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

# Remove the executable and clean files.
fclean: clean
	rm -f $(NAME)

# Clean and rebuild the project.
re: fclean all

# Check code style using norminette (including .c and .h).
norm: 
	@norminette ./extras/libft/
	@norminette -R CheckForbiddenSourceHeader ./extras/libft/libft.h
	@norminette ./source/
	@norminette -R CheckForbiddenSourceHeader ./include/

# Clone MiniLibX from its original repository.
mlx: 
	git clone git@github.com:42Paris/minilibx-linux.git
	mv minilibx-linux extras/minilibx
	cd extras/minilibx && ./configure

# Rules that are not associated with files.
.PHONY: all make_cub3D make_libft clean fclean re norm mlx
