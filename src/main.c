#include "../headers/graphics.h"

t_data			*data;
t_player		*player;
t_config		*config;
t_texture		*texture;

void	get_mlx_image()
{
	data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void	key_hook(int keycode)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 1 || keycode == 0 || keycode == 13 || keycode == 2 || keycode == 123 || keycode == 124)
		move_player(keycode);
	ray_casting();
}

void	mlx_initialization()
{
	data = malloc(sizeof(t_data));
	texture = malloc(sizeof(t_texture));
	data->mlx = mlx_init(data->window);
	data->window = mlx_new_window(data->mlx, 100, 100, "mlx");
}

void	player_initialization()
{
	player = malloc(sizeof(t_player));
	player->position_x = 22.0;
	player->position_y = 11.5;
	player->direction_x= -1.0;
	player->direction_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
	player->move_speed = 0.3;
	player->rotation_speed = 0.3;
}

void	get_texture(char *filename)
{
	texture->colours = (int *)mlx_get_data_addr(mlx_xpm_file_to_image
			(data->mlx, filename, &data->image_width, &data->image_height),
												&data->bits_per_pixel, &data->line_length, &data->endian);
}

void	texture_to_structure()
{

}

int		main(int argc, char **argv)
{
	parse_config_file(argv[1]);
	player_initialization();
	mlx_initialization();
	get_mlx_image();
	get_texture("/Users/shamil/Desktop/CLionProjects/cub3d/src/wood.xpm");
	mlx_hook(data->window, 2, (1L << 02), (int (*)()) key_hook, &player);
	mlx_loop(data->mlx);
}
