/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#              */
/*   Created: 2023/11/02 00:07:56 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 02:08:03 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Print an error message to the standard error output.
 *
 * @param str The error message to be printed.
 */
void	display_error(char *str)
{
	printf("Error\n");
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

/**
 * Initialize the MLX library, create the game window and image frame.
 *
 * @param cub3d A pointer to the structure.
 * @return [0] Successful initialization [1] Failure.
 */
int	inicialize_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (cub3d->mlx == NULL)
		return (1);
	cub3d->window = mlx_new_window(cub3d->mlx, WIN_W, WIN_H, "cub3d");
	if (cub3d->window == NULL)
		return (free(cub3d->mlx), 1);
	cub3d->frame.mlx_img = mlx_new_image(cub3d->mlx, WIN_W, WIN_H);
	if (cub3d->frame.mlx_img == NULL)
	{
		mlx_destroy_window(cub3d->mlx, cub3d->window);
		mlx_destroy_display(cub3d->mlx);
		return (free(cub3d->mlx), 1);
	}
	cub3d->frame.addr = mlx_get_data_addr(cub3d->frame.mlx_img,
			&(cub3d->frame.bpp), &(cub3d->frame.line_len),
			&(cub3d->frame.endian));
	if (cub3d->frame.addr == NULL)
	{
		mlx_destroy_window(cub3d->mlx, cub3d->window);
		mlx_destroy_image(cub3d->mlx, cub3d->frame.mlx_img);
		mlx_destroy_display(cub3d->mlx);
		return (free(cub3d->mlx), 1);
	}
	return (0);
}

/**
 * Destroy the MLX window and free associated resources.
 *
 * @param cub3d The structure.
 */
void	destroy_mlx(t_cub3d cub3d)
{
	mlx_destroy_window(cub3d.mlx, cub3d.window);
	mlx_destroy_image(cub3d.mlx, cub3d.frame.mlx_img);
	if (cub3d.n_tex.frame.mlx_img)
		mlx_destroy_image(cub3d.mlx, cub3d.n_tex.frame.mlx_img);
	if (cub3d.s_tex.frame.mlx_img)
		mlx_destroy_image(cub3d.mlx, cub3d.s_tex.frame.mlx_img);
	if (cub3d.w_tex.frame.mlx_img)
		mlx_destroy_image(cub3d.mlx, cub3d.w_tex.frame.mlx_img);
	if (cub3d.e_tex.frame.mlx_img)
		mlx_destroy_image(cub3d.mlx, cub3d.e_tex.frame.mlx_img);
	mlx_destroy_display(cub3d.mlx);
	free(cub3d.mlx);
}

/**
 * Get the minimum of two floating-point numbers.
 *
 * @param a The first floating-point number.
 * @param b The second floating-point number.
 * @return The smaller of the two numbers.
 */
float	min_float(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}
