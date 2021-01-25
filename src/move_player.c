#include "../headers/graphics.h"

int	move_forward()
{
	player->location->x += player->pdx * 5;
	player->location->y += player->pdy * 5;
	return 1;
}

void	move_backward()
{
	player->location->x -= player->pdx * 5;
	player->location->y -= player->pdy * 5;
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
	if (keycode == 13)
	{
		if (all->map[(int)((player->location->y + (player->pdy * 5)) / SCALE)][(int)((player->location->x + (player->pdx * 5)) / SCALE)] == '1')
			return ;
		move_forward();
	}
	else
	{
		if (keycode == 1)
		{
			if (all->map[(int)((player->location->y - (player->pdy * 5)) / SCALE)][(int)((player->location->x - (player->pdx * 5)) / SCALE)] == '1')
				return ;
			move_backward();
		}
		if (keycode == 0)
			look_left();
		if (keycode == 2)
			look_right();
	}
	mlx_destroy_image(all->data->mlx, all->data->image);
}