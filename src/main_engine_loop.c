#include "../headers/graphics.h"

void	get_image()
{
	mlx->image = mlx_new_image(mlx->mlx, config_info->width, config_info->height);
	mlx->address = mlx_get_data_addr(mlx->image, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

void	player_ini()
{
	data->position_x = 500;
	data->position_y = 500;
	data->direction_x = -1.0;
	data->direction_y = 0;
}

int	key_press(int keycode)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
		move_player(keycode);
	get_image();
	draw_map();
	ray_casting();
	return (0);
}

void	main_engine_loop()
{
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, config_info->width, config_info->height, "cub3d");
	get_image();
	get_texture();
	draw_map();
	player_ini();
	mlx_hook(mlx->window, 2, (1L<<0), &key_press, data);
	mlx_loop(mlx->mlx);
}


