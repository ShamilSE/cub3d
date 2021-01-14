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

void	move_right()
{
	player->direction += 0.1f;
	player->pdx = (float)cos((double)player->direction) * 5;
	player->pdy = (float)sin((double)player->direction) * 5;
}