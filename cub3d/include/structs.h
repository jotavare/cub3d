/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:08:25 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 03:12:42 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_pixel_pos
{
	int	x;
	int	y;
}	t_pixel_pos;

typedef struct s_frame
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_frame;

typedef struct s_texture
{
	t_frame	frame;
	int		width;
	int		height;
}	t_texture;

typedef struct s_parse_data
{
	int		**map;
	int		map_h;
	int		map_w;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		fc;
	int		cc;
	int		fc_set;
	int		cc_set;
	int		parse_errno;
}	t_parse_data;

typedef struct s_player_data
{
	float	fov;
	float	pdx;
	float	pdy;
	float	pa;
	int		move_forward;
	int		move_backward;
	int		move_right;
	int		move_left;
	int		move_pa_left;
	int		move_pa_right;
	double	plane_vec_x;
	double	plane_vec_y;
}	t_player_data;

typedef struct s_ray_data
{
	float		ra;
	float		rx;
	float		ry;
	float		xo;
	float		yo;
	int			mx;
	int			my;
	int			mp;
	int			hit_horizontal;
	t_texture	*texture;
}	t_ray_data;

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
}	t_cub3d;

typedef struct s_texturing_data
{
	int			t_off;
	t_pixel_pos	src;
	t_pixel_pos	dst;
	t_cub3d		*data;
	t_texture	*texture;
}	t_texturing_data;

#endif