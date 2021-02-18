/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:30:50 by mismene           #+#    #+#             */
/*   Updated: 2021/02/15 19:30:53 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_left(void)
{
	mlx_destroy_image(data->mlx, data->image);
	if (config->map[(int)(data->pos_x - data->dir_y *
	data->move_speed)][(int)(data->pos_y)] == '0')
		data->pos_x -= data->dir_y * data->move_speed;
	if (config->map[(int)(data->pos_x)][(int)(data->pos_y +
	data->dir_x * data->move_speed)] == '0')
		data->pos_y += data->dir_x * data->move_speed;
	data->image = mlx_new_image(data->mlx,
			config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
			&data->bpp, &data->size, &data->endian);
	calc();
}

void	move_right(void)
{
	mlx_destroy_image(data->mlx, data->image);
	if (config->map[(int)(data->pos_x + data->dir_y *
	data->move_speed)][(int)(data->pos_y)] == '0')
		data->pos_x += data->dir_y * data->move_speed;
	if (config->map[(int)(data->pos_x)][(int)(data->pos_y -
	data->dir_x * data->move_speed)] == '0')
		data->pos_y -= data->dir_x * data->move_speed;
	data->image = mlx_new_image(data->mlx,
			config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
			&data->bpp, &data->size, &data->endian);
	calc();
}

void	look_left(void)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	mlx_destroy_image(data->mlx, data->image);
	data->dir_x = data->dir_x * cos(data->rot_speed) -
			data->dir_y * sin(data->rot_speed);
	data->dir_y = old_dir_x * sin(data->rot_speed) +
			data->dir_y * cos(data->rot_speed);
	data->plane_x = data->plane_x * cos(data->rot_speed) -
			data->plane_y * sin(data->rot_speed);
	data->plane_y = old_plane_x * sin(data->rot_speed) +
			data->plane_y * cos(data->rot_speed);
	data->image = mlx_new_image(data->mlx,
			config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
			&data->bpp, &data->size, &data->endian);
	calc();
}

void	look_right(void)
{
	mlx_destroy_image(data->mlx, data->image);
	turn_right();
	data->image = mlx_new_image(data->mlx,
			config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
			&data->bpp, &data->size, &data->endian);
	calc();
}

int		movings(int key)
{
	if (key == K_W)
		move_forward();
	if (key == K_S)
		move_backward();
	if (key == K_D)
		move_right();
	if (key == K_A)
		move_left();
	if (key == 123)
		look_left();
	if (key == 124)
		look_right();
	if (key == K_ESC)
		exit(0);
	return (0);
}
