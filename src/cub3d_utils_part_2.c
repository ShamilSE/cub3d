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
	mlx_hook(g_data->win, 2, 1L << 0, &movings, &g_data);
	mlx_hook(g_data->win, 17, 1L << 0, &close_window, &g_data);
	mlx_loop(g_data->mlx);
}

void	prepare_to_draw_helper(void)
{
	if (g_t_calc->side == 0)
		g_t_calc->perp_wall_dist = (g_t_calc->map_x -
			g_data->pos_x + (double)(1 - g_t_calc->step_x) / 2) / g_t_calc->ray_dir_x;
	else
		g_t_calc->perp_wall_dist = (g_t_calc->map_y -
			g_data->pos_y + (double)(1 - g_t_calc->step_y) / 2) / g_t_calc->ray_dir_y;
}

int		prepare_to_draw(double *z_buffer, int line_height)
{
	double	wall_x;

	prepare_to_draw_helper();
	z_buffer[g_t_calc->x] = g_t_calc->perp_wall_dist;
	line_height = (int)(g_config->s_height / g_t_calc->perp_wall_dist);
	g_t_calc->draw_start = -line_height / 2 + g_config->s_height / 2;
	if (g_t_calc->draw_start < 0)
		g_t_calc->draw_start = 0;
	g_t_calc->draw_end = line_height / 2 + g_config->s_height / 2;
	if (g_t_calc->draw_end >= g_config->s_height)
		g_t_calc->draw_end = g_config->s_height - 1;
	if (g_t_calc->side == 0)
		wall_x = g_data->pos_y + g_t_calc->perp_wall_dist * g_t_calc->ray_dir_y;
	else
		wall_x = g_data->pos_x + g_t_calc->perp_wall_dist * g_t_calc->ray_dir_x;
	wall_x -= floor(wall_x);
	g_t_calc->text_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if (g_t_calc->side == 0 && g_t_calc->ray_dir_x > 0)
		g_t_calc->text_x = TEXTURE_WIDTH - g_t_calc->text_x - 1;
	if (g_t_calc->side == 1 && g_t_calc->ray_dir_y < 0)
		g_t_calc->text_x = TEXTURE_WIDTH - g_t_calc->text_x - 1;
	return (line_height);
}
