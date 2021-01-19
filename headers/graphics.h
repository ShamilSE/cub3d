//
// Created by Shamil on 06.01.2021.
//

#ifndef CUB3D_GRAPHICS_H
# define CUB3D_GRAPHICS_H

#define BUFFER_SIZE 1
#define SCALE 100

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
	float		x;
	float		y;
}				t_point;

typedef struct	s_player {
	float		direction;
	float		pdx;
	float		pdy;
	t_point		*location;
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
void	move_player(int keycode);
/*
 * map and player drawing
 */
void			draw_map();
void			draw_block(int size, t_point *point, int color);
char			**parse_map(char *str);
void			throw_ray();

/*
 * rerender image
 */
void	get_image();

/*
 * global variables
 */
t_data			*data;
t_all			*all;
t_player		*player;
t_point			*player_location;
int				rays_count;
int				h;
#define PI 3.1415926f

# endif //CUB3D_GRAPHICS_H
