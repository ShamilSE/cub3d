//
// Created by Mussels Ismene on 1/8/21.
//

#include "graphics.h"

void	ft_print_hello()
{
	printf("hello\n");
}

void	hooks()
{
	t_data	vars;

	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, 1920, 1080, "hook");
	mlx_key_hook(vars.window, ft_print_hello, &vars);
	mlx_loop(vars.mlx);
}