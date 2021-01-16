//
// Created by Mussels Ismene on 1/14/21.
//

#include "headers/graphics.h"

void	throw_ray()
{
	int		i;
	float	x;
	float	y;
	float	start;
	float	end;

	start = player->direction - PI / 4;
	end = player->direction + PI / 4;
	x = player->location->x;
	y = player->location->y;
	i = 0;
	while (start <= end)
	{
		while (all->map[(int) (y / SCALE)][(int) (x / SCALE)] != '1')
		{
			x += cosf(start);
			y += sinf(start);
			my_mlx_pixel_put(all->data, (int)x, (int)y, 0xFF0000);
			i++;
		}
		x = player->location->x;
		y = player->location->y;
		start += PI/2 /500;
	}
}