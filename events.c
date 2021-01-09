//
// Created by Mussels Ismene on 1/8/21.
//

#include "graphics.h"

int	events(int keycode, t_data *data)
{
	int i = 0;
	if (keycode == 53) {
		mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
	else if (keycode == 13)
	{
		printf("you pushed 'W'\n");
		my_mlx_pixel_put(data, i, i, 0x00FF0000);
	}
	else if (keycode == 0)
		printf("you pushed 'A'\n");
	else if (keycode == 1)
		printf("you pushed 'S'\n");
	else if (keycode == 2)
		printf("you pushed 'D'\n");
}