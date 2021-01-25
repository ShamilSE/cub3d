#include "../headers/graphics.h"

void	get_image()
{
	data->image = mlx_new_image(data->mlx, 1200, 800);
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void	player_ini()
{
	player->location->x = 500;
	player->location->y = 500;
	player->direction = PI / 3;
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
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, 1200, 800, "Shamil");
	get_image();
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	all->data = data;
	all->player = player;
	all->player->location = player_location;
	get_texture();
	draw_map();
	player_ini();
	mlx_hook(data->window, 2, (1L<<0), &key_press, all);
	mlx_loop(data->mlx);
}