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
	while (i < t_calc->draw_start)
	{
		my_mlx_pixel_put(data, x_view, i, create_rgb(config->celling[0],
		config->celling[1], config->celling[2]));
		i++;
	}
}

void	draw_floor(int x_view)
{
	int		i;

	i = t_calc->draw_end;
	while (i < config->s_height)
	{
		my_mlx_pixel_put(data, x_view, i, create_rgb(config->floor[0],
		config->floor[1], config->floor[2]));
		i++;
	}
}

void	draw_walls_helper(int y, double step, int color)
{
	if (y >= t_calc->draw_start && y <= t_calc->draw_end)
	{
		t_calc->text_y = (int)t_calc->texture_position & (texHeight - 1);
		if (t_calc->side == 0)
		{
			if (t_calc->stepX > 0)
				color = texture_south->address[texHeight *
				t_calc->text_y + t_calc->text_x];
			else
				color = texture_north->address[texHeight *
				t_calc->text_y + t_calc->text_x];
		}
		else
		{
			if (t_calc->stepY > 0)
				color = texture_west->address[texHeight *
				t_calc->text_y + t_calc->text_x];
			else
				color = texture_east->address[texHeight *
				t_calc->text_y + t_calc->text_x];
		}
		t_calc->texture_position += step;
		my_mlx_pixel_put(data, t_calc->x, y, color);
	}
}

void	draw_walls(int line_height)
{
	int		y;
	double	step;
	int		color;

	color = 0;
	step = 1.0 * texHeight / line_height;
	t_calc->texture_position =
	(t_calc->draw_start - config->s_height / 2 + line_height / 2) * step;
	y = 0;
	while (y < config->s_height)
	{
		draw_walls_helper(y, step, color);
		y++;
	}
}
