/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 07:32:51 by mismene           #+#    #+#             */
/*   Updated: 2021/02/18 07:32:53 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_sprites_helper(void)
{
	g_sprites->transform_x = g_sprites->inv_det *
	(g_data->dir_y * g_sprites->sprite_x - g_data->dir_x * g_sprites->sprite_y);
	g_sprites->transform_y = g_sprites->inv_det * (-g_data->plane_y
	* g_sprites->sprite_x + g_data->plane_x * g_sprites->sprite_y);
	g_sprites->sprite_screen_x = (int)((g_config->s_width / 2) *
	(1 + g_sprites->transform_x / g_sprites->transform_y));
	g_sprites->sprite_height =
	fabs((g_config->s_height / (g_sprites->transform_y)));
	g_sprites->draw_start_y =
	-g_sprites->sprite_height / 2 + g_config->s_height / 2;
	if (g_sprites->draw_start_y < 0)
		g_sprites->draw_start_y = 0;
}

void	calc_sprites_helper_2(int *d, int *color_sprite, int y)
{
	*d = (y) * 256 - g_config->s_height *
					128 + g_sprites->sprite_height * 128;
	g_sprites->text_y = ((*d * TEXTURE_HEIGHT)
		/ g_sprites->sprite_height) / 256;
	*color_sprite = g_texture_sprite->address
	[TEXTURE_WIDTH * g_sprites->text_y + g_sprites->text_x];
}
