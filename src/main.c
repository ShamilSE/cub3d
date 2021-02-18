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
		g_t_calc->side_dist_x =
		(g_data->pos_x - g_t_calc->map_x) * g_t_calc->delta_dist_x;
	}
	else
	{
		g_t_calc->step_x = 1;
		g_t_calc->side_dist_x =
		(g_t_calc->map_x + 1.0 - g_data->pos_x) * g_t_calc->delta_dist_x;
	}
	if (g_t_calc->ray_dir_y < 0)
	{
		g_t_calc->step_y = -1;
		g_t_calc->side_dist_y =
		(g_data->pos_y - g_t_calc->map_y) * g_t_calc->delta_dist_y;
	}
	else
	{
		g_t_calc->step_y = 1;
		g_t_calc->side_dist_y =
		(g_t_calc->map_y + 1.0 - g_data->pos_y) * g_t_calc->delta_dist_y;
	}
}

void	calc_helper(void)
{
	g_data->image = mlx_new_image(
	g_data->mlx, g_config->s_width, g_config->s_height);
	g_data->addr = mlx_get_data_addr(g_data->image,
		&g_data->bpp, &g_data->size, &g_data->endian);
	g_t_calc->x = 0;
}

void	calc_helper_1(void)
{
	g_t_calc->camera_x = 2 * g_t_calc->x / (double)g_config->s_width - 1;
	g_t_calc->ray_dir_x =
	g_data->dir_x + g_data->plane_x * g_t_calc->camera_x;
	g_t_calc->ray_dir_y =
	g_data->dir_y + g_data->plane_y * g_t_calc->camera_x;
	g_t_calc->map_x = (int)g_data->pos_x;
	g_t_calc->map_y = (int)g_data->pos_y;
	g_t_calc->delta_dist_x = sqrt(1 +
	(g_t_calc->ray_dir_y * g_t_calc->ray_dir_y) /
	(g_t_calc->ray_dir_x * g_t_calc->ray_dir_x));
}

void	calc(void)
{
	double	z_buffer[g_config->s_width];
	int		line_height;

	calc_helper();
	while (g_t_calc->x < g_config->s_width)
	{
		calc_helper_1();
		g_t_calc->delta_dist_y = sqrt(1 + (g_t_calc->ray_dir_x *
		g_t_calc->ray_dir_x) / (g_t_calc->ray_dir_y * g_t_calc->ray_dir_y));
		define_step_side_dist();
		count_distance();
		line_height = prepare_to_draw(z_buffer, line_height);
		draw_celling(g_t_calc->x);
		draw_floor(g_t_calc->x);
		draw_walls(line_height);
		g_t_calc->x++;
	}
	draw_srpites(z_buffer);
	mlx_put_image_to_window(g_data->mlx, g_data->win, g_data->image, 0, 0);
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
	is_screen_size_correct();
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
	g_data->win = mlx_new_window(g_data->mlx,
	g_config->s_width, g_config->s_height, "mlx");
	get_textures();
	calc();
	loop_of_mlx();
}
