/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_part_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 20:47:52 by mismene           #+#    #+#             */
/*   Updated: 2021/02/16 20:47:54 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_of_mlx(void)
{
	mlx_hook(data->win, 2, 1L << 0, &movings, &data);
	mlx_hook(data->win, 17, 1L << 0, &close_window, &data);
	mlx_loop(data->mlx);
}

void	prepare_to_draw_helper(void)
{
	if (t_calc->side == 0)
		t_calc->perpWallDist = (t_calc->mapX -
			data->posX + (double)(1 - t_calc->stepX) / 2) / t_calc->rayDirX;
	else
		t_calc->perpWallDist = (t_calc->mapY -
			data->posY + (double)(1 - t_calc->stepY) / 2) / t_calc->rayDirY;
}

int		prepare_to_draw(double *z_buffer, int line_height)
{
	double	wall_x;

	prepare_to_draw_helper();
	z_buffer[t_calc->x] = t_calc->perpWallDist;
	line_height = (int)(config->s_height / t_calc->perpWallDist);
	t_calc->draw_start = -line_height / 2 + config->s_height / 2;
	if (t_calc->draw_start < 0)
		t_calc->draw_start = 0;
	t_calc->draw_end = line_height / 2 + config->s_height / 2;
	if (t_calc->draw_end >= config->s_height)
		t_calc->draw_end = config->s_height - 1;
	if (t_calc->side == 0)
		wall_x = data->posY + t_calc->perpWallDist * t_calc->rayDirY;
	else
		wall_x = data->posX + t_calc->perpWallDist * t_calc->rayDirX;
	wall_x -= floor(wall_x);
	t_calc->text_x = (int)(wall_x * (double)texWidth);
	if (t_calc->side == 0 && t_calc->rayDirX > 0)
		t_calc->text_x = texWidth - t_calc->text_x - 1;
	if (t_calc->side == 1 && t_calc->rayDirY < 0)
		t_calc->text_x = texWidth - t_calc->text_x - 1;
	return (line_height);
}
