//
// Created by Shamil on 07.01.2021.
//

#include "graphics.h"

void	ft_cast_ray(t_all *all)
{
	t_player	ray = *all->player;

	while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
	{
		ray.x += cos(ray.direction);
		ray.y += sin(ray.direction);
//		my_mlx_pixel_put(all->mlx, all->win, ray.x, ray.y, 0x990099);
	}
}