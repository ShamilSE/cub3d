#include "../headers/graphics.h"

t_config *config;
t_data *data;

void	move_forward()
{
	data->position_x += data->direction_x * data->move_speed;
	data->position_y += data->direction_y * data->move_speed;
}

void	move_backward()
{
	data->position_x -= data->direction_x * data->move_speed;
	data->position_y -= data->direction_y * data->move_speed;
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
	double oldDirX = data->direction_x;
	data->direction_x = data->direction_x * cos(data->rotation_speed) - data->direction_y * sin(data->rotation_speed);
	data->direction_y = oldDirX * sin(data->rotation_speed) + data->direction_y * cos(data->rotation_speed);
	double oldPlaneX = data->plane_x;
	data->plane_x = data->plane_x * cos(data->rotation_speed) - data->plane_y * sin(data->rotation_speed);
	data->plane_y = oldPlaneX * sin(data->rotation_speed) + data->plane_y * cos(data->rotation_speed);
}

void	look_right()
{
	double oldDirX = data->direction_x;
	data->direction_x = data->direction_x * cos(-data->rotation_speed) - data->direction_y * sin(-data->rotation_speed);
	data->direction_y = oldDirX * sin(-data->rotation_speed) + data->direction_y * cos(-data->rotation_speed);
	double oldPlaneX = data->plane_x;
	data->plane_x = data->plane_x * cos(-data->rotation_speed) - data->plane_y * sin(-data->rotation_speed);
	data->plane_y = oldPlaneX * sin(-data->rotation_speed) + data->plane_y * cos(-data->rotation_speed);
}

void	move_player(int keycode)
{
//	for (int i = 0; config->map[i]; ++i)
//	{
//		printf("%s\n", config->map[i]);
//	}
	if (keycode == 13)
	{
		if ((config->map[(int)(data->position_x + data->direction_x * data->move_speed)][(int)(data->position_y)] == '1')
		|| (config->map[(int)(data->position_x)][(int)(data->position_y + data->direction_y * data->move_speed)] == '1'))
			return ;
		move_forward();
	}
	if (keycode == 1)
	{
		if (!config->map[(int)(data->position_x)][(int)(data->position_y - data->direction_y * data->move_speed)] ||
				(!config->map[(int)(data->position_x - data->direction_x * data->move_speed)][(int)(data->position_y)]))
			return ;
		move_backward();
	}
	if (keycode == 123)
		look_left();
	if (keycode == 124)
		look_right();
	printf("data->position_y: %f\n", data->position_y);
	printf("data->position_x: %f\n", data->position_x);
	puts("\n");
}