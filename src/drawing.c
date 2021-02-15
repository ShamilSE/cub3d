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

void	draw_walls(int lineHeight, int texX, int x)
{
	int		y;
	double	step;
	double	texPos;

	step = 1.0 * texHeight / lineHeight;
	texPos = (t_calc->draw_start - config->s_height / 2 + lineHeight / 2) * step;
	y = 0;
	while (y < config->s_height)
	{
		if (y >= t_calc->draw_start && y <= t_calc->draw_end)
		{
			int text_y = (int)texPos & (texHeight - 1);
			int color;
			if (t_calc->side == 0)
			{
				if (t_calc->stepX > 0)
					color = texture_south->address[texHeight * text_y + texX];
				else
					color = texture_north->address[texHeight * text_y + texX];
			}
			else
			{
				if (t_calc->stepY > 0)
					color = texture_west->address[texHeight * text_y + texX];
				else
					color = texture_east->address[texHeight * text_y + texX];
			}

			texPos += step;
			my_mlx_pixel_put(data, x, y, color);
		}
		y++;
	}
}

void	draw_srpites(double *zBuffer)
{
	double spriteDistance[sprites->count];
	for (int i = 0; i < sprites->count; ++i) {
		spriteDistance[i] = ((data->posX - sprites->x[i]) *
							 (data->posX - sprites->x[i]) + (data->posY - sprites->y[i]) * (data->posY - sprites->y[i]));
	}
	double	dist_tmp;
	double	x_tmp;
	double	y_tmp;
	for (int i = 0; i < sprites->count; ++i)
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
	}
	for(int i = 0; i < sprites->count; i++)
	{
		double spriteX = sprites->x[i] - data->posX;
		double spriteY = sprites->y[i] - data->posY;
		double invDet = 1.0 / (data->planeX * data->dirY - data->dirX * data->planeY);
		double transformX = invDet * (data->dirY * spriteX - data->dirX * spriteY);
		double transformY = invDet * (-data->planeY * spriteX + data->planeX * spriteY);
		int spriteScreenX = (int)((config->s_width / 2) * (1 + transformX / transformY));
		int spriteHeight = abs((int)(config->s_height / (transformY)));
		int drawStartY = -spriteHeight / 2 + config->s_height / 2;
		if (drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + config->s_height / 2;
		if (drawEndY >= config->s_height) drawEndY = config->s_height - 1;
		int spriteWidth = abs((int)(config->s_height / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= config->s_width) drawEndX = config->s_width - 1;
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < config->s_width && transformY < zBuffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++)
				{
					int d = (y) * 256 - config->s_height * 128 + spriteHeight * 128;
					int texY = ((d * texHeight) / spriteHeight) / 256;
					int color_sprite = texture_sprite->address[texWidth * texY + texX];
					if (color_sprite != 0)
						my_mlx_pixel_put(data, stripe, y, color_sprite);
				}
		}
	}
}
