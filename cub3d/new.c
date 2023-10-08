#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

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

void draw_line(int x, int drawStart, int drawEnd, int color)
{
    for (int y = drawStart; y <= drawEnd; y++)
        mlx_pixel_put(vars.mlx, vars.win, x, y, color);
}

void draw_frame()
{
    for (int x = 0; x < screenWidth; x++)
    {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = player.dirX + player.planeX * cameraX;
        double rayDirY = player.dirY + player.planeY * cameraX;

        int mapX = (int)player.posX;
        int mapY = (int)player.posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

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

        // Assign colors based on the wall type in your map.
        switch (map.worldMap[mapX][mapY])
        {
            case 1:  color = 0xFF0000; break; // Red
            case 2:  color = 0x00FF00; break; // Green
            case 3:  color = 0x0000FF; break; // Blue
            case 4:  color = 0xFFFFFF; break; // White
            default: color = 0xFFFF00; break; // Yellow
        }

        if (side == 1)
            color = color / 2;

        draw_line(x, drawStart, drawEnd, color);
    }
}

int key_pressed(int keycode)
{
    return (keycode == 53 || keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126);
}

int update_player_position()
{
    if (key_pressed(53)) // ESC key
        exit(0);

    if (key_pressed(123)) // Left arrow key
    {
        double oldDirX = player.dirX;
        player.dirX = player.dirX * cos(player.rotSpeed) - player.dirY * sin(player.rotSpeed);
        player.dirY = oldDirX * sin(player.rotSpeed) + player.dirY * cos(player.rotSpeed);
        double oldPlaneX = player.planeX;
        player.planeX = player.planeX * cos(player.rotSpeed) - player.planeY * sin(player.rotSpeed);
        player.planeY = oldPlaneX * sin(player.rotSpeed) + player.planeY * cos(player.rotSpeed);
    }

    if (key_pressed(124)) // Right arrow key
    {
        double oldDirX = player.dirX;
        player.dirX = player.dirX * cos(-player.rotSpeed) - player.dirY * sin(-player.rotSpeed);
        player.dirY = oldDirX * sin(-player.rotSpeed) + player.dirY * cos(-player.rotSpeed);
        double oldPlaneX = player.planeX;
        player.planeX = player.planeX * cos(-player.rotSpeed) - player.planeY * sin(-player.rotSpeed);
        player.planeY = oldPlaneX * sin(-player.rotSpeed) + player.planeY * cos(-player.rotSpeed);
    }

    if (key_pressed(125)) // Down arrow key
    {
        if (map.worldMap[(int)(player.posX - player.dirX * player.moveSpeed)][(int)(player.posY)] == 0)
            player.posX -= player.dirX * player.moveSpeed;

        if (map.worldMap[(int)(player.posX)][(int)(player.posY - player.dirY * player.moveSpeed)] == 0)
            player.posY -= player.dirY * player.moveSpeed;
    }

    if (key_pressed(126)) // Up arrow key
    {
        if (map.worldMap[(int)(player.posX + player.dirX * player.moveSpeed)][(int)(player.posY)] == 0)
            player.posX += player.dirX * player.moveSpeed;

        if (map.worldMap[(int)(player.posX)][(int)(player.posY + player.dirY * player.moveSpeed)] == 0)
            player.posY += player.dirY * player.moveSpeed;
    }
	return (0);
}

int close_window()
{
	exit(0);
}

int main(void)
{
    player.posX = 22;
    player.posY = 12;
    player.dirX = -1;
    player.dirY = 0;
    player.planeX = 0;
    player.planeY = 0.66;
    player.moveSpeed = 0.05;
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
    mlx_hook(vars.win, 17, 1L<<17, close_window, NULL);

    draw_frame();
    mlx_loop(vars.mlx);
    return (0);
}