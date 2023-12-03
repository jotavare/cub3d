#include "../headers/cub3d.h"
#include <stdio.h>
#include <math.h>

typedef struct s_data {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}               t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
    int x;
    int y;
}				t_vars;

void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_filled_circle(t_data *data, int x_center, int y_center, int radius, int color) {
    int x, y;
    for (x = -radius; x <= radius; x++) {
        for (y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                my_mlx_pixel_put(data, x_center + x, y_center + y, color);
            }
        }
    }
}

// if i click w(119) then redraw the circle at a new location
int key_hook(int keycode, t_vars *vars, t_data img)
{
	if (keycode == 119) {
		vars->y -= 10;
		draw_filled_circle(&img, vars->x, vars->y, 50, 0x00FF0000);
		mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	}
	return (0);
}

int main(void) {
    t_data img;
    t_vars vars;

    vars.x = 250;
    vars.y = 250;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1000, 1000, "Hello world!");
    img.img = mlx_new_image(vars.mlx, 1000, 1000);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
        &img.endian);
    //img.mlx = vars.mlx;
    //img.mlx_win = vars.win;

    draw_filled_circle(&img, vars.x, vars.y, 50, 0x00FF0000);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_loop(vars.mlx);
}
