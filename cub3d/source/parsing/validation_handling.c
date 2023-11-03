/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:21 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/03 01:16:57 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Checks if a given line contains map content.
 *
 * @param line - The input line to check.
 * @return [1] Line contains map content [0] Otherwise.
 */
int	line_data_check(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (1);
	return (0);
}

/**
 * Sets the parsing error code in the structure.
 *
 * @param parse_data - A pointer to the structure.
 * @param n - The error code to set.
 */
void	assign_error_code(t_parse_data *parse_data, int n)
{
	parse_data->parse_errno = n;
}

/**
 * Prints a descriptive error message to stderr based on
 * the provided error code.
 *
 * @param err - The error code indicating the specific parsing error.
 */
void	display_parsing_error(int err)
{
	printf("Error\n");
	if (err == 1)
		ft_putstr_fd("Can't open file.\n", 2);
	if (err == 2)
		ft_putstr_fd("File is not a .cub file.\n", 2);
	if (err == 3)
		ft_putstr_fd("Invalid data line.\n", 2);
	if (err == 4)
		ft_putstr_fd("Missing data line.\n", 2);
	if (err == 5)
		ft_putstr_fd("Duplicate data line.\n", 2);
	if (err == 6)
		ft_putstr_fd("Trailing characters after data line.\n", 2);
	if (err == 7)
		ft_putstr_fd("Wrong color format.\n", 2);
	if (err == 8)
		ft_putstr_fd("Trailing data after map end.\n", 2);
	if (err == 9)
		ft_putstr_fd("Invalid characters in map.\n", 2);
	if (err == 10)
		ft_putstr_fd("Map is not enclosed by walls.\n", 2);
	if (err == 11)
		ft_putstr_fd("Map has no starting point.\n", 2);
	if (err == 12)
		ft_putstr_fd("Map has more than one starting point.\n", 2);
}

/**
 * Outputs the map content to the standard output, character by character.
 *
 * @param parse_data - A pointer to the structure containing
 * the parsed map data.
 */
void	output_game_map(t_parse_data *parse_data)
{
	int		**map;
	int		i;
	char	c;

	map = parse_data->map;
	while (*map)
	{
		i = -1;
		while (++i < parse_data->map_w)
		{
			c = (char)map[0][i] + '0';
			write(1, &c, 1);
		}
		map++;
		write(1, "\n", 1);
	}
	return ;
}
