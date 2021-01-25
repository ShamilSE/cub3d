//
// Created by Mussels Ismene on 1/14/21.
//

#include "headers/graphics.h"

void	draw_wall(float ray_length, int x_view, float start, char flag)
{
	int		wall_height;
	int		wall_start;
	int		wall_end;
	float	ca;
	int		i;
	int		wall_color;

	wall_color = flag == 'S' ? 0x0000FF : 0xFF0000;
	i = 0;
	ca = player->direction - start;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	ray_length = ray_length * cosf(ca);
	wall_height = (int)((float)h * SCALE / ray_length);
	if ((float)wall_height > h)
		wall_height = (int)h;
	wall_start = -wall_height / 2 + (int)h / 2;
	wall_end = wall_height / 2 + (int)h / 2;
	if(wall_start < 0)
		wall_start = 0;
	if(wall_end >= (int)h)
		wall_end = (int)h - 1;
	while (i < wall_start)
		my_mlx_pixel_put(all->data, x_view, i++, 0xFFFF00);
	while (wall_start < wall_end)
		my_mlx_pixel_put(all->data, x_view, wall_start++, wall_color);
	i = (int)h - 1;
	while (i >= wall_end)
		my_mlx_pixel_put(all->data, x_view, i--, 0xFFC0CB);
//	ft_printf("here\n");
}

void	throw_ray()
{
	float	x;
	float	y;
	float	start;
	float	end;
	float	ray_length;
	int		x_view;
	char	flag;

	x_view = 0;
	ray_length = 0;
	start = player->direction - PI / 6;
	end = player->direction + PI / 6;
	x = player->location->x;
	y = player->location->y;
	while (start <= end)
	{
		ray_length = 0;
		while (1)
		{
			x += cosf(start);
			if (all->map[(int) (y / SCALE)][(int) (x / SCALE)] == '1')
			{
				flag = 'S';
				break ;
			}
			y += sinf(start);
			if (all->map[(int) (y / SCALE)][(int) (x / SCALE)] == '1')
			{
				flag = 'N';
				break ;
			}
//			my_mlx_pixel_put(all->data, (int)x, (int)y, 0xFF0000);
			ray_length ++;
		}
		x = player->location->x;
		y = player->location->y;
		start += PI / 3 / 1200;
		draw_wall(ray_length, x_view, start, flag);
		x_view++;
	}
}