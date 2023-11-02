/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:07 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 03:20:03 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Check if mandatory data fields in the .cub file are missing.
 *
 * @param parse_data - A pointer to the structure.
 * @return [1] Mandatory data fields are missing [0] Otherwise.
 */

int	data_missing(t_parse_data *parse_data)
{
	return (!(parse_data->no && parse_data->so && parse_data->we
			&& parse_data->ea && parse_data->cc_set && parse_data->fc_set));
}

/**
 * Check if a line in the .cub file is a valid texture specification line.
 *
 * @param line - The line to be checked.
 * @return [1] Line starts with "NO ", "SO ", "WE ", or "EA " [0] Otherwise.
 */

int	valid_texture_line(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

/**
 * Checks if a line in the .cub file is a valid color specification line.
 *
 * @param line - The line to be checked.
 * @return [1] Line starts with "F " or "C " [0] otherwise.
 */

int	valid_color_line(char *line)
{
	return (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2));
}

/**
 * Validate an RGB color specified as an array of strings.
 *
 * @param split - An array of strings representing color (R, G, and B).
 * @return [1] Color is a valid RGB color (between 0 and 255) [0] Otherwise.
 */

int	valid_color(char **split)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	while (j < 3)
	{
		str = split[j];
		i = -1;
		while (str[++i])
			if (!ft_isdigit(str[i]))
				return (0);
		i = ft_atoi(str);
		if (i > 255 || i < 0)
			return (0);
		j++;
	}
	return (1);
}
