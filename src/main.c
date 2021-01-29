#include "../headers/graphics.h"

<<<<<<< HEAD
t_data			*data;
t_mlx			*mlx;


void	key_hook(int keycode)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 1 || keycode == 0 || keycode == 13 || keycode == 2)
		move_player(keycode);
}

void	mlx_initialization()
{
	mlx = malloc(sizeof(t_mlx));
	data->mlx = mlx;
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, 720, 480, "mlx");
	mlx_hook(mlx->window, 2,(1L << 02), key_hook, &data);
}

void	player_initialization()
{
	data = malloc(sizeof(t_data));
	data->position_x = 22.0;
	data->position_y = 11.5;
	data->direction_x= -1.0;
	data->direction_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.66;
}

int		main(int argc, char **argv)
{
	parse_config_file(argv[1]);
	player_initialization();
	mlx_initialization();
	for (int x = 0; config->map[x]; ++x)
	{
		printf("%s\n", config->map[x]);
	}
	mlx_loop(mlx->mlx);
=======
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
>>>>>>> f946e95b166abcb49454c5dd6231930b98c61352
}