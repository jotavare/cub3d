/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:40 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 03:00:51 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Fills the background of the frame with ceiling and floor colors.
 * Fill the top half of the frame with the ceiling color.
 * Fill the bottom half of the frame with the floor color.
 *
 * @param cub3d - The CUB3D game instance.
 */
void	render_ceiling_floor(t_cub3d *cub3d)
{
	t_pixel_pos	pix;
	int			ceiling_stop;

	ceiling_stop = WIN_H / 2;
	pix.y = -1;
	while (++pix.y < ceiling_stop)
	{
		pix.x = -1;
		while (++pix.x < WIN_W)
			frame_draw_pixel(cub3d->frame, pix, cub3d->parse.cc);
	}
	while (++pix.y < WIN_H)
	{
		pix.x = -1;
		while (++pix.x < WIN_W)
			frame_draw_pixel(cub3d->frame, pix, cub3d->parse.fc);
	}
}
