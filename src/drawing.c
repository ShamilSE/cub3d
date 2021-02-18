/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:54:45 by mismene           #+#    #+#             */
/*   Updated: 2021/02/15 16:54:47 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites_calc(int i, double *sprite_distance)
{
	g_sprites->dist_tmp = sprite_distance[i];
	g_sprites->x_tmp = g_sprites->x[i];
	g_sprites->y_tmp = g_sprites->y[i];
	sprite_distance[i] = sprite_distance[i + 1];
	sprite_distance[i + 1] = g_sprites->dist_tmp;
	g_sprites->x[i] = g_sprites->x[i + 1];
	g_sprites->y[i] = g_sprites->y[i + 1];
	g_sprites->x[i + 1] = g_sprites->x_tmp;
	g_sprites->y[i + 1] = g_sprites->y_tmp;
}

void	sort_sprites(void)
{
	double	sprite_distance[g_sprites->count];
	int		i;

	i = 0;
	while (i < g_sprites->count)
	{
		sprite_distance[i] = ((g_data->pos_x - g_sprites->x[i]) *
		(g_data->pos_x - g_sprites->x[i]) +
		(g_data->pos_y - g_sprites->y[i]) * (g_data->pos_y - g_sprites->y[i]));
		i++;
	}
	i = 0;
	while (i < g_sprites->count)
	{
		if (sprite_distance[i] < sprite_distance[i + 1])
		{
			sort_sprites_calc(i, sprite_distance);
			i = -1;
		}
		i++;
	}
}

void	calc_sprites(int i)
{
	g_sprites->transform_x = g_sprites->inv_det *
	(g_data->dir_y * g_sprites->sprite_x - g_data->dir_x * g_sprites->sprite_y);
	g_sprites->transform_y = g_sprites->inv_det *
	(-g_data->plane_y * g_sprites->sprite_x + g_data->plane_x * g_sprites->sprite_y);
	g_sprites->sprite_screen_x = (int)((g_config->s_width / 2) *
			(1 + g_sprites->transform_x / g_sprites->transform_y));
	g_sprites->sprite_height =
	abs((int)(g_config->s_height / (g_sprites->transform_y)));
	g_sprites->draw_start_y = -g_sprites->sprite_height / 2 + g_config->s_height / 2;
	if (g_sprites->draw_start_y < 0)
		g_sprites->draw_start_y = 0;
	g_sprites->draw_end_y = g_sprites->sprite_height / 2 + g_config->s_height / 2;
	if (g_sprites->draw_end_y >= g_config->s_height)
		g_sprites->draw_end_y = g_config->s_height - 1;
	g_sprites->sprite_width = abs((int)(g_config->s_height / (g_sprites->transform_y)));
	g_sprites->draw_start_x = -g_sprites->sprite_width / 2 + g_sprites->sprite_screen_x;
	if (g_sprites->draw_start_x < 0)
		g_sprites->draw_start_x = 0;
	g_sprites->draw_end_x = g_sprites->sprite_width / 2 + g_sprites->sprite_screen_x;
	if (g_sprites->draw_end_x >= g_config->s_width)
		g_sprites->draw_end_x = g_config->s_width - 1;
	g_sprites->stripe = g_sprites->draw_start_x;
}

void	draw_sprites_helper(double *z_buffer)
{
	int	y;
	int	d;
	int	color_sprite;

	g_sprites->text_x = (int)(256 * (g_sprites->stripe -
			(-g_sprites->sprite_width / 2 + g_sprites->sprite_screen_x))
			* TEXTURE_WIDTH / g_sprites->sprite_width) / 256;
	if (g_sprites->transform_y > 0 &&
	g_sprites->stripe > 0 && g_sprites->stripe < g_config->s_width &&
		g_sprites->transform_y < z_buffer[g_sprites->stripe])
	{
		y = g_sprites->draw_start_y;
		while (y < g_sprites->draw_end_y)
		{
			d = (y) * 256 - g_config->s_height *
					128 + g_sprites->sprite_height * 128;
			g_sprites->text_y = ((d * TEXTURE_HEIGHT) / g_sprites->sprite_height) / 256;
			color_sprite = g_texture_sprite->address
			[TEXTURE_WIDTH * g_sprites->text_y + g_sprites->text_x];
			if (color_sprite != 0)
				my_mlx_pixel_put(g_data, g_sprites->stripe, y, color_sprite);
			y++;
		}
	}
	g_sprites->stripe++;
}

void	draw_srpites(double *z_buffer)
{
	int	i;

	i = 0;
	sort_sprites();
	while (i < g_sprites->count)
	{
		g_sprites->sprite_x = g_sprites->x[i] - g_data->pos_x;
		g_sprites->sprite_y = g_sprites->y[i] - g_data->pos_y;
		g_sprites->inv_det = 1.0 / (g_data->plane_x *
			g_data->dir_y - g_data->dir_x * g_data->plane_y);
		calc_sprites(i);
		while (g_sprites->stripe < g_sprites->draw_end_x)
			draw_sprites_helper(z_buffer);
		i++;
	}
}
