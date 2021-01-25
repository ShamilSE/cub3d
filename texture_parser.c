//
// Created by Shamil on 24.01.2021.
//

#include "headers/graphics.h"

void	texture_parser()
{
	int		fd;
	char	*line;
	// t_point	*texture_point;
	t_data	*data;
	int		colour;
	int		i;
	char	*texture;
	int x;
	int y;

	data = malloc(sizeof(t_data));
	// texture_point = malloc(sizeof(t_point));
	// texture_point->x = 64;
	// texture_point->y = 64;
	x = 64;
	y = 64;
	fd = open("wall_texture.xpm", O_RDONLY);
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, 100, 100, "texture");
	data->image = mlx_new_image(data->mlx, 100, 100);
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
	texture = mlx_get_data_addr(mlx_xpm_file_to_image(data->mlx, "wall_texture.xpm", &x, &y), &data->bits_per_pixel, &data->line_length, &data->endian);
	ft_printf("%s\n", texture);
	// while ((i = get_next_line(fd, &line)) > 0)
	// {
	// 	if (ft_strchr(line, '#')) {
	// 		line = ft_strchr(line, '#');
	// 		line++;
	// 		colour = atoi(line);
	// 		ft_printf("%i\n", colour);
	// 		if (texture_point->x > 64) {
	// 			texture_point->x = 0;
	// 			texture_point->y++;
	// 			if (texture_point->y == 64)
	// 				break;
	// 		}
	// 		my_mlx_pixel_put(data, texture_point->x++, texture_point->y, colour);
	// 	}
	// }
	// mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	// mlx_loop(data->mlx);
}