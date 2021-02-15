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
	if (config->map[(int)(data->posX - data->dirY *
	data->moveSpeed)][(int)(data->posY)] == '0')
		data->posX -= data->dirY * data->moveSpeed;
	if (config->map[(int)(data->posX)][(int)(data->posY +
	data->dirX * data->moveSpeed)] == '0')
		data->posY += data->dirX * data->moveSpeed;
	data->image = mlx_new_image(data->mlx,
			config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
			&data->bpp, &data->size, &data->endian);
	calc();
}

void	move_right(void)
{
	mlx_destroy_image(data->mlx, data->image);
	if (config->map[(int)(data->posX + data->dirY *
	data->moveSpeed)][(int)(data->posY)] == '0')
		data->posX += data->dirY * data->moveSpeed;
	if (config->map[(int)(data->posX)][(int)(data->posY -
	data->dirX * data->moveSpeed)] == '0')
		data->posY -= data->dirX * data->moveSpeed;
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

	old_dir_x = data->dirX;
	old_plane_x = data->planeX;
	mlx_destroy_image(data->mlx, data->image);
	data->dirX = data->dirX * cos(data->rotSpeed) -
			data->dirY * sin(data->rotSpeed);
	data->dirY = old_dir_x * sin(data->rotSpeed) +
			data->dirY * cos(data->rotSpeed);
	data->planeX = data->planeX * cos(data->rotSpeed) -
			data->planeY * sin(data->rotSpeed);
	data->planeY = old_plane_x * sin(data->rotSpeed) +
			data->planeY * cos(data->rotSpeed);
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
