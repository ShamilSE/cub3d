#include "headers/graphics.h"

//void	draw_block(int size) {
//	while (size)
//	{
//		my_mlx_pixel_put();
//		size--;
//	}
//}


void	draw_map(t_all *all)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	j = 0;
	x = 10;
	y = 10;
//	for (int i = 0; i < 5; i++)
//		printf("map: %s\n", all->map[i]);
	i = 0;
	while (all->map[i])
	{
		while (all->map[i][j]) {
			if (all->map[i][j] == '1') {
//				printf("j = %d\ni = %d\nx = %d\ny = %d\n\n", j, i, x, y);
				my_mlx_pixel_put(all->data, x, y, 0xFFFFFF);
			}
			j++;
			x++;
		}
		j = 0;
		x = 10;
		y++;
		i++;
	}
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
}