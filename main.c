#include "graphics.h"

t_player	*player_place(char **map)
{
	t_player	player;

	player.x = 10;
	player.y = 10;
}


void	key_press(t_all *all)
{
	mlx_pixel_put(all->data->mlx, all->data->window, 10, 10, 0x00FF0000);
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
}

int main()
{
	t_data		data;
	t_all		all;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 500, 500, "Shamil");
	all.data = &data;
	mlx_hook(data.window, 2, (1L<<0), key_press, &all);
	mlx_loop(data.mlx);
}