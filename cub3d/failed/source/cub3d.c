#include "../headers/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

int draw_square(t_vars *vars, t_data *img)
{
    int square_size = 32; // Size of the square in pixels
    int square_color = 0x00FF0000; // Red color (You can change this)

    for (int y = vars->y; y < vars->y + square_size; y++) {
        for (int x = vars->x; x < vars->x + square_size; x++) {
            // Check if the pixel coordinates are within the image bounds
            if (x >= 0 && x < 500 && y >= 0 && y < 500) {
                my_mlx_pixel_put(img, x, y, square_color);
            }
        }
    }

    mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);

    return (0);
}


int	main(void)
{
	t_vars  vars;
	t_data	img;

    vars.mlx = NULL;
    vars.win = NULL;

    vars.x = 250;
    vars.y = 250;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

    draw_square(&vars, &img);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

    mlx_hook(vars.win, PRESS, PRESS_M, keypress, &vars);
    mlx_hook(vars.win, RELEASE, RELEASE_M, keyrelease, &vars);
    mlx_hook(vars.win, DESTROY, DESTROY_M, destroy, &vars);
    mlx_mouse_hook(vars.win, motion, &vars);
    mlx_loop_hook(vars.mlx, draw_square, &vars);
	mlx_loop(vars.mlx);
}