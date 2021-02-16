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
		sprite_distance[i] = ((data->posX - sprites->x[i]) *
		(data->posX - sprites->x[i]) +
		(data->posY - sprites->y[i]) * (data->posY - sprites->y[i]));
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
	sprites->transformX = sprites->invDet *
	(data->dirY * sprites->spriteX - data->dirX * sprites->spriteY);
	sprites->transformY = sprites->invDet *
	(-data->planeY * sprites->spriteX + data->planeX * sprites->spriteY);
	sprites->spriteScreenX = (int)((config->s_width / 2) *
			(1 + sprites->transformX / sprites->transformY));
	sprites->spriteHeight =
	abs((int)(config->s_height / (sprites->transformY)));
	sprites->drawStartY = -sprites->spriteHeight / 2 + config->s_height / 2;
	if (sprites->drawStartY < 0)
		sprites->drawStartY = 0;
	sprites->drawEndY = sprites->spriteHeight / 2 + config->s_height / 2;
	if (sprites->drawEndY >= config->s_height)
		sprites->drawEndY = config->s_height - 1;
	sprites->spriteWidth = abs((int)(config->s_height / (sprites->transformY)));
	sprites->drawStartX = -sprites->spriteWidth / 2 + sprites->spriteScreenX;
	if (sprites->drawStartX < 0)
		sprites->drawStartX = 0;
	sprites->drawEndX = sprites->spriteWidth / 2 + sprites->spriteScreenX;
	if (sprites->drawEndX >= config->s_width)
		sprites->drawEndX = config->s_width - 1;
	sprites->stripe = sprites->drawStartX;
}

void	draw_sprites_helper(double *z_buffer)
{
	int	y;
	int	d;
	int	color_sprite;

	sprites->text_x = (int)(256 * (sprites->stripe -
			(-sprites->spriteWidth / 2 + sprites->spriteScreenX))
			* texWidth / sprites->spriteWidth) / 256;
	if (sprites->transformY > 0 &&
	sprites->stripe > 0 && sprites->stripe < config->s_width &&
		sprites->transformY < z_buffer[sprites->stripe])
	{
		y = sprites->drawStartY;
		while (y < sprites->drawEndY)
		{
			d = (y) * 256 - config->s_height *
					128 + sprites->spriteHeight * 128;
			sprites->text_y = ((d * texHeight) / sprites->spriteHeight) / 256;
			color_sprite = texture_sprite->address
			[texWidth * sprites->text_y + sprites->text_x];
			if (color_sprite != 0)
				my_mlx_pixel_put(data, sprites->stripe, y, color_sprite);
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
		sprites->spriteX = sprites->x[i] - data->posX;
		sprites->spriteY = sprites->y[i] - data->posY;
		sprites->invDet = 1.0 / (data->planeX *
			data->dirY - data->dirX * data->planeY);
		calc_sprites(i);
		while (sprites->stripe < sprites->drawEndX)
			draw_sprites_helper(z_buffer);
		i++;
	}
}
