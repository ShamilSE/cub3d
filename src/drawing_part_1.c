/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:33:14 by mismene           #+#    #+#             */
/*   Updated: 2021/02/16 17:33:16 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_celling(int x_view)
{
	int		i;

	i = 0;
	while (i < g_t_calc->draw_start)
	{
		my_mlx_pixel_put(g_data, x_view, i, create_rgb(g_config->celling[0],
		g_config->celling[1], g_config->celling[2]));
		i++;
	}
}

void	draw_floor(int x_view)
{
	int		i;

	i = g_t_calc->draw_end;
	while (i < g_config->s_height)
	{
		my_mlx_pixel_put(g_data, x_view, i, create_rgb(g_config->floor[0],
		g_config->floor[1], g_config->floor[2]));
		i++;
	}
}

void	draw_walls_helper(int y, double step, int color)
{
	if (y >= g_t_calc->draw_start && y <= g_t_calc->draw_end)
	{
		g_t_calc->text_y = (int)g_t_calc->texture_position & (texHeight - 1);
		if (g_t_calc->side == 0)
		{
			if (g_t_calc->step_x > 0)
				color = g_texture_south->address[texHeight *
				g_t_calc->text_y + g_t_calc->text_x];
			else
				color = g_texture_north->address[texHeight *
				g_t_calc->text_y + g_t_calc->text_x];
		}
		else
		{
			if (g_t_calc->step_y > 0)
				color = g_texture_west->address[texHeight *
				g_t_calc->text_y + g_t_calc->text_x];
			else
				color = g_texture_east->address[texHeight *
				g_t_calc->text_y + g_t_calc->text_x];
		}
		g_t_calc->texture_position += step;
		my_mlx_pixel_put(g_data, g_t_calc->x, y, color);
	}
}

void	draw_walls(int line_height)
{
	int		y;
	double	step;
	int		color;

	color = 0;
	step = 1.0 * texHeight / line_height;
	g_t_calc->texture_position =
	(g_t_calc->draw_start - g_config->s_height / 2 + line_height / 2) * step;
	y = 0;
	while (y < g_config->s_height)
	{
		draw_walls_helper(y, step, color);
		y++;
	}
}
