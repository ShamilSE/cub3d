//
// Created by Mussels Ismene on 1/12/21.
//

#include "headers/graphics.h"

int	move_forward(t_player *player)
{
	player->y--;
	return 1;
}

void	move_backward(t_player *player)
{
	player->y++;
}

void	move_left(t_player *player)
{
	player->x--;
}

void	move_right(t_player *player)
{
	player->x++;
}