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

	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	data->dir_x = data->dir_x *
	cos(-data->rot_speed) - data->dir_y * sin(-data->rot_speed);
	data->dir_y = old_dir_x * sin(-data->rot_speed) +
				data->dir_y * cos(-data->rot_speed);
	data->plane_x = data->plane_x * cos(-data->rot_speed) -
				data->plane_y * sin(-data->rot_speed);
	data->plane_y = old_plane_x * sin(-data->rot_speed) +
				data->plane_y * cos(-data->rot_speed);
}

void	move_forward(void)
{
	mlx_destroy_image(data->mlx, data->image);
	if (config->map[(int)(data->pos_x +
			data->dir_x * data->move_speed)][(int)(data->pos_y)] == '0')
		data->pos_x += data->dir_x * data->move_speed;
	if (config->map[(int)(data->pos_x)][(int)(data->pos_y
			+ data->dir_y * data->move_speed)] == '0')
		data->pos_y += data->dir_y * data->move_speed;
	data->image = mlx_new_image(data->mlx,
		config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
			&data->bpp, &data->size, &data->endian);
	calc();
}

void	move_backward(void)
{
	mlx_destroy_image(data->mlx, data->image);
	if (config->map[(int)(data->pos_x -
	data->dir_x * data->move_speed)][(int)(data->pos_y)] == '0')
		data->pos_x -= data->dir_x * data->move_speed;
	if (config->map[(int)(data->pos_x)][(int)(data->pos_y -
				data->dir_y * data->move_speed)] == '0')
		data->pos_y -= data->dir_y * data->move_speed;
	data->image = mlx_new_image(data->mlx,
			config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
			&data->bpp, &data->size, &data->endian);
	calc();
}
