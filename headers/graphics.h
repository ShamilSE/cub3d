#ifndef CUB3D_GRAPHICS_H
# define CUB3D_GRAPHICS_H

#define BUFFER_SIZE 1
#define SCALE 60
#define mapWidth 24
#define mapHeight 24

#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct	s_texture
{
	void		*image;
	int			width;
	int			height;
	int			*colours;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;


typedef struct	s_mlx {
	void		*image;
	void		*window;
	void		*mlx;
	void		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx;

typedef struct	s_data {
	double		position_x;
	double		position_y;
	double		direction_x;
	double		direction_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rotation_speed;
	t_mlx		*mlx;
}				t_data;

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

/*
* map and player drawing
*/
void			draw_map();
void			ray_casting();


void			move_player(int keycode);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			get_image();
char			**parse_map(char *filename);
void			get_texture();
void			parse_config_file(char *filename);
void			throw_error(char *error_message);

/*
* main_engine_loop
*/
void	main_engine_loop();


/*
* global variables
*/
t_data			*data;
t_mlx			*mlx;
t_config		*config;
int				rays_count;
#define PI 3.1415926f

#endif