/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:46 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/03 01:17:26 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Draws the minimap and the player's position in 2D.
 *
 * @param cub3d - A pointer to the main CUB3D structure.
 */
void	display_minimap(t_cub3d *cub3d)
{
	render_frame_2d_map(cub3d);
	render_frame_player(cub3d, cub3d->player.pdy / 64.0, cub3d->player.pdx
		/ 64.0);
}

/**
 * Draws the 2D representation of the map, with walls
 * represented in one color and sprites in another.
 *
 * @param cub3d - A pointer to the main CUB3D structure.
 */
void	render_frame_2d_map(t_cub3d *cub3d)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub3d->parse.map_h)
	{
		x = 0;
		while (x < cub3d->parse.map_w)
		{
			if (cub3d->parse.map[y][x] == 1)
				render_frame_block(cub3d, y, x, 4473924);
			if (cub3d->parse.map[y][x] == 2)
				render_frame_block(cub3d, y, x, 9211020);
			x++;
		}
		y++;
	}
}

/**
 * Draws the player's position on the minimap.
 * The player's position is scaled and represented with a specific color.
 *
 * @param cub3d - A pointer to the main CUB3D structure.
 * @param y_start - Scaled Y-coordinate of the player's position.
 * @param x_start - Scaled X-coordinate of the player's position.
 */
void	render_frame_player(t_cub3d *cub3d, float y_start, float x_start)
{
	t_pixel_pos	pos;
	int			x_end;
	int			y_end;

	x_end = x_start * MINIMAP_SCALE + MINIMAP_SCALE / 3;
	y_end = y_start * MINIMAP_SCALE + MINIMAP_SCALE / 3;
	pos.y = y_start * MINIMAP_SCALE - MINIMAP_SCALE / 3;
	while (pos.y < y_end)
	{
		pos.x = x_start * MINIMAP_SCALE - MINIMAP_SCALE / 3;
		while (pos.x < x_end)
		{
			frame_draw_pixel(cub3d->frame, pos, 16762880);
			pos.x++;
		}
		pos.y++;
	}
}

/**
 * Draws a block on the minimap based on the provided
 * position (y_start, x_start) and color.
 * This function is used to draw walls and sprites.
 *
 * @param cub3d - A pointer to the main CUB3D structure.
 * @param y_start - Scaled Y-coordinate of the block's position.
 * @param x_start - Scaled X-coordinate of the block's position.
 * @param color - The color of the block.
 */
void	render_frame_block(t_cub3d *cub3d, int y_start, int x_start, int color)
{
	t_pixel_pos	pos;
	int			x_end;
	int			y_end;

	x_end = x_start * MINIMAP_SCALE + MINIMAP_SCALE;
	y_end = y_start * MINIMAP_SCALE + MINIMAP_SCALE;
	pos.y = y_start * MINIMAP_SCALE;
	while (pos.y < y_end)
	{
		pos.x = x_start * MINIMAP_SCALE;
		while (pos.x < x_end)
		{
			frame_draw_pixel(cub3d->frame, pos, color);
			pos.x++;
		}
		pos.y++;
	}
}
