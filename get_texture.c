#include "headers/graphics.h"

void	get_texture()
{
	t_texture	*texture;
	int i = 0;
	int x = 0;
	int y = 0;

	texture = malloc(sizeof(t_texture));
	texture->image = mlx_xpm_file_to_image(data->mlx, "/Users/mismene/Desktop/CLionProjects/cub3d/textures/wood.xpm", &texture->width, &texture->height);
	texture->colours = (int *)mlx_get_data_addr(texture->image, &texture->bpp, &texture->size_line, &texture->endian);
//	ft_printf("%i\n", texture->colours[0]);
//	while (texture->colours[i]) {
//		my_mlx_pixel_put(all->data, x, y, texture->colours[i++]);
//		if (x == 63) {
//			x = 0;
//			y++;
//			if (y == 63)
//				break ;
//		}
//		x++;
//	}
	all->texture = texture;
}