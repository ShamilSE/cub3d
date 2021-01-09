#include "graphics.h"

void	render_next_frame(t_data *img)
{
	mlx_hook(img->window, 2, 1L<<0, events, img);
}

int main()
{
	t_data		img;
	t_player	player;
//определяю игрока
	player.x = 10;
	player.y = 10;
//инициализация mlx
	img.mlx = mlx_init();
	img.image = mlx_new_image(img.mlx, 500, 500);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.window = mlx_new_window(img.mlx, 500, 500, "Shamil");
//	рисую точку
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
//	кладу image в window
	mlx_put_image_to_window(img.mlx, img.window, img.image, 0, 0);
//	зацикливаю
	mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_loop(img.mlx);
}