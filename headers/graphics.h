//
// Created by Shamil on 06.01.2021.
//

#ifndef CUB3D_GRAPHICS_H
# define CUB3D_GRAPHICS_H

#define BUFFER_SIZE 1

#define SCALE 16
#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct	s_data {
	void		*image;
	void		*window;
	void		*mlx;
	void		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_point {
	int			x;
	int			y;
}				t_point;

typedef struct	s_player {
	float		x;
	float		y;
	float		direction;
	float		start;
	float		end;
}				t_player;

typedef struct	s_all {
	t_data		*data;
	t_player	*player;
	char		**map;
}				t_all;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			my_mlx_line_put(t_point *start, t_point *end, t_data *data);

/*
 * moving
 */
int				move_forward(t_player *player);
void			move_backward(t_player *player);
void			move_left(t_player *player);
void			move_right(t_player *player);
/*
 * map
 */
void			draw_map(t_all *all);
char			**parse_map(char *str);

# endif //CUB3D_GRAPHICS_H
