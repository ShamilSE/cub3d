//
// Created by Shamil on 07.01.2021.
//

#include "graphics.h"

void	ft_cast_ray(t_all *all)
{
	t_plr	ray = *all->plr; // задаем координаты луча равные координатам игрока

	while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
	{
		ray.x += cos(ray.dir);
		ray.y += sin(ray.dir);
		my_mlx_pixel_put(all->mlx, all->win, ray.x, ray.y, 0x990099);
	}
}