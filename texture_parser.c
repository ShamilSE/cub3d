#include "headers/graphics.h"

void	*texture_parser()
{
	t_image	*texture;
	int		image_width;
	int		image_height;

	texture = malloc(sizeof(t_image));
	texture->image = mlx_xpm_file_to_image(data->image, "wall_texture.xpm", &image_width, &image_height);
}