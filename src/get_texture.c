#include "../headers/graphics.h"

void	get_texture()
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	texture->image = mlx_xpm_file_to_image(data->mlx, "/Users/shamil/Desktop/CLionProjects/cub3d/textures/wood.xpm", &texture->width, &texture->height);
	texture->colours = (int *)mlx_get_data_addr(texture->image, &texture->bpp, &texture->size_line, &texture->endian);
	all->texture = texture;
}