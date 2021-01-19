#include "headers/graphics.h"

void	draw_block(int size, t_point *point, int color) {
	float	size_reminder;
	float	size_reminder2;
	float	x_reminder;
	float	y_reminder;

	size_reminder2 = size;
	y_reminder = point->y;
	size_reminder = size;
	x_reminder = point->x;
	while (size > 0)
	{
		while (size_reminder > 0)
		{
//			my_mlx_pixel_put(all->data, point->x, point->y, color);
			point->x++;
			size_reminder--;
		}
		size_reminder = size_reminder2;
		point->x = x_reminder;
		size--;
		point->y++;
	}
	point->x += size_reminder2;
	point->y = y_reminder;
}

void	draw_map()
{
	int		i;
	int		j;
	t_point	point;
	int		size;

	point.x = 10;
	point.y = 10;
	size = 80;
	i = 0;
	j = 0;
	while (all->map[i])
	{
		while (all->map[i][j]) {
			if (all->map[i][j] == '1') {
				draw_block(size, &point, 0x800080);
			} else if (all->map[i][j] == '0') {
				draw_block(size, &point, 0xFFFFFF);
			}
			j++;
		}
		j = 0;
		point.y += size;
		point.x = 10;
		i++;
	}
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
}