#include "../headers/graphics.h"

t_data			*data;
t_all			*all;
t_player		*player;

void	init_structures()
{
	data = malloc(sizeof(t_data));
	all = malloc(sizeof(t_all));
	player = malloc(sizeof(t_player));
	player_location = malloc(sizeof(t_point));
}

int main(int argc, char **argv)
{
	screen_height = 800;
	screen_width = 1200;
	init_structures();
	if (argc == 2)
		all->map = parse_config_file(argv[1]);
	else
	{
		ft_printf("you need to put map as second argument\n");
		exit(1);
	}
	mlx_main_loop();
}