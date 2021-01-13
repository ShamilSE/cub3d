#include "headers/graphics.h"

size_t	count_map_strings(char *str)
{
	int		fd;
	size_t	map_length;
	char	*line;

	map_length = 1;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		map_length++;
	return (map_length);
}

char	**parse_map(char *str, t_player *player)
{
	char	**map;
	int		i;
	int		fd;
	char	*line;

	fd =  open(str, O_RDONLY);
	i = 0;
	map = malloc(sizeof(char *) * (count_map_strings(str) + 1));
	while (get_next_line(fd, &line) > 0)
	{
		map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	map[i] = ft_strdup(line);
	free(line);
	map[i + 1] = 0x0;
	return (map);
}

int	key_press(int keycode, t_all *all)
{
	my_mlx_pixel_put(all->data, (int)all->player->x, (int)all->player->y, 0);
	ft_printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit(0);
	else if (keycode == 13)
		move_forward(all->player);
	else if (keycode == 1)
		move_backward(all->player);
	else if (keycode == 0)
		move_left(all->player);
	else if (keycode == 2)
		move_right(all->player);
	my_mlx_pixel_put(all->data, (int)all->player->x, (int)all->player->y, 0xFFFFFF);
	mlx_put_image_to_window(all->data->mlx, all->data->window, all->data->image, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_data		data;
	t_all		*all;
	t_player	player;

	all = malloc(sizeof(t_all));
	if (argc == 2)
		all->map = parse_map(argv[1], &player);
	else
	{
		ft_printf("you need to put map as second argument\n");
		exit(1);
	}
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 500, 500, "Shamil");
	data.image = mlx_new_image(data.mlx, 500, 500);
	data.address = mlx_get_data_addr(data.image, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_put_image_to_window(data.mlx, data.window, data.image, 0, 0);
	player.x = 10;
	player.y = 10;
	all->data = &data;
	all->player = &player;
	draw_map(all);
	mlx_hook(data.window, 2, (1L<<0), &key_press, all);
	mlx_loop(data.mlx);
}