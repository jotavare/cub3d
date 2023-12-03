#include "../headers/cub3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

//place the example code below here:s

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

typedef struct s_vars {
    void    *mlx;
    void    *win;
}   t_vars;

typedef struct s_player {
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    double moveSpeed;
    double rotSpeed;
}   t_player;

typedef struct s_map {
    int worldMap[mapWidth][mapHeight];
}   t_map;

t_player player;
t_vars vars;
t_map map;

//ft_strdup
char	*ft_strdup(const char *s1)
{
    char	*str;
    int		i;

    i = 0;
    while (s1[i])
        i++;
    str = (char *)malloc(sizeof(char) * (i + 1));
    if (!str)
        return (0);
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

//ft_itoa
char	*ft_itoa(int n)
{
    char	*str;
    int		len;
    long	nbr;

    nbr = n;
    len = 0;
    if (nbr == 0)
        return (ft_strdup("0"));
    if (nbr < 0)
    {
        nbr = -nbr;
        len++;
    }
    while (n != 0)
    {
        n = n / 10;
        len++;
    }
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (0);
    str[len] = '\0';
    while (nbr != 0)
    {
        str[--len] = nbr % 10 + '0';
        nbr = nbr / 10;
    }
    if (len == 1)
        str[0] = '-';
    return (str);
}

void draw_line(int x, int drawStart, int drawEnd, int color)
{
    for (int y = drawStart; y <= drawEnd; y++)
        mlx_pixel_put(vars.mlx, vars.win, x, y, color);
}

void draw_frame()
{
    int x = 0;

    while (x < screenWidth)
    {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = player.dirX + player.planeX * cameraX;
        double rayDirY = player.dirY + player.planeY * cameraX;

        int mapX = (int)player.posX;
        int mapY = (int)player.posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX;
        double deltaDistY;

        if (rayDirX == 0)
            deltaDistX = 1e30;
        else
            deltaDistX = fabs(1 / rayDirX);

        if (rayDirY == 0)
            deltaDistY = 1e30;
        else
            deltaDistY = fabs(1 / rayDirY);

        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (player.posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.posX) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (player.posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.posY) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (map.worldMap[mapX][mapY] > 0)
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        int lineHeight = (int)(screenHeight / perpWallDist);

        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        int color;

        int colors[] = {0xFFFF00, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFFFF};
        int mapValue = map.worldMap[mapX][mapY];
        if (mapValue < 0 || mapValue > 4) {
            mapValue = 0;
        }
        color = colors[mapValue];

        if (side == 1)
            color = color / 2;

        draw_line(x, drawStart, drawEnd, color);
        
        x++;
    }
}

// calculate the game fps and print it on the window
void    calculate_fps()
{
    static int  fps = 0;
    static int  old_time = 0;
    static char *fps_str = NULL;
    char        *tmp;

    if (fps_str == NULL)
        fps_str = ft_itoa(fps);
    if (fps_str == NULL)
        return ;
    fps++;
    if (old_time != 0 && old_time != time(NULL))
    {
        tmp = ft_itoa(fps);
        if (tmp == NULL)
            return ;
        free(fps_str);
        fps_str = tmp;
        fps = 0;
    }
    mlx_string_put(vars.mlx, vars.win, 10, 70, 0x00FF0000, "fps");
    mlx_string_put(vars.mlx, vars.win, 70, 70, 0x00FF0000, fps_str);
    old_time = time(NULL);
}

int update_player_position(int key_pressed)
{
    mlx_clear_window(vars.mlx, vars.win);
    draw_frame();
    if (key_pressed == 53) // ESC key
        exit(0);

    if (key_pressed == 100) // Right arrow key
    {
        double oldDirX = player.dirX;
        player.dirX = player.dirX * cos(-player.rotSpeed) - player.dirY * sin(-player.rotSpeed);
        player.dirY = oldDirX * sin(-player.rotSpeed) + player.dirY * cos(-player.rotSpeed);
        double oldPlaneX = player.planeX;
        player.planeX = player.planeX * cos(-player.rotSpeed) - player.planeY * sin(-player.rotSpeed);
        player.planeY = oldPlaneX * sin(-player.rotSpeed) + player.planeY * cos(-player.rotSpeed);
    }

    if (key_pressed == 115) // Down arrow key
    {
        if (map.worldMap[(int)(player.posX - player.dirX * player.moveSpeed)][(int)(player.posY)] == 0)
            player.posX -= player.dirX * player.moveSpeed;

        if (map.worldMap[(int)(player.posX)][(int)(player.posY - player.dirY * player.moveSpeed)] == 0)
            player.posY -= player.dirY * player.moveSpeed;
    }

    if (key_pressed == 119) // Up arrow key
    {
        if (map.worldMap[(int)(player.posX + player.dirX * player.moveSpeed)][(int)(player.posY)] == 0)
            player.posX += player.dirX * player.moveSpeed;

        if (map.worldMap[(int)(player.posX)][(int)(player.posY + player.dirY * player.moveSpeed)] == 0)
            player.posY += player.dirY * player.moveSpeed;
    }
    if(key_pressed == 97) // Left arrow key
    {
        double oldDirX = player.dirX;
        player.dirX = player.dirX * cos(player.rotSpeed) - player.dirY * sin(player.rotSpeed);
        player.dirY = oldDirX * sin(player.rotSpeed) + player.dirY * cos(player.rotSpeed);
        double oldPlaneX = player.planeX;
        player.planeX = player.planeX * cos(player.rotSpeed) - player.planeY * sin(player.rotSpeed);
        player.planeY = oldPlaneX * sin(player.rotSpeed) + player.planeY * cos(player.rotSpeed);
    }

    // print on the window the player position
    mlx_string_put(vars.mlx, vars.win, 10, 10, 0x00FF0000, "posX");
    mlx_string_put(vars.mlx, vars.win, 70, 10, 0x00FF0000, ft_itoa(player.posX));
    mlx_string_put(vars.mlx, vars.win, 10, 30, 0x00FF0000, "posY");
    mlx_string_put(vars.mlx, vars.win, 70, 30, 0x00FF0000, ft_itoa(player.posY));

    // print on the window the keycode pressed
    mlx_string_put(vars.mlx, vars.win, 10, 50, 0x00FF0000, "keycode");
    mlx_string_put(vars.mlx, vars.win, 70, 50, 0x00FF0000, ft_itoa(key_pressed));

    // print on the window the ray direction
    mlx_string_put(vars.mlx, vars.win, 10, 90, 0x00FF0000, "rayDirX");
    mlx_string_put(vars.mlx, vars.win, 70, 90, 0x00FF0000, ft_itoa(player.dirX));
    printf("rayDirX: %f\n", ft_itoa(player.dirX));
    mlx_string_put(vars.mlx, vars.win, 10, 110, 0x00FF0000, "rayDirY");
    mlx_string_put(vars.mlx, vars.win, 70, 110, 0x00FF0000, ft_itoa(player.dirY));

    

    calculate_fps();
	return (0);
}

int main(void)
{
    player.posX = 22;
    player.posY = 12;
    player.dirX = -1;
    player.dirY = 0;
    player.planeX = 0;
    player.planeY = 0.66;
    player.moveSpeed = 0.20;
    player.rotSpeed = 0.05;

	int customMap[mapWidth][mapHeight]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// Copy the custom map data into the worldMap array
    for (int i = 0; i < mapWidth; i++)
    {
        for (int j = 0; j < mapHeight; j++)
        {
            map.worldMap[i][j] = customMap[i][j];
        }
    }

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Raycaster");

    mlx_hook(vars.win, 2, 1L<<0, &update_player_position, NULL);
    mlx_loop(vars.mlx);
    return (0);
}