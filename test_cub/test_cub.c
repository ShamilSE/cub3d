#include "../headers//mlx.h"
#include "../headers/graphics.h"
#include "cub3d.h"

t_data *data;
t_texture *texture_north;
t_texture *texture_south;
t_texture *texture_west;
t_texture *texture_east;
t_texture *texture_sprite;

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (str1 == NULL || str2 == NULL)
		return (1);
	while (*(str1 + i) && *(str1 + i) == *(str2 + i) && i < n - 1)
		i++;
	if (n)
		return (*(str1 + i) - *(str2 + i));
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

void	draw_celling(int x_view)
{
	int		i;

	i = 0;
	while (i < draw_start)
	{
		my_mlx_pixel_put(data, x_view, i, create_rgb(config->celling[0], config->celling[1], config->celling[2]));
		i++;
	}
}

void	draw_floor(int x_view)
{
	int		i;

	i = draw_end;
	while (i < config->s_height)
	{
		my_mlx_pixel_put(data, x_view, i, create_rgb(config->floor[0], config->floor[1], config->floor[2]));
		i++;
	}
}

void	draw_walls(int lineHeight, int texX, int x)
{
	int	y;
	// How much to increase the texture coordinate perscreen pixel
	double step = 1.0 * texHeight / lineHeight;
	// Starting texture coordinate
	double texPos = (draw_start - config->s_height / 2 + lineHeight / 2) * step;
	y = 0;

	while (y < config->s_height)
	{
		if (y >= draw_start && y <= draw_end)
		{
			int text_y = (int)texPos & (texHeight - 1);
			int color;

			if (side == 0)
			{
				if (stepX > 0)
					color = texture_south->address[texHeight * text_y + texX];
				else
					color = texture_north->address[texHeight * text_y + texX];
			}
			else
			{
				if (stepY > 0)
					color = texture_west->address[texHeight * text_y + texX];
				else
					color = texture_east->address[texHeight * text_y + texX];
			}

			texPos += step;
			my_mlx_pixel_put(data, x, y, color);
		}
		y++;
	}
}

void	draw_srpites(double *zBuffer)
{
	double spriteDistance[sprites->count];
	for (int i = 0; i < sprites->count; ++i) {
		spriteDistance[i] = ((data->posX - sprites->x[i]) * (data->posX - sprites->x[i]) + (data->posY - sprites->y[i]) * (data->posY - sprites->y[i]));
	}
		double	dist_tmp;
		double	x_tmp;
		double	y_tmp;
	for (int i = 0; i < sprites->count; ++i)
	{

		if (spriteDistance[i] < spriteDistance[i + 1])
		{
			dist_tmp = spriteDistance[i];
			x_tmp = sprites->x[i];
			y_tmp = sprites->y[i];
			spriteDistance[i] = spriteDistance[i + 1];
			spriteDistance[i + 1] = dist_tmp;
			sprites->x[i] = sprites->x[i + 1];
			sprites->y[i] = sprites->y[i + 1];
			sprites->x[i + 1] = x_tmp;
			sprites->y[i + 1] = y_tmp;
			i = -1;
		}
	}
	for(int i = 0; i < sprites->count; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = sprites->x[i] - data->posX;
		double spriteY = sprites->y[i] - data->posY;

		double invDet = 1.0 / (data->planeX * data->dirY - data->dirX * data->planeY); //required for correct matrix multiplication

		double transformX = invDet * (data->dirY * spriteX - data->dirX * spriteY);
		double transformY = invDet * (-data->planeY * spriteX + data->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((config->s_width / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(config->s_height / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + config->s_height / 2;
		if (drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + config->s_height / 2;
		if (drawEndY >= config->s_height) drawEndY = config->s_height - 1;
		//calculate width of the sprite
		int spriteWidth = abs((int)(config->s_height / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= config->s_width) drawEndX = config->s_width - 1;
		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < config->s_width && transformY < zBuffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - config->s_height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * texHeight) / spriteHeight) / 256;
					int color_sprite = texture_sprite->address[texWidth * texY + texX]; //get current color from the texture
					if (color_sprite != 0)
						my_mlx_pixel_put(data, stripe, y, color_sprite); //paint pixel if it isn't black, black is the invisible color
				}
		}
	}
}

void	calc()
{
	data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
	data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
	double zBuffer[config->s_width];
	int	x;

	x = 0;
	while (x < config->s_width)
	{
		double cameraX = 2 * x / (double)config->s_width - 1;
		double rayDirX = data->dirX + data->planeX * cameraX;
		double rayDirY = data->dirY + data->planeY * cameraX;
		int mapX = (int)data->posX;
		int mapY = (int)data->posY;
		double sideDistX;
		double sideDistY;
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;
		int hit = 0;
		/*
		** if ray direction < 0 - sideDistX (length from current player position to first x-crossing) will be the ray to left side
		** else from current to right
		*/
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
		}
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (config->map[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - data->posX + (double)(1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - data->posY + (double)(1 - stepY) / 2) / rayDirY;
		zBuffer[x] = perpWallDist;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(config->s_height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		draw_start = -lineHeight / 2 + config->s_height / 2;
		if(draw_start < 0)
			draw_start = 0;
		draw_end = lineHeight / 2 + config->s_height / 2;
		if(draw_end >= config->s_height)
			draw_end = config->s_height - 1;

		// texturing calculations

		// calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = data->posY + perpWallDist * rayDirY;
		else
			wallX = data->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		draw_celling(x);
		draw_floor(x);
		draw_walls(lineHeight,texX, x);
		x++;
	}
	draw_srpites(zBuffer);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

void	get_textures()
{
	int g_width;
	int g_height;

	texture_north = malloc(sizeof(t_texture));
	texture_south = malloc(sizeof(t_texture));
	texture_west = malloc(sizeof(t_texture));
	texture_east = malloc(sizeof(t_texture));
	texture_sprite = malloc(sizeof(t_texture));
	if (!(texture_north->image = mlx_xpm_file_to_image(data->mlx, config->north, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_south->image = mlx_xpm_file_to_image(data->mlx, config->south, &g_width, &g_height)))
		throw_error("invalid texture path");;
	if (!(texture_west->image = mlx_xpm_file_to_image(data->mlx, config->west, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_east->image = mlx_xpm_file_to_image(data->mlx, config->east, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_sprite->image = mlx_xpm_file_to_image(data->mlx, config->sprite, &g_width, &g_height)))
		throw_error("invalid sprite path");
	texture_north->address = (int *)mlx_get_data_addr(texture_north->image, &texture_north->bpp, &texture_north->size, &texture_north->endian);
	texture_south->address = (int *)mlx_get_data_addr(texture_south->image, &texture_south->bpp, &texture_south->size, &texture_south->endian);
	texture_west->address = (int *)mlx_get_data_addr(texture_west->image, &texture_west->bpp, &texture_west->size, &texture_west->endian);
	texture_east->address = (int *)mlx_get_data_addr(texture_east->image, &texture_east->bpp, &texture_east->size, &texture_east->endian);
	texture_sprite->address = (int *)mlx_get_data_addr(texture_sprite->image, &texture_sprite->bpp, &texture_sprite->size, &texture_sprite->endian);
}

int	close_window(t_data *data)
{
	exit(0);
	return 0;
}

//void	scale_reso()
//{
//	int		mlx_size_x;
//	int		mlx_size_y;
//
//	mlx_get_screen_size(data->mlx, &mlx_size_x, &mlx_size_y);
//	config->s_width = mlx_size_x;
//	config->s_height = mlx_size_y;
//}

//void	is_screen_size_correct()
//{
//	int		mlx_size_x;
//	int		mlx_size_y;
//
//	if (config->s_width < 20 || config->s_height < 20)
//		throw_error("the window size is too small");
//	mlx_get_screen_size(data->mlx, &mlx_size_x, &mlx_size_y);
//	if (config->s_width > mlx_size_x || config->s_height > mlx_size_y)
//		scale_reso();
//}

void	spawn_direction()
{
	if (config->player == 'W')
	{
		for (int i = 0; i < 16; ++i) {
			turn_right();
		}
	} else if (config->player == 'S')
	{
		for (int i = 0; i < 32; ++i) {
			turn_right();
		}
	} else if (config->player == 'E')
	{
		for (int i = 0; i < 47; ++i) {
			turn_right();
		}
	}
}


int	main(int argc, char **argv)
{
	data = malloc(sizeof(t_data));
	sprites = malloc(sizeof(t_sprites));
	sprites->count = 0;
	if (argc < 2)
		throw_error("put second argument");
	else
		parse_config_file(argv[1]);
	if (argc > 3)
		throw_error("too many arguments");
	data->mlx = mlx_init();
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->moveSpeed = 0.1;
	data->rotSpeed = 0.1;
	spawn_direction();
	data->win = mlx_new_window(data->mlx, config->s_width, config->s_height, "mlx");
//	is_screen_size_correct();
	get_textures();
	calc();
	if (!(ft_strncmp(argv[2], "--save", 6)) && ft_strlen(argv[2]) == 6)
	{
		screenshot();
		exit(0);
	}
	else if ((ft_strncmp(argv[2], "--save", 6) || ft_strlen(argv[2]) != 6) && argc == 3)
		throw_error("unexpected second argument, need --save");
	mlx_hook(data->win, 2, 1L<<0, &movings, &data);
	mlx_hook(data->win, 17, 1L<<0, &close_window, &data);
	mlx_loop(data->mlx);
}