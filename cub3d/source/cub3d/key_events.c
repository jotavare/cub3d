/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:08:02 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 02:13:40 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Handle key press events for player movement and game actions.
 *
 * @param keysym An integer representing the key symbol of the pressed key.
 * @param cub3d A pointer to the structure.
 * @return [0] Successful key event handling.
 */
int	handle_keydown(int keysym, t_cub3d *cub3d)
{
	if (keysym == XK_Escape)
		cub3d->exit = 1;
	if (keysym == XK_w)
		cub3d->player.move_forward = 1;
	if (keysym == XK_s)
		cub3d->player.move_backward = 1;
	if (keysym == XK_a)
		cub3d->player.move_left = 1;
	if (keysym == XK_d)
		cub3d->player.move_right = 1;
	if (keysym == XK_Left)
		cub3d->player.move_pa_left = 1;
	if (keysym == XK_Right)
		cub3d->player.move_pa_right = 1;
	return (0);
}

/**
 * Handle key release events and stops corresponding player movements.
 *
 * @param keysym An integer representing the key symbol of the released key.
 * @param cub3d A pointer to the structure.
 * @return [0] Sucessful key event handling.
 */
int	handle_keyup(int keysym, t_cub3d *cub3d)
{
	if (keysym == XK_w)
		cub3d->player.move_forward = 0;
	if (keysym == XK_s)
		cub3d->player.move_backward = 0;
	if (keysym == XK_a)
		cub3d->player.move_left = 0;
	if (keysym == XK_d)
		cub3d->player.move_right = 0;
	if (keysym == XK_Left)
		cub3d->player.move_pa_left = 0;
	if (keysym == XK_Right)
		cub3d->player.move_pa_right = 0;
	return (0);
}

/**
 * Handle the event when the window is closed or killed, setting the exit flag.
 *
 * @param cub3d A pointer to the structure.
 * @return [0] Successful handling of the window close event.
 */
int	handle_window_kill(t_cub3d *cub3d)
{
	cub3d->exit = 1;
	return (0);
}
