/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:26:53 by mismene           #+#    #+#             */
/*   Updated: 2021/02/15 16:26:54 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers//mlx.h"
#include "cub3d.h"

t_data		*data;
t_texture	*texture_north;
t_texture	*texture_south;
t_texture	*texture_west;
t_texture	*texture_east;
t_texture	*texture_sprite;

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (str1 == NULL || str2 == NULL)
		return (1);
	while (*(str1 + i) && *(str1 + i) == *(str2 + i) && i < n - 1)
		i++;
	if (n)
		return (*(str1 + i) - *(str2 + i));
	return (0);
}

void	calc()
{
	data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
	double zBuffer[config->s_width];
	int	x;

	x = 0;
	while (x < config->s_width)
	{
		double cameraX = 2 * x / (double)config->s_width - 1;
		double rayDirX = data->dirX + data->planeX * cameraX;
		double rayDirY = data->dirY + data->planeY * cameraX;
		int mapX = (int)data->posX;
		int mapY = (int)data->posY;
		double sideDistX;
		double sideDistY;
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;
		int hit = 0;
		/*
		** if ray direction < 0 - sideDistX (length from current player position to first x-crossing) will be the ray to left side
		** else from current to right
		*/
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
		while (!hit)
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
			if (config->map[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - data->posX + (double)(1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - data->posY + (double)(1 - stepY) / 2) / rayDirY;
		zBuffer[x] = perpWallDist;
		int lineHeight = (int)(config->s_height / perpWallDist);
		draw_start = -lineHeight / 2 + config->s_height / 2;
		if(draw_start < 0)
			draw_start = 0;
		draw_end = lineHeight / 2 + config->s_height / 2;
		if(draw_end >= config->s_height)
			draw_end = config->s_height - 1;
		double wallX;
		if (side == 0)
			wallX = data->posY + perpWallDist * rayDirY;
		else
			wallX = data->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;
		draw_celling(x);
		draw_floor(x);
		draw_walls(lineHeight,texX, x);
		x++;
	}
	draw_srpites(zBuffer);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

void	get_textures()
{
	int g_width;
	int g_height;

	if (!(texture_north = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(texture_south = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(texture_west = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(texture_east = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(texture_sprite = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(texture_north->image = mlx_xpm_file_to_image(data->mlx, config->north, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_south->image = mlx_xpm_file_to_image(data->mlx, config->south, &g_width, &g_height)))
		throw_error("invalid texture path");;
	if (!(texture_west->image = mlx_xpm_file_to_image(data->mlx, config->west, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_east->image = mlx_xpm_file_to_image(data->mlx, config->east, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_sprite->image = mlx_xpm_file_to_image(data->mlx, config->sprite, &g_width, &g_height)))
		throw_error("invalid sprite path");
	texture_north->address = (int *)mlx_get_data_addr(texture_north->image, &texture_north->bpp, &texture_north->size, &texture_north->endian);
	texture_south->address = (int *)mlx_get_data_addr(texture_south->image, &texture_south->bpp, &texture_south->size, &texture_south->endian);
	texture_west->address = (int *)mlx_get_data_addr(texture_west->image, &texture_west->bpp, &texture_west->size, &texture_west->endian);
	texture_east->address = (int *)mlx_get_data_addr(texture_east->image, &texture_east->bpp, &texture_east->size, &texture_east->endian);
	texture_sprite->address = (int *)mlx_get_data_addr(texture_sprite->image, &texture_sprite->bpp, &texture_sprite->size, &texture_sprite->endian);
}

int	close_window(t_data *data)
{
	exit(0);
	return 0;
}

void	scale_reso()
{
	int		mlx_size_x;
	int		mlx_size_y;

	mlx_get_screen_size(data->mlx, &mlx_size_x, &mlx_size_y);
	config->s_width = mlx_size_x;
	config->s_height = mlx_size_y;
}

void	is_screen_size_correct()
{
	int		mlx_size_x;
	int		mlx_size_y;

	if (config->s_width < 20 || config->s_height < 20)
		throw_error("the window size is too small");
	mlx_get_screen_size(data->mlx, &mlx_size_x, &mlx_size_y);
	if (config->s_width > mlx_size_x || config->s_height > mlx_size_y)
		scale_reso();
}

void	spawn_direction()
{
	if (config->player == 'W')
	{
		for (int i = 0; i < 47; ++i) {
			turn_right();
		}

	} else if (config->player == 'S')
	{
		for (int i = 0; i < 32; ++i) {
			turn_right();
		}
	} else if (config->player == 'E')
	{
		for (int i = 0; i < 16; ++i) {
			turn_right();
		}
	}
}

void	data_ini()
{
	data->mlx = mlx_init();
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->moveSpeed = 0.1;
	data->rotSpeed = 0.1;
}

int	main(int argc, char **argv)
{
	if (!(data = malloc(sizeof(t_data))))
		throw_error("no memory");
	if (!(sprites = malloc(sizeof(t_sprites))))
		throw_error("no memory");
	sprites->count = 0;
	if (argc < 2)
		throw_error("put second argument");
	else
		parse_config_file(argv[1]);
	if (argc > 3)
		throw_error("too many arguments");
	if (!(ft_strncmp(argv[2], "--save", 6)) && ft_strlen(argv[2]) == 6)
	{
		screenshot();
		exit(0);
	}
	else if ((ft_strncmp(argv[2], "--save", 6) || ft_strlen(argv[2]) != 6) && argc == 3)
		throw_error("unexpected second argument, need --save");
	data_ini();
	spawn_direction();
	data->win = mlx_new_window(data->mlx, config->s_width, config->s_height, "mlx");
	is_screen_size_correct();
	get_textures();
	calc();
	mlx_hook(data->win, 2, 1L<<0, &movings, &data);
	mlx_hook(data->win, 17, 1L<<0, &close_window, &data);
	mlx_loop(data->mlx);
}
