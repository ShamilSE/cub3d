//
// Created by Shamil on 07.01.2021.
//

#include "headers/graphics.h"

void	ft_cast_ray()
{
	t_player	ray = *all->player;

	while (all->map[(int)(ray.pdy / SCALE)][(int)(ray.pdx / SCALE)] != '1')
	{
		ray.pdx += (float)cos((double)ray.direction);
		ray.pdy += (float)sin((double)ray.direction);
		my_mlx_pixel_put(all->data, (int)ray.pdx, (int)ray.pdy, 0x000000);
	}
}