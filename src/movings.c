#include "cub3d.h"

void	turn_right()
{
	double oldDirX = data->dirX;
	data->dirX = data->dirX * cos(-data->rotSpeed) - data->dirY * sin(-data->rotSpeed);
	data->dirY = oldDirX * sin(-data->rotSpeed) + data->dirY * cos(-data->rotSpeed);
	double oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(-data->rotSpeed) - data->planeY * sin(-data->rotSpeed);
	data->planeY = oldPlaneX * sin(-data->rotSpeed) + data->planeY * cos(-data->rotSpeed);
}

int	movings(int key)
{
	if (key == K_W)
	{
		mlx_destroy_image(data->mlx, data->image);
		if (config->map[(int)(data->posX + data->dirX * data->moveSpeed)][(int)(data->posY)] == '0')
			data->posX += data->dirX * data->moveSpeed;
		if (config->map[(int)(data->posX)][(int)(data->posY + data->dirY * data->moveSpeed)] == '0')
			data->posY += data->dirY * data->moveSpeed;
		data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	if (key == K_S)
	{
		mlx_destroy_image(data->mlx, data->image);
		if (config->map[(int)(data->posX - data->dirX * data->moveSpeed)][(int)(data->posY)] == '0')
			data->posX -= data->dirX * data->moveSpeed;
		if (config->map[(int)(data->posX)][(int)(data->posY - data->dirY * data->moveSpeed)] == '0')
			data->posY -= data->dirY * data->moveSpeed;
		data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	if (key == K_D)
	{
		mlx_destroy_image(data->mlx, data->image);
		if (config->map[(int)(data->posX + data->dirY * data->moveSpeed)][(int)(data->posY)] == '0')
			data->posX += data->dirY * data->moveSpeed;
		if (config->map[(int)(data->posX)][(int)(data->posY - data->dirX * data->moveSpeed)] == '0')
			data->posY -= data->dirX * data->moveSpeed;
		data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	if (key == K_A)
	{
		mlx_destroy_image(data->mlx, data->image);
		if (config->map[(int)(data->posX - data->dirY * data->moveSpeed)][(int)(data->posY)] == '0')
			data->posX -= data->dirY * data->moveSpeed;
		if (config->map[(int)(data->posX)][(int)(data->posY + data->dirX * data->moveSpeed)] == '0')
			data->posY += data->dirX * data->moveSpeed;
		data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	if (key == 123)
	{
		mlx_destroy_image(data->mlx, data->image);
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY * sin(data->rotSpeed);
		data->dirY = oldDirX * sin(data->rotSpeed) + data->dirY * cos(data->rotSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY * sin(data->rotSpeed);
		data->planeY = oldPlaneX * sin(data->rotSpeed) + data->planeY * cos(data->rotSpeed);
		data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	if (key == 124)
	{
		mlx_destroy_image(data->mlx, data->image);
		//both camera direction and camera plane must be rotated
		turn_right();
		data->image = mlx_new_image(data->mlx, config->s_width, config->s_height);
		data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->size, &data->endian);
		calc();
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}