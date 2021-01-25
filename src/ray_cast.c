#include "../headers/graphics.h"

void	draw_wall(int wall_start, int wall_end, int x_view, int texture_height, int ray_length)
{
//	double	step = 1.0 * texture_height / ray_length;
//	int		texture_position = (wall_start - (int)screen_height / 2 + ray_length) * (int)step;
//	int		color;
//	int x = (int)texture_position & (texture_height - 1);
//
//	step = 1.0 * texture_height / ray_length;
//	for (int y = wall_start; y < wall_end; y++)
//	{
//		texture_position += (int)step;
//		color = all->texture->colours[y];
//		my_mlx_pixel_put(all->data, x_view, wall_start--, color);
//	}

	while (wall_start < wall_end) {

		my_mlx_pixel_put(all->data, x_view, wall_start++, all->texture->colours[0]);
//		texture_position += (int)step;
	}
}

void	draw_space(float ray_length, int x_view, float start, char flag)
{
	int		wall_height;
	int		wall_start;
	int		wall_end;
	float	ca;
	int		i;
	int		texture_height;


	texture_height = 64;
	i = 0;
	ca = player->direction - start;

	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	ray_length = ray_length * cosf(ca);
	wall_height = (int)((float)screen_height * SCALE / ray_length);
	if ((float)wall_height > screen_height)
		wall_height = (int)screen_height;
	wall_start = -wall_height / 2 + (int)screen_height / 2;
	wall_end = wall_height / 2 + (int)screen_height / 2;
	if(wall_start < 0)
		wall_start = 0;
	if(wall_end >= (int)screen_height)
		wall_end = (int)screen_height - 1;
	while (i < wall_start)
		my_mlx_pixel_put(all->data, x_view, i++, 0xFFFF00);
	draw_wall(wall_start, wall_end, x_view,texture_height, ray_length);
	i = (int)screen_height - 1;
	while (i >= wall_end)
		my_mlx_pixel_put(all->data, x_view, i--, 0xFFC0CB);
}

void	ray_cast()
{
	float	x;
	float	y;
	float	start;
	float	end;
	float	ray_length;
	int		x_view;
	char	flag;

	rays_count = 500;
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
			ray_length ++;
		}
		x = player->location->x;
		y = player->location->y;
		start += PI / 3 / (float)screen_width;
		draw_space(ray_length, x_view, start, flag);
		x_view++;
	}
}