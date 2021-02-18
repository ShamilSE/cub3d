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
	if (g_t_calc->ray_dir_x < 0)
	{
		g_t_calc->step_x = -1;
		g_t_calc->side_dist_x = (data->pos_x - g_t_calc->map_x) * g_t_calc->delta_dist_x;
	}
	else
	{
		g_t_calc->step_x = 1;
		g_t_calc->side_dist_x =
		(g_t_calc->map_x + 1.0 - data->pos_x) * g_t_calc->delta_dist_x;
	}
	if (g_t_calc->ray_dir_y < 0)
	{
		g_t_calc->step_y = -1;
		g_t_calc->side_dist_y = (data->pos_y - g_t_calc->map_y) * g_t_calc->delta_dist_y;
	}
	else
	{
		g_t_calc->step_y = 1;
		g_t_calc->side_dist_y =
		(g_t_calc->map_y + 1.0 - data->pos_y) * g_t_calc->delta_dist_y;
	}
}

void	count_distance(void)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (g_t_calc->side_dist_x < g_t_calc->side_dist_y)
		{
			g_t_calc->side_dist_x += g_t_calc->delta_dist_x;
			g_t_calc->map_x += g_t_calc->step_x;
			g_t_calc->side = 0;
		}
		else
		{
			g_t_calc->side_dist_y += g_t_calc->delta_dist_y;
			g_t_calc->map_y += g_t_calc->step_y;
			g_t_calc->side = 1;
		}
		if (config->map[g_t_calc->map_x][g_t_calc->map_y] == '1')
			hit = 1;
	}
}

void	calc_helper(void)
{
	data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
		&data->bpp, &data->size, &data->endian);
	g_t_calc->x = 0;
}

void	calc(void)
{
	double	z_buffer[config->s_width];
	int		line_height;

	calc_helper();
	while (g_t_calc->x < config->s_width)
	{
		g_t_calc->camera_x = 2 * g_t_calc->x / (double)config->s_width - 1;
		g_t_calc->ray_dir_x = data->dir_x + data->plane_x * g_t_calc->camera_x;
		g_t_calc->ray_dir_y = data->dir_y + data->plane_y * g_t_calc->camera_x;
		g_t_calc->map_x = (int)data->pos_x;
		g_t_calc->map_y = (int)data->pos_y;
		g_t_calc->delta_dist_x = sqrt(1 + (g_t_calc->ray_dir_y * g_t_calc->ray_dir_y) /
				(g_t_calc->ray_dir_x * g_t_calc->ray_dir_x));
		g_t_calc->delta_dist_y = sqrt(1 + (g_t_calc->ray_dir_x * g_t_calc->ray_dir_x) /
				(g_t_calc->ray_dir_y * g_t_calc->ray_dir_y));
		define_step_side_dist();
		count_distance();
		line_height = prepare_to_draw(z_buffer, line_height);
		draw_celling(g_t_calc->x);
		draw_floor(g_t_calc->x);
		draw_walls(line_height);
		g_t_calc->x++;
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
