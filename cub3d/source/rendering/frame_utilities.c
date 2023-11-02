/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:51 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 01:58:10 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Clears the entire frame by setting all its pixels to black (color 0).
 *
 * @param frame - The frame to be cleared.
 */
void	clear_frame(t_frame frame)
{
	char	*pixel;
	int		total;
	int		i;

	pixel = frame.addr;
	total = WIN_W * WIN_H;
	i = 0;
	while (i < total)
	{
		*(int *)pixel = 0;
		pixel += 4;
		i++;
	}
}

/**
 * Sets the color of a single pixel on the frame at the specified position 'p'.
 * It directly modifies the frame's memory to change the pixel color.
 *
 * @param frame - The frame where the pixel color is set.
 * @param p - The position (x, y) of the pixel to be colored.
 * @param color - The color value to be set for the pixel.
 */
inline void	frame_draw_pixel(t_frame frame, t_pixel_pos p, int color)
{
	*(int *)(frame.addr + 4 * (p.x + p.y * WIN_W)) = color;
}

/**
 * Displays the contents of the frame in the window. It uses the
 * mlx_put_image_to_window function to render the frame within the window.
 *
 * @param cub3d - A pointer to the main CUB3D structure.
 */
void	put_frame_to_window(t_cub3d *cub3d)
{
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->frame.mlx_img, 0,
		0);
}
