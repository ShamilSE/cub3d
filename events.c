//
// Created by Mussels Ismene on 1/8/21.
//

#include "graphics.h"

int	events(int keycode, t_data *data)
{
	if (keycode == 53) {
		mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
	else if (keycode == 13)
	{
		printf("you pushed 'W'\n");
	}
	else if (keycode == 0)
		printf("you pushed 'A'\n");
	else if (keycode == 1)
		printf("you pushed 'S'\n");
	else if (keycode == 2)
		printf("you pushed 'D'\n");
	else if (keycode == 12) {
		t_point x = {5, 5};
		t_point y = {10, 5};
		t_point z = {5, 10};
		t_point j = {10, 10};

		draw_square(&x, &y, &z, &j, data);
		printf("square\n");
	}
}