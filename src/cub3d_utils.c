/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:37:03 by mismene           #+#    #+#             */
/*   Updated: 2021/02/16 18:37:05 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scale_reso(void)
{
	int		mlx_size_x;
	int		mlx_size_y;

	mlx_get_screen_size(g_data->mlx, &mlx_size_x, &mlx_size_y);
	config->s_width = mlx_size_x;
	config->s_height = mlx_size_y;
}

void	is_screen_size_correct(void)
{
	int		mlx_size_x;
	int		mlx_size_y;

	if (config->s_width < 20 || config->s_height < 20)
		throw_error("the window size is too small");
	mlx_get_screen_size(g_data->mlx, &mlx_size_x, &mlx_size_y);
	if (config->s_width > mlx_size_x || config->s_height > mlx_size_y)
		scale_reso();
}

void	spawn_direction(void)
{
	int	i;

	i = 0;
	if (config->player == 'W')
		while (i++ < 47)
			turn_right();
	else if (config->player == 'S')
		while (i++ < 32)
			turn_right();
	else if (config->player == 'E')
		while (i++ < 16)
			turn_right();
}

void	data_ini(void)
{
	g_data->mlx = mlx_init();
	g_data->dir_x = -1;
	g_data->dir_y = 0;
	g_data->plane_x = 0;
	g_data->plane_y = 0.66;
	g_data->move_speed = 0.1;
	g_data->rot_speed = 0.1;
}

void	allocation(void)
{
	if (!(g_data = malloc(sizeof(t_data))))
		throw_error("no memory");
	if (!(sprites = malloc(sizeof(t_sprites))))
		throw_error("no memory");
	if (!(g_t_calc = malloc(sizeof(t_calc_vars))))
		throw_error("no memory");
}
