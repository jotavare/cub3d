/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:49:01 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 03:10:24 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Renders the 3D view of the game world by calculating the
 * height of vertical columns representing walls and texturing them.
 * It uses raycasting to determine the wall heights and textures.
 *
 * @param data A pointer to the CUB3D data structure.
 * @param ray The ray data for a particular column.
 * @param ray_num The index of the ray.
 */
void	render_3d_ray(t_cub3d *data, t_ray_data ray, int ray_num)
{
	int					lineh;
	float				disw;
	int					lineo;
	float				ca;
	t_texturing_data	text_data;

	text_data.t_off = 0;
	ca = data->player.pa - ray.ra;
	disw = (cos(ca)) * (cos(ray.ra) * (ray.rx - data->player.pdx) - sin(ray.ra)
			* (ray.ry - data->player.pdy));
	lineh = (RES * WIN_H) / disw;
	if (lineh > WIN_H)
	{
		text_data.t_off = (lineh - WIN_H) / 2;
		lineh = WIN_H;
	}
	lineo = WIN_H - (WIN_H / 2 - lineh / 2);
	text_data.src.x = ray_num;
	text_data.src.y = lineo - lineh;
	text_data.dst.x = text_data.src.x + 1;
	text_data.dst.y = lineo;
	text_data.data = data;
	ray.texture = get_ray_texture(text_data.data, ray);
	render_texture_pillar(ray, &text_data);
}

/**
 * Render a textured pillar for a ray, accounting for wall
 * height and texturing.
 *
 * @param ray The ray data for a particular column.
 * @param text_data A pointer to the texturing data.
 */
void	render_texture_pillar(t_ray_data ray, t_texturing_data *text_data)
{
	int	height;
	int	ray_hit_pos;

	text_data->texture = ray.texture;
	ray_hit_pos = ray_hit_position(ray);
	height = text_data->dst.y - text_data->src.y;
	while (text_data->src.x < text_data->dst.x)
	{
		frame_texture_line(text_data, text_data->src, height, ray_hit_pos);
		text_data->src.x++;
	}
}

/**
 * Renders a line of a texture onto the frame, taking into
 * account the source and destination positions, window line
 * height, and texture x-coordinate.
 *
 * @param text_data A pointer to the texturing data.
 * @param window_src The source position on the window.
 * @param window_line_h The height of the window line.
 * @param texture_x The x-coordinate in the texture.
 */
void	frame_texture_line(t_texturing_data *text_data, t_pixel_pos window_src,
		int window_line_h, int texture_x)
{
	t_pixel_pos	window_pos;
	t_pixel_pos	texture_pos;
	int			i;

	i = 0;
	window_pos.x = window_src.x;
	window_pos.y = window_src.y;
	texture_pos.x = texture_x;
	while (i < window_line_h)
	{
		texture_pos.y = (float)(i + text_data->t_off) / (window_line_h
				+ text_data->t_off * 2) * (text_data->texture->height);
		frame_draw_pixel(text_data->data->frame, window_pos,
			retrieve_texture_pixel(*(text_data->texture), texture_pos));
		window_pos.y++;
		i++;
	}
}

/**
 * Calculates the position in the texture where the ray has
 * hit based on whether the ray is horizontal or vertical.
 *
 * @param ray The ray data for a particular column.
 * @return The x-coordinate in the texture where the ray has hit.
 */
int	ray_hit_position(t_ray_data ray)
{
	int	width;

	width = ray.texture->width;
	if (ray.hit_horizontal)
	{
		if (ray.yo > 0.0)
			return (width - ((int)(ray.rx / RES * width) % width) - 1);
		return (((int)(ray.rx / RES * width) % width));
	}
	if (ray.xo > 0.0)
		return (((int)(ray.ry / RES * width) % width));
	return (width - ((int)(ray.ry / RES * width) % width) - 1);
}

/**
 * Determines the appropriate texture (North, South, East,
 * or West) for a ray based on its orientation and hit direction.
 *
 * @param data A pointer to the CUB3D data structure.
 * @param ray The ray data for a particular column.
 * @return A pointer to the texture for the ray.
 */
t_texture	*get_ray_texture(t_cub3d *data, t_ray_data ray)
{
	if (ray.hit_horizontal)
	{
		if (ray.yo > 0.0)
			return (&data->s_tex);
		return (&data->n_tex);
	}
	if (ray.xo > 0.0)
		return (&data->e_tex);
	return (&data->w_tex);
}
