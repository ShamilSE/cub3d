#include "mlx/mlx.h"
#include "key_macos.h"
#include "../headers/graphics.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define mapWidth 24
#define mapHeight 24
#define width 1280
#define height 720

t_data *data;
t_texture *texture1;
t_texture *texture2;
t_texture *texture3;
t_texture *texture4;
t_texture *texture5;

unsigned int	get_pixel(int x, int y, t_texture *t);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	verLine(int x, int y1, int y2)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		my_mlx_pixel_put(data, x, y,get_pixel(x, y, texture1));
		y++;
	}
}

void	draw_celling(int draw_start, int x_view)
{
	int		i;

	i = 0;
	while (i < draw_start)
	{
		my_mlx_pixel_put(data, x_view, i, 0xFDFDFD);
		i++;
	}
}

void	draw_floor(int draw_end, int x_view)
{
	int		i;

	i = draw_end;
	while (i < height)
	{
		my_mlx_pixel_put(data, x_view, i, 0xDFDFDF);
		i++;
	}
}

void	calc()
{
	data->image = mlx_new_image(data->mlx, width, height);
	data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
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
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
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
			if (config->map[mapX][mapY] == '1')
				hit = 1;
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
		int y = 0;
		double	wallX;
		if (side == 0)
			wallX = data->posX + perpWallDist * rayDirY;
		else
			wallX = data->posY + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		int		text_x = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			text_x = texWidth - text_x - 1;
		if (side == 1 && rayDirY < 0)
			text_x = texWidth - text_x - 1;
		double	step = 1.0 * texHeight / lineHeight;
		double	texture_position = (drawStart - (double)height / 2 + (double)lineHeight / 2) * step;
		while (y < height)
		{
			if (y >= drawStart && y <= drawEnd) {
				int text_y = (int)texture_position & (texHeight - 1);
				texture_position += step;
				my_mlx_pixel_put(data, x, y, get_pixel(text_x, text_y, texture1));
			}
			y++;
		}
			draw_celling(drawStart, x);
			draw_floor(drawEnd, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

int	key_press(int key)
{
	if (key == K_W)
	{
		mlx_destroy_image(data->mlx, data->image);
		if (config->map[(int)(data->posX + data->dirX * data->moveSpeed)][(int)(data->posY)] == '0')
			data->posX += data->dirX * data->moveSpeed;
		if (config->map[(int)(data->posX)][(int)(data->posY + data->dirY * data->moveSpeed)] == '0')
			data->posY += data->dirY * data->moveSpeed;
		data->image = mlx_new_image(data->mlx, width, height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		mlx_destroy_image(data->mlx, data->image);
		if (config->map[(int)(data->posX - data->dirX * data->moveSpeed)][(int)(data->posY)] == '0')
			data->posX -= data->dirX * data->moveSpeed;
		if (config->map[(int)(data->posX)][(int)(data->posY - data->dirY * data->moveSpeed)] == '0')
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

unsigned int	get_pixel(int x, int y, t_texture *t)
{
	char	*dst;
	unsigned int	color;

	dst = t->address + (y * t->size + x * (t->bpp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void	get_textures()
{
	int g_width;
	int g_height;

	texture1->image = mlx_xpm_file_to_image(data->mlx, config->north, &g_width, &g_height);
	texture1->address = mlx_get_data_addr(texture1->image, &texture1->bpp, &texture1->size, &texture1->endian);
	texture2->image = mlx_xpm_file_to_image(data->mlx, "wood.xpm", &g_width, &g_height);
	texture3->image = mlx_xpm_file_to_image(data->mlx, "wood.xpm", &g_width, &g_height);
	texture4->image = mlx_xpm_file_to_image(data->mlx, "wood.xpm", &g_width, &g_height);
	texture5->image = mlx_xpm_file_to_image(data->mlx, "wood.xpm", &g_width, &g_height);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		throw_error("put second argument");
	else
		parse_config_file(argv[1]);
	data = malloc(sizeof(t_data));
	texture1 = malloc(sizeof(t_texture));
	texture2 = malloc(sizeof(t_texture));
	texture3 = malloc(sizeof(t_texture));
	texture4 = malloc(sizeof(t_texture));
	texture5 = malloc(sizeof(t_texture));
	data->mlx = mlx_init();
	data->posX = 2;
	data->posY = 2;
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->moveSpeed = 0.1;
	data->rotSpeed = 0.1;
	data->win = mlx_new_window(data->mlx, width, height, "mlx");
	get_textures();
	calc();
	mlx_hook(data->win, X_EVENT_KEY_PRESS, 0, &key_press, &data);
	mlx_loop(data->mlx);
}