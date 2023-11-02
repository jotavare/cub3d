/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:33 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 03:55:52 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Trims leading and trailing spaces and newlines and checks
 * if the trimmed line is either a texture line or a color line.
 * If it's neither, it's considered valid data.
 *
 * @param line - The line to be validated.
 * @return [1] Line is valid data. [0] Otherwise.
 */

int	valid_data_line(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
		return (1);
	if (trimmed[0] && !valid_texture_line(trimmed)
		&& !valid_color_line(trimmed))
		return (free(trimmed), 0);
	return (free(trimmed), 1);
}

/**
 * Checks if a given line is empty (consists only of spaces or newlines).
 *
 * @param line - The line to be checked for emptiness.
 * @return [1] Line is empty. [0] Otherwise.
 */

int	valid_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || line[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Validates the format of the input file by checking if it contains
 * valid data lines, proper start and end of map, and empty lines
 * after the map.
 *
 * @param file - The name of the file to be validated.
 * @param parse_data - A pointer to the structure for error handling.
 * @return [0] File format is valid. [1] Error in the file format.
 */
int	valid_file_format(char *file, t_parse_data *parse_data)
{
	int		fd;
	char	*line;
	int		map_started;
	int		map_ended;

	map_started = 0;
	map_ended = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (assign_error_code(parse_data, 1), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
			map_started = line_data_check(line);
		if (!map_started && !valid_data_line(line))
			return (assign_error_code(parse_data, 3), free(line), close(fd), 3);
		if (map_started && !line_data_check(line))
			map_ended = 1;
		if (map_ended && !valid_empty_line(line))
			return (assign_error_code(parse_data, 8), free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}

/**
 * Checks whether the given filename has the ".cub" file extension.
 *
 * @param filename - The filename to be checked for the ".cub" extension.
 * @return [1] Filename has the ".cub" extension. [0] Otherwise.
 */

int	valid_cub_extension(char *filename)
{
	int	i;

	i = 0;
	while (filename[i] != '\0')
		i++;
	i--;
	if (filename[i] != 'b')
		return (0);
	i--;
	if (filename[i] != 'u')
		return (0);
	i--;
	if (filename[i] != 'c')
		return (0);
	i--;
	if (filename[i] != '.')
		return (0);
	i--;
	if (i != 0 && filename[i] != '/')
		return (1);
	return (0);
}
