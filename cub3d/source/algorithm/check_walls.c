/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:50:52 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 01:50:53 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Verifies if a given point (x, y) is inside the game map boundaries.
 *
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @param w The width of the game map.
 * @param h The height of the game map.
 *
 * @return [1] point is within the map boundaries [0] not within
 * the map boundaries.
 */
int	map_coords(int x, int y, int w, int h)
{
	return ((x > 0 && y > 0) && (x < w && y < h));
}

/**
 * Compute the distance to the nearest horizontal wall intersection
 * for a given ray.
 *
 * @param player A pointer to the player's data.
 * @param ray A pointer to the ray's data.
 * @param atan The tangent of the ray's angle.
 */
void	calc_horizon_dist_wall(t_player_data *player, t_ray_data *ray,
		float atan)
{
	if (sin(ray->ra) > 0.00001)
	{
		ray->ry = (((int)player->pdy >> 6) << 6) - 0.001;
		ray->rx = ((player->pdy - ray->ry) * atan + player->pdx);
		ray->yo = -RES;
		ray->xo = -ray->yo * atan;
	}
	else if (sin(ray->ra) < -0.00001)
	{
		ray->ry = (((int)player->pdy >> 6) << 6) + RES;
		ray->rx = ((player->pdy - ray->ry) * atan + player->pdx);
		ray->yo = RES;
		ray->xo = -ray->yo * atan;
	}
	else
	{
		ray->ry = player->pdy;
		ray->rx = player->pdx;
		if (cos(ray->ra) < 0.00001)
			ray->xo = -RES;
		else
			ray->xo = RES;
		ray->yo = 0;
	}
}

/**
 * Check for the presence of horizontal walls and intersections
 * for a given ray within the game map.
 *
 * @param data A pointer to the CUB3D data structure.
 * @param ray_elem A pointer to the ray's data element.
 *
 * @return A pointer to the updated ray data structure.
 */
t_ray_data	*horizontal_wall_check(t_cub3d *data, t_ray_data *ray_elem)
{
	t_ray_data		*ray;
	t_player_data	*player;
	float			atan;
	int				ok;

	ok = 0;
	ray = ray_elem;
	atan = 1.0 / tan(ray->ra);
	calc_horizon_dist_wall(player = &(data->player), ray, atan);
	while (!ok)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		if ((map_coords(ray->mx, ray->my, data->parse.map_w, data->parse.map_h)
				&& data->parse.map[ray->my][ray->mx] == 2)
			|| !map_coords(ray->mx, ray->my, data->parse.map_w,
				data->parse.map_h))
			ok = 1;
		if (!ok)
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
		}
	}
	return (ray);
}

/**
 * computes the distance to the nearest vertical wall intersection
 * for a given ray.
 *
 * @param player A pointer to the player's data.
 * @param ray A pointer to the ray's data.
 * @param atan The tangent of the ray's angle.
 */
void	calc_vertical_dist_wall(t_player_data *player, t_ray_data *ray,
		float atan)
{
	if (cos(ray->ra) < 0.00001)
	{
		ray->rx = (((int)player->pdx >> 6) << 6) - 0.001;
		ray->ry = ((player->pdx - ray->rx) * atan + player->pdy);
		ray->xo = -RES;
		ray->yo = -ray->xo * atan;
	}
	else
	{
		ray->rx = (((int)player->pdx >> 6) << 6) + RES;
		ray->ry = ((player->pdx - ray->rx) * atan + player->pdy);
		ray->xo = RES;
		ray->yo = -ray->xo * atan;
	}
}

/**
 * Checks for the presence of vertical walls and intersections
 * for a given ray within the game map.
 *
 * @param data A pointer to the CUB3D data structure.
 * @param ray_elem A pointer to the ray's data element.
 *
 * @return A pointer to the updated ray data structure.
 */
t_ray_data	*vertical_wall_check(t_cub3d *data, t_ray_data *ray_elem)
{
	t_ray_data		*ray;
	t_player_data	*player;
	float			atan;
	int				ok;

	ok = 0;
	ray = ray_elem;
	atan = tan(ray->ra);
	calc_vertical_dist_wall(player = &(data->player), ray, atan);
	while (!ok)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		if ((map_coords(ray->mx, ray->my, data->parse.map_w, data->parse.map_h)
				&& data->parse.map[ray->my][ray->mx] == 2)
			|| !map_coords(ray->mx, ray->my, data->parse.map_w,
				data->parse.map_h))
			ok = 1;
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
		}
	}
	return (ray);
}
