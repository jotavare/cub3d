/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:08:00 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/03 02:37:01 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Main function of the Cub3D game.
 * Initialize the main game structure and the MLX library.
 * Parse the .cub file, load textures, and initialize the player.
 * Set event hooks and start the game loop.
 * Free resources and handle memory allocation errors.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return [0] Successful game execution [!= 0] Error code on failure.
 */
int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
	{
		printf("Error\n");
		printf("Invalid number of arguments.\n");
		return (0);
	}
	ft_bzero(&cub3d, sizeof(t_cub3d));
	if (inicialize_mlx(&cub3d) != 0)
		return (display_error("MLX error."), 2);
	if (read_parse_file(argv[1], &cub3d.parse) != 0)
		return (display_parsing_error(cub3d.parse.parse_errno),
			cub3d_free(&cub3d), 3);
	if (initialize_texture_loading(&cub3d) != 0)
		return (display_error("Invalid textures."), cub3d_free(&cub3d), 4);
	initialize_player(&cub3d);
	set_hooks(&cub3d);
	mlx_loop(cub3d.mlx);
	cub3d_free(&cub3d);
	if (cub3d.alloc_err)
		return (display_error("Memory allocation error."), 1);
	return (0);
}

/**
 * Frees resources and deallocates memory for the Cub3D game.
 *
 * @param cub3d A pointer to the structure.
 */
void	cub3d_free(t_cub3d *cub3d)
{
	free_parsing_data(&cub3d->parse);
	destroy_mlx(*cub3d);
}

/**
 * Game loop function that handles rendering, player movement, and events.
 * Perform raycasting and rendering of the 3D world.
 * Check if the game should exit and end the MLX loop.
 *
 * @param cub3d A pointer to the structure.
 * @return [0] Successful execution [!= 0] Error code on failure.
 */
int	cub3d_loop(t_cub3d *cub3d)
{
	clear_frame(cub3d->frame);
	cub3d->ray_list = 0;
	render_ceiling_floor(cub3d);
	if (pew_pew_rays(cub3d) != 0)
	{
		cub3d->alloc_err = 1;
		return (mlx_loop_end(cub3d->mlx), 1);
	}
	render_3d_world(cub3d);
	update_player_pos(cub3d);
	display_minimap(cub3d);
	put_frame_to_window(cub3d);
	if (cub3d->ray_list)
		free(cub3d->ray_list);
	if (cub3d->exit)
		mlx_loop_end(cub3d->mlx);
	return (0);
}

/**
 * Sets event hooks, including keyboard and window close events.
 *
 * @param cub3d A pointer to the structure.
 */
void	set_hooks(t_cub3d *cub3d)
{
	cub3d->exit = 0;
	mlx_loop_hook(cub3d->mlx, &cub3d_loop, cub3d);
	mlx_hook(cub3d->window, KeyRelease, KeyReleaseMask, &handle_keyup, cub3d);
	mlx_hook(cub3d->window, KeyPress, KeyPressMask, &handle_keydown, cub3d);
	mlx_hook(cub3d->window, DestroyNotify, NoEventMask, &handle_window_kill,
		cub3d);
}
