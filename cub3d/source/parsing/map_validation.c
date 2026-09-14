/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:31:52 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/03 01:16:44 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Checks if the map contains any invalid blocks, i.e., blocks with value -1.
 *
 * @param parse_data - A pointer to the structure containing the map data.
 * @return [1] No invalid blocks found. [0] Invalid blocks found.
 */
int	invalid_blocks_found(t_parse_data *parse_data)
{
	int	**map;
	int	i;

	map = parse_data->map;
	while (*map)
	{
		i = -1;
		while (++i < parse_data->map_w)
			if (map[0][i] == -1)
				return (1);
		map++;
	}
	return (0);
}

/**
 * Checks if empty spaces in the map are enclosed by walls.
 *
 * @param parse_data - A pointer to the structure containing the map data.
 * @param x - The x-coordinate of the empty space.
 * @param y - The y-coordinate of the empty space.
 * @return [1] Empty space is enclosed. [0] Empty space is not enclosed.
 */
int	verify_enclosed_space(t_parse_data *parse_data, int x, int y)
{
	int	**map;

	if (x <= 0 || y <= 0 || x >= parse_data->map_w - 1 || y >= parse_data->map_h
		- 1)
		return (0);
	map = parse_data->map;
	if (!map[y - 1][x] || !map[y + 1][x] || !map[y][x - 1] || !map[y][x + 1])
		return (0);
	return (1);
}

/**
 * Checks if the map contains holes (empty spaces) enclosed by walls.
 *
 * @param parse_data - A pointer to the structure containing the map data.
 * @return [1] No holes. [0] Holes are found.
 */
int	check_map_holes(t_parse_data *parse_data)
{
	int	**map;
	int	x;
	int	y;

	y = -1;
	map = parse_data->map;
	while (map[++y])
	{
		x = -1;
		while (++x < parse_data->map_w)
			if ((map[y][x] == 1 || (map[y][x] >= 3 && map[y][x] <= 6))
				&& !verify_enclosed_space(parse_data, x, y))
				return (1);
	}
	return (0);
}

/**
 * Counts the number of spawn points in the map.
 *
 * @param parse_data - A pointer to the structure containing the map data.
 * @return The number of spawn points found in the map.
 */
int	count_spawn_points(t_parse_data *parse_data)
{
	int	**map;
	int	x;
	int	y;
	int	count;

	count = 0;
	y = -1;
	map = parse_data->map;
	while (map[++y])
	{
		x = -1;
		while (++x < parse_data->map_w)
			if (map[y][x] >= 3 && map[y][x] <= 6)
				count++;
	}
	return (count);
}

/**
 * Checks if the map is valid by verifying it against several
 * criteria, including the absence of invalid blocks, the
 * presence of a single spawn point, and the absence of holes.
 *
 * @param parse_data - A pointer to the structure containing the map data.
 * @return [1] Map is valid. [0] Map is invalid.
 */
int	validate_game_map(t_parse_data *parse_data)
{
	int	count;

	if (invalid_blocks_found(parse_data))
		return (assign_error_code(parse_data, 9), 0);
	count = count_spawn_points(parse_data);
	if (count == 0)
		return (assign_error_code(parse_data, 11), 0);
	if (count > 1)
		return (assign_error_code(parse_data, 12), 0);
	if (check_map_holes(parse_data))
		return (assign_error_code(parse_data, 10), 0);
	return (1);
}
