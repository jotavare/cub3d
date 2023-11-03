/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:48 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/03 01:17:31 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Loads the texture data for each of the cardinal direction textures
 * (North, South, West, East).
 * Also extracts relevant information like address, bits per pixel,
 * line length, and endian for each texture's frame.
 *
 * @param cub3d - A pointer to the main CUB3D structure.
 */
void	initialize_texture_data(t_cub3d *cub3d)
{
	cub3d->n_tex.frame.addr = mlx_get_data_addr(cub3d->n_tex.frame.mlx_img,
			&(cub3d->n_tex.frame.bpp), &(cub3d->n_tex.frame.line_len),
			&(cub3d->n_tex.frame.endian));
	cub3d->s_tex.frame.addr = mlx_get_data_addr(cub3d->s_tex.frame.mlx_img,
			&(cub3d->s_tex.frame.bpp), &(cub3d->s_tex.frame.line_len),
			&(cub3d->s_tex.frame.endian));
	cub3d->w_tex.frame.addr = mlx_get_data_addr(cub3d->w_tex.frame.mlx_img,
			&(cub3d->w_tex.frame.bpp), &(cub3d->w_tex.frame.line_len),
			&(cub3d->w_tex.frame.endian));
	cub3d->e_tex.frame.addr = mlx_get_data_addr(cub3d->e_tex.frame.mlx_img,
			&(cub3d->e_tex.frame.bpp), &(cub3d->e_tex.frame.line_len),
			&(cub3d->e_tex.frame.endian));
}

/**
 * Loads the textures from image files (XPM files) for
 * North, South, West, and East directions.
 * If successful, it calls initialize_texture_data to extract texture data.
 *
 * @param cub3d - A pointer to the structure.
 * @return [0] Textures are successfully loaded [1] Texture loading fails.
 */
int	initialize_texture_loading(t_cub3d *cub3d)
{
	cub3d->n_tex.frame.mlx_img = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->parse.no, &cub3d->n_tex.width, &cub3d->n_tex.height);
	cub3d->s_tex.frame.mlx_img = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->parse.so, &cub3d->s_tex.width, &cub3d->s_tex.height);
	cub3d->w_tex.frame.mlx_img = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->parse.we, &cub3d->w_tex.width, &cub3d->w_tex.height);
	cub3d->e_tex.frame.mlx_img = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->parse.ea, &cub3d->e_tex.width, &cub3d->e_tex.height);
	if (!cub3d->n_tex.frame.mlx_img || !cub3d->s_tex.frame.mlx_img
		|| !cub3d->w_tex.frame.mlx_img || !cub3d->e_tex.frame.mlx_img)
		return (1);
	initialize_texture_data(cub3d);
	return (0);
}

/**
 * Retrieves the color of a pixel at the specified position (p)
 * from a given texture.
 * It uses the address and information obtained from the texture
 * frame to access the pixel's color.
 *
 * @param texture - The texture from which to retrieve the pixel color.
 * @param p - The position (x, y) of the pixel to be retrieved.
 * @return The color value of the specified pixel.
 */
inline int	retrieve_texture_pixel(t_texture texture, t_pixel_pos p)
{
	return (*(int *)(texture.frame.addr + 4 * (p.x + p.y * texture.width)));
}
