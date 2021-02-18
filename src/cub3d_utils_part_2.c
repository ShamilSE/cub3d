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
		t_calc->perp_wall_dist = (t_calc->map_x -
			data->pos_x + (double)(1 - t_calc->step_x) / 2) / t_calc->ray_dir_x;
	else
		t_calc->perp_wall_dist = (t_calc->map_y -
			data->pos_y + (double)(1 - t_calc->step_y) / 2) / t_calc->ray_dir_y;
}

int		prepare_to_draw(double *z_buffer, int line_height)
{
	double	wall_x;

	prepare_to_draw_helper();
	z_buffer[t_calc->x] = t_calc->perp_wall_dist;
	line_height = (int)(config->s_height / t_calc->perp_wall_dist);
	t_calc->draw_start = -line_height / 2 + config->s_height / 2;
	if (t_calc->draw_start < 0)
		t_calc->draw_start = 0;
	t_calc->draw_end = line_height / 2 + config->s_height / 2;
	if (t_calc->draw_end >= config->s_height)
		t_calc->draw_end = config->s_height - 1;
	if (t_calc->side == 0)
		wall_x = data->pos_y + t_calc->perp_wall_dist * t_calc->ray_dir_y;
	else
		wall_x = data->pos_x + t_calc->perp_wall_dist * t_calc->ray_dir_x;
	wall_x -= floor(wall_x);
	t_calc->text_x = (int)(wall_x * (double)texWidth);
	if (t_calc->side == 0 && t_calc->ray_dir_x > 0)
		t_calc->text_x = texWidth - t_calc->text_x - 1;
	if (t_calc->side == 1 && t_calc->ray_dir_y < 0)
		t_calc->text_x = texWidth - t_calc->text_x - 1;
	return (line_height);
}
