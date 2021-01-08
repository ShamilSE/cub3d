//
// Created by Mussels Ismene on 1/8/21.
//

#include "graphics.h"

int	events(int keycode, t_data *data)
{
	printf("keycode is: %i\n", keycode);
	if (keycode == 53)
		exit(0);
	else if (keycode == 1)
		printf("keycode is 1\n");
}

void	event_hook(t_data *vars)
{
	mlx_hook(vars->window, 2, 1L<<0, events, &vars);
}