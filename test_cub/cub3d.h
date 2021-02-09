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
#define numSprites 1

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

t_data *data;
t_texture *texture;
t_sprites	*sprites;

#endif