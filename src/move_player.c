#include "../headers/graphics.h"

t_config *config;
t_player *player;

void	move_forward()
{
	player->position_x += player->direction_x * player->move_speed;
	player->position_y += player->direction_y * player->move_speed;
}

void	move_backward()
{
	player->position_x -= player->direction_x * player->move_speed;
	player->position_y -= player->direction_y * player->move_speed;
}

//void	move_left()
//{
//	player->location->x += (float)sin((double)player->direction) * 5;;
//	player->location->y -= (float)cos((double)player->direction) * 5;
//}
//
//void	move_right()
//{
//
//}

void	look_left()
{
	double oldDirX = player->direction_x;
	player->direction_x = player->direction_x * cos(player->rotation_speed) - player->direction_y * sin(player->rotation_speed);
	player->direction_y = oldDirX * sin(player->rotation_speed) + player->direction_y * cos(player->rotation_speed);
	double oldPlaneX = player->plane_x;
	player->plane_x = player->plane_x * cos(player->rotation_speed) - player->plane_y * sin(player->rotation_speed);
	player->plane_y = oldPlaneX * sin(player->rotation_speed) + player->plane_y * cos(player->rotation_speed);
}

void	look_right()
{
	double oldDirX = player->direction_x;
	player->direction_x = player->direction_x * cos(-player->rotation_speed) - player->direction_y * sin(-player->rotation_speed);
	player->direction_y = oldDirX * sin(-player->rotation_speed) + player->direction_y * cos(-player->rotation_speed);
	double oldPlaneX = player->plane_x;
	player->plane_x = player->plane_x * cos(-player->rotation_speed) - player->plane_y * sin(-player->rotation_speed);
	player->plane_y = oldPlaneX * sin(-player->rotation_speed) + player->plane_y * cos(-player->rotation_speed);
}

void	move_player(int keycode)
{
//	for (int i = 0; config->map[i]; ++i)
//	{
//		printf("%s\n", config->map[i]);
//	}
	if (keycode == 13)
	{
		if ((config->map[(int)(player->position_x + player->direction_x * player->move_speed)][(int)(player->position_y)] == '1')
		|| (config->map[(int)(player->position_x)][(int)(player->position_y + player->direction_y * player->move_speed)] == '1'))
			return ;
		move_forward();
	}
	if (keycode == 1)
	{
		if (!config->map[(int)(player->position_x)][(int)(player->position_y - player->direction_y * player->move_speed)] ||
			(!config->map[(int)(player->position_x - player->direction_x * player->move_speed)][(int)(player->position_y)]))
			return ;
		move_backward();
	}
	if (keycode == 123)
		look_left();
	if (keycode == 124)
		look_right();
	printf("player->position_y: %f\n", player->position_y);
	printf("player->position_x: %f\n", player->position_x);
	puts("\n");
}