//
// Created by Shamil on 06.01.2021.
//

#ifndef CUB3D_GRAPHICS_H
# define CUB3D_GRAPHICS_H

#include <stdio.h>

typedef struct	s_data {
	void		*image;
	void		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_point {
	int			x;
	int			y;
}				t_point;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			my_mlx_line_put(t_point *start, t_point *end);

# endif //CUB3D_GRAPHICS_H
