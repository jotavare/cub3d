/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:08:25 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:19:18 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * Represents a 2D pixel position with x and y coordinates.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 */
typedef struct s_pixel_pos
{
	int				x;
	int				y;
}					t_pixel_pos;

/**
 * Represents a frame containing image data and related properties.
 *
 * @param mlx_img A pointer to the image data.
 * @param addr The address of the image data.
 * @param bpp Bits per pixel.
 * @param line_len The length of a line in the image.
 * @param endian Endianness of the image data.
 */
typedef struct s_frame
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_frame;

/**
 * Represents a texture with image data, dimensions, and a frame.
 *
 * @param frame The frame containing image data and related properties.
 * @param width The width of the texture.
 * @param height The height of the texture.
 */
typedef struct s_texture
{
	t_frame			frame;
	int				width;
	int				height;
}					t_texture;

/**
 * Represents parsed data for a map, including map dimensions, texture
 * paths, and additional configuration settings.
 *
 * @param map A 2D integer array representing the map layout.
 * @param map_h The height of the map.
 * @param map_w The width of the map.
 * @param no Path to the north-facing wall texture.
 * @param so Path to the south-facing wall texture.
 * @param we Path to the west-facing wall texture.
 * @param ea Path to the east-facing wall texture.
 * @param fc The floor color value.
 * @param cc The ceiling color value.
 * @param fc_set Flag indicating if the floor color is set.
 * @param cc_set Flag indicating if the ceiling color is set.
 * @param parse_errno An error code indicating parsing errors (if any).
 */
typedef struct s_parse_data
{
	int				**map;
	int				map_h;
	int				map_w;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				fc;
	int				cc;
	int				fc_set;
	int				cc_set;
	int				parse_errno;
}					t_parse_data;

/**
 * Represents player-related data including position, orientation, and
 * input state.
 *
 * @param fov The field of view (FOV) angle.
 * @param pdx The player's horizontal position.
 * @param pdy The player's vertical position.
 * @param pa The player's angle of orientation.
 * @param move_forward Flag for moving forward.
 * @param move_backward Flag for moving backward.
 * @param move_right Flag for moving to the right.
 * @param move_left Flag for moving to the left.
 * @param move_pa_left Flag for rotating player angle to the left.
 * @param move_pa_right Flag for rotating player angle to the right.
 * @param plane_vec_x The vector component for the camera's plane in
 * the x-direction.
 * @param plane_vec_y The vector component for the camera's plane in
 * the y-direction.
 */
typedef struct s_player_data
{
	float			fov;
	float			pdx;
	float			pdy;
	float			pa;
	int				move_forward;
	int				move_backward;
	int				move_right;
	int				move_left;
	int				move_pa_left;
	int				move_pa_right;
	double			plane_vec_x;
	double			plane_vec_y;
}					t_player_data;

/**
 * Represents data related to a ray's properties and interactions in
 * a 2D space.
 *
 * @param ra The ray's angle.
 * @param rx The ray's horizontal component.
 * @param ry The ray's vertical component.
 * @param xo The starting X-coordinate of the ray.
 * @param yo The starting Y-coordinate of the ray.
 * @param mx The map grid X-coordinate where the ray intersects.
 * @param my The map grid Y-coordinate where the ray intersects.
 * @param mp The type of map element the ray intersects with.
 * @param hit_horizontal Flag indicating if the ray hit a horizontal
 * map boundary.
 * @param texture Pointer to the texture associated with the ray.
 */
typedef struct s_ray_data
{
	float			ra;
	float			rx;
	float			ry;
	float			xo;
	float			yo;
	int				mx;
	int				my;
	int				mp;
	int				hit_horizontal;
	t_texture		*texture;
}					t_ray_data;

/**
 * Represents the main data structure for the Cub3D game, containing
 * various game elements.
 *
 * @param mlx A pointer to the MLX (MiniLibX) connection.
 * @param window A pointer to the game window.
 * @param parse Parsed data for the game map and configuration.
 * @param frame Data related to the game's frame.
 * @param n_tex North-facing wall texture data.
 * @param s_tex South-facing wall texture data.
 * @param w_tex West-facing wall texture data.
 * @param e_tex East-facing wall texture data.
 * @param player Player-related data, including position, orientation,
 * and input state.
 * @param ray_list An array of ray data structures.
 * @param ray_count The number of rays in the array.
 * @param exit A flag indicating whether the game should exit.
 * @param alloc_err Flag indicating memory allocation errors.
 */
typedef struct s_cub3d
{
	void			*mlx;
	void			*window;
	t_parse_data	parse;
	t_frame			frame;
	t_texture		n_tex;
	t_texture		s_tex;
	t_texture		w_tex;
	t_texture		e_tex;
	t_player_data	player;
	t_ray_data		*ray_list;
	int				ray_count;
	int				exit;
	int				alloc_err;
}					t_cub3d;

/**
 * Represents data related to texturing in the Cub3D game, including
 * offsets, source and destination pixel positions, a reference to the
 * game's data, and the texture to be applied.
 *
 * @param t_off The texturing offset.
 * @param src The source pixel position for texturing.
 * @param dst The destination pixel position for texturing.
 * @param data A pointer to the main game data structure (t_cub3d).
 * @param texture A pointer to the texture to be applied.
 */
typedef struct s_texturing_data
{
	int				t_off;
	t_pixel_pos		src;
	t_pixel_pos		dst;
	t_cub3d			*data;
	t_texture		*texture;
}					t_texturing_data;

#endif
