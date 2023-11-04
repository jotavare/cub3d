/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_inicialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:04:34 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 17:54:41 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Frees memory for the 2D integer array representing the game map.
 *
 * @param map A pointer to the 2D integer array.
 */
void	free_2d_map(int **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/**
 * Allocates memory for the game map (initializes with zeros).
 * The dimensions are specified in parse_data struct.
 *
 * @param parse_data A pointer to the structure.
 * @return [0] Map allocation successful [1] Failure.
 */
int	initialize_map(t_parse_data *parse_data)
{
	int	i;

	parse_data->map = malloc(sizeof(int *) * (parse_data->map_h + 1));
	if (!parse_data->map)
		return (1);
	i = 0;
	while (i < parse_data->map_h)
	{
		parse_data->map[i] = malloc(sizeof(int) * parse_data->map_w);
		if (!parse_data->map[i])
			return (free_2d_map(parse_data->map), 1);
		ft_bzero((void *)parse_data->map[i], sizeof(int) * parse_data->map_w);
		i++;
	}
	parse_data->map[i] = 0;
	return (0);
}

/**
 * Frees memory associated with stucture.
 * Including the game map and texture file paths.
 *
 * @param parse_data A pointer to the structure to be freed.
 */
void	free_parsing_data(t_parse_data *parse_data)
{
	free_2d_map(parse_data->map);
	if (parse_data->no)
		free(parse_data->no);
	if (parse_data->so)
		free(parse_data->so);
	if (parse_data->we)
		free(parse_data->we);
	if (parse_data->ea)
		free(parse_data->ea);
}

/**
 * Parses a .cub configuration file, extracts relevant data,
 * and populates the structure.
 *
 * @param file Name of the .cub configuration file.
 * @param parse_data A pointer to structure.
 * @return [0] Successful parsing [1] Parsing error.
 */
int	read_parse_file(char *file, t_parse_data *parse_data)
{
	ft_bzero((void *)parse_data, sizeof(t_parse_data));
	if (!valid_cub_extension(file))
		return (assign_error_code(parse_data, 2), 1);
	if (valid_file_format(file, parse_data))
		return (1);
	if (process_data_file_line(file, parse_data) != 0)
		return (1);
	if (map_dimensions_file(file, parse_data) != 0)
		return (1);
	if (initialize_map(parse_data) != 0)
		return (1);
	if (read_populate_map_file(file, parse_data) != 0)
		return (1);
	if (!validate_game_map(parse_data))
		return (1);
	return (0);
}
