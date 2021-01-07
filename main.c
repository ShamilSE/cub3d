#include "mlx/mlx.h"
#include "graphics.h"

int main()
{
	void	*mlx;
	void	*window;
	t_data	img;
	t_point	start;
	t_point	end;

	start.x = 5;
	start.y = 5;
	end.x = 10;
	end.y = 10;

	mlx = mlx_init();
	img.image = mlx_new_image(mlx, 1920, 1080);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.line_length, &img.endian);
	window = mlx_new_window(mlx, 1920, 1080, "Shamil");
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 10, 10, 0x00FF0000);
	my_mlx_line_put(&start, &end);
	mlx_put_image_to_window(mlx, window, img.image, 0, 0);
	mlx_loop(mlx);
}