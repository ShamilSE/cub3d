#include "minilibx_opengl_20191021/mlx.h"
#include "graphics.h"

int main()
{
	void	*mlx;
	void	*window;
	t_data	img;

	mlx = mlx_init();
	img.image = mlx_new_image(mlx, 1920, 1080);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.line_length, &img.endian);
	window = mlx_new_window(mlx, 1920, 1080, "Shamil");
	my_mlx_pixel_put(&img, 5, 5, 0x00FFFFFF);
	mlx_put_image_to_window(mlx, window, img.image, 0, 0);
	mlx_loop(mlx);
}