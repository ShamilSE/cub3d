#include "../headers/graphics.h"

void	player_ini()
{
	data->position_x = 500;
	data->position_y = 500;
	data->direction_x = -1.0;
	data->direction_y = 0;
	player->pdx = (float)cos((double)player->direction) * 5;
	player->pdy = (float)sin((double)player->direction) * 5;
	ray_cast();
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
}

int	key_press(int keycode)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
		move_player(keycode);
	get_image();
	draw_map();
	ray_cast();
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
	return (0);
}

void	mlx_main_loop()
{
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, config_info->width, config_info->height, "cub3d");
	get_image();
	get_texture();
//	draw_map();
	player_ini();
	mlx_hook(data->window, 2, (1L<<0), &key_press, all);
	mlx_loop(data->mlx);
}