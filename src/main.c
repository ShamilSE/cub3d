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

#include "cub3d.h"

t_data		*data;
t_texture	*texture_north;
t_texture	*texture_south;
t_texture	*texture_west;
t_texture	*texture_east;
t_texture	*texture_sprite;
t_calc_vars	*t_calc;

void	calc()
{
	double	z_buffer[config->s_width];
	int		hit;
	int		lineHeight;
	double	wallX;

	data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
	t_calc->x = 0;
	while (t_calc->x < config->s_width)
	{
		t_calc->cameraX = 2 * t_calc->x / (double)config->s_width - 1;
		t_calc->rayDirX = data->dirX + data->planeX * t_calc->cameraX;
		t_calc->rayDirY = data->dirY + data->planeY * t_calc->cameraX;
		t_calc->mapX = (int)data->posX;
		t_calc->mapY = (int)data->posY;
		t_calc->deltaDistX = sqrt(1 + (t_calc->rayDirY * t_calc->rayDirY) / (t_calc->rayDirX * t_calc->rayDirX));
		t_calc->deltaDistY = sqrt(1 + (t_calc->rayDirX * t_calc->rayDirX) / (t_calc->rayDirY * t_calc->rayDirY));
		hit = 0;
		/*
		** if ray direction < 0 - sideDistX (length from current player position to first x-crossing) will be the ray to left side
		** else from current to right
		*/
		if (t_calc->rayDirX < 0)
		{
			t_calc->stepX = -1;
			t_calc->sideDistX = (data->posX - t_calc->mapX) * t_calc->deltaDistX;
		}
		else
		{
			t_calc->stepX = 1;
			t_calc->sideDistX = (t_calc->mapX + 1.0 - data->posX) * t_calc->deltaDistX;
		}
		if (t_calc->rayDirY < 0)
		{
			t_calc->stepY = -1;
			t_calc->sideDistY = (data->posY - t_calc->mapY) * t_calc->deltaDistY;
		}
		else
		{
			t_calc->stepY = 1;
			t_calc->sideDistY = (t_calc->mapY + 1.0 - data->posY) * t_calc->deltaDistY;
		}
		while (!hit)
		{
			if (t_calc->sideDistX < t_calc->sideDistY)
			{
				t_calc->sideDistX += t_calc->deltaDistX;
				t_calc->mapX += t_calc->stepX;
				t_calc->side = 0;
			}
			else
			{
				t_calc->sideDistY += t_calc->deltaDistY;
				t_calc->mapY += t_calc->stepY;
				t_calc->side = 1;
			}
			if (config->map[t_calc->mapX][t_calc->mapY] == '1')
				hit = 1;
		}
		if (t_calc->side == 0)
			t_calc->perpWallDist = (t_calc->mapX - data->posX + (double)(1 - t_calc->stepX) / 2) / t_calc->rayDirX;
		else
			t_calc->perpWallDist = (t_calc->mapY - data->posY + (double)(1 - t_calc->stepY) / 2) / t_calc->rayDirY;
		z_buffer[t_calc->x] = t_calc->perpWallDist;
		lineHeight = (int)(config->s_height / t_calc->perpWallDist);
		t_calc->draw_start = -lineHeight / 2 + config->s_height / 2;
		if(t_calc->draw_start < 0)
			t_calc->draw_start = 0;
		t_calc->draw_end = lineHeight / 2 + config->s_height / 2;
		if(t_calc->draw_end >= config->s_height)
			t_calc->draw_end = config->s_height - 1;
		if (t_calc->side == 0)
			wallX = data->posY + t_calc->perpWallDist * t_calc->rayDirY;
		else
			wallX = data->posX + t_calc->perpWallDist * t_calc->rayDirX;
		wallX -= floor(wallX);
		t_calc->text_x = (int)(wallX * (double)texWidth);
		if (t_calc->side == 0 && t_calc->rayDirX > 0)
			t_calc->text_x = texWidth - t_calc->text_x - 1;
		if (t_calc->side == 1 && t_calc->rayDirY < 0)
			t_calc->text_x = texWidth - t_calc->text_x - 1;
		draw_celling(t_calc->x);
		draw_floor(t_calc->x);
		draw_walls(lineHeight);
		t_calc->x++;
	}
	draw_srpites(z_buffer);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}



int	main(int argc, char **argv)
{
	allocation();
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
