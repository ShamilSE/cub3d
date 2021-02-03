#ifndef CUB3D_GRAPHICS_H
# define CUB3D_GRAPHICS_H

#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 32

typedef struct	s_texture
{
	void		*image;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct	s_data {
	void		*image;
	int			image_width;
	int			image_height;
	void		*window;
	void		*mlx;
	void		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_player {
	double		position_x;
	double		position_y;
	double		direction_x;
	double		direction_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rotation_speed;
}				t_player;

typedef struct	s_config {
	int			s_width;
	int			s_height;
	char		**map;
	int			floor[3];
	int			celling[3];
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
}				t_config;

void			move_player(int keycode);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			get_mlx_image();
char			**parse_map(char *filename);
void			get_texture();
void			parse_config_file(char *filename);
void			throw_error(char *error_message);
void			ray_casting();

/*
** global scope
*/
t_player		*player;
t_data			*data;
t_config		*config;
t_texture		*texture;

#endif