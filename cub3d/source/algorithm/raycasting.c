/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:49:07 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/03 01:17:19 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Use Pythagoras theorem to calculate the distance between
 * two points(ax, ay) and (bx, by).
 *
 * Formula: sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))
 *
 * @param ax The x-coordinate of the first point.
 * @param ay The y-coordinate of the first point.
 * @param bx The x-coordinate of the second point.
 * @param by The y-coordinate of the second point.
 * @return The Euclidean distance between the two points.
 */
float	pythagoras_distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

/**
 * Check for the shortest line between two ray intersections:
 * horizontal and vertical.
 *
 * @param p The player data.
 * @param h_inter The data of the horizontal ray intersection.
 * @param v_inter The data of the vertical ray intersection.
 * @return The ray data with the shortest line.
 */
t_ray_data	shortest_line(t_player_data *p, t_ray_data h_inter,
		t_ray_data v_inter)
{
	float	dish;
	float	disv;

	dish = pythagoras_distance(p->pdx, p->pdy, h_inter.rx, h_inter.ry);
	disv = pythagoras_distance(p->pdx, p->pdy, v_inter.rx, v_inter.ry);
	if (dish > disv && dish != pythagoras_distance(p->pdx, p->pdy, p->pdx,
			p->pdy))
	{
		v_inter.hit_horizontal = 0;
		return (v_inter);
	}
	h_inter.hit_horizontal = 1;
	return (h_inter);
}

/**
 * Renders the 3D world based on the ray data and ray number.
 *
 * @param data A pointer to the CUB3D data structure.
 */
void	render_3d_world(t_cub3d *data)
{
	int	i;
	int	ray_num;

	ray_num = 0;
	i = data->ray_count - 1;
	while (i >= 0)
	{
		render_3d_ray(data, data->ray_list[i], ray_num);
		ray_num++;
		i--;
	}
}

/**
 * Calculates the angle of a ray based on the window's X position.
 *
 * @param data A pointer to the CUB3D data structure.
 * @param window_x The X position of the window.
 * @return The angle of the ray in radians.
 */
double	ray_angle(t_cub3d *data, int window_x)
{
	double	ra_vec_x;
	double	ra_vec_y;
	double	pa_vec_x;
	double	pa_vec_y;
	double	camera_x;

	camera_x = 2 * window_x / (double)WIN_W - 1;
	pa_vec_x = cos(data->player.pa);
	pa_vec_y = sin(data->player.pa);
	ra_vec_x = pa_vec_x + data->player.plane_vec_x * camera_x;
	ra_vec_y = pa_vec_y + data->player.plane_vec_y * camera_x;
	return (atan2(ra_vec_y, ra_vec_x));
}

/**
 * Cast rays to determine ray intersections and stores the
 * results in the ray list.
 *
 * @param data A pointer to the CUB3D data structure.
 * @return [0] Success [1] Failure.
 */
int	pew_pew_rays(t_cub3d *data)
{
	t_ray_data	vertical_inter;
	t_ray_data	horizontal_inter;
	int			i;

	i = 0;
	data->ray_count = 0;
	data->ray_list = malloc(sizeof(t_ray_data) * (WIN_W) + 1);
	if (!data->ray_list)
		return (1);
	while (i < WIN_W)
	{
		data->ray_list[i].ra = ray_angle(data, i);
		horizontal_inter = *horizontal_wall_check(data, &data->ray_list[i]);
		vertical_inter = *vertical_wall_check(data, &data->ray_list[i]);
		data->ray_list[i] = shortest_line(&(data->player), horizontal_inter,
				vertical_inter);
		i++;
	}
	data->ray_count = WIN_W;
	return (0);
}
