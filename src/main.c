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

void	define_step_side_dist(void)
{
	if (t_calc->rayDirX < 0)
	{
		t_calc->stepX = -1;
		t_calc->sideDistX = (data->posX - t_calc->mapX) * t_calc->deltaDistX;
	}
	else
	{
		t_calc->stepX = 1;
		t_calc->sideDistX =
		(t_calc->mapX + 1.0 - data->posX) * t_calc->deltaDistX;
	}
	if (t_calc->rayDirY < 0)
	{
		t_calc->stepY = -1;
		t_calc->sideDistY = (data->posY - t_calc->mapY) * t_calc->deltaDistY;
	}
	else
	{
		t_calc->stepY = 1;
		t_calc->sideDistY =
		(t_calc->mapY + 1.0 - data->posY) * t_calc->deltaDistY;
	}
}

void	count_distance(void)
{
	int	hit;

	hit = 0;
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
}

void	calc_helper(void)
{
	data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
		&data->bpp, &data->size, &data->endian);
	t_calc->x = 0;
}

void	calc(void)
{
	double	z_buffer[config->s_width];
	int		line_height;

	calc_helper();
	while (t_calc->x < config->s_width)
	{
		t_calc->cameraX = 2 * t_calc->x / (double)config->s_width - 1;
		t_calc->rayDirX = data->dirX + data->planeX * t_calc->cameraX;
		t_calc->rayDirY = data->dirY + data->planeY * t_calc->cameraX;
		t_calc->mapX = (int)data->posX;
		t_calc->mapY = (int)data->posY;
		t_calc->deltaDistX = sqrt(1 + (t_calc->rayDirY * t_calc->rayDirY) /
				(t_calc->rayDirX * t_calc->rayDirX));
		t_calc->deltaDistY = sqrt(1 + (t_calc->rayDirX * t_calc->rayDirX) /
				(t_calc->rayDirY * t_calc->rayDirY));
		define_step_side_dist();
		count_distance();
		line_height = prepare_to_draw(z_buffer, line_height);
		draw_celling(t_calc->x);
		draw_floor(t_calc->x);
		draw_walls(line_height);
		t_calc->x++;
	}
	draw_srpites(z_buffer);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

int		main(int argc, char **argv)
{
	allocation();
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
	else if ((ft_strncmp(argv[2], "--save", 6) ||
	ft_strlen(argv[2]) != 6) && argc == 3)
		throw_error("unexpected second argument, need --save");
	data_ini();
	spawn_direction();
	data->win = mlx_new_window(data->mlx,
	config->s_width, config->s_height, "mlx");
	is_screen_size_correct();
	get_textures();
	calc();
	loop_of_mlx();
}
