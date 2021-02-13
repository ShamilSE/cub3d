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
	int			floor[4];
	int			celling[4];
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	char		player;
	unsigned int	map_strings;
}				t_config;

char			**parse_map(char *filename);
void			parse_config_file(char *filename);
void			throw_error(char *error_message);
size_t			count_map_strings(char *str);
void			screenshot();
int				movings(int key);
void			calc();
void			turn_right();

t_config *config;

#endif