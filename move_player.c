//
// Created by Mussels Ismene on 1/12/21.
//

#include "headers/graphics.h"

int	move_forward()
{
	player->location->x += player->pdx;
	player->location->y += player->pdy;
	return 1;
}

void	move_backward()
{
	player->location->x -= player->pdx;
	player->location->y -= player->pdy;
}

void	look_left()
{
	player->direction -= 0.1f;
	player->pdx = (float)cos((double)player->direction) * 5;
	player->pdy = (float)sin((double)player->direction) * 5;
}

void	look_right()
{
	player->direction += 0.1f;
	player->pdx = (float)cos((double)player->direction) * 5;
	player->pdy = (float)sin((double)player->direction) * 5;
}

void	move_player(int keycode)
{
// w
	if (keycode == 13)
	{

		move_forward();
	}
//	s
	else if (keycode == 1)
		move_backward();
//	a
	else if (keycode == 0)
		look_left();
//	d
	else if (keycode == 2)
		look_right();
	mlx_destroy_image(all->data->mlx, all->data->image);
}