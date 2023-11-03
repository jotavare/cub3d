/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:31 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/03 01:25:08 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Fill the structure with data extracted from a line, handling texture
 * and color data.
 *
 * @param file - The name of the file containing the data.
 * @param parse_data - A pointer to the structure for storing the parsed data.
 * @return [0] Data is read and parsed. [1] Error opening/parsing the file.
 */
int	process_data_file_line(char *file, t_parse_data *parse_data)
{
	int		fd;
	char	*line;
	char	*trimmed_line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		trimmed_line = ft_strtrim(line, " \n");
		if (!trimmed_line)
			return (free(line), close(fd), 1);
		if (process_parsed_data_line(trimmed_line, parse_data) != 0)
			return (free(trimmed_line), free(line), close(fd), 1);
		free(trimmed_line);
		free(line);
		line = get_next_line(fd);
	}
	if (data_missing(parse_data))
		return (assign_error_code(parse_data, 4), close(fd), 1);
	return (close(fd), 0);
}

/**
 * Fill the structure with color data from a split line.
 *
 * @param line_split - The split line containing the color data.
 * @param parse_data - A pointer to the structure for storing the color info.
 * @return [0] Color data is filled [1] Error in the color format/data.
 */
int	read_color_split_line(char **line_split, t_parse_data *parse_data)
{
	char	**color_split;

	color_split = ft_split(line_split[1], ',');
	if (!color_split)
		return (1);
	if (!color_split[0] || !color_split[1] || !color_split[2] || color_split[3]
		|| !valid_color(color_split))
		return (ft_split_free(color_split), assign_error_code(parse_data, 7),
			1);
	if (!ft_strncmp(line_split[0], "F", 1))
	{
		parse_data->fc = (ft_atoi(color_split[0]) << 16)
			+ (ft_atoi(color_split[1]) << 8) + (ft_atoi(color_split[2]));
		parse_data->fc_set = 1;
	}
	if (!ft_strncmp(line_split[0], "C", 1))
	{
		parse_data->cc = (ft_atoi(color_split[0]) << 16)
			+ (ft_atoi(color_split[1]) << 8) + (ft_atoi(color_split[2]));
		parse_data->cc_set = 1;
	}
	if (line_split[2])
		return (assign_error_code(parse_data, 6), ft_split_free(color_split),
			1);
	return (ft_split_free(color_split), 0);
}

/**
 * Fill the structure with texture data from a split line.
 *
 * @param line_split - The split line containing the texture data.
 * @param parse_data - A pointer to the structure for storing the texture info.
 * @return [0] Texture data is filled. [1] Error in the texture format/data.
 */
int	read_text_split_line(char **line_split, t_parse_data *parse_data)
{
	if (!ft_strncmp(line_split[0], "NO ", 2))
		parse_data->no = ft_strdup(line_split[1]);
	if (!ft_strncmp(line_split[0], "SO ", 2))
		parse_data->so = ft_strdup(line_split[1]);
	if (!ft_strncmp(line_split[0], "WE ", 2))
		parse_data->we = ft_strdup(line_split[1]);
	if (!ft_strncmp(line_split[0], "EA ", 2))
		parse_data->ea = ft_strdup(line_split[1]);
	if (line_split[2])
		return (assign_error_code(parse_data, 6), 1);
	return (0);
}

/**
 * Check if a line is a duplicate of previously parsed data.
 *
 * @param line - The line to check for duplication.
 * @param parse_data - A pointer to the structure containing
 * previously parsed data.
 * @return [1] Line is a duplicate. [0] Otherwise.
 */
int	check_duplicate_line(char *line, t_parse_data *parse_data)
{
	if (!ft_strncmp(line, "NO ", 3) && parse_data->no)
		return (1);
	if (!ft_strncmp(line, "SO ", 3) && parse_data->so)
		return (1);
	if (!ft_strncmp(line, "WE ", 3) && parse_data->we)
		return (1);
	if (!ft_strncmp(line, "EA ", 3) && parse_data->ea)
		return (1);
	if (!ft_strncmp(line, "F ", 2) && parse_data->fc_set)
		return (1);
	if (!ft_strncmp(line, "C ", 2) && parse_data->cc_set)
		return (1);
	return (0);
}

/**
 * Fills the structure with data extracted from a line.
 *
 * @param line - The line to extract data from.
 * @param parse_data - A pointer to the structure for storing the parsed data.
 * @return [0] Data is successfully extracted. [1] Error in the format or data.
 */
int	process_parsed_data_line(char *line, t_parse_data *parse_data)
{
	char	**line_split;

	if (check_duplicate_line(line, parse_data))
		return (assign_error_code(parse_data, 5), 1);
	line_split = ft_split(line, ' ');
	if (!line_split)
		return (1);
	if (!line_split[0] || !line_split[1])
		return (ft_split_free(line_split), 0);
	if (valid_texture_line(line))
		if (read_text_split_line(line_split, parse_data) != 0)
			return (ft_split_free(line_split), 1);
	if (valid_color_line(line))
		if (read_color_split_line(line_split, parse_data) != 0)
			return (ft_split_free(line_split), 1);
	return (ft_split_free(line_split), 0);
}
