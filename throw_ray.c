//
// Created by Mussels Ismene on 1/14/21.
//

#include "headers/graphics.h"

void	throw_ray()
{
	int		i;
	float	x;
	float	y;

	x = player->location->x;
	y = player->location->y;
	i = 0;
	while (i < 10)
	{
		x += player->pdx;
		y += player->pdy;
		my_mlx_pixel_put(all->data, (int)x, (int)y, 0xFF0000);
		i++;
	}
}