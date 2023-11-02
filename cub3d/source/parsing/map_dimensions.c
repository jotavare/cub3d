/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:28 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 04:05:47 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if a character is a valid map character, which typically
 * includes numbers (0, 1) and direction indicators (N, S, E, W).
 *
 * @param c - The character to check.
 * @return [1] The character is a valid map character. [0] Otherwise.
 */
int	valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

/**
 * Calculates the length of a line until the last valid map character,
 * which is used to determine the map width.
 *
 * @param line - The line to calculate the length for.
 * @return The length of the line until the last valid map character.
 */
int	calc_map_line_length(char *line)
{
	int	i;
	int	last_i;
	int	in_map_char;

	i = 0;
	last_i = 0;
	in_map_char = 0;
	while (line[i])
	{
		if (!valid_map_char(line[i]) && in_map_char)
			last_i = i;
		in_map_char = valid_map_char(line[i]);
		i++;
	}
	return (last_i);
}

/**
 * Skips to the end of the file to avoid reading unnecessary lines,
 * ensuring efficient file processing.
 *
 * @param fd - The file descriptor to skip to the end of the file.
 */
void	end_of_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

/**
 * Reads the map size from a file and updates the map width and height in
 * the structure, ensuring the correct determination of map dimensions.
 *
 * @param file - The name of the file containing the map data.
 * @param parse_data - A pointer to the structure for storing the map size.
 * @return [0] Map size is successfully determined [1] Error opening the file.
 */
int	map_dimensions_file(char *file, t_parse_data *parse_data)
{
	int		fd;
	char	*line;
	int		map_started;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
			map_started = line_data_check(line);
		if (map_started && !line_data_check(line))
			return (free(line), end_of_file(fd), close(fd), 0);
		if (map_started)
			parse_data->map_h++;
		if (map_started && calc_map_line_length(line) > parse_data->map_w)
			parse_data->map_w = calc_map_line_length(line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}
