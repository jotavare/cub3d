#include "headers/cub3d.h"

int	keypress(int keycode, t_vars *vars)
{
    if (keycode == A)
        vars->x -= 10;
    if (keycode == D)
        vars->x += 10;
    if (keycode == W)
        vars->y -= 10;
    if (keycode == S)
        vars->y += 10;
    if (keycode == ESC)
        exit(0);
    if (keycode)
        printf("[%d] Key pressed.\n", keycode);
	return (0);
}

int keyrelease(int keycode, t_vars *vars)
{
    if (keycode)
        printf("[%d] Key released.\n", keycode);
    return (0);
}

int destroy(int keycode, t_vars *vars)
{
    if (vars->mlx && vars->win)
	{
        mlx_clear_window(vars->mlx, vars->win);
        mlx_destroy_window(vars->mlx, vars->win);
		printf("Window destroyed.\n");
	}
    else
	{
        printf("Error: Attempted to destroy NULL mlx or win pointer.\n");
    }
    return (0);
}

int motion(int keycode, int x, int y, t_vars *vars)
{
    printf("Keycode=%d | X=%d | Y=%d\n", keycode, x, y);
    return (0);
}