#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480

t_data *data;

int	worldMap[24][24] = {
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	verLine(int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

void	calc()
{
	int	x;

	x = 0;
	while (x < width)
	{
		double cameraX = 2 * x / (double)width - 1;
		double rayDirX = data->dirX + data->planeX * cameraX;
		double rayDirY = data->dirY + data->planeY * cameraX;

		int mapX = (int)data->posX;
		int mapY = (int)data->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
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
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - data->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - data->posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)
			drawEnd = height - 1;

		int	color;
		if (worldMap[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;

		if (side == 1)
			color = color / 2;

		verLine(x, drawStart, drawEnd, color);

		x++;
	}
}

int	key_press(int key)
{
	if (key == K_W)
	{
		mlx_destroy_image(data->mlx, data->image);
		if (!worldMap[(int)(data->posX + data->dirX * data->moveSpeed)][(int)(data->posY)])
			data->posX += data->dirX * data->moveSpeed;
		if (!worldMap[(int)(data->posX)][(int)(data->posY + data->dirY * data->moveSpeed)])
			data->posY += data->dirY * data->moveSpeed;
		data->image = mlx_new_image(data->mlx, width, height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		mlx_destroy_image(data->mlx, data->image);
		if (!worldMap[(int)(data->posX - data->dirX * data->moveSpeed)][(int)(data->posY)])
			data->posX -= data->dirX * data->moveSpeed;
		if (!worldMap[(int)(data->posX)][(int)(data->posY - data->dirY * data->moveSpeed)])
			data->posY -= data->dirY * data->moveSpeed;
		data->image = mlx_new_image(data->mlx, width, height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	//rotate to the right
	if (key == K_D)
	{
		mlx_destroy_image(data->mlx, data->image);
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-data->rotSpeed) - data->dirY * sin(-data->rotSpeed);
		data->dirY = oldDirX * sin(-data->rotSpeed) + data->dirY * cos(-data->rotSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(-data->rotSpeed) - data->planeY * sin(-data->rotSpeed);
		data->planeY = oldPlaneX * sin(-data->rotSpeed) + data->planeY * cos(-data->rotSpeed);
		data->image = mlx_new_image(data->mlx, width, height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	//rotate to the left
	if (key == K_A)
	{
		mlx_destroy_image(data->mlx, data->image);
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY * sin(data->rotSpeed);
		data->dirY = oldDirX * sin(data->rotSpeed) + data->dirY * cos(data->rotSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY * sin(data->rotSpeed);
		data->planeY = oldPlaneX * sin(data->rotSpeed) + data->planeY * cos(data->rotSpeed);
		data->image = mlx_new_image(data->mlx, width, height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}

int	main(void)
{
	data = malloc(sizeof(t_data));
	data->mlx = mlx_init();

	data->posX = 12;
	data->posY = 5;
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->moveSpeed = 0.05;
	data->rotSpeed = 0.05;

	data->image = mlx_new_image(data->mlx, width, height);
	data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
	data->win = mlx_new_window(data->mlx, width, height, "mlx");
	calc();
	mlx_hook(data->win, X_EVENT_KEY_PRESS, 0, &key_press, &data);
	mlx_loop(data->mlx);
}