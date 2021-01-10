#include "graphics.h"

void	key_press(int keycode, t_all *all)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit(0);
	mlx_pixel_put(all->data->mlx, all->data->window, 10, 10, 0x00FF0000);
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
}

int main()
{
	t_data		data;
	t_all		all;
	t_player	player;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 500, 500, "Shamil");
	data.image = mlx_new_image(data.mlx, 500, 500);
	data.address = mlx_get_data_addr(data.image, &data.bits_per_pixel, &data.line_length, &data.endian);
	all.data = &data;
	all.player = &player;
	mlx_hook(data.window, 2, (1L<<0), &key_press, &all);
	mlx_loop(data.mlx);
}