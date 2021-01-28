#include "../headers/graphics.h"

t_data	*data;
t_mlx	*mlx;

void	init()
{
	data = malloc(sizeof(t_data));
	mlx = malloc(sizeof(t_mlx));
}

int		main(int argc, char **argv)
{
	init();
	if (argc == 2)
		parse_config_file(argv[1]);
	else
		throw_error("you need to put map as second argument\n");
	mlx_main_loop();
}