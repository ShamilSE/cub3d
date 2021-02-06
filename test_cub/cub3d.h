#ifndef CUB3D_H
# define CUB3D_H

#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480
#define numSprites 19

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

t_data *data;
t_texture *texture;

#endif