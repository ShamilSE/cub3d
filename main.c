#include "graphics.h"

int main()
{
	t_data	img;

	img.mlx = mlx_init();
	img.image = mlx_new_image(img.mlx, 1920, 1080);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.window = mlx_new_window(img.mlx, 1920, 1080, "Shamil");
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 100, 100, 0x00FF0000);
	mlx_put_image_to_window(img.mlx, img.window, img.image, 0, 0);
	event_hook(&img);
	mlx_loop(img.mlx);
}