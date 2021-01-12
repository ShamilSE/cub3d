//
// Created by Mussels Ismene on 1/7/21.
//

#include "headers/graphics.h"

void	my_mlx_line_put(t_point *start, t_point *end, t_data *data)
{
	int	x;
	int	y;
	if (start->x > end->x)
	{
		x = start->x;
		while (x-- > end->x)
			my_mlx_pixel_put(data, x, start->y, 0x00FF0000);
	}
	else
	{
		x = end->x;
		while (x-- > start->x)
			my_mlx_pixel_put(data, x, start->y, 0x00FF0000);
	}
	if (start->y > end->y)
	{
		y = start->y;
		while (y-- > end->y)
			my_mlx_pixel_put(data, x, y, 0x00FF0000);
	}
	else
	{
		y = end->y;
		while (y-- > start->y)
			my_mlx_pixel_put(data, x, y, 0x00FF0000);
	}
}