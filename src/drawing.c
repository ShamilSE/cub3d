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

t_sprites *sprites;

t_texture	*texture_north;
t_texture	*texture_south;
t_texture	*texture_west;
t_texture	*texture_east;
t_texture	*texture_sprite;
t_calc_vars	*t_calc;

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

void	draw_walls_helper(int y, double step)
{
	if (y >= t_calc->draw_start && y <= t_calc->draw_end)
	{
		t_calc->text_y = (int)t_calc->texture_position & (texHeight - 1);
		int color;
		if (t_calc->side == 0)
		{
			if (t_calc->stepX > 0)
				color = texture_south->address[texHeight * t_calc->text_y + t_calc->text_x];
			else
				color = texture_north->address[texHeight * t_calc->text_y + t_calc->text_x];
		}
		else
		{
			if (t_calc->stepY > 0)
				color = texture_west->address[texHeight * t_calc->text_y + t_calc->text_x];
			else
				color = texture_east->address[texHeight * t_calc->text_y + t_calc->text_x];
		}
		t_calc->texture_position += step;
		my_mlx_pixel_put(data, t_calc->x, y, color);
	}
}

void	draw_walls(int lineHeight)
{
	int		y;
	double	step;

	step = 1.0 * texHeight / lineHeight;
	t_calc->texture_position = (t_calc->draw_start - config->s_height / 2 + lineHeight / 2) * step;
	y = 0;
	while (y < config->s_height)
	{
		draw_walls_helper(y, step);
		y++;
	}
}

void	sort_sprites()
{
	double	spriteDistance[sprites->count];
	double	dist_tmp;
	double	x_tmp;
	double	y_tmp;
	int		i;

	i = 0;
	while (i < sprites->count)
	{
		spriteDistance[i] = ((data->posX - sprites->x[i]) *
			( data->posX - sprites->x[i]) + (data->posY - sprites->y[i]) * (data->posY - sprites->y[i]));
		i++;
	}
	i = 0;
	while (i < sprites->count)
	{
		if (spriteDistance[i] < spriteDistance[i + 1])
		{
			dist_tmp = spriteDistance[i];
			x_tmp = sprites->x[i];
			y_tmp = sprites->y[i];
			spriteDistance[i] = spriteDistance[i + 1];
			spriteDistance[i + 1] = dist_tmp;
			sprites->x[i] = sprites->x[i + 1];
			sprites->y[i] = sprites->y[i + 1];
			sprites->x[i + 1] = x_tmp;
			sprites->y[i + 1] = y_tmp;
			i = -1;
		}
		i++;
	}
}

void	calc_sprites()
{

}

void	draw_srpites(double *zBuffer)
{
	int	i;

	i = 0;
	sort_sprites();
	while (i < sprites->count)
	{
		sprites->spriteX = sprites->x[i] - data->posX;
		sprites->spriteY = sprites->y[i] - data->posY;
		sprites->invDet = 1.0 / (data->planeX * data->dirY - data->dirX * data->planeY);
		sprites->transformX = sprites->invDet * (data->dirY * sprites->spriteX - data->dirX * sprites->spriteY);
		sprites->transformY = sprites->invDet * (-data->planeY * sprites->spriteX + data->planeX * sprites->spriteY);
		sprites->spriteScreenX = (int)((config->s_width / 2) * (1 + sprites->transformX / sprites->transformY));
		sprites->spriteHeight = abs((int)(config->s_height / (sprites->transformY)));
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
		for (int stripe = sprites->drawStartX; stripe < sprites->drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-sprites->spriteWidth / 2 + sprites->spriteScreenX)) * texWidth / sprites->spriteWidth) / 256;
			if (sprites->transformY > 0 && stripe > 0 && stripe < config->s_width && sprites->transformY < zBuffer[stripe])
				for (int y = sprites->drawStartY; y < sprites->drawEndY; y++)
				{
					int d = (y) * 256 - config->s_height * 128 + sprites->spriteHeight * 128;
					int texY = ((d * texHeight) / sprites->spriteHeight) / 256;
					int color_sprite = texture_sprite->address[texWidth * texY + texX];
					if (color_sprite != 0)
						my_mlx_pixel_put(data, stripe, y, color_sprite);
				}
		}
		i++;
	}
}
