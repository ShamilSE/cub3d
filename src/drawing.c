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
	sprites->dist_tmp = sprite_distance[i];
	sprites->x_tmp = sprites->x[i];
	sprites->y_tmp = sprites->y[i];
	sprite_distance[i] = sprite_distance[i + 1];
	sprite_distance[i + 1] = sprites->dist_tmp;
	sprites->x[i] = sprites->x[i + 1];
	sprites->y[i] = sprites->y[i + 1];
	sprites->x[i + 1] = sprites->x_tmp;
	sprites->y[i + 1] = sprites->y_tmp;
}

void	sort_sprites(void)
{
	double	sprite_distance[sprites->count];
	int		i;

	i = 0;
	while (i < sprites->count)
	{
		sprite_distance[i] = ((g_data->pos_x - sprites->x[i]) *
		(g_data->pos_x - sprites->x[i]) +
		(g_data->pos_y - sprites->y[i]) * (g_data->pos_y - sprites->y[i]));
		i++;
	}
	i = 0;
	while (i < sprites->count)
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
	sprites->transform_x = sprites->inv_det *
	(g_data->dir_y * sprites->sprite_x - g_data->dir_x * sprites->sprite_y);
	sprites->transform_y = sprites->inv_det *
	(-g_data->plane_y * sprites->sprite_x + g_data->plane_x * sprites->sprite_y);
	sprites->sprite_screen_x = (int)((g_config->s_width / 2) *
			(1 + sprites->transform_x / sprites->transform_y));
	sprites->sprite_height =
	abs((int)(g_config->s_height / (sprites->transform_y)));
	sprites->draw_start_y = -sprites->sprite_height / 2 + g_config->s_height / 2;
	if (sprites->draw_start_y < 0)
		sprites->draw_start_y = 0;
	sprites->draw_end_y = sprites->sprite_height / 2 + g_config->s_height / 2;
	if (sprites->draw_end_y >= g_config->s_height)
		sprites->draw_end_y = g_config->s_height - 1;
	sprites->sprite_width = abs((int)(g_config->s_height / (sprites->transform_y)));
	sprites->draw_start_x = -sprites->sprite_width / 2 + sprites->sprite_screen_x;
	if (sprites->draw_start_x < 0)
		sprites->draw_start_x = 0;
	sprites->draw_end_x = sprites->sprite_width / 2 + sprites->sprite_screen_x;
	if (sprites->draw_end_x >= g_config->s_width)
		sprites->draw_end_x = g_config->s_width - 1;
	sprites->stripe = sprites->draw_start_x;
}

void	draw_sprites_helper(double *z_buffer)
{
	int	y;
	int	d;
	int	color_sprite;

	sprites->text_x = (int)(256 * (sprites->stripe -
			(-sprites->sprite_width / 2 + sprites->sprite_screen_x))
			* TEXTURE_WIDTH / sprites->sprite_width) / 256;
	if (sprites->transform_y > 0 &&
	sprites->stripe > 0 && sprites->stripe < g_config->s_width &&
		sprites->transform_y < z_buffer[sprites->stripe])
	{
		y = sprites->draw_start_y;
		while (y < sprites->draw_end_y)
		{
			d = (y) * 256 - g_config->s_height *
					128 + sprites->sprite_height * 128;
			sprites->text_y = ((d * texHeight) / sprites->sprite_height) / 256;
			color_sprite = g_texture_sprite->address
			[TEXTURE_WIDTH * sprites->text_y + sprites->text_x];
			if (color_sprite != 0)
				my_mlx_pixel_put(g_data, sprites->stripe, y, color_sprite);
			y++;
		}
	}
	sprites->stripe++;
}

void	draw_srpites(double *z_buffer)
{
	int	i;

	i = 0;
	sort_sprites();
	while (i < sprites->count)
	{
		sprites->sprite_x = sprites->x[i] - g_data->pos_x;
		sprites->sprite_y = sprites->y[i] - g_data->pos_y;
		sprites->inv_det = 1.0 / (g_data->plane_x *
			g_data->dir_y - g_data->dir_x * g_data->plane_y);
		calc_sprites(i);
		while (sprites->stripe < sprites->draw_end_x)
			draw_sprites_helper(z_buffer);
		i++;
	}
}
