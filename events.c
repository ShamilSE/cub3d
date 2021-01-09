//
// Created by Mussels Ismene on 1/8/21.
//

#include "graphics.h"

int	events(int keycode, t_data *data)
{
//	printf("keycode %d\n", keycode);
	if (keycode == 53) {
		mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
	else if (keycode == 13)
	{
		printf("you pushed 'W'\n");
		return 1;
	}
	else if (keycode == 0)
		printf("you pushed 'A'\n");
	else if (keycode == 1)
		printf("you pushed 'S'\n");
	else if (keycode == 2)
		printf("you pushed 'D'\n");
	else
		return 0;
}