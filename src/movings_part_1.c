/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movings_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:42:16 by mismene           #+#    #+#             */
/*   Updated: 2021/02/15 19:42:19 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_right(void)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g_data->dir_x;
	old_plane_x = g_data->plane_x;
	g_data->dir_x = g_data->dir_x *
	cos(-g_data->rot_speed) - g_data->dir_y * sin(-g_data->rot_speed);
	g_data->dir_y = old_dir_x * sin(-g_data->rot_speed) +
				g_data->dir_y * cos(-g_data->rot_speed);
	g_data->plane_x = g_data->plane_x * cos(-g_data->rot_speed) -
				g_data->plane_y * sin(-g_data->rot_speed);
	g_data->plane_y = old_plane_x * sin(-g_data->rot_speed) +
				g_data->plane_y * cos(-g_data->rot_speed);
}

void	move_forward(void)
{
	mlx_destroy_image(g_data->mlx, g_data->image);
	if (config->map[(int)(g_data->pos_x +
			g_data->dir_x * g_data->move_speed)][(int)(g_data->pos_y)] == '0')
		g_data->pos_x += g_data->dir_x * g_data->move_speed;
	if (config->map[(int)(g_data->pos_x)][(int)(g_data->pos_y
			+ g_data->dir_y * g_data->move_speed)] == '0')
		g_data->pos_y += g_data->dir_y * g_data->move_speed;
	g_data->image = mlx_new_image(g_data->mlx,
		config->s_width, config->s_height);
	g_data->addr = mlx_get_data_addr(g_data->image,
			&g_data->bpp, &g_data->size, &g_data->endian);
	calc();
}

void	move_backward(void)
{
	mlx_destroy_image(g_data->mlx, g_data->image);
	if (config->map[(int)(g_data->pos_x -
	g_data->dir_x * g_data->move_speed)][(int)(g_data->pos_y)] == '0')
		g_data->pos_x -= g_data->dir_x * g_data->move_speed;
	if (config->map[(int)(g_data->pos_x)][(int)(g_data->pos_y -
				g_data->dir_y * g_data->move_speed)] == '0')
		g_data->pos_y -= g_data->dir_y * g_data->move_speed;
	g_data->image = mlx_new_image(g_data->mlx,
			config->s_width, config->s_height);
	g_data->addr = mlx_get_data_addr(g_data->image,
			&g_data->bpp, &g_data->size, &g_data->endian);
	calc();
}
