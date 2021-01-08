//
// Created by Mussels Ismene on 1/8/21.
//

#include "graphics.h"

int	events(int keycode, t_data *data)
{
	printf("keycode is: %i\n", keycode);
	if (keycode == 53)
		mlx_destroy_window(data->mlx, data->window);
}

void	event_hook(t_data *vars)
{
	mlx_hook(vars->window, 2, 1L<<0, events, &vars);
}