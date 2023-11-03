/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+  +#+           */
/*   Created: 2023/11/02 00:07:58 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 02:04:23 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Update the player's position based on key events for movement and rotation.
 *
 * @param data A pointer to the structure.
 */
void	update_player_pos(t_cub3d *data)
{
	if (data->player.move_pa_right)
		data->player.pa -= (float)PLAYER_ANGLE_SPEED / 100.0;
	if (data->player.move_pa_left)
		data->player.pa += (float)PLAYER_ANGLE_SPEED / 100.0;
	update_player_plane_vector(data);
	if (data->player.move_left)
		player_move(data, (float)PLAYER_SPEED * -sin(data->player.pa),
			(float)PLAYER_SPEED * -cos(data->player.pa));
	if (data->player.move_right)
		player_move(data, (float)PLAYER_SPEED * sin(data->player.pa),
			(float)PLAYER_SPEED * cos(data->player.pa));
	if (data->player.move_forward)
		player_move(data, (float)PLAYER_SPEED * cos(data->player.pa),
			(float)PLAYER_SPEED * -sin(data->player.pa));
	if (data->player.move_backward)
		player_move(data, (float)PLAYER_SPEED * -cos(data->player.pa),
			(float)PLAYER_SPEED * sin(data->player.pa));
}

/**
 * Update the player's plane vector used in rendering.
 *
 * @param data A pointer to the structure.
 */
void	update_player_plane_vector(t_cub3d *data)
{
	double	plane_angle;
	double	multiplier;

	multiplier = 0.75;
	plane_angle = data->player.pa + (PI / 2.0);
	data->player.plane_vec_x = cos(plane_angle) * multiplier;
	data->player.plane_vec_y = sin(plane_angle) * multiplier;
}

/**
 * Move the player in the game world.
 *
 * @param data A pointer to the structure.
 * @param x_add The amount to move in the x-direction.
 * @param y_add The amount to move in the y-direction.
 */
void	player_move(t_cub3d *data, float x_add, float y_add)
{
	int	x_neg;
	int	y_neg;

	x_neg = x_add < 0;
	y_neg = y_add < 0;
	if (x_neg)
		x_add = -x_add;
	if (y_neg)
		y_add = -y_add;
	while (x_add > 0 || y_add > 0)
	{
		if (x_add > 0 && x_neg)
			data->player.pdx += max_valid_x_move(data, -min_float(0.02, x_add));
		if (x_add > 0 && !x_neg)
			data->player.pdx += max_valid_x_move(data, min_float(0.02, x_add));
		if (y_add > 0 && y_neg)
			data->player.pdy += max_valid_y_move(data, -min_float(0.02, y_add));
		if (y_add > 0 && !y_neg)
			data->player.pdy += max_valid_y_move(data, min_float(0.02, y_add));
		x_add -= 0.02;
		y_add -= 0.02;
	}
}

/**
 * Get the maximum allowed movement in the x-direction for the player.
 *
 * @param data A pointer to the structure.
 * @param x_want The desired x-movement.
 * @return The maximum allowed x-movement.
 */
float	max_valid_x_move(t_cub3d *data, float x_want)
{
	int	map_y;
	int	map_x_want;

	if (x_want < 0)
		map_x_want = data->player.pdx + x_want - ((float)SLIDE_DISTANCE * RES);
	else
		map_x_want = data->player.pdx + x_want + ((float)SLIDE_DISTANCE * RES);
	map_x_want /= RES;
	map_y = data->player.pdy / (float)RES;
	if (data->parse.map[map_y][map_x_want] == 2)
		return (0);
	map_y = data->player.pdy / (float)RES + SLIDE_DISTANCE;
	if (data->parse.map[map_y][map_x_want] == 2)
		return (0);
	map_y = data->player.pdy / (float)RES - SLIDE_DISTANCE;
	if (data->parse.map[map_y][map_x_want] == 2)
		return (0);
	return (x_want);
}

/**
 * Get the maximum allowed movement in the y-direction for the player.
 *
 * @param data A pointer to the structure.
 * @param y_want The desired y-movement.
 * @return The maximum allowed y-movement.
 */
float	max_valid_y_move(t_cub3d *data, float y_want)
{
	int	map_x;
	int	map_y_want;

	if (y_want < 0)
		map_y_want = data->player.pdy + y_want - ((float)SLIDE_DISTANCE * RES);
	else
		map_y_want = data->player.pdy + y_want + ((float)SLIDE_DISTANCE * RES);
	map_y_want /= RES;
	map_x = data->player.pdx / (float)RES;
	if (data->parse.map[map_y_want][map_x] == 2)
		return (0);
	map_x = data->player.pdx / (float)RES + SLIDE_DISTANCE;
	if (data->parse.map[map_y_want][map_x] == 2)
		return (0);
	map_x = data->player.pdx / (float)RES - SLIDE_DISTANCE;
	if (data->parse.map[map_y_want][map_x] == 2)
		return (0);
	return (y_want);
}
