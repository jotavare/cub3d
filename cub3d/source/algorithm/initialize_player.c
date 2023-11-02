/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:51:51 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 01:51:52 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Calculate the initial player angle (pa) based on the
 * starting point's identifier.
 *
 * @param start The starting point identifier.
 * @return The initial player angle in radians.
 */
float	start_point_angle(int start)
{
	if (start == 3)
		return (PI / 2.0);
	if (start == 4)
		return (3.0 * (PI / 2.0));
	if (start == 5)
		return (0.0);
	if (start == 6)
		return (PI);
	return (-1.000001);
}

/**
 * Initialize the player data, including their position
 * (pdy, pdx), angle (pa), and plane vector.
 *
 * @param data A pointer to the CUB3D data structure.
 */
void	initialize_player(t_cub3d *data)
{
	t_player_data	*player;
	int				y;
	int				x;

	player = &(data->player);
	player->fov = 60;
	y = -1;
	while (++y < data->parse.map_h)
	{
		x = -1;
		while (++x < data->parse.map_w)
		{
			if (data->parse.map[y][x] >= 3)
			{
				player->pa = start_point_angle(data->parse.map[y][x]);
				player->pdy = y * RES + RES / 2;
				player->pdx = x * RES + RES / 2;
				update_player_plane_vector(data);
				data->parse.map[y][x] = 1;
			}
		}
	}
}
