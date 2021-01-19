//
// Created by Mussels Ismene on 1/14/21.
//

#include "headers/graphics.h"

void	draw_wall(float ray_length, int x_view)
{
	int		wall_height;
	int		wall_start;
	int		wall_end;

	wall_height = (int)((float)h * SCALE / ray_length);
	wall_start = -wall_height / 2 + h / 2;
	wall_end = wall_height / 2 + h / 2;
	if(wall_start < 0)
		wall_start = 0;
	if(wall_end >= h)
		wall_end = h - 1;
	while (wall_start < wall_end)
		my_mlx_pixel_put(all->data, x_view, wall_start++, 0x00FF00);
}

void	throw_ray()
{
	float	x;
	float	y;
	float	start;
	float	end;
	float	ray_length;
	int		x_view;

	x_view = 100;
	ray_length = 0;
	start = player->direction - PI / 4;
	end = player->direction + PI / 4;
	x = player->location->x;
	y = player->location->y;
	while (start <= end)
	{
		ray_length = 0;
		while (all->map[(int) (y / SCALE)][(int) (x / SCALE)] != '1')
		{
			x += cosf(start);
			y += sinf(start);
//			my_mlx_pixel_put(all->data, (int)x, (int)y, 0xFF0000);
			ray_length ++;
		}
		x = player->location->x;
		y = player->location->y;
		start += PI / 2 / (float)rays_count;
		draw_wall(ray_length, x_view);
		x_view++;
	}
}