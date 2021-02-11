#ifndef CUB3D_H
# define CUB3D_H

#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define texWidth 64
#define texHeight 64

typedef struct	s_data
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	void	*image;
	char	*addr;
	int		bpp;
	int		endian;
	int		size;
	double	moveSpeed;
	double	rotSpeed;
	int		*colours;
	int		i_width;
	int		i_height;
}				t_data;

typedef struct	s_texture
{
	void		*image;
	int			*address;
	int			bpp;
	int			size;
	int			endian;
}				t_texture;

typedef struct	s_sprites
{
	int			*x;
	int			*y;
	int			count;
}				t_sprites;

typedef struct	s_bpm
{
	char			file_type[2];
	unsigned int	file_size;
	unsigned int	reserved_bytes;
	unsigned int	data_offset;
	unsigned int	second_header_size;
	unsigned int	img_width;
	unsigned int	img_height;
	short			planes;
	short			bpp;
	unsigned int	compression;
	unsigned int	img_size;
	unsigned int	x_pixels_per_meter;
	unsigned int	y_pixels_per_meter;
	unsigned int	total_colors;
	unsigned int	important_colors;
}				t_bmp;

t_data		*data;
t_texture	*texture;
t_sprites	*sprites;
t_bmp		*bmp;
int			draw_start;
int			draw_end;
int			side;
int			stepX;
int			stepY;

#endif