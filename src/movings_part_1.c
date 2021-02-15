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

	old_dir_x = data->dirX;
	old_plane_x = data->planeX;
	data->dirX = data->dirX *
	cos(-data->rotSpeed) - data->dirY * sin(-data->rotSpeed);
	data->dirY = old_dir_x * sin(-data->rotSpeed) +
				data->dirY * cos(-data->rotSpeed);
	data->planeX = data->planeX * cos(-data->rotSpeed) -
				data->planeY * sin(-data->rotSpeed);
	data->planeY = old_plane_x * sin(-data->rotSpeed) +
				data->planeY * cos(-data->rotSpeed);
}

void	move_forward(void)
{
	mlx_destroy_image(data->mlx, data->image);
	if (config->map[(int)(data->posX +
			data->dirX * data->moveSpeed)][(int)(data->posY)] == '0')
		data->posX += data->dirX * data->moveSpeed;
	if (config->map[(int)(data->posX)][(int)(data->posY
			+ data->dirY * data->moveSpeed)] == '0')
		data->posY += data->dirY * data->moveSpeed;
	data->image = mlx_new_image(data->mlx,
		config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
			&data->bpp, &data->size, &data->endian);
	calc();
}

void	move_backward(void)
{
	mlx_destroy_image(data->mlx, data->image);
	if (config->map[(int)(data->posX -
	data->dirX * data->moveSpeed)][(int)(data->posY)] == '0')
		data->posX -= data->dirX * data->moveSpeed;
	if (config->map[(int)(data->posX)][(int)(data->posY -
				data->dirY * data->moveSpeed)] == '0')
		data->posY -= data->dirY * data->moveSpeed;
	data->image = mlx_new_image(data->mlx,
			config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image,
			&data->bpp, &data->size, &data->endian);
	calc();
}
