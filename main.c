#include "headers/graphics.h"

t_data			*data;
t_all			*all;
t_player		*player;

void	player_ini()
{
	player->location->x = 10;
	player->location->y = 10;
	player->direction = PI;
	player->pdx = (float)cos((double)player->direction) * 5;
	player->pdy = (float)sin((double)player->direction) * 5;
	my_mlx_pixel_put(all->data, (int)all->player->location->x, (int)all->player->location->y, 0xFFFFFF);
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
}

int	key_press(int keycode)
{
	my_mlx_pixel_put(all->data, (int)all->player->location->x, (int)all->player->location->y, 0);
	ft_printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit(0);
// w
	else if (keycode == 13) {
		mlx_destroy_image(all->data->mlx, all->data->image);
		move_forward();
	}
//	s
	else if (keycode == 1) {
		mlx_destroy_image(all->data->mlx, all->data->image);
		move_backward();
	}
//	a
	else if (keycode == 0) {
		mlx_destroy_image(all->data->mlx, all->data->image);
		look_left();
	}
//	d
	else if (keycode == 2) {
		mlx_destroy_image(all->data->mlx, all->data->image);
		move_right();
	}
	data->image = mlx_new_image(data->mlx, 1200, 800);
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
	draw_map();

	my_mlx_pixel_put(all->data, (int)all->player->location->x, (int)all->player->location->y, 0xFFFFFF);
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	data = malloc(sizeof(t_data));
	all = malloc(sizeof(t_all));
	player = malloc(sizeof(t_player));
	player_location = malloc(sizeof(t_point));
	if (argc == 2)
		all->map = parse_map(argv[1]);
	else
	{
		ft_printf("you need to put map as second argument\n");
		exit(1);
	}
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, 1200, 800, "Shamil");
	data->image = mlx_new_image(data->mlx, 1200, 800);
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	all->data = data;
	all->player = player;
	all->player->location = player_location;
	draw_map();
	player_ini();
	mlx_hook(data->window, 2, (1L<<0), &key_press, all);
	mlx_loop(data->mlx);
}