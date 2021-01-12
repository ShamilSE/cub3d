#include "headers/graphics.h"

void	draw_map(char **map, t_all *all)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	j = 0;
	x = 10;
	y = 10;
	while (map[i])
	{
		while (map[i][j]) {
			if (map[i][j] == '1') {
				my_mlx_pixel_put(all->data, x, y, 0xFF0000);
			}
			j++;
			x++;
		}
		y++;
		i++;
	}
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
}