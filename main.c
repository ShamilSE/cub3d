#include <stdio.h>
#include "minilibx_opengl_20191021/mlx.h"

int main()
{
	void	*mlx;
	void	*window;
	mlx = mlx_init();
	window = mlx_new_window(mlx, 1000, 1000, "Shamil");
	mlx_loop(mlx);
}
