/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_populate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:25 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/03 01:16:41 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Assigns values to an array representing a row in the map based
 * on characters from a provided line, effectively translating
 * characters into map elements.
 *
 * @param row - An array representing a row in the map.
 * @param line - The line containing characters representing the map row.
 */
void	fill_map_row(int *row, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			row[i] = 0;
		else if (line[i] == '0')
			row[i] = 1;
		else if (line[i] == '1')
			row[i] = 2;
		else if (line[i] == 'N')
			row[i] = 3;
		else if (line[i] == 'S')
			row[i] = 4;
		else if (line[i] == 'E')
			row[i] = 5;
		else if (line[i] == 'W')
			row[i] = 6;
		else
			row[i] = -1;
		i++;
	}
}

/**
 * Reads the map data from a file and populates the map array
 * in the structure.
 *
 * @param file - The name of the file containing the map data.
 * @param parse_data - A pointer to the structure for storing the map.
 * @return [0] Map is successfully read. [1] Error opening the file.
 */
int	read_populate_map_file(char *file, t_parse_data *parse_data)
{
	int		fd;
	char	*line;
	int		map_started;
	int		row;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	map_started = 0;
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
			map_started = line_data_check(line);
		if (map_started && !line_data_check(line))
			return (free(line), close(fd), 0);
		if (map_started)
			fill_map_row(parse_data->map[row++], line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}
