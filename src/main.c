#include "../headers/graphics.h"

t_data			*data;
t_mlx			*mlx;
t_config		*config;
t_texture		*texture;

void	get_mlx_image()
{
	mlx->image = mlx_new_image(mlx->mlx, config->s_width, config->s_height);
	mlx->address = mlx_get_data_addr(mlx->image, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

void	key_hook(int keycode)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 1 || keycode == 0 || keycode == 13 || keycode == 2 || keycode == 123 || keycode == 124)
		move_player(keycode);
}

void	mlx_initialization()
{
	mlx = malloc(sizeof(t_mlx));
	texture = malloc(sizeof(t_texture));
	data->mlx = mlx;
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, 100, 100, "mlx");
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
	data->move_speed = 0.3;
	data->rotation_speed = 0.3;
}

//void	get_texture()
//{
//	texture->colours = mlx_xpm_file_to_image();
//}

int		main(int argc, char **argv)
{
	parse_config_file(argv[1]);
	player_initialization();
	mlx_initialization();
	get_mlx_image();
//	get_texture();
	mlx_hook(mlx->window, 2,(1L << 02), key_hook, &data);
	mlx_loop(mlx->mlx);
}
