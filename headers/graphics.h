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


typedef struct	s_config {
	char		*filename;
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
void			get_mlx_image();
char			**parse_map(char *filename);
void			get_texture();
void			parse_config_file(char *filename);
void			throw_error(char *error_message);
void			ray_casting();

t_config *config;

#endif