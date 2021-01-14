//
// Created by Mussels Ismene on 1/14/21.
//

#include "headers/graphics.h"

void	throw_ray()
{
	int	i;
	t_point *point;

	point = malloc(sizeof(t_point));
	i = 0;
	while (i < 10)
	{
		point->x += player->pdx;
		point->y += player->pdy;
//		my_mlx_pixel_put(all->data, (int)point->x, (int)point->y, 0xFF0000);
		i++;
	}
	free(point);
}