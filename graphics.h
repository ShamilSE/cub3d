//
// Created by Shamil on 06.01.2021.
//

#ifndef CUB3D_GRAPHICS_H
# define CUB3D_GRAPHICS_H

typedef struct	s_data {
	void		*image;
	void		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

# endif //CUB3D_GRAPHICS_H
